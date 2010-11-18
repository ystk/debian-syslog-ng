
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "cfg-grammar.y"


#include "syslog-ng.h"
#include "cfg.h"
#include "sgroup.h"
#include "dgroup.h"
#include "center.h"
#include "filter.h"
#include "templates.h"
#include "logreader.h"
#include "logparser.h"
#include "logrewrite.h"

#if ENABLE_SSL /* BEGIN MARK: tls */
#include "tlscontext.h"
#endif         /* END MARK */

#include "affile.h"
#include "afinter.h"
#include "afsocket.h"
#include "afinet.h"
#include "afunix.h"
#include "afstreams.h"
#include "afuser.h"
#include "afprog.h"
#if ENABLE_SQL
#include "afsql.h"
#endif

#include "messages.h"

#include "syslog-names.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FIXME: the lexer allocates strings with strdup instead of g_strdup,
 * therefore there are unnecessary g_strdup/free pairs in the grammar. These
 * should be removed. */

void yyerror(char *msg);
int yylex();

LogDriver *last_driver;
LogReaderOptions *last_reader_options;
LogWriterOptions *last_writer_options;
LogTemplate *last_template;
SocketOptions *last_sock_options;
LogParser *last_parser;
FilterRE *last_re_filter;
LogRewrite *last_rewrite;
gint last_addr_family = AF_INET;
gchar *last_include_file;

#if ENABLE_SSL
TLSContext *last_tls_context;
#endif


#if ! ENABLE_IPV6
#undef AF_INET6
#define AF_INET6 0; g_assert_not_reached()

#endif

static struct _LogTemplate *
cfg_check_inline_template(GlobalConfig *cfg, const gchar *template_or_name)
{
  struct _LogTemplate *template = cfg_lookup_template(configuration, template_or_name);
  if (template == NULL)
    {
      template = log_template_new(NULL, template_or_name);
      template->def_inline = TRUE;
    }
  return template;
}

static gboolean
cfg_check_template(LogTemplate *template)
{
  GError *error = NULL;
  if (!log_template_compile(template, &error))
    {
      msg_error("Error compiling template",
                evt_tag_str("template", template->template),
                evt_tag_str("error", error->message),
                NULL);
      g_clear_error(&error);
      return FALSE;
    }
  return TRUE;
}




/* Line 189 of yacc.c  */
#line 172 "cfg-grammar.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KW_SOURCE = 258,
     KW_FILTER = 259,
     KW_PARSER = 260,
     KW_DESTINATION = 261,
     KW_LOG = 262,
     KW_OPTIONS = 263,
     KW_INCLUDE = 264,
     KW_INTERNAL = 265,
     KW_FILE = 266,
     KW_PIPE = 267,
     KW_UNIX_STREAM = 268,
     KW_UNIX_DGRAM = 269,
     KW_TCP = 270,
     KW_UDP = 271,
     KW_TCP6 = 272,
     KW_UDP6 = 273,
     KW_USERTTY = 274,
     KW_DOOR = 275,
     KW_SUN_STREAMS = 276,
     KW_PROGRAM = 277,
     KW_SQL = 278,
     KW_TYPE = 279,
     KW_COLUMNS = 280,
     KW_INDEXES = 281,
     KW_VALUES = 282,
     KW_PASSWORD = 283,
     KW_DATABASE = 284,
     KW_USERNAME = 285,
     KW_TABLE = 286,
     KW_ENCODING = 287,
     KW_DELIMITERS = 288,
     KW_QUOTES = 289,
     KW_QUOTE_PAIRS = 290,
     KW_NULL = 291,
     KW_SYSLOG = 292,
     KW_TRANSPORT = 293,
     KW_FSYNC = 294,
     KW_MARK_FREQ = 295,
     KW_STATS_FREQ = 296,
     KW_STATS_LEVEL = 297,
     KW_FLUSH_LINES = 298,
     KW_SUPPRESS = 299,
     KW_FLUSH_TIMEOUT = 300,
     KW_LOG_MSG_SIZE = 301,
     KW_FILE_TEMPLATE = 302,
     KW_PROTO_TEMPLATE = 303,
     KW_CHAIN_HOSTNAMES = 304,
     KW_NORMALIZE_HOSTNAMES = 305,
     KW_KEEP_HOSTNAME = 306,
     KW_CHECK_HOSTNAME = 307,
     KW_BAD_HOSTNAME = 308,
     KW_KEEP_TIMESTAMP = 309,
     KW_USE_DNS = 310,
     KW_USE_FQDN = 311,
     KW_DNS_CACHE = 312,
     KW_DNS_CACHE_SIZE = 313,
     KW_DNS_CACHE_EXPIRE = 314,
     KW_DNS_CACHE_EXPIRE_FAILED = 315,
     KW_DNS_CACHE_HOSTS = 316,
     KW_PERSIST_ONLY = 317,
     KW_TZ_CONVERT = 318,
     KW_TS_FORMAT = 319,
     KW_FRAC_DIGITS = 320,
     KW_LOG_FIFO_SIZE = 321,
     KW_LOG_DISK_FIFO_SIZE = 322,
     KW_LOG_FETCH_LIMIT = 323,
     KW_LOG_IW_SIZE = 324,
     KW_LOG_PREFIX = 325,
     KW_PROGRAM_OVERRIDE = 326,
     KW_HOST_OVERRIDE = 327,
     KW_THROTTLE = 328,
     KW_TLS = 329,
     KW_PEER_VERIFY = 330,
     KW_KEY_FILE = 331,
     KW_CERT_FILE = 332,
     KW_CA_DIR = 333,
     KW_CRL_DIR = 334,
     KW_TRUSTED_KEYS = 335,
     KW_TRUSTED_DN = 336,
     KW_FLAGS = 337,
     KW_PAD_SIZE = 338,
     KW_TIME_ZONE = 339,
     KW_RECV_TIME_ZONE = 340,
     KW_SEND_TIME_ZONE = 341,
     KW_LOCAL_TIME_ZONE = 342,
     KW_TIME_REOPEN = 343,
     KW_TIME_REAP = 344,
     KW_TIME_SLEEP = 345,
     KW_TMPL_ESCAPE = 346,
     KW_OPTIONAL = 347,
     KW_CREATE_DIRS = 348,
     KW_OWNER = 349,
     KW_GROUP = 350,
     KW_PERM = 351,
     KW_DIR_OWNER = 352,
     KW_DIR_GROUP = 353,
     KW_DIR_PERM = 354,
     KW_TEMPLATE = 355,
     KW_TEMPLATE_ESCAPE = 356,
     KW_FOLLOW_FREQ = 357,
     KW_OVERWRITE_IF_OLDER = 358,
     KW_DEFAULT_FACILITY = 359,
     KW_DEFAULT_LEVEL = 360,
     KW_KEEP_ALIVE = 361,
     KW_MAX_CONNECTIONS = 362,
     KW_LOCALIP = 363,
     KW_IP = 364,
     KW_LOCALPORT = 365,
     KW_PORT = 366,
     KW_DESTPORT = 367,
     KW_IP_TTL = 368,
     KW_SO_BROADCAST = 369,
     KW_IP_TOS = 370,
     KW_SO_SNDBUF = 371,
     KW_SO_RCVBUF = 372,
     KW_SO_KEEPALIVE = 373,
     KW_SPOOF_SOURCE = 374,
     KW_USE_TIME_RECVD = 375,
     KW_FACILITY = 376,
     KW_LEVEL = 377,
     KW_HOST = 378,
     KW_MATCH = 379,
     KW_MESSAGE = 380,
     KW_NETMASK = 381,
     KW_TAGS = 382,
     KW_CSV_PARSER = 383,
     KW_VALUE = 384,
     KW_DB_PARSER = 385,
     KW_REWRITE = 386,
     KW_SET = 387,
     KW_SUBST = 388,
     KW_YES = 389,
     KW_NO = 390,
     KW_GC_IDLE_THRESHOLD = 391,
     KW_GC_BUSY_THRESHOLD = 392,
     KW_COMPRESS = 393,
     KW_MAC = 394,
     KW_AUTH = 395,
     KW_ENCRYPT = 396,
     KW_IFDEF = 397,
     KW_ENDIF = 398,
     LL_DOTDOT = 399,
     LL_IDENTIFIER = 400,
     LL_NUMBER = 401,
     LL_FLOAT = 402,
     LL_STRING = 403,
     KW_OR = 404,
     KW_AND = 405,
     KW_NOT = 406
   };
#endif
/* Tokens.  */
#define KW_SOURCE 258
#define KW_FILTER 259
#define KW_PARSER 260
#define KW_DESTINATION 261
#define KW_LOG 262
#define KW_OPTIONS 263
#define KW_INCLUDE 264
#define KW_INTERNAL 265
#define KW_FILE 266
#define KW_PIPE 267
#define KW_UNIX_STREAM 268
#define KW_UNIX_DGRAM 269
#define KW_TCP 270
#define KW_UDP 271
#define KW_TCP6 272
#define KW_UDP6 273
#define KW_USERTTY 274
#define KW_DOOR 275
#define KW_SUN_STREAMS 276
#define KW_PROGRAM 277
#define KW_SQL 278
#define KW_TYPE 279
#define KW_COLUMNS 280
#define KW_INDEXES 281
#define KW_VALUES 282
#define KW_PASSWORD 283
#define KW_DATABASE 284
#define KW_USERNAME 285
#define KW_TABLE 286
#define KW_ENCODING 287
#define KW_DELIMITERS 288
#define KW_QUOTES 289
#define KW_QUOTE_PAIRS 290
#define KW_NULL 291
#define KW_SYSLOG 292
#define KW_TRANSPORT 293
#define KW_FSYNC 294
#define KW_MARK_FREQ 295
#define KW_STATS_FREQ 296
#define KW_STATS_LEVEL 297
#define KW_FLUSH_LINES 298
#define KW_SUPPRESS 299
#define KW_FLUSH_TIMEOUT 300
#define KW_LOG_MSG_SIZE 301
#define KW_FILE_TEMPLATE 302
#define KW_PROTO_TEMPLATE 303
#define KW_CHAIN_HOSTNAMES 304
#define KW_NORMALIZE_HOSTNAMES 305
#define KW_KEEP_HOSTNAME 306
#define KW_CHECK_HOSTNAME 307
#define KW_BAD_HOSTNAME 308
#define KW_KEEP_TIMESTAMP 309
#define KW_USE_DNS 310
#define KW_USE_FQDN 311
#define KW_DNS_CACHE 312
#define KW_DNS_CACHE_SIZE 313
#define KW_DNS_CACHE_EXPIRE 314
#define KW_DNS_CACHE_EXPIRE_FAILED 315
#define KW_DNS_CACHE_HOSTS 316
#define KW_PERSIST_ONLY 317
#define KW_TZ_CONVERT 318
#define KW_TS_FORMAT 319
#define KW_FRAC_DIGITS 320
#define KW_LOG_FIFO_SIZE 321
#define KW_LOG_DISK_FIFO_SIZE 322
#define KW_LOG_FETCH_LIMIT 323
#define KW_LOG_IW_SIZE 324
#define KW_LOG_PREFIX 325
#define KW_PROGRAM_OVERRIDE 326
#define KW_HOST_OVERRIDE 327
#define KW_THROTTLE 328
#define KW_TLS 329
#define KW_PEER_VERIFY 330
#define KW_KEY_FILE 331
#define KW_CERT_FILE 332
#define KW_CA_DIR 333
#define KW_CRL_DIR 334
#define KW_TRUSTED_KEYS 335
#define KW_TRUSTED_DN 336
#define KW_FLAGS 337
#define KW_PAD_SIZE 338
#define KW_TIME_ZONE 339
#define KW_RECV_TIME_ZONE 340
#define KW_SEND_TIME_ZONE 341
#define KW_LOCAL_TIME_ZONE 342
#define KW_TIME_REOPEN 343
#define KW_TIME_REAP 344
#define KW_TIME_SLEEP 345
#define KW_TMPL_ESCAPE 346
#define KW_OPTIONAL 347
#define KW_CREATE_DIRS 348
#define KW_OWNER 349
#define KW_GROUP 350
#define KW_PERM 351
#define KW_DIR_OWNER 352
#define KW_DIR_GROUP 353
#define KW_DIR_PERM 354
#define KW_TEMPLATE 355
#define KW_TEMPLATE_ESCAPE 356
#define KW_FOLLOW_FREQ 357
#define KW_OVERWRITE_IF_OLDER 358
#define KW_DEFAULT_FACILITY 359
#define KW_DEFAULT_LEVEL 360
#define KW_KEEP_ALIVE 361
#define KW_MAX_CONNECTIONS 362
#define KW_LOCALIP 363
#define KW_IP 364
#define KW_LOCALPORT 365
#define KW_PORT 366
#define KW_DESTPORT 367
#define KW_IP_TTL 368
#define KW_SO_BROADCAST 369
#define KW_IP_TOS 370
#define KW_SO_SNDBUF 371
#define KW_SO_RCVBUF 372
#define KW_SO_KEEPALIVE 373
#define KW_SPOOF_SOURCE 374
#define KW_USE_TIME_RECVD 375
#define KW_FACILITY 376
#define KW_LEVEL 377
#define KW_HOST 378
#define KW_MATCH 379
#define KW_MESSAGE 380
#define KW_NETMASK 381
#define KW_TAGS 382
#define KW_CSV_PARSER 383
#define KW_VALUE 384
#define KW_DB_PARSER 385
#define KW_REWRITE 386
#define KW_SET 387
#define KW_SUBST 388
#define KW_YES 389
#define KW_NO 390
#define KW_GC_IDLE_THRESHOLD 391
#define KW_GC_BUSY_THRESHOLD 392
#define KW_COMPRESS 393
#define KW_MAC 394
#define KW_AUTH 395
#define KW_ENCRYPT 396
#define KW_IFDEF 397
#define KW_ENDIF 398
#define LL_DOTDOT 399
#define LL_IDENTIFIER 400
#define LL_NUMBER 401
#define LL_FLOAT 402
#define LL_STRING 403
#define KW_OR 404
#define KW_AND 405
#define KW_NOT 406




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 99 "cfg-grammar.y"

        gint token;
	gint64 num;
	double fnum;
	char *cptr;
	void *ptr;
	FilterExprNode *node;



