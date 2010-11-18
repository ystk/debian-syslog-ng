#include "syslog-ng.h"
#include "messages.h"
#include "templates.h"
#include "misc.h"
#include "logpatterns.h"
#include "logparser.h"
#include "radix.h"
#include "tags.h"
#include "stats.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if HAVE_GETOPT_H
#include <getopt.h>
#endif

#include <locale.h>

#define BOOL(x) ((x) ? "TRUE" : "FALSE")

static gchar *full_colors[] =
{
  "\33[01;34m", /* blue */
  "\33[01;33m", /* yellow */
  "\33[01;32m", /* green */
  "\33[01;31m"  /* red */
};

static gchar *empty_colors[] =
{
  "", "", "", ""
};

#define COLOR_BLUE 0
#define COLOR_YELLOW 1
#define COLOR_GREEN 2
#define COLOR_RED 3

static gchar *no_color = "\33[01;0m";
static gchar **colors = empty_colors;


static gchar *patterndb_file = PATH_PATTERNDB_FILE;
static gboolean color_out = FALSE;

static gchar *merge_dir = NULL;

typedef struct _PdbToolMergeState
{
  GString *merged;
  gint version;
  gboolean in_rule;
} PdbToolMergeState;

void
pdbtool_merge_start_element(GMarkupParseContext *context, const gchar *element_name, const gchar **attribute_names,
                                        const gchar **attribute_values, gpointer user_data, GError **error)
{
  PdbToolMergeState *state = (PdbToolMergeState *) user_data;
  gchar *buff;
  gint i;

  if (g_str_equal(element_name, "patterndb"))
    {
      for (i = 0; attribute_names[i]; i++)
        {
          if (g_str_equal(attribute_names[i], "version"))
            state->version = strtol(attribute_values[i], NULL, 10);
        }
      return;
    }
  else if (g_str_equal(element_name, "rule"))
    state->in_rule = TRUE;

  if (g_str_equal(element_name, "program"))
    g_string_append(state->merged, "<ruleset");
  else if (state->version == 1 && state->in_rule && g_str_equal(element_name, "pattern"))
    g_string_append_printf(state->merged, "<patterns>\n<%s", element_name);
  else if (state->version == 1 && state->in_rule && g_str_equal(element_name, "url"))
    g_string_append_printf(state->merged, "<urls>\n<%s", element_name);
  else
    g_string_append_printf(state->merged, "<%s", element_name);

  for (i = 0; attribute_names[i]; i++)
    {
      buff = g_markup_printf_escaped(" %s='%s'", attribute_names[i], attribute_values[i]);
      g_string_append_printf(state->merged, "%s", buff);
      g_free(buff);
    }

  g_string_append(state->merged, ">");
}


void
pdbtool_merge_end_element(GMarkupParseContext *context, const gchar *element_name, gpointer user_data, GError **error)
{
  PdbToolMergeState *state = (PdbToolMergeState *) user_data;
  
  if (g_str_equal(element_name, "patterndb"))
    return;
  else if (g_str_equal(element_name, "rule"))
    state->in_rule = FALSE;

  if (g_str_equal(element_name, "program"))
    g_string_append(state->merged, "</ruleset>");
  else if (state->version == 1 && state->in_rule && g_str_equal(element_name, "pattern"))
    g_string_append_printf(state->merged, "</%s>\n</patterns>", element_name);
  else if (state->version == 1 && state->in_rule && g_str_equal(element_name, "url"))
    g_string_append_printf(state->merged, "</%s>\n</urls>", element_name);
  else
    g_string_append_printf(state->merged, "</%s>", element_name);
}

void
pdbtool_merge_text(GMarkupParseContext *context, const gchar *text, gsize text_len, gpointer user_data, GError **error)
{
  PdbToolMergeState *state = (PdbToolMergeState *) user_data;
  gchar *buff = g_markup_printf_escaped("%s", text);

  g_string_append(state->merged, buff);

  g_free(buff);
}

GMarkupParser pdbtool_merge_parser =
{
  .start_element = pdbtool_merge_start_element,
  .end_element = pdbtool_merge_end_element,
  .text = pdbtool_merge_text,
  .passthrough = NULL,
  .error = NULL
};

static gboolean
pdbtool_merge_file(const gchar *filename, GString *merged)
{
  GMarkupParseContext *parse_ctx = NULL;
  gchar *full_name = g_build_filename(merge_dir, filename, NULL);
  PdbToolMergeState state;
  GError *error = NULL;
  gboolean success = TRUE;
  gchar *buff = NULL;
  gsize buff_len;

  if (!g_file_get_contents(full_name, &buff, &buff_len, &error))
    {
      fprintf(stderr, "Error reading pattern database file; filename='%s', error='%s'\n",
            filename, error ? error->message : "Unknown error");
      success = FALSE;
      goto error;
    }

  state.version = 0;
  state.merged = merged;
  state.in_rule = FALSE;

  parse_ctx = g_markup_parse_context_new(&pdbtool_merge_parser, 0, &state, NULL);
  if (!g_markup_parse_context_parse(parse_ctx, buff, buff_len, &error))
    {
      fprintf(stderr, "Error parsing pattern database file; filename='%s', error='%s'\n",
            filename, error ? error->message : "Unknown error");
      success = FALSE;
      goto error;
    }

  if (!g_markup_parse_context_end_parse(parse_ctx, &error))
    {
      fprintf(stderr, "Error parsing pattern database file; filename='%s', error='%s'\n",
            filename, error ? error->message : "Unknown error");
      success = FALSE;
      goto error;
    }

error:
  g_free(full_name);

  if (buff)
    g_free(buff);

  if (parse_ctx)
    g_markup_parse_context_free(parse_ctx);

  return success;
}

static gint
pdbtool_merge(int argc, char *argv[])
{
  GDir *pdb_dir;
  GDate date;
  const gchar *filename;
  GError *error = NULL;
  GString *merged = NULL;
  gchar *buff;
  gboolean ok = TRUE;

  if (!merge_dir)
    {
      fprintf(stderr, "No directory is specified to merge from\n");
      return 1;
    }

  if (!patterndb_file)
    {
      fprintf(stderr, "No patterndb file is specified to merge to\n");
      return 1;
    }

  if ((pdb_dir = g_dir_open(merge_dir, 0, &error)) == NULL)
    {
      fprintf(stderr, "Error opening patterndb directory; errror='%s'\n", error ? error->message : "Unknown error");
      return 1;
    }

  merged = g_string_sized_new(4096);
  g_date_clear(&date, 1);
  g_date_set_time_t(&date, time (NULL)); 

  buff = g_markup_printf_escaped("<?xml version='1.0' encoding='UTF-8'?>\n<patterndb version='3' pub_date='%04d-%02d-%02d'>",
                                    g_date_get_year(&date), g_date_get_month(&date), g_date_get_day(&date));
  g_string_append(merged, buff);
  g_free(buff);

  while ((filename = g_dir_read_name(pdb_dir)) != NULL && ok)
    ok = pdbtool_merge_file(filename, merged);

  g_dir_close(pdb_dir);

  g_string_append(merged, "</patterndb>\n");

  if (ok)
    if (!g_file_set_contents(patterndb_file, merged->str, merged->len, &error))
      {
        fprintf(stderr, "Error storing patterndb; filename='%s', errror='%s'\n", patterndb_file, error ? error->message : "Unknown error");
        ok = FALSE;
      }

  g_string_free(merged, TRUE);

  return ok ? 0 : 1;
}

static GOptionEntry merge_options[] =
{
  { "directory", 'D', 0, G_OPTION_ARG_STRING, &merge_dir,
    "Directory from merge pattern databases", "<directory>" },
  { NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL }
};

static gchar *match_program = NULL;
static gchar *match_message = NULL;
static gboolean debug_pattern = FALSE;
static gboolean debug_pattern_parse = FALSE;

gboolean
pdbtool_match_values(NVHandle handle, const gchar *name, const gchar *value, gssize length, gpointer user_data)
{
  gint *ret = user_data;

  printf("%s=%.*s\n", name, (gint) length, value);
  if (g_str_equal(name, ".classifier.rule_id"))
    *ret = 0;
  return FALSE;
}