/* Line 214 of yacc.c  */
#line 521 "cfg-grammar.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 533 "cfg-grammar.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  58
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2709

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  157
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  171
/* YYNRULES -- Number of rules.  */
#define YYNRULES  476
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1167

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   406

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     155,   156,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   152,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   153,     2,   154,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,    11,    12,    15,    18,    21,
      24,    27,    30,    33,    36,    39,    44,    50,    56,    61,
      66,    72,    74,    78,    79,    84,    89,    94,    99,   104,
     107,   108,   116,   122,   123,   126,   127,   131,   132,   138,
     142,   143,   148,   153,   158,   163,   168,   173,   175,   180,
     185,   189,   190,   192,   194,   196,   198,   200,   202,   206,
     211,   216,   217,   221,   222,   226,   231,   233,   238,   243,
     244,   250,   251,   257,   258,   264,   265,   271,   272,   276,
     277,   281,   284,   285,   290,   294,   299,   303,   308,   312,
     317,   319,   321,   323,   324,   327,   330,   331,   333,   338,
     343,   348,   353,   355,   357,   358,   361,   364,   365,   367,
     368,   374,   376,   381,   386,   387,   393,   394,   397,   400,
     401,   403,   408,   413,   418,   423,   424,   430,   432,   437,
     438,   442,   444,   449,   451,   452,   456,   459,   460,   462,
     467,   469,   472,   473,   478,   483,   488,   493,   498,   503,
     508,   513,   518,   523,   528,   533,   538,   543,   548,   553,
     558,   563,   568,   573,   578,   583,   588,   591,   592,   596,
     597,   599,   601,   603,   605,   607,   609,   611,   616,   617,
     621,   624,   625,   627,   632,   637,   641,   646,   650,   655,
     659,   664,   668,   673,   677,   682,   686,   691,   696,   701,
     706,   711,   712,   716,   719,   720,   722,   727,   731,   736,
     740,   745,   749,   754,   759,   760,   766,   767,   773,   774,
     780,   781,   787,   788,   792,   793,   797,   800,   801,   803,
     805,   807,   808,   812,   815,   816,   821,   826,   831,   836,
     838,   840,   842,   844,   849,   850,   854,   857,   858,   860,
     861,   867,   872,   877,   878,   882,   885,   886,   888,   893,
     898,   903,   908,   913,   914,   920,   925,   930,   931,   935,
     940,   941,   944,   947,   948,   950,   955,   960,   965,   970,
     975,   980,   985,   990,   995,  1000,  1005,  1010,  1015,  1020,
    1025,  1030,  1032,  1035,  1036,  1041,  1046,  1051,  1056,  1061,
    1066,  1071,  1076,  1081,  1086,  1091,  1094,  1095,  1099,  1100,
    1105,  1110,  1115,  1120,  1125,  1130,  1135,  1140,  1145,  1150,
    1155,  1160,  1165,  1170,  1175,  1180,  1185,  1190,  1195,  1200,
    1205,  1210,  1215,  1220,  1225,  1230,  1235,  1239,  1244,  1248,
    1253,  1257,  1262,  1266,  1271,  1275,  1280,  1284,  1289,  1294,
    1299,  1304,  1309,  1314,  1319,  1324,  1329,  1334,  1337,  1338,
    1340,  1345,  1350,  1355,  1360,  1365,  1370,  1375,  1377,  1379,
    1382,  1386,  1390,  1394,  1399,  1404,  1409,  1414,  1419,  1424,
    1425,  1432,  1433,  1440,  1441,  1448,  1449,  1456,  1457,  1464,
    1467,  1468,  1470,  1475,  1478,  1479,  1484,  1489,  1492,  1493,
    1496,  1498,  1501,  1503,  1507,  1509,  1510,  1516,  1517,  1523,
    1526,  1527,  1532,  1534,  1539,  1544,  1547,  1548,  1550,  1555,
    1560,  1565,  1570,  1575,  1578,  1579,  1581,  1584,  1585,  1586,
    1595,  1596,  1604,  1607,  1608,  1613,  1618,  1623,  1625,  1627,
    1629,  1631,  1633,  1635,  1637,  1639,  1641,  1643,  1645,  1647,
    1649,  1651,  1653,  1655,  1657,  1659,  1661,  1663,  1665,  1667,
    1669,  1671,  1673,  1675,  1677,  1679,  1681,  1683,  1685,  1687,
    1689,  1691,  1693,  1696,  1697,  1699,  1701
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     158,     0,    -1,   159,    -1,    -1,   161,   152,   160,   159,
      -1,    -1,     3,   162,    -1,     6,   166,    -1,     7,   167,
      -1,     4,   163,    -1,     5,   164,    -1,   131,   165,    -1,
     100,   176,    -1,     8,   175,    -1,     9,   168,    -1,   321,
     153,   182,   154,    -1,   321,   153,   287,   152,   154,    -1,
     321,   153,   302,   152,   154,    -1,   321,   153,   312,   154,
      -1,   321,   153,   231,   154,    -1,   153,   169,   171,   173,
     154,    -1,   321,    -1,   170,   152,   169,    -1,    -1,     3,
     155,   321,   156,    -1,     4,   155,   321,   156,    -1,     5,
     155,   321,   156,    -1,   131,   155,   321,   156,    -1,     6,
     155,   321,   156,    -1,   172,   171,    -1,    -1,     7,   153,
     169,   171,   173,   154,   152,    -1,    82,   155,   174,   156,
     152,    -1,    -1,   321,   174,    -1,    -1,   153,   283,   154,
      -1,    -1,   321,   177,   153,   178,   154,    -1,   179,   152,
     178,    -1,    -1,   100,   155,   321,   156,    -1,   101,   155,
     319,   156,    -1,   116,   155,   146,   156,    -1,   117,   155,
     146,   156,    -1,   114,   155,   319,   156,    -1,   118,   155,
     319,   156,    -1,   180,    -1,   113,   155,   146,   156,    -1,
     115,   155,   146,   156,    -1,   183,   152,   182,    -1,    -1,
     184,    -1,   185,    -1,   191,    -1,   213,    -1,   223,    -1,
     220,    -1,    10,   155,   156,    -1,    11,   155,   186,   156,
      -1,    12,   155,   188,   156,    -1,    -1,   321,   187,   228,
      -1,    -1,   321,   189,   190,    -1,    92,   155,   319,   156,
      -1,   228,    -1,    14,   155,   196,   156,    -1,    13,   155,
     198,   156,    -1,    -1,    16,   192,   155,   202,   156,    -1,
      -1,    15,   193,   155,   207,   156,    -1,    -1,    18,   194,
     155,   202,   156,    -1,    -1,    17,   195,   155,   207,   156,
      -1,    -1,   321,   197,   200,    -1,    -1,   321,   199,   200,
      -1,   201,   200,    -1,    -1,    94,   155,   323,   156,    -1,
      94,   155,   156,    -1,    95,   155,   323,   156,    -1,    95,
     155,   156,    -1,    96,   155,   146,   156,    -1,    96,   155,
     156,    -1,    92,   155,   319,   156,    -1,   212,    -1,   229,
      -1,   180,    -1,    -1,   203,   204,    -1,   205,   204,    -1,
      -1,   206,    -1,   108,   155,   321,   156,    -1,   109,   155,
     321,   156,    -1,   110,   155,   323,   156,    -1,   111,   155,
     323,   156,    -1,   229,    -1,   181,    -1,    -1,   208,   209,
      -1,   210,   209,    -1,    -1,   206,    -1,    -1,    74,   211,
     155,   285,   156,    -1,   212,    -1,   106,   155,   319,   156,
      -1,   107,   155,   146,   156,    -1,    -1,    37,   214,   155,
     215,   156,    -1,    -1,   216,   217,    -1,   218,   217,    -1,
      -1,   206,    -1,    38,   155,   321,   156,    -1,    38,   155,
      15,   156,    -1,    38,   155,    16,   156,    -1,    38,   155,
      74,   156,    -1,    -1,    74,   219,   155,   285,   156,    -1,
     212,    -1,    22,   155,   221,   156,    -1,    -1,   321,   222,
     228,    -1,   142,    -1,    21,   155,   224,   156,    -1,   143,
      -1,    -1,   321,   225,   226,    -1,   227,   226,    -1,    -1,
     142,    -1,    20,   155,   321,   156,    -1,   143,    -1,   229,
     228,    -1,    -1,    69,   155,   146,   156,    -1,    49,   155,
     319,   156,    -1,    50,   155,   319,   156,    -1,    51,   155,
     319,   156,    -1,    56,   155,   319,   156,    -1,    55,   155,
     320,   156,    -1,    57,   155,   319,   156,    -1,    71,   155,
     321,   156,    -1,    72,   155,   321,   156,    -1,    70,   155,
     321,   156,    -1,    84,   155,   321,   156,    -1,    52,   155,
     319,   156,    -1,    82,   155,   230,   156,    -1,    46,   155,
     146,   156,    -1,    68,   155,   146,   156,    -1,    83,   155,
     146,   156,    -1,   102,   155,   147,   156,    -1,   102,   155,
     146,   156,    -1,    54,   155,   319,   156,    -1,    32,   155,
     321,   156,    -1,   127,   155,   324,   156,    -1,   105,   155,
     326,   156,    -1,   104,   155,   327,   156,    -1,   321,   230,
      -1,    -1,   232,   152,   231,    -1,    -1,   233,    -1,   238,
      -1,   243,    -1,   271,    -1,   272,    -1,   265,    -1,   275,
      -1,    11,   155,   234,   156,    -1,    -1,   321,   235,   236,
      -1,   237,   236,    -1,    -1,   281,    -1,    92,   155,   319,
     156,    -1,    94,   155,   323,   156,    -1,    94,   155,   156,
      -1,    95,   155,   323,   156,    -1,    95,   155,   156,    -1,
      96,   155,   146,   156,    -1,    96,   155,   156,    -1,    97,
     155,   323,   156,    -1,    97,   155,   156,    -1,    98,   155,
     323,   156,    -1,    98,   155,   156,    -1,    99,   155,   146,
     156,    -1,    99,   155,   156,    -1,    93,   155,   319,   156,
      -1,   103,   155,   146,   156,    -1,    39,   155,   319,   156,
      -1,    87,   155,   321,   156,    -1,    12,   155,   239,   156,
      -1,    -1,   321,   240,   241,    -1,   242,   241,    -1,    -1,
     281,    -1,    94,   155,   323,   156,    -1,    94,   155,   156,
      -1,    95,   155,   323,   156,    -1,    95,   155,   156,    -1,
      96,   155,   146,   156,    -1,    96,   155,   156,    -1,    14,
     155,   248,   156,    -1,    13,   155,   250,   156,    -1,    -1,
      16,   244,   155,   254,   156,    -1,    -1,    15,   245,   155,
     259,   156,    -1,    -1,    18,   246,   155,   254,   156,    -1,
      -1,    17,   247,   155,   259,   156,    -1,    -1,   321,   249,
     252,    -1,    -1,   321,   251,   252,    -1,   252,   253,    -1,
      -1,   281,    -1,   264,    -1,   180,    -1,    -1,   321,   255,
     256,    -1,   256,   258,    -1,    -1,   108,   155,   321,   156,
      -1,   110,   155,   323,   156,    -1,   111,   155,   323,   156,
      -1,   112,   155,   323,   156,    -1,   181,    -1,   281,    -1,
     264,    -1,   257,    -1,   119,   155,   319,   156,    -1,    -1,
     321,   260,   261,    -1,   261,   262,    -1,    -1,   257,    -1,
      -1,    74,   263,   155,   285,   156,    -1,   106,   155,   319,
     156,    -1,    37,   155,   266,   156,    -1,    -1,   321,   267,
     268,    -1,   268,   269,    -1,    -1,   257,    -1,    38,   155,
     321,   156,    -1,    38,   155,    15,   156,    -1,    38,   155,
      16,   156,    -1,    38,   155,    74,   156,    -1,   119,   155,
     319,   156,    -1,    -1,    74,   270,   155,   285,   156,    -1,
      19,   155,   321,   156,    -1,    22,   155,   273,   156,    -1,
      -1,   321,   274,   280,    -1,    23,   155,   276,   156,    -1,
      -1,   277,   278,    -1,   279,   278,    -1,    -1,   142,    -1,
      24,   155,   321,   156,    -1,   123,   155,   321,   156,    -1,
     111,   155,   323,   156,    -1,    30,   155,   321,   156,    -1,
      28,   155,   321,   156,    -1,    29,   155,   321,   156,    -1,
      31,   155,   321,   156,    -1,    25,   155,   324,   156,    -1,
      26,   155,   324,   156,    -1,    27,   155,   324,   156,    -1,
      66,   155,   146,   156,    -1,    67,   155,   146,   156,    -1,
      65,   155,   146,   156,    -1,    84,   155,   321,   156,    -1,
      87,   155,   321,   156,    -1,    36,   155,   321,   156,    -1,
     143,    -1,   281,   280,    -1,    -1,    82,   155,   282,   156,
      -1,    66,   155,   146,   156,    -1,    43,   155,   146,   156,
      -1,    45,   155,   146,   156,    -1,    44,   155,   146,   156,
      -1,   100,   155,   321,   156,    -1,   101,   155,   319,   156,
      -1,    84,   155,   321,   156,    -1,    64,   155,   321,   156,
      -1,    65,   155,   146,   156,    -1,    73,   155,   146,   156,
      -1,   321,   282,    -1,    -1,   284,   152,   283,    -1,    -1,
      40,   155,   146,   156,    -1,    41,   155,   146,   156,    -1,
      42,   155,   146,   156,    -1,    43,   155,   146,   156,    -1,
      45,   155,   146,   156,    -1,    49,   155,   319,   156,    -1,
      50,   155,   319,   156,    -1,    51,   155,   319,   156,    -1,
      52,   155,   319,   156,    -1,    53,   155,   321,   156,    -1,
     120,   155,   319,   156,    -1,    56,   155,   319,   156,    -1,
      55,   155,   320,   156,    -1,    88,   155,   146,   156,    -1,
      89,   155,   146,   156,    -1,    90,   155,   146,   156,    -1,
      66,   155,   146,   156,    -1,    69,   155,   146,   156,    -1,
      68,   155,   146,   156,    -1,    46,   155,   146,   156,    -1,
      54,   155,   319,   156,    -1,    64,   155,   321,   156,    -1,
      65,   155,   146,   156,    -1,   137,   155,   146,   156,    -1,
     136,   155,   146,   156,    -1,    93,   155,   319,   156,    -1,
      94,   155,   323,   156,    -1,    94,   155,   156,    -1,    95,
     155,   323,   156,    -1,    95,   155,   156,    -1,    96,   155,
     146,   156,    -1,    96,   155,   156,    -1,    97,   155,   323,
     156,    -1,    97,   155,   156,    -1,    98,   155,   323,   156,
      -1,    98,   155,   156,    -1,    99,   155,   146,   156,    -1,
      99,   155,   156,    -1,    57,   155,   319,   156,    -1,    58,
     155,   146,   156,    -1,    59,   155,   146,   156,    -1,    60,
     155,   146,   156,    -1,    61,   155,   321,   156,    -1,    47,
     155,   321,   156,    -1,    48,   155,   321,   156,    -1,    85,
     155,   321,   156,    -1,    86,   155,   321,   156,    -1,    87,
     155,   321,   156,    -1,   286,   285,    -1,    -1,   142,    -1,
      75,   155,   321,   156,    -1,    76,   155,   321,   156,    -1,
      77,   155,   321,   156,    -1,    78,   155,   321,   156,    -1,
      79,   155,   321,   156,    -1,    80,   155,   324,   156,    -1,
      81,   155,   324,   156,    -1,   143,    -1,   288,    -1,   151,
     287,    -1,   287,   149,   287,    -1,   287,   150,   287,    -1,
     155,   287,   156,    -1,   121,   155,   299,   156,    -1,   121,
     155,   146,   156,    -1,   122,   155,   300,   156,    -1,     4,
     155,   321,   156,    -1,   126,   155,   321,   156,    -1,   127,
     155,   324,   156,    -1,    -1,    22,   155,   321,   289,   296,
     156,    -1,    -1,   123,   155,   321,   290,   296,   156,    -1,
      -1,   124,   155,   321,   291,   294,   156,    -1,    -1,   125,
     155,   321,   292,   296,   156,    -1,    -1,     3,   155,   321,
     293,   296,   156,    -1,   295,   294,    -1,    -1,   297,    -1,
     129,   155,   321,   156,    -1,   297,   296,    -1,    -1,    24,
     155,   321,   156,    -1,    82,   155,   298,   156,    -1,   321,
     298,    -1,    -1,   327,   299,    -1,   327,    -1,   301,   300,
      -1,   301,    -1,   326,   144,   326,    -1,   326,    -1,    -1,
     128,   155,   303,   309,   156,    -1,    -1,   130,   155,   304,
     305,   156,    -1,   306,   305,    -1,    -1,    11,   155,   321,
     156,    -1,   308,    -1,    25,   155,   324,   156,    -1,   100,
     155,   321,   156,    -1,   310,   309,    -1,    -1,   307,    -1,
      82,   155,   311,   156,    -1,    33,   155,   321,   156,    -1,
      34,   155,   321,   156,    -1,    35,   155,   321,   156,    -1,
      36,   155,   321,   156,    -1,   321,   311,    -1,    -1,   313,
      -1,   314,   313,    -1,    -1,    -1,   133,   155,   321,   321,
     315,   317,   156,   152,    -1,    -1,   132,   155,   321,   316,
     317,   156,   152,    -1,   318,   317,    -1,    -1,   129,   155,
     321,   156,    -1,    24,   155,   321,   156,    -1,    82,   155,
     298,   156,    -1,   134,    -1,   135,    -1,   146,    -1,   319,
      -1,    62,    -1,   145,    -1,   148,    -1,   322,    -1,     5,
      -1,   131,    -1,     9,    -1,    25,    -1,    33,    -1,    34,
      -1,    35,    -1,    36,    -1,   128,    -1,   130,    -1,    32,
      -1,   132,    -1,   133,    -1,   129,    -1,    71,    -1,    72,
      -1,    38,    -1,    80,    -1,    81,    -1,   125,    -1,    24,
      -1,    23,    -1,   104,    -1,   105,    -1,   321,    -1,   146,
      -1,   325,    -1,   321,   325,    -1,    -1,   321,    -1,   321,
      -1,    37,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   317,   317,   322,   321,   336,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   352,   356,   360,   363,   366,
     370,   374,   377,   378,   382,   383,   384,   385,   386,   390,
     391,   395,   399,   400,   405,   406,   411,   416,   415,   424,
     425,   429,   430,   434,   435,   436,   437,   441,   442,   443,
     447,   448,   452,   453,   454,   455,   456,   457,   461,   465,
     466,   471,   470,   481,   480,   490,   491,   495,   496,   497,
     497,   498,   498,   499,   499,   500,   500,   505,   504,   518,
     517,   531,   532,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   550,   550,   561,   562,   566,   570,   571,
     572,   573,   574,   575,   580,   580,   591,   592,   596,   599,
     598,   611,   615,   616,   620,   620,   625,   625,   636,   637,
     641,   642,   643,   644,   645,   647,   646,   658,   662,   667,
     666,   676,   679,   680,   687,   686,   697,   698,   702,   705,
     706,   712,   713,   717,   718,   719,   720,   721,   722,   723,
     724,   725,   726,   727,   728,   729,   730,   731,   732,   733,
     734,   735,   736,   737,   738,   744,   753,   754,   759,   760,
     764,   765,   766,   767,   768,   769,   771,   776,   781,   780,
     791,   792,   796,   797,   798,   799,   800,   801,   802,   803,
     804,   805,   806,   807,   808,   809,   810,   811,   812,   813,
     817,   822,   821,   832,   833,   837,   838,   839,   840,   841,
     842,   843,   847,   848,   849,   849,   850,   850,   851,   851,
     852,   852,   857,   856,   868,   867,   878,   879,   883,   884,
     885,   890,   889,   902,   903,   908,   909,   910,   911,   912,
     913,   914,   918,   919,   924,   923,   936,   937,   941,   943,
     942,   957,   962,   966,   965,   977,   978,   982,   983,   984,
     985,   986,   987,   989,   988,  1004,  1008,  1013,  1012,  1024,
    1029,  1029,  1038,  1039,  1043,  1046,  1047,  1048,  1049,  1050,
    1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,
    1061,  1063,  1071,  1072,  1076,  1077,  1078,  1079,  1080,  1081,
    1089,  1090,  1091,  1092,  1093,  1097,  1098,  1103,  1104,  1108,
    1109,  1110,  1111,  1112,  1113,  1114,  1115,  1116,  1117,  1118,
    1119,  1120,  1121,  1122,  1123,  1132,  1133,  1134,  1135,  1136,
    1137,  1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,
    1147,  1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,
    1157,  1159,  1160,  1161,  1162,  1163,  1164,  1169,  1170,  1174,
    1178,  1183,  1188,  1193,  1198,  1203,  1207,  1211,  1219,  1220,
    1221,  1222,  1223,  1227,  1228,  1229,  1230,  1231,  1232,  1234,
    1233,  1246,  1245,  1258,  1257,  1281,  1280,  1292,  1291,  1306,
    1307,  1311,  1312,  1328,  1329,  1333,  1338,  1342,  1343,  1348,
    1349,  1353,  1354,  1358,  1362,  1371,  1370,  1377,  1376,  1385,
    1386,  1391,  1395,  1396,  1400,  1413,  1414,  1418,  1419,  1420,
    1421,  1422,  1423,  1427,  1428,  1432,  1436,  1437,  1442,  1441,
    1454,  1453,  1462,  1463,  1467,  1487,  1498,  1502,  1503,  1504,
    1508,  1509,  1513,  1514,  1515,  1520,  1521,  1522,  1523,  1524,
    1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,
    1535,  1536,  1537,  1538,  1539,  1540,  1541,  1542,  1543,  1547,
    1548,  1552,  1556,  1557,  1561,  1578,  1592
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_SOURCE", "KW_FILTER", "KW_PARSER",
  "KW_DESTINATION", "KW_LOG", "KW_OPTIONS", "KW_INCLUDE", "KW_INTERNAL",
  "KW_FILE", "KW_PIPE", "KW_UNIX_STREAM", "KW_UNIX_DGRAM", "KW_TCP",
  "KW_UDP", "KW_TCP6", "KW_UDP6", "KW_USERTTY", "KW_DOOR",
  "KW_SUN_STREAMS", "KW_PROGRAM", "KW_SQL", "KW_TYPE", "KW_COLUMNS",
  "KW_INDEXES", "KW_VALUES", "KW_PASSWORD", "KW_DATABASE", "KW_USERNAME",
  "KW_TABLE", "KW_ENCODING", "KW_DELIMITERS", "KW_QUOTES",
  "KW_QUOTE_PAIRS", "KW_NULL", "KW_SYSLOG", "KW_TRANSPORT", "KW_FSYNC",
  "KW_MARK_FREQ", "KW_STATS_FREQ", "KW_STATS_LEVEL", "KW_FLUSH_LINES",
  "KW_SUPPRESS", "KW_FLUSH_TIMEOUT", "KW_LOG_MSG_SIZE", "KW_FILE_TEMPLATE",
  "KW_PROTO_TEMPLATE", "KW_CHAIN_HOSTNAMES", "KW_NORMALIZE_HOSTNAMES",
  "KW_KEEP_HOSTNAME", "KW_CHECK_HOSTNAME", "KW_BAD_HOSTNAME",
  "KW_KEEP_TIMESTAMP", "KW_USE_DNS", "KW_USE_FQDN", "KW_DNS_CACHE",
  "KW_DNS_CACHE_SIZE", "KW_DNS_CACHE_EXPIRE", "KW_DNS_CACHE_EXPIRE_FAILED",
  "KW_DNS_CACHE_HOSTS", "KW_PERSIST_ONLY", "KW_TZ_CONVERT", "KW_TS_FORMAT",
  "KW_FRAC_DIGITS", "KW_LOG_FIFO_SIZE", "KW_LOG_DISK_FIFO_SIZE",
  "KW_LOG_FETCH_LIMIT", "KW_LOG_IW_SIZE", "KW_LOG_PREFIX",
  "KW_PROGRAM_OVERRIDE", "KW_HOST_OVERRIDE", "KW_THROTTLE", "KW_TLS",
  "KW_PEER_VERIFY", "KW_KEY_FILE", "KW_CERT_FILE", "KW_CA_DIR",
  "KW_CRL_DIR", "KW_TRUSTED_KEYS", "KW_TRUSTED_DN", "KW_FLAGS",
  "KW_PAD_SIZE", "KW_TIME_ZONE", "KW_RECV_TIME_ZONE", "KW_SEND_TIME_ZONE",
  "KW_LOCAL_TIME_ZONE", "KW_TIME_REOPEN", "KW_TIME_REAP", "KW_TIME_SLEEP",
  "KW_TMPL_ESCAPE", "KW_OPTIONAL", "KW_CREATE_DIRS", "KW_OWNER",
  "KW_GROUP", "KW_PERM", "KW_DIR_OWNER", "KW_DIR_GROUP", "KW_DIR_PERM",
  "KW_TEMPLATE", "KW_TEMPLATE_ESCAPE", "KW_FOLLOW_FREQ",
  "KW_OVERWRITE_IF_OLDER", "KW_DEFAULT_FACILITY", "KW_DEFAULT_LEVEL",
  "KW_KEEP_ALIVE", "KW_MAX_CONNECTIONS", "KW_LOCALIP", "KW_IP",
  "KW_LOCALPORT", "KW_PORT", "KW_DESTPORT", "KW_IP_TTL", "KW_SO_BROADCAST",
  "KW_IP_TOS", "KW_SO_SNDBUF", "KW_SO_RCVBUF", "KW_SO_KEEPALIVE",
  "KW_SPOOF_SOURCE", "KW_USE_TIME_RECVD", "KW_FACILITY", "KW_LEVEL",
  "KW_HOST", "KW_MATCH", "KW_MESSAGE", "KW_NETMASK", "KW_TAGS",
  "KW_CSV_PARSER", "KW_VALUE", "KW_DB_PARSER", "KW_REWRITE", "KW_SET",
  "KW_SUBST", "KW_YES", "KW_NO", "KW_GC_IDLE_THRESHOLD",
  "KW_GC_BUSY_THRESHOLD", "KW_COMPRESS", "KW_MAC", "KW_AUTH", "KW_ENCRYPT",
  "KW_IFDEF", "KW_ENDIF", "LL_DOTDOT", "LL_IDENTIFIER", "LL_NUMBER",
  "LL_FLOAT", "LL_STRING", "KW_OR", "KW_AND", "KW_NOT", "';'", "'{'",
  "'}'", "'('", "')'", "$accept", "start", "stmts", "$@1", "stmt",
  "source_stmt", "filter_stmt", "parser_stmt", "rewrite_stmt", "dest_stmt",
  "log_stmt", "include_stmt", "log_items", "log_item", "log_forks",
  "log_fork", "log_flags", "log_flags_items", "options_stmt",
  "template_stmt", "$@2", "template_items", "template_item",
  "socket_option", "inet_socket_option", "source_items", "source_item",
  "source_afinter", "source_affile", "source_affile_params", "$@3",
  "source_afpipe_params", "$@4", "source_afpipe_options",
  "source_afsocket", "$@5", "$@6", "$@7", "$@8",
  "source_afunix_dgram_params", "$@9", "source_afunix_stream_params",
  "$@10", "source_afunix_options", "source_afunix_option",
  "source_afinet_udp_params", "$@11", "source_afinet_udp_options",
  "source_afinet_udp_option", "source_afinet_option",
  "source_afinet_tcp_params", "$@12", "source_afinet_tcp_options",
  "source_afinet_tcp_option", "$@13", "source_afsocket_stream_params",
  "source_afsyslog", "$@14", "source_afsyslog_params", "$@15",
  "source_afsyslog_options", "source_afsyslog_option", "$@16",
  "source_afprogram", "source_afprogram_params", "$@17",
  "source_afstreams", "source_afstreams_params", "$@18",
  "source_afstreams_options", "source_afstreams_option",
  "source_reader_options", "source_reader_option",
  "source_reader_option_flags", "dest_items", "dest_item", "dest_affile",
  "dest_affile_params", "$@19", "dest_affile_options",
  "dest_affile_option", "dest_afpipe", "dest_afpipe_params", "$@20",
  "dest_afpipe_options", "dest_afpipe_option", "dest_afsocket", "$@21",
  "$@22", "$@23", "$@24", "dest_afunix_dgram_params", "$@25",
  "dest_afunix_stream_params", "$@26", "dest_afunix_options",
  "dest_afunix_option", "dest_afinet_udp_params", "$@27",
  "dest_afinet_udp_options", "dest_afinet_option",
  "dest_afinet_udp_option", "dest_afinet_tcp_params", "$@28",
  "dest_afinet_tcp_options", "dest_afinet_tcp_option", "$@29",
  "dest_afsocket_option", "dest_afsyslog", "dest_afsyslog_params", "$@30",
  "dest_afsyslog_options", "dest_afsyslog_option", "$@31", "dest_afuser",
  "dest_afprogram", "dest_afprogram_params", "$@32", "dest_afsql",
  "dest_afsql_params", "$@33", "dest_afsql_options", "dest_afsql_option",
  "dest_writer_options", "dest_writer_option", "dest_writer_options_flags",
  "options_items", "options_item", "tls_options", "tls_option",
  "filter_expr", "filter_simple_expr", "$@34", "$@35", "$@36", "$@37",
  "$@38", "filter_match_opts", "filter_match_opt", "filter_re_opts",
  "filter_re_opt", "regexp_option_flags", "filter_fac_list",
  "filter_level_list", "filter_level", "parser_expr", "$@39", "$@40",
  "parser_db_opts", "parser_db_opt", "parser_column_opt", "parser_opt",
  "parser_csv_opts", "parser_csv_opt", "parser_csv_flags",
  "rewrite_expr_list", "rewrite_expr_list_build", "rewrite_expr", "$@41",
  "$@42", "rewrite_expr_opts", "rewrite_expr_opt", "yesno", "dnsmode",
  "string", "reserved_words_as_strings", "string_or_number", "string_list",
  "string_list_build", "level_string", "facility_string", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,    59,   123,   125,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   157,   158,   160,   159,   159,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   169,   170,   170,   170,   170,   170,   171,
     171,   172,   173,   173,   174,   174,   175,   177,   176,   178,
     178,   179,   179,   180,   180,   180,   180,   181,   181,   181,
     182,   182,   183,   183,   183,   183,   183,   183,   184,   185,
     185,   187,   186,   189,   188,   190,   190,   191,   191,   192,
     191,   193,   191,   194,   191,   195,   191,   197,   196,   199,
     198,   200,   200,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   203,   202,   204,   204,   205,   206,   206,
     206,   206,   206,   206,   208,   207,   209,   209,   210,   211,
     210,   210,   212,   212,   214,   213,   216,   215,   217,   217,
     218,   218,   218,   218,   218,   219,   218,   218,   220,   222,
     221,   223,   223,   223,   225,   224,   226,   226,   227,   227,
     227,   228,   228,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   230,   230,   231,   231,
     232,   232,   232,   232,   232,   232,   232,   233,   235,   234,
     236,   236,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     238,   240,   239,   241,   241,   242,   242,   242,   242,   242,
     242,   242,   243,   243,   244,   243,   245,   243,   246,   243,
     247,   243,   249,   248,   251,   250,   252,   252,   253,   253,
     253,   255,   254,   256,   256,   257,   257,   257,   257,   257,
     257,   257,   258,   258,   260,   259,   261,   261,   262,   263,
     262,   264,   265,   267,   266,   268,   268,   269,   269,   269,
     269,   269,   269,   270,   269,   271,   272,   274,   273,   275,
     277,   276,   278,   278,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   280,   280,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   282,   282,   283,   283,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   285,   285,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   287,   287,
     287,   287,   287,   288,   288,   288,   288,   288,   288,   289,
     288,   290,   288,   291,   288,   292,   288,   293,   288,   294,
     294,   295,   295,   296,   296,   297,   297,   298,   298,   299,
     299,   300,   300,   301,   301,   303,   302,   304,   302,   305,
     305,   306,   307,   307,   308,   309,   309,   310,   310,   310,
     310,   310,   310,   311,   311,   312,   313,   313,   315,   314,
     316,   314,   317,   317,   318,   318,   318,   319,   319,   319,
     320,   320,   321,   321,   321,   322,   322,   322,   322,   322,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   322,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   323,
     323,   324,   325,   325,   326,   327,   327
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     4,     0,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     4,     5,     5,     4,     4,
       5,     1,     3,     0,     4,     4,     4,     4,     4,     2,
       0,     7,     5,     0,     2,     0,     3,     0,     5,     3,
       0,     4,     4,     4,     4,     4,     4,     1,     4,     4,
       3,     0,     1,     1,     1,     1,     1,     1,     3,     4,
       4,     0,     3,     0,     3,     4,     1,     4,     4,     0,
       5,     0,     5,     0,     5,     0,     5,     0,     3,     0,
       3,     2,     0,     4,     3,     4,     3,     4,     3,     4,
       1,     1,     1,     0,     2,     2,     0,     1,     4,     4,
       4,     4,     1,     1,     0,     2,     2,     0,     1,     0,
       5,     1,     4,     4,     0,     5,     0,     2,     2,     0,
       1,     4,     4,     4,     4,     0,     5,     1,     4,     0,
       3,     1,     4,     1,     0,     3,     2,     0,     1,     4,
       1,     2,     0,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     2,     0,     3,     0,
       1,     1,     1,     1,     1,     1,     1,     4,     0,     3,
       2,     0,     1,     4,     4,     3,     4,     3,     4,     3,
       4,     3,     4,     3,     4,     3,     4,     4,     4,     4,
       4,     0,     3,     2,     0,     1,     4,     3,     4,     3,
       4,     3,     4,     4,     0,     5,     0,     5,     0,     5,
       0,     5,     0,     3,     0,     3,     2,     0,     1,     1,
       1,     0,     3,     2,     0,     4,     4,     4,     4,     1,
       1,     1,     1,     4,     0,     3,     2,     0,     1,     0,
       5,     4,     4,     0,     3,     2,     0,     1,     4,     4,
       4,     4,     4,     0,     5,     4,     4,     0,     3,     4,
       0,     2,     2,     0,     1,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     1,     2,     0,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     2,     0,     3,     0,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,     4,     3,     4,
       3,     4,     3,     4,     3,     4,     3,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     2,     0,     1,
       4,     4,     4,     4,     4,     4,     4,     1,     1,     2,
       3,     3,     3,     4,     4,     4,     4,     4,     4,     0,
       6,     0,     6,     0,     6,     0,     6,     0,     6,     2,
       0,     1,     4,     2,     0,     4,     4,     2,     0,     2,
       1,     2,     1,     3,     1,     0,     5,     0,     5,     2,
       0,     4,     1,     4,     4,     2,     0,     1,     4,     4,
       4,     4,     4,     2,     0,     1,     2,     0,     0,     8,
       0,     7,     2,     0,     4,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     0,   445,   447,   466,   465,   448,   455,   449,
     450,   451,   452,   461,   459,   460,   462,   463,   467,   468,
     464,   453,   458,   454,   446,   456,   457,   442,   443,     6,
       0,   444,     9,     0,    10,     0,     7,     0,    23,     8,
     308,    13,    14,    21,    12,    37,    11,     0,     1,     3,
      51,     0,     0,   169,     0,     0,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   427,     5,     0,     0,
       0,     0,     0,    71,    69,    75,    73,     0,     0,   114,
     131,   133,     0,     0,    52,    53,    54,    55,    57,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   368,     0,     0,     0,     0,     0,     0,
       0,   216,   214,   220,   218,     0,     0,     0,     0,     0,
       0,   170,   171,   172,   175,   173,   174,   176,     0,     0,
       0,     0,     0,     0,    33,    30,    23,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
     308,    40,     0,     0,     0,   425,   427,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   473,   369,     0,     0,     0,     0,   405,   407,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     270,     0,    19,   169,     0,     0,     0,     0,     0,    23,
       0,     0,    29,    22,     0,     0,     0,     0,     0,     0,
       0,     0,   437,   438,   439,     0,     0,     0,     0,     0,
       0,   441,   440,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   470,   336,   469,     0,   338,     0,     0,   340,
     342,     0,   344,     0,     0,   346,     0,     0,     0,   307,
       0,     0,     0,     0,     0,     0,    18,   426,    58,     0,
      61,     0,    63,     0,    79,     0,    77,   104,    93,   104,
      93,     0,   134,     0,   129,   116,    50,   387,     0,   379,
     476,     0,     0,   475,   400,     0,   402,   474,   404,   381,
     383,   385,     0,   473,     0,   471,   372,   370,   371,    16,
     416,   410,    17,     0,   178,     0,   201,     0,   224,     0,
     222,     0,     0,     0,     0,     0,     0,   267,     0,   273,
       0,   253,   168,    24,    25,    26,    28,    27,    30,    35,
      20,   309,   310,   311,   312,   313,   328,   352,   353,   314,
     315,   316,   317,   318,   329,   321,   320,   347,   348,   349,
     350,   351,   330,   331,   325,   327,   326,   354,   355,   356,
     322,   323,   324,   334,   335,   337,   339,   341,   343,   345,
     319,   333,   332,     0,     0,    38,    40,   430,     0,    59,
     142,    60,   142,    68,    82,    67,    82,     0,   107,     0,
      96,     0,     0,   132,   137,   128,   142,     0,   119,   394,
     376,   394,   374,   373,   399,   375,   401,     0,   394,   390,
     394,   377,   472,   378,     0,     0,     0,     0,     0,     0,
       0,   417,   412,     0,   416,     0,     0,   410,   177,   181,
     200,   204,   213,   227,   212,   227,     0,   244,     0,   231,
       0,     0,   265,   266,   293,   269,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   274,   291,   271,   273,   252,   256,    33,     0,
      35,     0,     0,    39,   433,   428,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    62,   142,
       0,    64,    66,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,    80,    82,    90,    91,    78,    72,
     109,     0,     0,     0,     0,     0,     0,    47,   103,   108,
     105,   107,   111,   102,    70,    94,    96,    97,    76,    74,
       0,   138,   140,   135,   137,   130,   115,     0,   125,   120,
     127,   117,   119,     0,     0,     0,   394,     0,   403,     0,
       0,     0,   390,   391,     0,   473,     0,     0,     0,     0,
     424,     0,   406,   415,     0,   408,   409,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
     181,   182,     0,     0,     0,   202,   204,   205,   225,   223,
     217,   247,   215,   234,   221,   219,   268,   293,     0,   473,
     473,   473,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   272,   254,     0,     0,    34,    41,
      42,     0,     0,     0,     0,   433,   433,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   167,     0,     0,     0,     0,     0,   473,   141,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,   106,
      95,     0,   136,     0,     0,   118,     0,   398,   388,   393,
     380,   382,     0,   384,   389,   386,     0,     0,     0,     0,
       0,     0,   424,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   306,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,     0,     0,
       0,   203,     0,   230,   226,   229,   228,   245,   232,   292,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   263,     0,     0,
       0,     0,     0,   239,   257,   241,   255,   240,     0,    32,
       0,   398,     0,     0,   432,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   167,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    84,     0,    86,     0,     0,    88,     0,     0,
       0,     0,     0,     0,   358,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   358,     0,     0,   398,
       0,   413,   419,   420,   421,   422,   418,   423,   414,   411,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   306,
       0,     0,     0,     0,   185,     0,   187,     0,     0,   189,
     191,     0,   193,     0,     0,   195,     0,     0,     0,   207,
       0,   209,     0,     0,   211,     0,   249,   248,   246,     0,
     242,   233,   275,   282,   283,   284,   279,   280,   278,   281,
     290,   287,   285,   286,   288,   289,   277,   276,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,   431,
       0,   162,   156,   144,   145,   146,   154,   161,   148,   147,
     149,   157,   143,   152,   150,   151,   155,   166,   158,   153,
     160,   159,   165,   164,   163,    65,    89,    83,    85,    87,
     112,   113,    45,    43,    44,    46,     0,     0,     0,     0,
       0,     0,     0,   359,   367,     0,   358,    98,    99,   100,
     101,    48,    49,   139,   122,   123,   124,   121,     0,   395,
     396,   397,   392,   198,   296,   298,   297,   302,   303,   295,
     304,   294,   305,   301,   199,   183,   196,   184,   186,   188,
     190,   192,   194,   299,   300,   197,   206,   208,   210,     0,
       0,     0,     0,     0,     0,     0,   358,     0,     0,     0,
       0,     0,   435,   436,   434,   429,     0,     0,     0,     0,
       0,   473,   473,   110,   357,   126,   251,   358,     0,   259,
     260,   261,   258,     0,   235,   236,   237,   238,   262,     0,
       0,     0,     0,     0,     0,     0,     0,   243,   264,   360,
     361,   362,   363,   364,   365,   366,   250
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,   117,    12,    39,    42,    44,    56,    46,
      49,    52,    69,    70,   184,   185,   291,   569,    51,    54,
     115,   352,   353,   627,   628,   132,   133,   134,   135,   359,
     480,   361,   482,   601,   136,   244,   243,   246,   245,   365,
     486,   363,   484,   614,   615,   489,   490,   635,   636,   629,
     487,   488,   630,   631,   782,   616,   137,   249,   497,   498,
     651,   652,   794,   138,   373,   496,   139,   371,   494,   643,
     644,   598,   633,   901,   169,   170,   171,   403,   529,   699,
     700,   172,   405,   531,   705,   706,   173,   275,   274,   277,
     276,   409,   535,   407,   533,   708,   844,   538,   713,   848,
     874,   991,   536,   711,   847,   988,  1110,   875,   174,   420,
     567,   735,   876,  1009,   175,   176,   416,   544,   177,   418,
     419,   564,   565,   716,   877,   958,   113,   114,  1065,  1066,
     152,   153,   501,   508,   509,   510,   499,   661,   662,   655,
     656,   938,   382,   385,   386,   156,   400,   401,   526,   527,
     521,   522,   523,   524,   811,   234,   235,   236,   746,   574,
     744,   745,   312,   313,   334,    41,   335,   394,   395,   388,
     384
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -928
static const yytype_int16 yypact[] =
{
      73,  2020,  2020,  2020,  2020,  -105,   -81,  2020,  2020,  2020,
      87,  -928,   -51,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
     -38,  -928,  -928,    -5,  -928,     7,  -928,     8,    88,  -928,
    2129,  -928,  -928,  -928,  -928,  -928,  -928,     9,  -928,  -928,
      53,   160,   -12,   112,    13,    16,    17,    19,    29,   110,
      33,    31,    32,    42,    46,    50,    54,    60,    61,    62,
      63,    65,    66,    67,    75,    76,    77,    78,    79,    80,
      81,    82,    93,    94,    95,   106,   108,   109,   111,   113,
     118,   119,   121,   133,   137,   141,   142,   143,   144,   145,
     146,   152,   154,    34,    39,    55,   -49,    73,   155,   157,
     158,   159,   161,  -928,  -928,  -928,  -928,   162,   163,  -928,
    -928,  -928,    89,    90,  -928,  -928,  -928,  -928,  -928,  -928,
     164,   165,   174,   175,   176,   177,   179,   180,   181,   182,
     160,   160,   -95,  -928,   183,   184,   115,   185,   188,   189,
     190,  -928,  -928,  -928,  -928,   191,   197,   200,   201,   203,
     206,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  2020,  2020,
    2020,  2020,  2020,   207,   277,   110,    88,   215,   219,   220,
     221,   225,   226,  2020,  2020,   -73,   -73,   -73,   -73,  2020,
     -73,   -13,   -73,   -73,   227,   230,   232,  2020,  2020,   233,
     234,   236,   241,  2020,  2020,  2020,   243,   244,   245,   -73,
     270,   427,   -60,   803,   889,   -58,   -73,   247,   248,  -928,
    2129,    36,   242,   251,   253,  -928,   -49,  -928,   240,  2020,
    2020,  2020,  2020,   254,   259,   262,   264,  2020,  2020,   266,
    -928,    53,  2020,  2020,  2020,  1786,  2020,  2020,  2020,  2020,
    2020,  2020,  -928,   -36,   160,   160,   268,  -928,  -928,   269,
    2020,  2020,  2020,  2020,   272,   274,   275,   276,  2020,  2020,
    -928,  2020,  -928,   112,   278,   279,   281,   282,   285,    88,
     287,   271,  -928,  -928,   288,   289,   290,   291,   293,   300,
     301,   302,  -928,  -928,  -928,   308,   310,   311,   312,   313,
     317,  -928,  -928,   322,   323,   324,   325,   326,   329,   330,
     331,   332,   333,   334,   335,   337,   339,   340,   341,   344,
     345,   346,  -928,  -928,  -928,   347,  -928,   348,   349,  -928,
    -928,   353,  -928,   356,   357,  -928,   358,   359,   361,  -928,
     364,   375,   379,   382,  2020,  2020,  -928,  -928,  -928,   380,
    -928,   381,  -928,   383,  -928,   385,  -928,  -928,  -928,  -928,
    -928,   386,  -928,   387,  -928,  -928,  -928,  -928,   388,  -928,
    -928,   389,   390,  -928,  1864,   391,  2020,  -928,   280,  -928,
    -928,  -928,   392,  2020,   393,  -928,  -928,   283,  -928,  -928,
      70,   432,  -928,   394,  -928,   395,  -928,   397,  -928,   398,
    -928,  2020,  2020,  2020,  2020,   405,   406,  -928,   407,   297,
     418,  -928,  -928,  -928,  -928,  -928,  -928,  -928,   110,  2020,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  2020,   -73,  -928,    36,  -928,  2020,  -928,
    2514,  -928,   606,  -928,  2361,  -928,  2361,   423,  2281,   426,
    2440,   428,   431,  -928,     4,  -928,  2514,   433,  2201,    26,
    -928,    26,  -928,  -928,  -928,  -928,  -928,  2020,    26,     3,
      26,  -928,  -928,  -928,   436,   441,   445,   446,   447,   448,
     449,  -928,  -928,   451,    70,   450,   452,   432,  -928,  2606,
    -928,   533,  -928,  -928,  -928,  -928,   453,  -928,   454,  -928,
     455,   456,  -928,  -928,   304,  -928,   458,   459,   461,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   476,   477,
     480,   488,  -928,  -928,  -928,   297,  -928,  -928,   277,   489,
    2020,   492,   493,  -928,    15,  -928,   496,   498,   499,   504,
     516,   517,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   536,   537,   538,   539,   540,   541,   542,  -928,  2514,
     544,  -928,  -928,   545,   546,   547,   548,   549,   550,   551,
     552,   554,   557,  -928,  -928,  2361,  -928,  -928,  -928,  -928,
    -928,   561,   571,   572,   573,   576,   582,  -928,  -928,  -928,
    -928,  2281,  -928,  -928,  -928,  -928,  2440,  -928,  -928,  -928,
     583,  -928,  -928,  -928,     4,  -928,  -928,   584,  -928,  -928,
    -928,  -928,  2201,   585,   586,   588,    26,   589,  -928,   591,
     587,   592,     3,  -928,   593,  2020,  2020,  2020,  2020,  2020,
    2020,  2020,  -928,  -928,  2020,  -928,  -928,   595,   596,   598,
     600,   601,   602,   607,   609,   613,   614,   617,   618,   619,
     620,   622,   623,   624,   625,   626,   630,   634,   636,  -928,
    2606,  -928,   638,   639,   642,  -928,   533,  -928,   670,   670,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,   304,  2020,  2020,
    2020,  2020,  2020,  2020,  2020,  2020,  2020,   442,   652,   653,
    2020,  2020,  1942,  2020,  -928,   410,   384,   650,  -928,  -928,
    -928,   648,   649,   651,   654,    15,    15,  2020,   659,   -73,
     -73,   -73,   -73,   -73,   -13,   -73,   -73,   661,   663,  2020,
    2020,  2020,  2020,   667,  2020,    -6,  1864,  2020,  2020,  -928,
     -73,   -73,   967,  1084,   -57,   -73,   668,   -73,   669,   671,
     -73,  -928,   675,  2020,  2020,  1942,  1942,   679,   685,  -928,
    -928,  2020,  -928,  1630,   677,  -928,  2020,  2020,  -928,  -928,
    -928,  -928,  2020,  -928,  -928,  -928,   660,   678,   684,   686,
     687,   688,  2020,   689,   690,   -73,   701,   702,   703,  2020,
     704,   705,   706,  2020,  2020,  2020,   -73,   -73,  1162,  1240,
     -46,  1318,  1396,   -44,  2020,   -73,   707,  -928,  1474,  1552,
     -37,  -928,   699,  -928,  -928,  -928,  -928,  2547,  1996,  -928,
     700,   708,   709,   710,   711,   712,   713,   714,   715,   716,
     717,   720,   721,   722,   726,   729,   731,  -928,   732,   733,
     734,   735,   736,  -928,  -928,  -928,  -928,  -928,   740,  -928,
    2020,  2020,  2020,   741,  -928,   739,   743,   744,   746,   747,
     748,   749,   750,   753,   754,   755,   759,   760,   761,   762,
     763,   764,  2020,   773,   774,   781,   783,   784,   785,   786,
     787,   788,  -928,   789,  -928,   790,   791,  -928,   794,   796,
     797,   798,   799,   800,   148,   801,   806,   807,   808,   809,
     810,   811,   812,   815,   817,   818,   148,   819,   821,  2020,
     822,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
     823,   824,   825,   826,   827,   828,   829,   830,   831,  2020,
     832,   833,   839,   840,  -928,   841,  -928,   842,   848,  -928,
    -928,   850,  -928,   852,   854,  -928,   855,   856,   857,  -928,
     859,  -928,   860,   867,  -928,   -73,  -928,  -928,  -928,   742,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  1708,   869,
    2020,  1942,  1942,  1942,   -73,  -928,   870,   871,   872,  -928,
     873,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,   874,   875,   876,   877,
     878,   881,   885,  -928,  -928,   886,   148,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,   887,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,   888,
     891,   -73,   893,   894,   895,   896,   148,   897,   898,   899,
     900,   901,  -928,  -928,  -928,  -928,  2020,  2020,  2020,  2020,
    2020,  2020,  2020,  -928,  -928,  -928,  -928,   148,   902,  -928,
    -928,  -928,  -928,   903,  -928,  -928,  -928,  -928,  -928,   904,
     905,   906,   907,   908,   909,   910,   911,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -928,  -928,   738,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -151,  -928,  -166,  -928,   -33,    74,  -928,  -928,
    -928,   420,  -928,  -464,  -692,   608,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -470,  -928,   487,  -928,   222,  -928,  -453,
     491,  -928,   231,  -928,  -928,  -462,  -928,  -928,  -928,  -928,
     209,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,   424,
    -928,  -449,  -440,   -39,   758,  -928,  -928,  -928,  -928,   369,
    -928,  -928,  -928,  -928,   367,  -928,  -928,  -928,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,   535,  -928,   662,  -928,  -928,
    -705,  -928,   664,  -928,  -928,  -928,  -928,  -555,  -928,  -928,
    -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,  -928,
    -928,   509,  -928,   362,  -506,   116,   851,  -928,  -927,  -928,
     -99,  -928,  -928,  -928,  -928,  -928,  -928,   416,  -928,  -480,
    -495,  -828,   696,   697,  -928,  -928,  -928,  -928,   555,  -928,
    -928,  -928,   560,  -928,   273,  -928,   858,  -928,  -928,  -928,
    -588,  -928,  -185,   336,    -1,  -928,  -192,  -661,   693,  -502,
     321
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      40,    43,    45,    47,   806,   658,    53,    55,    57,  1078,
     305,   306,   307,   308,   663,   310,   618,   314,   315,   292,
     613,   657,   613,   701,   640,   707,   632,   653,   659,   337,
     664,   341,   343,   602,   331,   293,   650,   637,   717,   741,
     599,   346,   599,   873,   617,   649,   617,   645,    48,   311,
     653,   262,   263,  1017,   264,   265,   599,   266,   851,   852,
     853,   302,   303,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    50,   304,   127,   128,     1,     2,     3,     4,
       5,     6,     7,   232,   233,   654,   338,    58,   344,   916,
     129,    64,    65,    66,    67,   514,   339,   742,   345,   917,
     968,    59,   974,   515,   516,   517,   518,   909,   654,   983,
     969,  1081,   975,   264,   265,    60,   154,   183,   155,   984,
     396,   302,   303,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   660,   304,   166,   167,   350,   351,   428,  1134,
     905,   906,   987,   990,   743,   781,   641,   642,    61,   168,
     769,   613,   519,   845,   845,   873,   873,   884,   885,   599,
      62,    63,   116,   140,   141,   397,   398,   663,   178,   632,
     520,   179,   180,     8,   181,   617,   799,   284,   285,   286,
     287,   288,   142,   637,   182,   186,   187,   188,   229,  1143,
     650,   230,   300,   301,   701,   130,   131,   189,   309,   649,
     707,   190,   846,   846,     9,   191,   319,   320,   231,   192,
    1156,   717,   325,   326,   327,   193,   194,   195,   196,    68,
     197,   198,   199,  1056,  1057,  1058,  1059,  1060,  1061,  1062,
     200,   201,   202,   203,   204,   205,   206,   207,   360,   362,
     364,   366,   251,   250,   843,   843,   372,   374,   208,   209,
     210,   377,   378,   379,   383,   387,   389,   390,   391,   392,
     393,   211,   568,   212,   213,   908,   214,   269,   215,   404,
     406,   408,   410,   216,   217,    13,   218,   415,   417,    14,
     421,   143,   144,   145,   146,   147,   148,   149,   219,   572,
    1063,  1064,   220,    15,    16,    17,   221,   222,   223,   224,
     225,   226,    18,    19,    20,    21,    22,   227,    23,   228,
     238,   150,   239,   240,   241,   151,   242,   247,   248,   252,
     253,   546,   547,   548,   549,   550,   551,   552,   553,   254,
     255,   256,   257,   554,   258,   259,   260,   261,   267,   268,
     270,    24,    25,   271,   272,   273,   278,   678,   679,   680,
      26,    27,   279,   477,   478,   280,   281,   282,   283,   290,
     289,   294,   555,   556,   557,   295,   296,   297,   681,   682,
     683,   298,   299,   316,    28,    29,   317,   684,   318,   321,
     322,   558,   323,   383,   559,   387,   685,   324,   686,   328,
     329,   330,   393,   347,   348,    30,   358,   354,    31,    32,
      33,    34,    35,    36,   696,   697,   355,   356,   560,   367,
     537,   539,   537,   539,   368,    37,   332,   369,    38,   370,
     561,   375,   399,   402,   507,   430,   333,   411,   570,   412,
     413,   414,    13,   265,   423,   424,    14,   425,   426,   562,
     563,   427,   429,   525,   431,   432,   433,   434,   866,   435,
      15,    16,    17,   678,   679,   680,   436,   437,   438,    18,
      19,    20,    21,    22,   439,    23,   440,   441,   442,   443,
    1154,  1155,   571,   444,   681,   682,   683,   575,   445,   446,
     447,   448,   449,   684,   867,   450,   451,   452,   453,   454,
     455,   456,   685,   457,   686,   458,   459,   460,    24,    25,
     461,   462,   463,   464,   465,   466,   387,    26,    27,   467,
     696,   697,   468,   469,   470,   471,   842,   472,   868,   473,
     869,   870,   871,   625,   609,   626,   610,   611,   612,   872,
     474,    28,    29,   475,   476,   736,   479,   481,   878,   483,
     864,   485,   493,   495,   500,   502,   503,   505,   511,   513,
     528,   530,    30,   532,   534,    31,    32,    33,    34,    35,
      36,   542,   543,   545,   888,   889,   890,   891,   892,   570,
     894,   895,    37,   332,   566,    38,   678,   679,   680,   619,
     913,   915,   634,   336,   638,   910,   911,   639,   859,   646,
     918,   665,   920,   927,   928,   923,   666,   681,   682,   683,
     667,   668,   669,   670,   671,   674,   684,   672,   675,   710,
     712,   714,   715,   718,   719,   685,   720,   686,   721,   722,
     723,   724,   725,   726,   727,   728,   729,   702,   703,   704,
     950,   730,   731,   696,   697,   732,   965,   967,   576,   971,
     973,   962,   963,   733,   738,   737,   980,   982,   739,   740,
     977,   747,   577,   748,   749,   578,   579,   580,   581,   750,
     582,   583,   584,   585,   393,   807,   808,   809,   810,   812,
     813,   751,   752,   814,   586,   587,   588,   589,   590,   753,
     754,   755,   756,   757,   758,   759,   760,   761,   591,   592,
     593,   762,   763,   764,   765,   766,   767,   768,   600,   770,
     771,   772,   773,   774,   775,   776,   777,   778,   594,   779,
     595,   596,   780,   678,   679,   680,   783,   850,   393,   393,
     393,   854,   855,   856,   857,   858,   784,   785,   786,   862,
     863,   787,   865,   597,   681,   682,   683,   788,   791,   793,
     796,   797,   802,   684,   798,   800,   886,   801,   803,   805,
     815,   816,   685,   817,   686,   818,   819,   820,   898,   899,
     900,   902,   821,   904,   822,   383,   387,   393,   823,   824,
     696,   697,   825,   826,   827,   828,   842,   829,   830,   831,
     832,   833,   925,   926,   609,   834,   610,   611,   612,   835,
     931,   836,   935,   838,   839,   937,   939,   840,   860,   861,
    1109,   940,   879,   880,   881,   887,   882,   896,    13,   897,
     883,   812,    14,   903,   919,   921,   941,   922,   954,  1118,
    1119,  1120,   959,   960,   961,   929,    15,    16,    17,  1121,
     924,   930,   936,   976,   942,    18,    19,    20,    21,    22,
     943,    23,   944,   945,   946,   948,   949,   951,   952,   953,
     955,   956,   957,   978,   985,   237,   992,   492,   790,   376,
     491,   795,   789,  1037,   993,   994,   995,   996,   997,   998,
     999,  1000,  1001,  1002,    24,    25,  1003,  1004,  1005,  1016,
     939,  1018,  1006,    26,    27,  1007,  1008,  1010,  1011,  1012,
    1013,  1014,  1015,  1019,    13,  1020,   573,  1111,    14,  1021,
    1022,   902,  1023,  1024,  1025,  1026,  1027,    28,    29,  1028,
    1029,  1030,    15,    16,    17,  1031,  1032,  1033,  1034,  1035,
    1036,    18,    19,    20,    21,    22,  1138,    23,    30,  1038,
    1039,    31,    32,    33,    34,    35,    36,  1040,   939,  1041,
    1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,    37,   332,
    1050,    38,  1051,  1052,  1053,  1054,  1055,  1067,   959,   340,
      24,    25,  1068,  1069,  1070,  1071,  1072,  1073,  1074,    26,
      27,  1075,    13,  1076,  1077,  1079,    14,  1080,  1082,  1083,
    1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1093,  1094,
      15,    16,    17,    28,    29,  1095,  1096,  1097,  1098,    18,
      19,    20,    21,    22,  1099,    23,  1100,  1115,  1101,  1117,
    1102,  1103,  1104,  1105,    30,  1106,  1107,    31,    32,    33,
      34,    35,    36,  1108,  1116,  1125,  1122,  1123,  1124,  1126,
    1127,  1128,  1129,  1130,    37,   332,  1131,    38,    24,    25,
    1132,   422,  1133,  1135,  1136,   342,  1137,    26,    27,  1139,
    1140,  1141,  1142,  1144,  1145,  1146,  1147,  1148,  1157,  1158,
    1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,   792,   837,
     709,    28,    29,   841,   734,  1092,   541,   540,   804,   849,
     504,   349,   676,   506,   673,   947,   512,   907,     0,    13,
     893,     0,    30,    14,   357,    31,    32,    33,    34,    35,
      36,     0,     0,     0,     0,     0,     0,    15,    16,    17,
       0,     0,    37,   332,     0,    38,    18,    19,    20,    21,
      22,     0,    23,   912,     0,  1149,  1150,  1151,  1152,  1153,
     393,   393,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,    25,     0,     0,     0,
       0,     0,     0,     0,    26,    27,     0,    13,     0,     0,
       0,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,    28,    29,
       0,     0,     0,     0,    18,    19,    20,    21,    22,     0,
      23,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,     0,    31,    32,    33,    34,    35,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
     332,     0,    38,    24,    25,     0,     0,     0,     0,     0,
     914,     0,    26,    27,     0,    13,     0,     0,     0,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    28,    29,     0,     0,
       0,     0,    18,    19,    20,    21,    22,     0,    23,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,     0,
      31,    32,    33,    34,    35,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,   332,     0,
      38,    24,    25,     0,     0,     0,     0,     0,   964,     0,
      26,    27,     0,    13,     0,     0,     0,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    16,    17,    28,    29,     0,     0,     0,     0,
      18,    19,    20,    21,    22,     0,    23,     0,     0,     0,
       0,     0,     0,     0,     0,    30,     0,     0,    31,    32,
      33,    34,    35,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,   332,     0,    38,    24,
      25,     0,     0,     0,     0,     0,   966,     0,    26,    27,
       0,    13,     0,     0,     0,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      16,    17,    28,    29,     0,     0,     0,     0,    18,    19,
      20,    21,    22,     0,    23,     0,     0,     0,     0,     0,
       0,     0,     0,    30,     0,     0,    31,    32,    33,    34,
      35,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,   332,     0,    38,    24,    25,     0,
       0,     0,     0,     0,   970,     0,    26,    27,     0,    13,
       0,     0,     0,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    16,    17,
      28,    29,     0,     0,     0,     0,    18,    19,    20,    21,
      22,     0,    23,     0,     0,     0,     0,     0,     0,     0,
       0,    30,     0,     0,    31,    32,    33,    34,    35,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,   332,     0,    38,    24,    25,     0,     0,     0,
       0,     0,   972,     0,    26,    27,     0,    13,     0,     0,
       0,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,    28,    29,
       0,     0,     0,     0,    18,    19,    20,    21,    22,     0,
      23,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,     0,    31,    32,    33,    34,    35,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
     332,     0,    38,    24,    25,     0,     0,     0,     0,     0,
     979,     0,    26,    27,     0,    13,     0,     0,     0,    14,
       0,     0,     0,     0,     0,   932,   933,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    28,    29,     0,     0,
       0,     0,    18,    19,    20,    21,    22,     0,    23,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,     0,
      31,    32,    33,    34,    35,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,   332,     0,
      38,    24,    25,     0,   934,     0,     0,     0,   981,     0,
      26,    27,     0,    13,     0,     0,     0,    14,     0,     0,
       0,     0,     0,  1112,  1113,     0,     0,     0,     0,     0,
       0,    15,    16,    17,    28,    29,     0,     0,     0,     0,
      18,    19,    20,    21,    22,     0,    23,     0,     0,     0,
       0,     0,     0,     0,     0,    30,     0,     0,    31,    32,
      33,    34,    35,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,    38,    24,
      25,     0,  1114,     0,     0,     0,     0,     0,    26,    27,
       0,    13,     0,     0,     0,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      16,    17,    28,    29,     0,     0,     0,     0,    18,    19,
      20,    21,    22,   380,    23,     0,     0,     0,     0,     0,
       0,     0,     0,    30,     0,     0,    31,    32,    33,    34,
      35,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,     0,     0,    38,    24,    25,     0,
       0,     0,     0,     0,     0,     0,    26,    27,     0,    13,
       0,     0,     0,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    16,    17,
      28,    29,     0,     0,     0,     0,    18,    19,    20,    21,
      22,   380,    23,     0,     0,     0,     0,     0,     0,     0,
       0,    30,     0,     0,    31,    32,    33,    34,    35,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,   381,     0,    38,    24,    25,     0,     0,     0,
       0,     0,     0,     0,    26,    27,     0,    13,     0,     0,
       0,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,    28,    29,
       0,     0,     0,     0,    18,    19,    20,    21,    22,     0,
      23,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,     0,    31,    32,    33,    34,    35,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,    38,    24,    25,     0,     0,     0,     0,     0,
       0,     0,    26,    27,     0,    13,     0,     0,     0,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   678,
     679,   680,     0,    15,    16,    17,    28,    29,     0,     0,
       0,     0,    18,    19,    20,    21,    22,     0,    23,     0,
     681,   682,   683,     0,     0,     0,     0,    30,     0,   684,
      31,    32,    33,    34,    35,    36,     0,     0,   685,     0,
     686,     0,     0,     0,     0,     0,     0,    37,   332,     0,
      38,    24,    25,     0,     0,     0,   696,   697,     0,     0,
      26,    27,   842,     0,   868,     0,   869,   870,   871,   625,
     609,   626,   610,   611,   612,   989,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,     0,     0,    31,    32,
      33,    34,    35,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,    38,    71,
      72,    73,    74,     0,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,     0,     0,    92,    93,    94,     0,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    97,    98,    99,   100,   101,   102,
       0,     0,   103,   104,   105,   106,   107,   108,   109,     0,
       0,     0,     0,   576,     0,     0,     0,     0,     0,   647,
       0,     0,     0,     0,     0,     0,     0,   577,     0,   110,
     578,   579,   580,   581,     0,   582,   583,   584,   585,     0,
       0,     0,     0,     0,     0,   111,   112,     0,     0,   586,
     587,   588,   589,   590,     0,   648,     0,     0,     0,     0,
       0,     0,     0,   591,   592,   593,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   594,     0,   595,   596,   607,   608,   621,
     622,   623,   624,   576,   625,   609,   626,   610,   611,   612,
       0,     0,     0,     0,     0,     0,     0,   577,   597,     0,
     578,   579,   580,   581,     0,   582,   583,   584,   585,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   586,
     587,   588,   589,   590,     0,   620,     0,     0,     0,     0,
       0,     0,     0,   591,   592,   593,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   594,     0,   595,   596,   607,   608,   621,
     622,   623,   624,   576,   625,   609,   626,   610,   611,   612,
       0,     0,     0,     0,     0,     0,     0,   577,   597,     0,
     578,   579,   580,   581,     0,   582,   583,   584,   585,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   586,
     587,   588,   589,   590,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   591,   592,   593,     0,     0,     0,     0,
       0,     0,     0,   603,     0,   604,   605,   606,     0,     0,
       0,     0,     0,   594,     0,   595,   596,   607,   608,     0,
       0,     0,   576,     0,     0,   609,     0,   610,   611,   612,
       0,     0,     0,     0,     0,     0,   577,     0,   597,   578,
     579,   580,   581,     0,   582,   583,   584,   585,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   586,   587,
     588,   589,   590,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   591,   592,   593,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   594,     0,   595,   596,   576,     0,   621,   622,
     623,   624,     0,   625,   609,   626,   610,   611,   612,     0,
     577,     0,     0,   578,   579,   580,   581,   597,   582,   583,
     584,   585,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   586,   587,   588,   589,   590,     0,     0,     0,
     678,   679,   680,     0,     0,     0,   591,   592,   593,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   681,   682,   683,     0,     0,   594,     0,   595,   596,
     684,   986,     0,     0,     0,     0,     0,     0,     0,   685,
       0,   686,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   597,     0,     0,     0,   677,     0,   696,   697,   678,
     679,   680,     0,   842,     0,   868,     0,   869,   870,   871,
     625,   609,   626,   610,   611,   612,     0,     0,     0,     0,
     681,   682,   683,     0,     0,     0,     0,     0,     0,   684,
       0,     0,     0,     0,     0,     0,     0,     0,   685,     0,
     686,     0,     0,   687,     0,     0,     0,     0,   688,   689,
     690,   691,   692,   693,   694,   695,   696,   697,     0,   698
};