static gint
pdbtool_match(int argc, char *argv[])
{
  LogPatternDatabase patterndb;
  LogMessage *msg = log_msg_new_empty();
  GSList *dbg_list = NULL, *p;
  RDebugInfo *dbg_info;
  gint i = 0, pos = 0;
  gint ret = 1;
  const gchar *name;
  gssize name_len;

  if (!match_message)
    {
      fprintf(stderr, "No message is given\n");
      return ret;
    }

  memset(&patterndb, 0x0, sizeof(LogPatternDatabase));

  if (!log_pattern_database_load(&patterndb, patterndb_file))
    return ret;

  log_msg_set_value(msg, LM_V_MESSAGE, match_message, strlen(match_message));
  if (match_program && match_program[0])
    log_msg_set_value(msg, LM_V_PROGRAM, match_program, strlen(match_program));

  log_db_parser_process_lookup(&patterndb, msg, debug_pattern ? &dbg_list : NULL);

  if (debug_pattern && !debug_pattern_parse)
    {
      printf("Pattern matching part:\n");
      p = dbg_list;
      while (p)
        {
          dbg_info = p->data;

          pos += dbg_info->i;

          if (dbg_info->pnode)
            {
              name = nv_registry_get_handle_name(logmsg_registry, dbg_info->pnode->handle, &name_len);

              printf("%s@%s:%s=%.*s@%s",
                    colors[COLOR_YELLOW],
                    r_parser_type_name(dbg_info->pnode->type),
                    name_len ? name : "",
                    name_len ? dbg_info->match_len : 0,
                    name_len ? match_message + dbg_info->match_off : "",
                    no_color
                  );
            }
          else if (dbg_info->i == dbg_info->node->keylen)
            {
              printf("%s%s%s", colors[COLOR_GREEN], dbg_info->node->key, no_color);
            }
          else
            {
              printf("%s%.*s%s", colors[COLOR_RED], dbg_info->i, dbg_info->node->key, no_color);
            }

          p = p->next;
        }
      printf("%s%s%s", colors[COLOR_BLUE], match_message + pos, no_color);

      printf("\nMatching part:\n");
    }

  if (debug_pattern && debug_pattern_parse)
    printf("PDBTOOL_HEADER=i:len:key;keylen:match_off;match_len:parser_type:parser_name\n");

  pos = 0;
  while (dbg_list)
    {
      /* NOTE: if i is smaller than node->keylen than we did not match the full node
       * so matching failed on this node, we need to highlight it somehow
       */
      dbg_info = dbg_list->data;
      if (debug_pattern_parse)
        {
          if (dbg_info->pnode)
            name = nv_registry_get_handle_name(logmsg_registry, dbg_info->pnode->handle, &name_len);

          printf("PDBTOOL_DEBUG=%d:%d:%d:%d:%d:%s:%s\n",
                i++, dbg_info->i, dbg_info->node->keylen, dbg_info->match_off, dbg_info->match_len,
                dbg_info->pnode ? r_parser_type_name(dbg_info->pnode->type) : "",
                dbg_info->pnode && name_len ? name : ""
                );
        }
      else
        {
          if (dbg_info->i == dbg_info->node->keylen || dbg_info->pnode)
            printf("%s%.*s%s", dbg_info->pnode ? colors[COLOR_YELLOW] : colors[COLOR_GREEN], dbg_info->i, match_message + pos, no_color);
          else
            printf("%s%.*s%s", colors[COLOR_RED], dbg_info->i, match_message + pos, no_color);
          pos += dbg_info->i;
        }

      g_free(dbg_info);
      dbg_list = g_slist_delete_link(dbg_list, dbg_list);
    }

  if (debug_pattern && !debug_pattern_parse)
    printf("\nValues:\n");

  nv_table_foreach(msg->payload, logmsg_registry, pdbtool_match_values, &ret);

  log_pattern_database_free(&patterndb);
  log_msg_unref(msg);
  return ret;
}

static GOptionEntry match_options[] =
{
  { "program", 'P', 0, G_OPTION_ARG_STRING, &match_program,
    "Program name to match as $PROGRAM", "<program>" },
  { "message", 'M', 0, G_OPTION_ARG_STRING, &match_message,
    "Message to match as $MSG", "<message>" },
  { "debug-pattern", 'D', 0, G_OPTION_ARG_NONE, &debug_pattern,
    "Print debuging information on pattern matching", NULL },
  { "csv-out", 'C', 0, G_OPTION_ARG_NONE, &debug_pattern_parse,
    "Output debuging information in parseable format", NULL },
  { "color-out", 'c', 0, G_OPTION_ARG_NONE, &color_out,
    "Color terminal output", NULL },
  { NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL }
};

static gboolean dump_program_tree = FALSE;

void
pdbtool_walk_tree(RNode *root, gint level, gboolean program)
{
  gint i;

  for (i = 0; i < level; i++)
    printf(" ");

  if (root->parser)
    printf("@%s:%s@ ", r_parser_type_name(root->parser->type), log_msg_get_value_name(root->parser->handle, NULL));
  printf("'%s' ", root->key ? root->key : "");

  if (root->value)
    {
      if (!program)
        printf("rule_id='%s'", ((LogDBResult*)root->value)->rule_id);
      else
        printf("RULES");
    }

  printf("\n");

  for (i = 0; i < root->num_children; i++)
    pdbtool_walk_tree(root->children[i], level + 1, program);

  for (i = 0; i < root->num_pchildren; i++)
    pdbtool_walk_tree(root->pchildren[i], level + 1, program);
}