static const yytype_int16 yycheck[] =
{
       1,     2,     3,     4,   665,   507,     7,     8,     9,   936,
     195,   196,   197,   198,   509,   200,   486,   202,   203,   185,
     484,   501,   486,   529,    20,   531,   488,    24,   508,   221,
     510,   223,   224,   482,   219,   186,   498,   490,   544,    24,
     480,   226,   482,   735,   484,   498,   486,   496,   153,    62,
      24,   150,   151,   881,   149,   150,   496,   152,   719,   720,
     721,   134,   135,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   153,   146,    21,    22,     3,     4,     5,     6,
       7,     8,     9,   132,   133,    82,   146,     0,   146,   146,
      37,     3,     4,     5,     6,    25,   156,    82,   156,   156,
     146,   152,   146,    33,    34,    35,    36,   768,    82,   146,
     156,   939,   156,   149,   150,   153,   128,     7,   130,   156,
     156,   134,   135,    11,    12,    13,    14,    15,    16,    17,
      18,    19,   129,   146,    22,    23,   100,   101,   289,  1066,
     146,   147,   847,   848,   129,   615,   142,   143,   153,    37,
     599,   615,    82,   708,   709,   847,   848,   745,   746,   599,
     153,   153,   153,     3,     4,   264,   265,   662,   155,   631,
     100,   155,   155,   100,   155,   615,   656,   178,   179,   180,
     181,   182,    22,   636,   155,   152,   155,   155,   154,  1116,
     652,   152,   193,   194,   700,   142,   143,   155,   199,   652,
     706,   155,   708,   709,   131,   155,   207,   208,   153,   155,
    1137,   717,   213,   214,   215,   155,   155,   155,   155,   131,
     155,   155,   155,    75,    76,    77,    78,    79,    80,    81,
     155,   155,   155,   155,   155,   155,   155,   155,   239,   240,
     241,   242,   152,   154,   708,   709,   247,   248,   155,   155,
     155,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   155,   428,   155,   155,   767,   155,   152,   155,   270,
     271,   272,   273,   155,   155,     5,   155,   278,   279,     9,
     281,   121,   122,   123,   124,   125,   126,   127,   155,   474,
     142,   143,   155,    23,    24,    25,   155,   155,   155,   155,
     155,   155,    32,    33,    34,    35,    36,   155,    38,   155,
     155,   151,   155,   155,   155,   155,   155,   155,   155,   155,
     155,    24,    25,    26,    27,    28,    29,    30,    31,   155,
     155,   155,   155,    36,   155,   155,   155,   155,   155,   155,
     155,    71,    72,   155,   155,   155,   155,    43,    44,    45,
      80,    81,   155,   354,   355,   155,   155,   154,   152,    82,
     153,   146,    65,    66,    67,   146,   146,   146,    64,    65,
      66,   146,   146,   146,   104,   105,   146,    73,   146,   146,
     146,    84,   146,   384,    87,   386,    82,   146,    84,   146,
     146,   146,   393,   146,   146,   125,   156,   155,   128,   129,
     130,   131,   132,   133,   100,   101,   155,   154,   111,   155,
     411,   412,   413,   414,   155,   145,   146,   155,   148,   155,
     123,   155,   154,   154,   144,   154,   156,   155,   429,   155,
     155,   155,     5,   150,   156,   156,     9,   156,   156,   142,
     143,   156,   155,    11,   156,   156,   156,   156,    38,   156,
      23,    24,    25,    43,    44,    45,   156,   156,   156,    32,
      33,    34,    35,    36,   156,    38,   156,   156,   156,   156,
    1131,  1132,   473,   156,    64,    65,    66,   478,   156,   156,
     156,   156,   156,    73,    74,   156,   156,   156,   156,   156,
     156,   156,    82,   156,    84,   156,   156,   156,    71,    72,
     156,   156,   156,   156,   156,   156,   507,    80,    81,   156,
     100,   101,   156,   156,   156,   156,   106,   156,   108,   155,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     155,   104,   105,   154,   152,   568,   156,   156,   154,   156,
     732,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   125,   156,   156,   128,   129,   130,   131,   132,
     133,   156,   156,   156,   749,   750,   751,   752,   753,   570,
     755,   756,   145,   146,   156,   148,    43,    44,    45,   156,
     772,   773,   156,   156,   156,   770,   771,   156,   146,   156,
     775,   155,   777,   785,   786,   780,   155,    64,    65,    66,
     155,   155,   155,   155,   155,   155,    73,   156,   156,   156,
     156,   156,   156,   155,   155,    82,   155,    84,   155,   155,
     155,   155,   155,   155,   155,   155,   155,    94,    95,    96,
     815,   155,   155,   100,   101,   155,   828,   829,    32,   831,
     832,   826,   827,   155,   570,   156,   838,   839,   156,   156,
     835,   155,    46,   155,   155,    49,    50,    51,    52,   155,
      54,    55,    56,    57,   665,   666,   667,   668,   669,   670,
     671,   155,   155,   674,    68,    69,    70,    71,    72,   155,
     155,   155,   155,   155,   155,   155,   155,   155,    82,    83,
      84,   155,   155,   155,   155,   155,   155,   155,    92,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   102,   155,
     104,   105,   155,    43,    44,    45,   155,   718,   719,   720,
     721,   722,   723,   724,   725,   726,   155,   155,   155,   730,
     731,   155,   733,   127,    64,    65,    66,   155,   155,   155,
     155,   155,   155,    73,   156,   156,   747,   156,   156,   156,
     155,   155,    82,   155,    84,   155,   155,   155,   759,   760,
     761,   762,   155,   764,   155,   766,   767,   768,   155,   155,
     100,   101,   155,   155,   155,   155,   106,   155,   155,   155,
     155,   155,   783,   784,   114,   155,   116,   117,   118,   155,
     791,   155,   793,   155,   155,   796,   797,   155,   146,   146,
     985,   802,   152,   155,   155,   146,   155,   146,     5,   146,
     156,   812,     9,   146,   146,   146,   156,   146,   819,  1011,
    1012,  1013,   823,   824,   825,   146,    23,    24,    25,  1014,
     155,   146,   155,   834,   156,    32,    33,    34,    35,    36,
     156,    38,   156,   156,   156,   156,   156,   146,   146,   146,
     146,   146,   146,   146,   155,   117,   156,   370,   636,   251,
     369,   652,   631,   902,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,    71,    72,   156,   156,   156,   880,
     881,   882,   156,    80,    81,   156,   155,   155,   155,   155,
     155,   155,   152,   152,     5,   156,   476,   155,     9,   156,
     156,   902,   156,   156,   156,   156,   156,   104,   105,   156,
     156,   156,    23,    24,    25,   156,   156,   156,   156,   156,
     156,    32,    33,    34,    35,    36,  1111,    38,   125,   156,
     156,   128,   129,   130,   131,   132,   133,   156,   939,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   145,   146,
     156,   148,   156,   156,   156,   156,   156,   156,   959,   156,
      71,    72,   156,   156,   156,   156,   156,   156,   156,    80,
      81,   156,     5,   156,   156,   156,     9,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
      23,    24,    25,   104,   105,   156,   156,   156,   156,    32,
      33,    34,    35,    36,   156,    38,   156,  1008,   156,  1010,
     156,   156,   156,   156,   125,   156,   156,   128,   129,   130,
     131,   132,   133,   156,   155,   152,   156,   156,   156,   155,
     155,   155,   155,   155,   145,   146,   155,   148,    71,    72,
     155,   283,   156,   156,   156,   156,   155,    80,    81,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   644,   700,
     535,   104,   105,   706,   565,   959,   414,   413,   662,   717,
     384,   230,   527,   386,   524,   812,   393,   766,    -1,     5,
     754,    -1,   125,     9,   236,   128,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,
      -1,    -1,   145,   146,    -1,   148,    32,    33,    34,    35,
      36,    -1,    38,   156,    -1,  1126,  1127,  1128,  1129,  1130,
    1131,  1132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    81,    -1,     5,    -1,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,   104,   105,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
      -1,    -1,   128,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,
     146,    -1,   148,    71,    72,    -1,    -1,    -1,    -1,    -1,
     156,    -1,    80,    81,    -1,     5,    -1,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    25,   104,   105,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,
     128,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,   146,    -1,
     148,    71,    72,    -1,    -1,    -1,    -1,    -1,   156,    -1,
      80,    81,    -1,     5,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,   104,   105,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,   128,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   145,   146,    -1,   148,    71,
      72,    -1,    -1,    -1,    -1,    -1,   156,    -1,    80,    81,
      -1,     5,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    25,   104,   105,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   125,    -1,    -1,   128,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   145,   146,    -1,   148,    71,    72,    -1,
      -1,    -1,    -1,    -1,   156,    -1,    80,    81,    -1,     5,
      -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,
     104,   105,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,    -1,    -1,   128,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   145,   146,    -1,   148,    71,    72,    -1,    -1,    -1,
      -1,    -1,   156,    -1,    80,    81,    -1,     5,    -1,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,   104,   105,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
      -1,    -1,   128,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,
     146,    -1,   148,    71,    72,    -1,    -1,    -1,    -1,    -1,
     156,    -1,    80,    81,    -1,     5,    -1,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    25,   104,   105,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,
     128,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,   146,    -1,
     148,    71,    72,    -1,    74,    -1,    -1,    -1,   156,    -1,
      80,    81,    -1,     5,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,   104,   105,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,   128,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   145,    -1,    -1,   148,    71,
      72,    -1,    74,    -1,    -1,    -1,    -1,    -1,    80,    81,
      -1,     5,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    25,   104,   105,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   125,    -1,    -1,   128,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   145,    -1,    -1,   148,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    -1,     5,
      -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,
     104,   105,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,    -1,    -1,   128,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   145,   146,    -1,   148,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    81,    -1,     5,    -1,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,   104,   105,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
      -1,    -1,   128,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,
      -1,    -1,   148,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    81,    -1,     5,    -1,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    -1,    23,    24,    25,   104,   105,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    -1,    38,    -1,
      64,    65,    66,    -1,    -1,    -1,    -1,   125,    -1,    73,
     128,   129,   130,   131,   132,   133,    -1,    -1,    82,    -1,
      84,    -1,    -1,    -1,    -1,    -1,    -1,   145,   146,    -1,
     148,    71,    72,    -1,    -1,    -1,   100,   101,    -1,    -1,
      80,    81,   106,    -1,   108,    -1,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,   128,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   145,    -1,    -1,   148,    40,
      41,    42,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    64,    65,    66,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,    90,
      -1,    -1,    93,    94,    95,    96,    97,    98,    99,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,   120,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,   136,   137,    -1,    -1,    68,
      69,    70,    71,    72,    -1,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    -1,   104,   105,   106,   107,   108,
     109,   110,   111,    32,   113,   114,   115,   116,   117,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,   127,    -1,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    -1,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    -1,   104,   105,   106,   107,   108,
     109,   110,   111,    32,   113,   114,   115,   116,   117,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,   127,    -1,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    94,    95,    96,    -1,    -1,
      -1,    -1,    -1,   102,    -1,   104,   105,   106,   107,    -1,
      -1,    -1,    32,    -1,    -1,   114,    -1,   116,   117,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,   127,    49,
      50,    51,    52,    -1,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,   104,   105,    32,    -1,   108,   109,
     110,   111,    -1,   113,   114,   115,   116,   117,   118,    -1,
      46,    -1,    -1,    49,    50,    51,    52,   127,    54,    55,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      43,    44,    45,    -1,    -1,    -1,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,   102,    -1,   104,   105,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   127,    -1,    -1,    -1,    39,    -1,   100,   101,    43,
      44,    45,    -1,   106,    -1,   108,    -1,   110,   111,   112,
     113,   114,   115,   116,   117,   118,    -1,    -1,    -1,    -1,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      84,    -1,    -1,    87,    -1,    -1,    -1,    -1,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,    -1,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,   100,   131,
     158,   159,   161,     5,     9,    23,    24,    25,    32,    33,
      34,    35,    36,    38,    71,    72,    80,    81,   104,   105,
     125,   128,   129,   130,   131,   132,   133,   145,   148,   162,
     321,   322,   163,   321,   164,   321,   166,   321,   153,   167,
     153,   175,   168,   321,   176,   321,   165,   321,     0,   152,
     153,   153,   153,   153,     3,     4,     5,     6,   131,   169,
     170,    40,    41,    42,    43,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    64,    65,    66,    68,    69,    85,    86,    87,
      88,    89,    90,    93,    94,    95,    96,    97,    98,    99,
     120,   136,   137,   283,   284,   177,   153,   160,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    21,    22,    37,
     142,   143,   182,   183,   184,   185,   191,   213,   220,   223,
       3,     4,    22,   121,   122,   123,   124,   125,   126,   127,
     151,   155,   287,   288,   128,   130,   302,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    22,    23,    37,   231,
     232,   233,   238,   243,   265,   271,   272,   275,   155,   155,
     155,   155,   155,     7,   171,   172,   152,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   154,
     152,   153,   132,   133,   312,   313,   314,   159,   155,   155,
     155,   155,   155,   193,   192,   195,   194,   155,   155,   214,
     154,   152,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   287,   287,   149,   150,   152,   155,   155,   152,
     155,   155,   155,   155,   245,   244,   247,   246,   155,   155,
     155,   155,   154,   152,   321,   321,   321,   321,   321,   153,
      82,   173,   171,   169,   146,   146,   146,   146,   146,   146,
     321,   321,   134,   135,   146,   319,   319,   319,   319,   321,
     319,    62,   319,   320,   319,   319,   146,   146,   146,   321,
     321,   146,   146,   146,   146,   321,   321,   321,   146,   146,
     146,   319,   146,   156,   321,   323,   156,   323,   146,   156,
     156,   323,   156,   323,   146,   156,   319,   146,   146,   283,
     100,   101,   178,   179,   155,   155,   154,   313,   156,   186,
     321,   188,   321,   198,   321,   196,   321,   155,   155,   155,
     155,   224,   321,   221,   321,   155,   182,   321,   321,   321,
      37,   146,   299,   321,   327,   300,   301,   321,   326,   321,
     321,   321,   321,   321,   324,   325,   156,   287,   287,   154,
     303,   304,   154,   234,   321,   239,   321,   250,   321,   248,
     321,   155,   155,   155,   155,   321,   273,   321,   276,   277,
     266,   321,   231,   156,   156,   156,   156,   156,   169,   155,
     154,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   155,   155,   154,   152,   321,   321,   156,
     187,   156,   189,   156,   199,   156,   197,   207,   208,   202,
     203,   207,   202,   156,   225,   156,   222,   215,   216,   293,
     156,   289,   156,   156,   299,   156,   300,   144,   290,   291,
     292,   156,   325,   156,    25,    33,    34,    35,    36,    82,
     100,   307,   308,   309,   310,    11,   305,   306,   156,   235,
     156,   240,   156,   251,   156,   249,   259,   321,   254,   321,
     259,   254,   156,   156,   274,   156,    24,    25,    26,    27,
      28,    29,    30,    31,    36,    65,    66,    67,    84,    87,
     111,   123,   142,   143,   278,   279,   156,   267,   171,   174,
     321,   321,   319,   178,   316,   321,    32,    46,    49,    50,
      51,    52,    54,    55,    56,    57,    68,    69,    70,    71,
      72,    82,    83,    84,   102,   104,   105,   127,   228,   229,
      92,   190,   228,    92,    94,    95,    96,   106,   107,   114,
     116,   117,   118,   180,   200,   201,   212,   229,   200,   156,
      74,   108,   109,   110,   111,   113,   115,   180,   181,   206,
     209,   210,   212,   229,   156,   204,   205,   206,   156,   156,
      20,   142,   143,   226,   227,   228,   156,    38,    74,   206,
     212,   217,   218,    24,    82,   296,   297,   296,   326,   296,
     129,   294,   295,   297,   296,   155,   155,   155,   155,   155,
     155,   155,   156,   309,   155,   156,   305,    39,    43,    44,
      45,    64,    65,    66,    73,    82,    84,    87,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   103,   236,
     237,   281,    94,    95,    96,   241,   242,   281,   252,   252,
     156,   260,   156,   255,   156,   156,   280,   281,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   278,   268,   173,   156,   174,   156,
     156,    24,    82,   129,   317,   318,   315,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   228,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   200,   211,   155,   155,   155,   155,   155,   155,   209,
     204,   155,   226,   155,   219,   217,   155,   155,   156,   296,
     156,   156,   155,   156,   294,   156,   324,   321,   321,   321,
     321,   311,   321,   321,   321,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   236,   155,   155,
     155,   241,   106,   180,   253,   264,   281,   261,   256,   280,
     321,   324,   324,   324,   321,   321,   321,   321,   321,   146,
     146,   146,   321,   321,   323,   321,    38,    74,   108,   110,
     111,   112,   119,   181,   257,   264,   269,   281,   154,   152,
     155,   155,   155,   156,   317,   317,   321,   146,   319,   319,
     319,   319,   319,   320,   319,   319,   146,   146,   321,   321,
     321,   230,   321,   146,   321,   146,   147,   327,   326,   324,
     319,   319,   156,   323,   156,   323,   146,   156,   319,   146,
     319,   146,   146,   319,   155,   321,   321,   323,   323,   146,
     146,   321,    15,    16,    74,   321,   155,   321,   298,   321,
     321,   156,   156,   156,   156,   156,   156,   311,   156,   156,
     319,   146,   146,   146,   321,   146,   146,   146,   282,   321,
     321,   321,   319,   319,   156,   323,   156,   323,   146,   156,
     156,   323,   156,   323,   146,   156,   321,   319,   146,   156,
     323,   156,   323,   146,   156,   155,    74,   257,   262,   119,
     257,   258,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   155,   270,
     155,   155,   155,   155,   155,   152,   321,   298,   321,   152,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   230,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,    75,    76,    77,    78,
      79,    80,    81,   142,   143,   285,   286,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   285,   156,
     156,   298,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   282,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   319,
     263,   155,    15,    16,    74,   321,   155,   321,   323,   323,
     323,   319,   156,   156,   156,   152,   155,   155,   155,   155,
     155,   155,   155,   156,   285,   156,   156,   155,   319,   156,
     156,   156,   156,   285,   156,   156,   156,   156,   156,   321,
     321,   321,   321,   321,   324,   324,   285,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1455 of yacc.c  */
#line 322 "cfg-grammar.y"
    {
            if (last_include_file && !cfg_lex_process_include(last_include_file))
              {
                free(last_include_file);
                last_include_file = NULL;
                YYERROR;
              }
            if (last_include_file)
              {
                free(last_include_file);
                last_include_file = NULL;
              }
          }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 340 "cfg-grammar.y"
    { cfg_add_source(configuration, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 341 "cfg-grammar.y"
    { cfg_add_dest(configuration, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 342 "cfg-grammar.y"
    { cfg_add_connection(configuration, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 343 "cfg-grammar.y"
    { cfg_add_filter(configuration, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 344 "cfg-grammar.y"
    { cfg_add_parser(configuration, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 345 "cfg-grammar.y"
    { cfg_add_rewrite(configuration, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 346 "cfg-grammar.y"
    { cfg_add_template(configuration, (yyvsp[(2) - (2)].ptr)); }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 347 "cfg-grammar.y"
    {  }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 348 "cfg-grammar.y"
    {  }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 352 "cfg-grammar.y"
    { (yyval.ptr) = log_source_group_new((yyvsp[(1) - (4)].cptr), (yyvsp[(3) - (4)].ptr)); free((yyvsp[(1) - (4)].cptr)); }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 356 "cfg-grammar.y"
    { (yyval.ptr) = log_filter_rule_new((yyvsp[(1) - (5)].cptr), (yyvsp[(3) - (5)].node)); free((yyvsp[(1) - (5)].cptr)); }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 360 "cfg-grammar.y"
    { (yyval.ptr) = log_parser_rule_new((yyvsp[(1) - (5)].cptr), (yyvsp[(3) - (5)].ptr)); free((yyvsp[(1) - (5)].cptr)); }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 363 "cfg-grammar.y"
    { (yyval.ptr) = log_rewrite_rule_new((yyvsp[(1) - (4)].cptr), (yyvsp[(3) - (4)].ptr)); free((yyvsp[(1) - (4)].cptr)); }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 366 "cfg-grammar.y"
    { (yyval.ptr) = log_dest_group_new((yyvsp[(1) - (4)].cptr), (yyvsp[(3) - (4)].ptr)); free((yyvsp[(1) - (4)].cptr)); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 370 "cfg-grammar.y"
    { LogPipeItem *pi = log_pipe_item_append_tail((yyvsp[(2) - (5)].ptr), (yyvsp[(3) - (5)].ptr)); (yyval.ptr) = log_connection_new(pi, (yyvsp[(4) - (5)].num)); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 374 "cfg-grammar.y"
    { last_include_file = (yyvsp[(1) - (1)].cptr); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 377 "cfg-grammar.y"
    { log_pipe_item_append((yyvsp[(1) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); (yyval.ptr) = (yyvsp[(1) - (3)].ptr); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 378 "cfg-grammar.y"
    { (yyval.ptr) = NULL; }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 382 "cfg-grammar.y"
    { (yyval.ptr) = log_pipe_item_new(EP_SOURCE, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 383 "cfg-grammar.y"
    { (yyval.ptr) = log_pipe_item_new(EP_FILTER, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 384 "cfg-grammar.y"
    { (yyval.ptr) = log_pipe_item_new(EP_PARSER, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 385 "cfg-grammar.y"
    { (yyval.ptr) = log_pipe_item_new(EP_REWRITE, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 386 "cfg-grammar.y"
    { (yyval.ptr) = log_pipe_item_new(EP_DESTINATION, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 390 "cfg-grammar.y"
    { log_pipe_item_append((yyvsp[(1) - (2)].ptr), (yyvsp[(2) - (2)].ptr)); (yyval.ptr) = (yyvsp[(1) - (2)].ptr); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 391 "cfg-grammar.y"
    { (yyval.ptr) = NULL; }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 395 "cfg-grammar.y"
    { LogPipeItem *pi = log_pipe_item_append_tail((yyvsp[(3) - (7)].ptr), (yyvsp[(4) - (7)].ptr)); (yyval.ptr) = log_pipe_item_new_ref(EP_PIPE, log_connection_new(pi, (yyvsp[(5) - (7)].num))); }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 399 "cfg-grammar.y"
    { (yyval.num) = (yyvsp[(3) - (5)].num); }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 400 "cfg-grammar.y"
    { (yyval.num) = 0; }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 405 "cfg-grammar.y"
    { (yyval.num) = log_connection_lookup_flag((yyvsp[(1) - (2)].cptr)) | (yyvsp[(2) - (2)].num); free((yyvsp[(1) - (2)].cptr)); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 406 "cfg-grammar.y"
    { (yyval.num) = 0; }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 411 "cfg-grammar.y"
    { (yyval.ptr) = NULL; }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 416 "cfg-grammar.y"
    {
	    last_template = log_template_new((yyvsp[(1) - (1)].cptr), NULL);
	    free((yyvsp[(1) - (1)].cptr));
	  }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 420 "cfg-grammar.y"
    { (yyval.ptr) = last_template;  }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 429 "cfg-grammar.y"
    { last_template->template = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); if (!cfg_check_template(last_template)) { YYERROR; } }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 430 "cfg-grammar.y"
    { log_template_set_escape(last_template, (yyvsp[(3) - (4)].num)); }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 434 "cfg-grammar.y"
    { last_sock_options->sndbuf = (yyvsp[(3) - (4)].num); }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 435 "cfg-grammar.y"
    { last_sock_options->rcvbuf = (yyvsp[(3) - (4)].num); }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 436 "cfg-grammar.y"
    { last_sock_options->broadcast = (yyvsp[(3) - (4)].num); }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 437 "cfg-grammar.y"
    { last_sock_options->keepalive = (yyvsp[(3) - (4)].num); }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 442 "cfg-grammar.y"
    { ((InetSocketOptions *) last_sock_options)->ttl = (yyvsp[(3) - (4)].num); }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 443 "cfg-grammar.y"
    { ((InetSocketOptions *) last_sock_options)->tos = (yyvsp[(3) - (4)].num); }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 447 "cfg-grammar.y"
    { if ((yyvsp[(1) - (3)].ptr)) {log_drv_append((yyvsp[(1) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); log_drv_unref((yyvsp[(3) - (3)].ptr)); (yyval.ptr) = (yyvsp[(1) - (3)].ptr); } else { YYERROR; } }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 448 "cfg-grammar.y"
    { (yyval.ptr) = NULL; }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 452 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 453 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 454 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 455 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 456 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 457 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 461 "cfg-grammar.y"
    { (yyval.ptr) = afinter_sd_new(); }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 465 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 466 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 471 "cfg-grammar.y"
    {
	    last_driver = affile_sd_new((yyvsp[(1) - (1)].cptr), 0);
	    free((yyvsp[(1) - (1)].cptr));
	    last_reader_options = &((AFFileSourceDriver *) last_driver)->reader_options;
	  }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 476 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 481 "cfg-grammar.y"
    {
	    last_driver = affile_sd_new((yyvsp[(1) - (1)].cptr), AFFILE_PIPE);
	    free((yyvsp[(1) - (1)].cptr));
	    last_reader_options = &((AFFileSourceDriver *) last_driver)->reader_options;
	  }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 486 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 490 "cfg-grammar.y"
    { last_driver->optional = (yyvsp[(3) - (4)].num); }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 491 "cfg-grammar.y"
    {}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 495 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 496 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 497 "cfg-grammar.y"
    { last_addr_family = AF_INET; }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 497 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(4) - (5)].ptr); }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 498 "cfg-grammar.y"
    { last_addr_family = AF_INET; }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 498 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(4) - (5)].ptr); }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 499 "cfg-grammar.y"
    { last_addr_family = AF_INET6; }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 499 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(4) - (5)].ptr); }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 500 "cfg-grammar.y"
    { last_addr_family = AF_INET6; }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 500 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(4) - (5)].ptr); }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 505 "cfg-grammar.y"
    {
	    last_driver = afunix_sd_new(
		(yyvsp[(1) - (1)].cptr),
		AFSOCKET_DGRAM | AFSOCKET_LOCAL);
	    free((yyvsp[(1) - (1)].cptr));
	    last_reader_options = &((AFSocketSourceDriver *) last_driver)->reader_options;
	    last_sock_options = &((AFUnixSourceDriver *) last_driver)->sock_options;
	  }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 513 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 518 "cfg-grammar.y"
    {
	    last_driver = afunix_sd_new(
		(yyvsp[(1) - (1)].cptr),
		AFSOCKET_STREAM | AFSOCKET_KEEP_ALIVE | AFSOCKET_LOCAL);
	    free((yyvsp[(1) - (1)].cptr));
	    last_reader_options = &((AFSocketSourceDriver *) last_driver)->reader_options;
	    last_sock_options = &((AFUnixSourceDriver *) last_driver)->sock_options;
	  }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 526 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 536 "cfg-grammar.y"
    { afunix_sd_set_uid(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 537 "cfg-grammar.y"
    { afunix_sd_set_uid(last_driver, "-2"); }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 538 "cfg-grammar.y"
    { afunix_sd_set_gid(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 539 "cfg-grammar.y"
    { afunix_sd_set_gid(last_driver, "-2"); }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 540 "cfg-grammar.y"
    { afunix_sd_set_perm(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 541 "cfg-grammar.y"
    { afunix_sd_set_perm(last_driver, -2); }
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 542 "cfg-grammar.y"
    { last_driver->optional = (yyvsp[(3) - (4)].num); }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 543 "cfg-grammar.y"
    {}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 544 "cfg-grammar.y"
    {}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 545 "cfg-grammar.y"
    {}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 550 "cfg-grammar.y"
    {
	    last_driver = afinet_sd_new(last_addr_family,
			NULL, 514,
			AFSOCKET_DGRAM);
	    last_reader_options = &((AFSocketSourceDriver *) last_driver)->reader_options;
	    last_sock_options = &((AFInetSourceDriver *) last_driver)->sock_options.super;
	  }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 557 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 570 "cfg-grammar.y"
    { afinet_sd_set_localip(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 571 "cfg-grammar.y"
    { afinet_sd_set_localip(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 572 "cfg-grammar.y"
    { afinet_sd_set_localport(last_driver, (yyvsp[(3) - (4)].cptr), afinet_sd_get_proto_name(last_driver)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 573 "cfg-grammar.y"
    { afinet_sd_set_localport(last_driver, (yyvsp[(3) - (4)].cptr), afinet_sd_get_proto_name(last_driver)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 580 "cfg-grammar.y"
    {
	    last_driver = afinet_sd_new(last_addr_family,
			NULL, 514,
			AFSOCKET_STREAM);
	    last_reader_options = &((AFSocketSourceDriver *) last_driver)->reader_options;
	    last_sock_options = &((AFInetSourceDriver *) last_driver)->sock_options.super;
	  }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 587 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 599 "cfg-grammar.y"
    {
#if ENABLE_SSL
	    last_tls_context = tls_context_new(TM_SERVER);
#endif
	  }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 605 "cfg-grammar.y"
    {
#if ENABLE_SSL
	    afsocket_sd_set_tls_context(last_driver, last_tls_context);
#endif
          }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 611 "cfg-grammar.y"
    {}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 615 "cfg-grammar.y"
    { afsocket_sd_set_keep_alive(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 616 "cfg-grammar.y"
    { afsocket_sd_set_max_connections(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 620 "cfg-grammar.y"
    { last_addr_family = AF_INET; }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 620 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(4) - (5)].ptr); }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 625 "cfg-grammar.y"
    {
	    last_driver = afinet_sd_new(last_addr_family,
			NULL, 601,
			AFSOCKET_STREAM | AFSOCKET_SYSLOG_PROTOCOL);
	    last_reader_options = &((AFSocketSourceDriver *) last_driver)->reader_options;
	    last_sock_options = &((AFInetSourceDriver *) last_driver)->sock_options.super;
	  }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 632 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 642 "cfg-grammar.y"
    { afinet_sd_set_transport(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 643 "cfg-grammar.y"
    { afinet_sd_set_transport(last_driver, "tcp"); }
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 644 "cfg-grammar.y"
    { afinet_sd_set_transport(last_driver, "udp"); }
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 645 "cfg-grammar.y"
    { afinet_sd_set_transport(last_driver, "tls"); }
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 647 "cfg-grammar.y"
    {
#if ENABLE_SSL
	    last_tls_context = tls_context_new(TM_SERVER);
#endif
	  }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 653 "cfg-grammar.y"
    {
#if ENABLE_SSL
	    afsocket_sd_set_tls_context(last_driver, last_tls_context);
#endif
          }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 658 "cfg-grammar.y"
    {}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 662 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 667 "cfg-grammar.y"
    {
	    last_driver = afprogram_sd_new((yyvsp[(1) - (1)].cptr));
	    free((yyvsp[(1) - (1)].cptr));
	    last_reader_options = &((AFProgramSourceDriver *) last_driver)->reader_options;
	  }
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 672 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 676 "cfg-grammar.y"
    {
#if ENABLE_SUN_STREAMS
}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 679 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 680 "cfg-grammar.y"
    {
#endif
}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 687 "cfg-grammar.y"
    {
#if ENABLE_SUN_STREAMS
	    last_driver = afstreams_sd_new((yyvsp[(1) - (1)].cptr));
	    free((yyvsp[(1) - (1)].cptr));
#endif
	  }
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 693 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 702 "cfg-grammar.y"
    {
#if ENABLE_SUN_STREAMS
}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 705 "cfg-grammar.y"
    { afstreams_sd_set_sundoor(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 706 "cfg-grammar.y"
    {
#endif
}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 717 "cfg-grammar.y"
    { last_reader_options->super.init_window_size = (yyvsp[(3) - (4)].num); }
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 718 "cfg-grammar.y"
    { last_reader_options->super.chain_hostnames = (yyvsp[(3) - (4)].num); }
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 719 "cfg-grammar.y"
    { last_reader_options->super.normalize_hostnames = (yyvsp[(3) - (4)].num); }
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 720 "cfg-grammar.y"
    { last_reader_options->super.keep_hostname = (yyvsp[(3) - (4)].num); }
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 721 "cfg-grammar.y"
    { last_reader_options->super.use_fqdn = (yyvsp[(3) - (4)].num); }
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 722 "cfg-grammar.y"
    { last_reader_options->super.use_dns = (yyvsp[(3) - (4)].num); }
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 723 "cfg-grammar.y"
    { last_reader_options->super.use_dns_cache = (yyvsp[(3) - (4)].num); }
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 724 "cfg-grammar.y"
    { last_reader_options->super.program_override = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 725 "cfg-grammar.y"
    { last_reader_options->super.host_override = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 726 "cfg-grammar.y"
    { gchar *p = strrchr((yyvsp[(3) - (4)].cptr), ':'); if (p) *p = 0; last_reader_options->super.program_override = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 727 "cfg-grammar.y"
    { last_reader_options->recv_time_zone = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 728 "cfg-grammar.y"
    { last_reader_options->check_hostname = (yyvsp[(3) - (4)].num); }
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 729 "cfg-grammar.y"
    { last_reader_options->options = (yyvsp[(3) - (4)].num); }
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 730 "cfg-grammar.y"
    { last_reader_options->msg_size = (yyvsp[(3) - (4)].num); }
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 731 "cfg-grammar.y"
    { last_reader_options->fetch_limit = (yyvsp[(3) - (4)].num); }
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 732 "cfg-grammar.y"
    { last_reader_options->padding = (yyvsp[(3) - (4)].num); }
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 733 "cfg-grammar.y"
    { last_reader_options->follow_freq = (long) ((yyvsp[(3) - (4)].fnum) * 1000); }
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 734 "cfg-grammar.y"
    { last_reader_options->follow_freq = ((yyvsp[(3) - (4)].num) * 1000); }
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 735 "cfg-grammar.y"
    { last_reader_options->super.keep_timestamp = (yyvsp[(3) - (4)].num); }
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 736 "cfg-grammar.y"
    { last_reader_options->text_encoding = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 737 "cfg-grammar.y"
    { log_reader_options_set_tags(last_reader_options, (yyvsp[(3) - (4)].ptr)); }
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 739 "cfg-grammar.y"
    {
	    if (last_reader_options->default_pri == 0xFFFF)
	      last_reader_options->default_pri = LOG_USER;
	    last_reader_options->default_pri = (last_reader_options->default_pri & ~7) | (yyvsp[(3) - (4)].num);
          }
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 745 "cfg-grammar.y"
    {
	    if (last_reader_options->default_pri == 0xFFFF)
	      last_reader_options->default_pri = LOG_NOTICE;
	    last_reader_options->default_pri = (last_reader_options->default_pri & 7) | (yyvsp[(3) - (4)].num);
          }
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 753 "cfg-grammar.y"
    { (yyval.num) = log_reader_options_lookup_flag((yyvsp[(1) - (2)].cptr)) | (yyvsp[(2) - (2)].num); free((yyvsp[(1) - (2)].cptr)); }
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 754 "cfg-grammar.y"
    { (yyval.num) = 0; }
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 759 "cfg-grammar.y"
    { log_drv_append((yyvsp[(1) - (3)].ptr), (yyvsp[(3) - (3)].ptr)); log_drv_unref((yyvsp[(3) - (3)].ptr)); (yyval.ptr) = (yyvsp[(1) - (3)].ptr); }
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 760 "cfg-grammar.y"
    { (yyval.ptr) = NULL; }
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 764 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 765 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 766 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 767 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 768 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 769 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 771 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 776 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 781 "cfg-grammar.y"
    {
	    last_driver = affile_dd_new((yyvsp[(1) - (1)].cptr), 0);
	    free((yyvsp[(1) - (1)].cptr));
	    last_writer_options = &((AFFileDestDriver *) last_driver)->writer_options;
	  }
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 787 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 797 "cfg-grammar.y"
    { last_driver->optional = (yyvsp[(3) - (4)].num); }
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 798 "cfg-grammar.y"
    { affile_dd_set_file_uid(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 799 "cfg-grammar.y"
    { affile_dd_set_file_uid(last_driver, "-2"); }
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 800 "cfg-grammar.y"
    { affile_dd_set_file_gid(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 801 "cfg-grammar.y"
    { affile_dd_set_file_gid(last_driver, "-2"); }
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 802 "cfg-grammar.y"
    { affile_dd_set_file_perm(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 803 "cfg-grammar.y"
    { affile_dd_set_file_perm(last_driver, -2); }
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 804 "cfg-grammar.y"
    { affile_dd_set_dir_uid(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 805 "cfg-grammar.y"
    { affile_dd_set_dir_uid(last_driver, "-2"); }
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 806 "cfg-grammar.y"
    { affile_dd_set_dir_gid(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 807 "cfg-grammar.y"
    { affile_dd_set_dir_gid(last_driver, "-2"); }
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 808 "cfg-grammar.y"
    { affile_dd_set_dir_perm(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 809 "cfg-grammar.y"
    { affile_dd_set_dir_perm(last_driver, -2); }
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 810 "cfg-grammar.y"
    { affile_dd_set_create_dirs(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 811 "cfg-grammar.y"
    { affile_dd_set_overwrite_if_older(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 812 "cfg-grammar.y"
    { affile_dd_set_fsync(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 813 "cfg-grammar.y"
    { affile_dd_set_local_time_zone(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 817 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 822 "cfg-grammar.y"
    {
	    last_driver = affile_dd_new((yyvsp[(1) - (1)].cptr), AFFILE_PIPE);
	    free((yyvsp[(1) - (1)].cptr));
	    last_writer_options = &((AFFileDestDriver *) last_driver)->writer_options;
	    last_writer_options->flush_lines = 0;
	  }
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 828 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 838 "cfg-grammar.y"
    { affile_dd_set_file_uid(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 839 "cfg-grammar.y"
    { affile_dd_set_file_uid(last_driver, "-2"); }
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 840 "cfg-grammar.y"
    { affile_dd_set_file_gid(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 841 "cfg-grammar.y"
    { affile_dd_set_file_gid(last_driver, "-2"); }
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 842 "cfg-grammar.y"
    { affile_dd_set_file_perm(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 843 "cfg-grammar.y"
    { affile_dd_set_file_perm(last_driver, -2); }
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 847 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 848 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 849 "cfg-grammar.y"
    { last_addr_family = AF_INET; }
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 849 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(4) - (5)].ptr); }
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 850 "cfg-grammar.y"
    { last_addr_family = AF_INET; }
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 850 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(4) - (5)].ptr); }
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 851 "cfg-grammar.y"
    { last_addr_family = AF_INET6; }
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 851 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(4) - (5)].ptr); }
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 852 "cfg-grammar.y"
    { last_addr_family = AF_INET6; }
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 852 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(4) - (5)].ptr); }
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 857 "cfg-grammar.y"
    {
	    last_driver = afunix_dd_new((yyvsp[(1) - (1)].cptr), AFSOCKET_DGRAM);
	    free((yyvsp[(1) - (1)].cptr));
	    last_writer_options = &((AFSocketDestDriver *) last_driver)->writer_options;
	    last_sock_options = &((AFUnixDestDriver *) last_driver)->sock_options;
	  }
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 863 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 868 "cfg-grammar.y"
    {
	    last_driver = afunix_dd_new((yyvsp[(1) - (1)].cptr), AFSOCKET_STREAM);
	    free((yyvsp[(1) - (1)].cptr));
	    last_writer_options = &((AFSocketDestDriver *) last_driver)->writer_options;
	    last_sock_options = &((AFUnixDestDriver *) last_driver)->sock_options;
	  }
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 874 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 890 "cfg-grammar.y"
    {
	    last_driver = afinet_dd_new(last_addr_family,
			(yyvsp[(1) - (1)].cptr), 514,
			AFSOCKET_DGRAM);
	    free((yyvsp[(1) - (1)].cptr));
	    last_writer_options = &((AFSocketDestDriver *) last_driver)->writer_options;
	    last_sock_options = &((AFInetDestDriver *) last_driver)->sock_options.super;
	  }
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 898 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 908 "cfg-grammar.y"
    { afinet_dd_set_localip(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 909 "cfg-grammar.y"
    { afinet_dd_set_localport(last_driver, (yyvsp[(3) - (4)].cptr), afinet_dd_get_proto_name(last_driver)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 910 "cfg-grammar.y"
    { afinet_dd_set_destport(last_driver, (yyvsp[(3) - (4)].cptr), afinet_dd_get_proto_name(last_driver)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 911 "cfg-grammar.y"
    { afinet_dd_set_destport(last_driver, (yyvsp[(3) - (4)].cptr), afinet_dd_get_proto_name(last_driver)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 919 "cfg-grammar.y"
    { afinet_dd_set_spoof_source(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 924 "cfg-grammar.y"
    {
	    last_driver = afinet_dd_new(last_addr_family,
			(yyvsp[(1) - (1)].cptr), 514,
			AFSOCKET_STREAM);
	    free((yyvsp[(1) - (1)].cptr));
	    last_writer_options = &((AFSocketDestDriver *) last_driver)->writer_options;
	    last_sock_options = &((AFInetDestDriver *) last_driver)->sock_options.super;
	  }
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 932 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 943 "cfg-grammar.y"
    {
#if ENABLE_SSL
	    last_tls_context = tls_context_new(TM_CLIENT);
#endif
	  }
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 949 "cfg-grammar.y"
    {
#if ENABLE_SSL
	    afsocket_dd_set_tls_context(last_driver, last_tls_context);
#endif
          }
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 957 "cfg-grammar.y"
    { afsocket_dd_set_keep_alive(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 962 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 966 "cfg-grammar.y"
    {
            last_driver = afinet_dd_new(last_addr_family, (yyvsp[(1) - (1)].cptr), 601, AFSOCKET_STREAM | AFSOCKET_SYSLOG_PROTOCOL);
	    last_writer_options = &((AFSocketDestDriver *) last_driver)->writer_options;
	    last_sock_options = &((AFInetDestDriver *) last_driver)->sock_options.super;
	    free((yyvsp[(1) - (1)].cptr));
	  }
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 972 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 983 "cfg-grammar.y"
    { afinet_dd_set_transport(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 984 "cfg-grammar.y"
    { afinet_dd_set_transport(last_driver, "tcp"); }
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 985 "cfg-grammar.y"
    { afinet_dd_set_transport(last_driver, "udp"); }
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 986 "cfg-grammar.y"
    { afinet_dd_set_transport(last_driver, "tls"); }
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 987 "cfg-grammar.y"
    { afinet_dd_set_spoof_source(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 989 "cfg-grammar.y"
    {
#if ENABLE_SSL
	    last_tls_context = tls_context_new(TM_CLIENT);
#endif
	  }
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 995 "cfg-grammar.y"
    {
#if ENABLE_SSL
	    afsocket_dd_set_tls_context(last_driver, last_tls_context);
#endif
          }
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1004 "cfg-grammar.y"
    { (yyval.ptr) = afuser_dd_new((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1008 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1013 "cfg-grammar.y"
    {
	    last_driver = afprogram_dd_new((yyvsp[(1) - (1)].cptr));
	    free((yyvsp[(1) - (1)].cptr));
	    last_writer_options = &((AFProgramDestDriver *) last_driver)->writer_options;
	  }
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1018 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1024 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1029 "cfg-grammar.y"
    {
            #if ENABLE_SQL	
            last_driver = afsql_dd_new();
            #endif /* ENABLE_SQL */
          }
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1034 "cfg-grammar.y"
    { (yyval.ptr) = last_driver; }
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1043 "cfg-grammar.y"
    {
#if ENABLE_SQL
}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1046 "cfg-grammar.y"
    { afsql_dd_set_type(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1047 "cfg-grammar.y"
    { afsql_dd_set_host(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1048 "cfg-grammar.y"
    { afsql_dd_set_port(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1049 "cfg-grammar.y"
    { afsql_dd_set_user(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1050 "cfg-grammar.y"
    { afsql_dd_set_password(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1051 "cfg-grammar.y"
    { afsql_dd_set_database(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1052 "cfg-grammar.y"
    { afsql_dd_set_table(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1053 "cfg-grammar.y"
    { afsql_dd_set_columns(last_driver, (yyvsp[(3) - (4)].ptr)); }
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1054 "cfg-grammar.y"
    { afsql_dd_set_indexes(last_driver, (yyvsp[(3) - (4)].ptr)); }
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1055 "cfg-grammar.y"
    { afsql_dd_set_values(last_driver, (yyvsp[(3) - (4)].ptr)); }
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 1056 "cfg-grammar.y"
    { afsql_dd_set_mem_fifo_size(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1057 "cfg-grammar.y"
    { afsql_dd_set_disk_fifo_size(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1058 "cfg-grammar.y"
    { afsql_dd_set_frac_digits(last_driver, (yyvsp[(3) - (4)].num)); }
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1059 "cfg-grammar.y"
    { afsql_dd_set_send_time_zone(last_driver,(yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 1060 "cfg-grammar.y"
    { afsql_dd_set_local_time_zone(last_driver,(yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 1061 "cfg-grammar.y"
    { afsql_dd_set_null_value(last_driver, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 1063 "cfg-grammar.y"
    {
#endif /* ENABLE_SQL */
}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 1076 "cfg-grammar.y"
    { last_writer_options->options = (yyvsp[(3) - (4)].num); }
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 1077 "cfg-grammar.y"
    { last_writer_options->mem_fifo_size = (yyvsp[(3) - (4)].num); }
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 1078 "cfg-grammar.y"
    { last_writer_options->flush_lines = (yyvsp[(3) - (4)].num); }
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 1079 "cfg-grammar.y"
    { last_writer_options->flush_timeout = (yyvsp[(3) - (4)].num); }
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 1080 "cfg-grammar.y"
    { last_writer_options->suppress = (yyvsp[(3) - (4)].num); }
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 1081 "cfg-grammar.y"
    {
	                                          last_writer_options->template = cfg_check_inline_template(configuration, (yyvsp[(3) - (4)].cptr));
                                                  if (!cfg_check_template(last_writer_options->template))
	                                            {
	                                              YYERROR;
	                                            }
	                                          free((yyvsp[(3) - (4)].cptr));
	                                        }
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 1089 "cfg-grammar.y"
    { log_writer_options_set_template_escape(last_writer_options, (yyvsp[(3) - (4)].num)); }
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 1090 "cfg-grammar.y"
    { last_writer_options->send_time_zone = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 1091 "cfg-grammar.y"
    { last_writer_options->ts_format = cfg_ts_format_value((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 1092 "cfg-grammar.y"
    { last_writer_options->frac_digits = (yyvsp[(3) - (4)].num); }
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 1093 "cfg-grammar.y"
    { last_writer_options->throttle = (yyvsp[(3) - (4)].num); }
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 1097 "cfg-grammar.y"
    { (yyval.num) = log_writer_options_lookup_flag((yyvsp[(1) - (2)].cptr)) | (yyvsp[(2) - (2)].num); free((yyvsp[(1) - (2)].cptr)); }
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 1098 "cfg-grammar.y"
    { (yyval.num) = 0; }
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 1103 "cfg-grammar.y"
    { (yyval.ptr) = (yyvsp[(1) - (3)].ptr); }
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 1104 "cfg-grammar.y"
    { (yyval.ptr) = NULL; }
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 1108 "cfg-grammar.y"
    { configuration->mark_freq = (yyvsp[(3) - (4)].num); }
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 1109 "cfg-grammar.y"
    { configuration->stats_freq = (yyvsp[(3) - (4)].num); }
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 1110 "cfg-grammar.y"
    { configuration->stats_level = (yyvsp[(3) - (4)].num); }
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 1111 "cfg-grammar.y"
    { configuration->flush_lines = (yyvsp[(3) - (4)].num); }
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 1112 "cfg-grammar.y"
    { configuration->flush_timeout = (yyvsp[(3) - (4)].num); }
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 1113 "cfg-grammar.y"
    { configuration->chain_hostnames = (yyvsp[(3) - (4)].num); }
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 1114 "cfg-grammar.y"
    { configuration->normalize_hostnames = (yyvsp[(3) - (4)].num); }
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 1115 "cfg-grammar.y"
    { configuration->keep_hostname = (yyvsp[(3) - (4)].num); }
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 1116 "cfg-grammar.y"
    { configuration->check_hostname = (yyvsp[(3) - (4)].num); }
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 1117 "cfg-grammar.y"
    { cfg_bad_hostname_set(configuration, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 1118 "cfg-grammar.y"
    { configuration->use_time_recvd = (yyvsp[(3) - (4)].num); }
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 1119 "cfg-grammar.y"
    { configuration->use_fqdn = (yyvsp[(3) - (4)].num); }
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 1120 "cfg-grammar.y"
    { configuration->use_dns = (yyvsp[(3) - (4)].num); }
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 1121 "cfg-grammar.y"
    { configuration->time_reopen = (yyvsp[(3) - (4)].num); }
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 1122 "cfg-grammar.y"
    { configuration->time_reap = (yyvsp[(3) - (4)].num); }
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 1124 "cfg-grammar.y"
    {
		  configuration->time_sleep = (yyvsp[(3) - (4)].num);
		  if ((yyvsp[(3) - (4)].num) > 500)
		    {
		      msg_notice("The value specified for time_sleep is too large", evt_tag_int("time_sleep", (yyvsp[(3) - (4)].num)), NULL);
		      configuration->time_sleep = 500;
		    }
		}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 1132 "cfg-grammar.y"
    { configuration->log_fifo_size = (yyvsp[(3) - (4)].num); }
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 1133 "cfg-grammar.y"
    { configuration->log_iw_size = (yyvsp[(3) - (4)].num); }
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 1134 "cfg-grammar.y"
    { configuration->log_fetch_limit = (yyvsp[(3) - (4)].num); }
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 1135 "cfg-grammar.y"
    { configuration->log_msg_size = (yyvsp[(3) - (4)].num); }
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 1136 "cfg-grammar.y"
    { configuration->keep_timestamp = (yyvsp[(3) - (4)].num); }
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 1137 "cfg-grammar.y"
    { configuration->ts_format = cfg_ts_format_value((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 1138 "cfg-grammar.y"
    { configuration->frac_digits = (yyvsp[(3) - (4)].num); }
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 1139 "cfg-grammar.y"
    { /* ignored */; }
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 1140 "cfg-grammar.y"
    { /* ignored */; }
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 1141 "cfg-grammar.y"
    { configuration->create_dirs = (yyvsp[(3) - (4)].num); }
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 1142 "cfg-grammar.y"
    { cfg_file_owner_set(configuration, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 1143 "cfg-grammar.y"
    { cfg_file_owner_set(configuration, "-2"); }
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 1144 "cfg-grammar.y"
    { cfg_file_group_set(configuration, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 1145 "cfg-grammar.y"
    { cfg_file_group_set(configuration, "-2"); }
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 1146 "cfg-grammar.y"
    { cfg_file_perm_set(configuration, (yyvsp[(3) - (4)].num)); }
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 1147 "cfg-grammar.y"
    { cfg_file_perm_set(configuration, -2); }
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 1148 "cfg-grammar.y"
    { cfg_dir_owner_set(configuration, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 1149 "cfg-grammar.y"
    { cfg_dir_owner_set(configuration, "-2"); }
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 1150 "cfg-grammar.y"
    { cfg_dir_group_set(configuration, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 1151 "cfg-grammar.y"
    { cfg_dir_group_set(configuration, "-2"); }
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 1152 "cfg-grammar.y"
    { cfg_dir_perm_set(configuration, (yyvsp[(3) - (4)].num)); }
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 1153 "cfg-grammar.y"
    { cfg_dir_perm_set(configuration, -2); }
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 1154 "cfg-grammar.y"
    { configuration->use_dns_cache = (yyvsp[(3) - (4)].num); }
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 1155 "cfg-grammar.y"
    { configuration->dns_cache_size = (yyvsp[(3) - (4)].num); }
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 1156 "cfg-grammar.y"
    { configuration->dns_cache_expire = (yyvsp[(3) - (4)].num); }
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 1158 "cfg-grammar.y"
    { configuration->dns_cache_expire_failed = (yyvsp[(3) - (4)].num); }
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 1159 "cfg-grammar.y"
    { configuration->dns_cache_hosts = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 1160 "cfg-grammar.y"
    { configuration->file_template_name = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 1161 "cfg-grammar.y"
    { configuration->proto_template_name = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 1162 "cfg-grammar.y"
    { configuration->recv_time_zone = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 1163 "cfg-grammar.y"
    { configuration->send_time_zone = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 1164 "cfg-grammar.y"
    { configuration->local_time_zone = g_strdup((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 1174 "cfg-grammar.y"
    {
#if ENABLE_SSL
}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 1179 "cfg-grammar.y"
    {
	    last_tls_context->verify_mode = tls_lookup_verify_mode((yyvsp[(3) - (4)].cptr));
            free((yyvsp[(3) - (4)].cptr));
          }
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 1184 "cfg-grammar.y"
    {
	    last_tls_context->key_file = g_strdup((yyvsp[(3) - (4)].cptr));
            free((yyvsp[(3) - (4)].cptr));
          }
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 1189 "cfg-grammar.y"
    {
	    last_tls_context->cert_file = g_strdup((yyvsp[(3) - (4)].cptr));
            free((yyvsp[(3) - (4)].cptr));
          }
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 1194 "cfg-grammar.y"
    {
	    last_tls_context->ca_dir = g_strdup((yyvsp[(3) - (4)].cptr));
            free((yyvsp[(3) - (4)].cptr));
          }
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 1199 "cfg-grammar.y"
    {
	    last_tls_context->crl_dir = g_strdup((yyvsp[(3) - (4)].cptr));
            free((yyvsp[(3) - (4)].cptr));
          }
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 1204 "cfg-grammar.y"
    {
            tls_session_set_trusted_fingerprints(last_tls_context, (yyvsp[(3) - (4)].ptr));
          }
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 1208 "cfg-grammar.y"
    {
            tls_session_set_trusted_dn(last_tls_context, (yyvsp[(3) - (4)].ptr));
          }
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 1211 "cfg-grammar.y"
    {
#endif
}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 1219 "cfg-grammar.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); if (!(yyvsp[(1) - (1)].node)) return 1; }
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 1220 "cfg-grammar.y"
    { (yyvsp[(2) - (2)].node)->comp = !((yyvsp[(2) - (2)].node)->comp); (yyval.node) = (yyvsp[(2) - (2)].node); }
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 1221 "cfg-grammar.y"
    { (yyval.node) = fop_or_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 1222 "cfg-grammar.y"
    { (yyval.node) = fop_and_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 1223 "cfg-grammar.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 1227 "cfg-grammar.y"
    { (yyval.node) = filter_facility_new((yyvsp[(3) - (4)].num));  }
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 1228 "cfg-grammar.y"
    { (yyval.node) = filter_facility_new(0x80000000 | (yyvsp[(3) - (4)].num)); }
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 1229 "cfg-grammar.y"
    { (yyval.node) = filter_level_new((yyvsp[(3) - (4)].num)); }
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 1230 "cfg-grammar.y"
    { (yyval.node) = filter_call_new((yyvsp[(3) - (4)].cptr), configuration); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 1231 "cfg-grammar.y"
    { (yyval.node) = filter_netmask_new((yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 1232 "cfg-grammar.y"
    { (yyval.node) = filter_tags_new((yyvsp[(3) - (4)].ptr)); }
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 1234 "cfg-grammar.y"
    {
	    last_re_filter = (FilterRE *) filter_re_new(LM_V_PROGRAM);
          }
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 1238 "cfg-grammar.y"
    {
            if(!filter_re_set_regexp(last_re_filter, (yyvsp[(3) - (6)].cptr)))
              YYERROR;
            free((yyvsp[(3) - (6)].cptr));

            (yyval.node) = &last_re_filter->super;
          }
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 1246 "cfg-grammar.y"
    {
	    last_re_filter = (FilterRE *) filter_re_new(LM_V_HOST);
          }
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 1250 "cfg-grammar.y"
    {
            if(!filter_re_set_regexp(last_re_filter, (yyvsp[(3) - (6)].cptr)))
              YYERROR;
            free((yyvsp[(3) - (6)].cptr));

            (yyval.node) = &last_re_filter->super;
          }
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 1258 "cfg-grammar.y"
    {
	    last_re_filter = (FilterRE *) filter_match_new();
	  }
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 1262 "cfg-grammar.y"
    {
            if(!filter_re_set_regexp(last_re_filter, (yyvsp[(3) - (6)].cptr)))
              YYERROR;
            free((yyvsp[(3) - (6)].cptr));
            (yyval.node) = &last_re_filter->super;

            if (last_re_filter->value_handle == 0)
              {
                static gboolean warn_written = FALSE;

                if (!warn_written)
                  {
                    msg_warning("WARNING: the match() filter without the use of the value() option is deprecated and hinders performance, please update your configuration",
                                NULL);
                    warn_written = TRUE;
                  }
              }
          }
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 1281 "cfg-grammar.y"
    {
	    last_re_filter = (FilterRE *) filter_re_new(LM_V_MESSAGE);
          }
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 1285 "cfg-grammar.y"
    {
            if(!filter_re_set_regexp(last_re_filter, (yyvsp[(3) - (6)].cptr)))
              YYERROR;
	    free((yyvsp[(3) - (6)].cptr));
            (yyval.node) = &last_re_filter->super;
          }
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 1292 "cfg-grammar.y"
    {
	    last_re_filter = (FilterRE *) filter_re_new(LM_V_SOURCE);
            filter_re_set_matcher(last_re_filter, log_matcher_string_new());
          }
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 1297 "cfg-grammar.y"
    {
            if(!filter_re_set_regexp(last_re_filter, (yyvsp[(3) - (6)].cptr)))
              YYERROR;
	    free((yyvsp[(3) - (6)].cptr));
            (yyval.node) = &last_re_filter->super;
          }
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 1313 "cfg-grammar.y"
    {
            const gchar *p = (yyvsp[(3) - (4)].cptr);
            if (p[0] == '$')
              {
                msg_warning("Value references in filters should not use the '$' prefix, those are only needed in templates",
                            evt_tag_str("value", (yyvsp[(3) - (4)].cptr)),
                            NULL);
                p++;
              }
            last_re_filter->value_handle = log_msg_get_value_handle(p);
            free((yyvsp[(3) - (4)].cptr));
          }
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 1334 "cfg-grammar.y"
    {
            filter_re_set_matcher(last_re_filter, log_matcher_new((yyvsp[(3) - (4)].cptr)));
            free((yyvsp[(3) - (4)].cptr));
          }
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 1338 "cfg-grammar.y"
    { filter_re_set_flags(last_re_filter, (yyvsp[(3) - (4)].num)); }
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 1342 "cfg-grammar.y"
    { (yyval.num) = log_matcher_lookup_flag((yyvsp[(1) - (2)].cptr)) | (yyvsp[(2) - (2)].num); free((yyvsp[(1) - (2)].cptr)); }
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 1343 "cfg-grammar.y"
    { (yyval.num) = 0; }
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 1348 "cfg-grammar.y"
    { (yyval.num) = (1 << ((yyvsp[(1) - (2)].num) >> 3)) | (yyvsp[(2) - (2)].num); }
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 1349 "cfg-grammar.y"
    { (yyval.num) = (1 << ((yyvsp[(1) - (1)].num) >> 3)); }
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 1353 "cfg-grammar.y"
    { (yyval.num) = (yyvsp[(1) - (2)].num) | (yyvsp[(2) - (2)].num); }
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 1354 "cfg-grammar.y"
    { (yyval.num) = (yyvsp[(1) - (1)].num); }
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 1359 "cfg-grammar.y"
    {
	    (yyval.num) = syslog_make_range((yyvsp[(1) - (3)].num), (yyvsp[(3) - (3)].num));
	  }
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 1363 "cfg-grammar.y"
    {
	    (yyval.num) = 1 << (yyvsp[(1) - (1)].num);
	  }
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 1371 "cfg-grammar.y"
    {
            last_parser = (LogParser *) log_csv_parser_new();
          }
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 1375 "cfg-grammar.y"
    { (yyval.ptr) = last_parser; }
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 1377 "cfg-grammar.y"
    {
            last_parser = (LogParser *) log_db_parser_new();
          }
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 1381 "cfg-grammar.y"
    { (yyval.ptr) = last_parser; }
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 1391 "cfg-grammar.y"
    { log_db_parser_set_db_file(((LogDBParser *) last_parser), (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 1396 "cfg-grammar.y"
    { log_column_parser_set_columns((LogColumnParser *) last_parser, (yyvsp[(3) - (4)].ptr)); }
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 1400 "cfg-grammar.y"
    {
                                                  LogTemplate *template = cfg_check_inline_template(configuration, (yyvsp[(3) - (4)].cptr));
                                                  if (!cfg_check_template(template))
                                                    {
                                                      YYERROR;
                                                    }
                                                  log_parser_set_template(last_parser, template);
                                                  free((yyvsp[(3) - (4)].cptr));
                                                }
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 1419 "cfg-grammar.y"
    { log_csv_parser_set_flags((LogColumnParser *) last_parser, (yyvsp[(3) - (4)].num)); }
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 1420 "cfg-grammar.y"
    { log_csv_parser_set_delimiters((LogColumnParser *) last_parser, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 1421 "cfg-grammar.y"
    { log_csv_parser_set_quotes((LogColumnParser *) last_parser, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 1422 "cfg-grammar.y"
    { log_csv_parser_set_quote_pairs((LogColumnParser *) last_parser, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 1423 "cfg-grammar.y"
    { log_csv_parser_set_null_value((LogColumnParser *) last_parser, (yyvsp[(3) - (4)].cptr)); free((yyvsp[(3) - (4)].cptr)); }
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 1427 "cfg-grammar.y"
    { (yyval.num) = log_csv_parser_lookup_flag((yyvsp[(1) - (2)].cptr)) | (yyvsp[(2) - (2)].num); free((yyvsp[(1) - (2)].cptr)); }
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 1428 "cfg-grammar.y"
    { (yyval.num) = 0; }
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 1432 "cfg-grammar.y"
    { (yyval.ptr) = g_list_reverse((yyvsp[(1) - (1)].ptr)); }
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 1436 "cfg-grammar.y"
    { (yyval.ptr) = g_list_append((yyvsp[(2) - (2)].ptr), (yyvsp[(1) - (2)].ptr)); }
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 1437 "cfg-grammar.y"
    { (yyval.ptr) = NULL; }
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 1442 "cfg-grammar.y"
    {
            last_rewrite = log_rewrite_subst_new((yyvsp[(4) - (4)].cptr));
            free((yyvsp[(4) - (4)].cptr));
          }
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 1447 "cfg-grammar.y"
    {
            if(!log_rewrite_set_regexp(last_rewrite, (yyvsp[(3) - (8)].cptr)))
              YYERROR;
            free((yyvsp[(3) - (8)].cptr));
            (yyval.ptr) = last_rewrite;
          }
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 1454 "cfg-grammar.y"
    {
            last_rewrite = log_rewrite_set_new((yyvsp[(3) - (3)].cptr));
            free((yyvsp[(3) - (3)].cptr));
          }
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 1458 "cfg-grammar.y"
    { (yyval.ptr) = last_rewrite; }
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 1468 "cfg-grammar.y"
    {
            const gchar *p = (yyvsp[(3) - (4)].cptr);
            if (p[0] == '$')
              {
                msg_warning("Value references in rewrite rules should not use the '$' prefix, those are only needed in templates",
                            evt_tag_str("value", (yyvsp[(3) - (4)].cptr)),
                            NULL);
                p++;
              }
            last_rewrite->value_handle = log_msg_get_value_handle(p);
            if (log_msg_is_handle_macro(last_rewrite->value_handle))
              {
                msg_warning("Macros are read-only, they cannot be changed in rewrite rules, falling back to MESSAGE instead",
                            evt_tag_str("macro", p),
                            NULL);
                last_rewrite->value_handle = LM_V_MESSAGE;
              }
            free((yyvsp[(3) - (4)].cptr));
          }
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 1488 "cfg-grammar.y"
    {
            if (strcmp((yyvsp[(3) - (4)].cptr), "glob") == 0)
              {
                msg_error("Rewrite rules do not support glob expressions",
                          NULL);
                YYERROR;
              }
            log_rewrite_set_matcher(last_rewrite, log_matcher_new((yyvsp[(3) - (4)].cptr)));
            free((yyvsp[(3) - (4)].cptr));
          }
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 1498 "cfg-grammar.y"
    { log_rewrite_set_flags(last_rewrite, (yyvsp[(3) - (4)].num)); }
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 1502 "cfg-grammar.y"
    { (yyval.num) = 1; }
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 1503 "cfg-grammar.y"
    { (yyval.num) = 0; }
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 1504 "cfg-grammar.y"
    { (yyval.num) = (yyvsp[(1) - (1)].num); }
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 1508 "cfg-grammar.y"
    { (yyval.num) = (yyvsp[(1) - (1)].num); }
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 1509 "cfg-grammar.y"
    { (yyval.num) = 2; }
    break;

  case 444:

/* Line 1455 of yacc.c  */
#line 1515 "cfg-grammar.y"
    { (yyval.cptr) = cfg_lex_get_keyword_string((yyvsp[(1) - (1)].token)); }
    break;

  case 469:

/* Line 1455 of yacc.c  */
#line 1547 "cfg-grammar.y"
    { (yyval.cptr) = (yyvsp[(1) - (1)].cptr); }
    break;

  case 470:

/* Line 1455 of yacc.c  */
#line 1548 "cfg-grammar.y"
    { char buf[32]; snprintf(buf, sizeof(buf), "%" G_GINT64_FORMAT, (yyvsp[(1) - (1)].num)); (yyval.cptr) = strdup(buf); }
    break;

  case 471:

/* Line 1455 of yacc.c  */
#line 1552 "cfg-grammar.y"
    { (yyval.ptr) = g_list_reverse((yyvsp[(1) - (1)].ptr)); }
    break;

  case 472:

/* Line 1455 of yacc.c  */
#line 1556 "cfg-grammar.y"
    { (yyval.ptr) = g_list_append((yyvsp[(2) - (2)].ptr), g_strdup((yyvsp[(1) - (2)].cptr))); free((yyvsp[(1) - (2)].cptr)); }
    break;

  case 473:

/* Line 1455 of yacc.c  */
#line 1557 "cfg-grammar.y"
    { (yyval.ptr) = NULL; }
    break;

  case 474:

/* Line 1455 of yacc.c  */
#line 1562 "cfg-grammar.y"
    {
	    /* return the numeric value of the "level" */
	    int n = syslog_name_lookup_level_by_name((yyvsp[(1) - (1)].cptr));
	    if (n == -1)
	      {
	        msg_error("Unknown priority level",
                          evt_tag_str("priority", (yyvsp[(1) - (1)].cptr)),
                          NULL);
	        YYERROR;
	      }
	    free((yyvsp[(1) - (1)].cptr));
            (yyval.num) = n;
	  }
    break;

  case 475:

/* Line 1455 of yacc.c  */
#line 1579 "cfg-grammar.y"
    {
            /* return the numeric value of facility */
	    int n = syslog_name_lookup_facility_by_name((yyvsp[(1) - (1)].cptr));
	    if (n == -1)
	      {
	        msg_error("Unknown facility",
	                  evt_tag_str("facility", (yyvsp[(1) - (1)].cptr)),
	                  NULL);
                YYERROR;
	      }
	    free((yyvsp[(1) - (1)].cptr));
	    (yyval.num) = n;
	  }
    break;

  case 476:

/* Line 1455 of yacc.c  */
#line 1592 "cfg-grammar.y"
    { (yyval.num) = LOG_SYSLOG; }
    break;



/* Line 1455 of yacc.c  */
#line 6130 "cfg-grammar.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1596 "cfg-grammar.y"


extern int linenum;

void
yyerror(char *msg)
{
  fprintf(stderr, "%s in %s at line %d.\n\n"
                  "syslog-ng documentation: http://www.balabit.com/support/documentation/?product=syslog-ng\n"
                  "mailing list: https://lists.balabit.hu/mailman/listinfo/syslog-ng\n", msg, cfg_lex_get_current_file(), cfg_lex_get_current_lineno());
}