static gint
pdbtool_dump(int argc, char *argv[])
{
 LogPatternDatabase patterndb;

 memset(&patterndb, 0x0, sizeof(LogPatternDatabase));

 if (!log_pattern_database_load(&patterndb, patterndb_file))
   return 1;

 if (dump_program_tree)
   pdbtool_walk_tree(patterndb.programs, 0, TRUE);
 else if (match_program)
   {
     RNode *ruleset = r_find_node(patterndb.programs, g_strdup(match_program), g_strdup(match_program), strlen(match_program), NULL);
     if (ruleset && ruleset->value)
       pdbtool_walk_tree(((LogDBProgram *)ruleset->value)->rules, 0, FALSE);
   }

 return 0;
}

static GOptionEntry dump_options[] =
{
  { "program", 'P', 0, G_OPTION_ARG_STRING, &match_program,
    "Program name ($PROGRAM) to dump", "<program>" },
  { "program-tree", 'T', 0, G_OPTION_ARG_NONE, &dump_program_tree,
    "Dump the program ($PROGRAM) tree", NULL },
  { NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL }
};



const gchar *
pdbtool_mode(int *argc, char **argv[])
{
  gint i;
  const gchar *mode;

  for (i = 1; i < (*argc); i++)
    {
      if ((*argv)[i][0] != '-')
        {
          mode = (*argv)[i];
          memmove(&(*argv)[i], &(*argv)[i+1], ((*argc) - i) * sizeof(gchar *));
          (*argc)--;
          return mode;
        }
    }
  return NULL;
}

static GOptionEntry pdbtool_options[] =
{
  { "pdb",       'p', 0, G_OPTION_ARG_STRING, &patterndb_file,
    "Name of the patterndb file", "<patterndb_file>" },
  { NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL }
};

static struct
{
  const gchar *mode;
  const GOptionEntry *options;
  const gchar *description;
  gint (*main)(gint argc, gchar *argv[]);
} modes[] =
{
  { "match", match_options, "Match a message against the pattern database", pdbtool_match },
  { "dump", dump_options, "Dump pattern datebase tree", pdbtool_dump },
  { "merge", merge_options, "Merge pattern databases", pdbtool_merge },
  { NULL, NULL },
};

void
usage(void)
{
  gint mode;

  fprintf(stderr, "Syntax: pdbtool <command> [options]\nPossible commands are:\n");
  for (mode = 0; modes[mode].mode; mode++)
    {
      fprintf(stderr, "    %-12s %s\n", modes[mode].mode, modes[mode].description);
    }
  exit(1);
}

int
main(int argc, char *argv[])
{
  const gchar *mode_string;
  GOptionContext *ctx;
  gint mode, ret = 0;
  GError *error = NULL;

  stats_init();
  log_tags_init();
  log_msg_registry_init();
  log_db_parser_global_init();
  mode_string = pdbtool_mode(&argc, &argv);
  if (!mode_string)
    {
      usage();
    }

  ctx = NULL;
  for (mode = 0; modes[mode].mode; mode++)
    {
      if (strcmp(modes[mode].mode, mode_string) == 0)
        {
          ctx = g_option_context_new(mode_string);
          g_option_context_set_summary(ctx, modes[mode].description);
          g_option_context_add_main_entries(ctx, modes[mode].options, NULL);
          g_option_context_add_main_entries(ctx, pdbtool_options, NULL);
          msg_add_option_group(ctx);
          break;
        }
    }
  if (!ctx)
    {
      fprintf(stderr, "Unknown command\n");
      usage();
    }

  setlocale(LC_ALL, "");
  if (!g_option_context_parse(ctx, &argc, &argv, &error))
    {
      fprintf(stderr, "Error parsing command line arguments: %s\n", error ? error->message : "Invalid arguments");
      g_clear_error(&error);
      g_option_context_free(ctx);
      return 1;
    }
  g_option_context_free(ctx);

  msg_init(TRUE);

  if (color_out)
    colors = full_colors;

  ret = modes[mode].main(argc, argv);
  stats_destroy();
  log_tags_deinit();

  msg_deinit();
  return ret;
}
