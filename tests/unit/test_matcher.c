#include "logmatcher.h"
#include "apphook.h"

#include <stdlib.h>
#include <string.h>

int
testcase_match(const gchar *log, gint parse_flags, const gchar *pattern, gint matcher_flags, gboolean expected_result, LogMatcher *m)
{
  LogMessage *msg;
  gboolean result;
  gchar buf[1024];
  NVHandle nonasciiz = log_msg_get_value_handle("NON-ASCIIZ");
  gssize msglen;

  msg = log_msg_new(log, strlen(log), g_sockaddr_inet_new("10.10.10.10", 1010), parse_flags, NULL, -1, 0xFFFF);

  g_snprintf(buf, sizeof(buf), "%sAAAAAAAAAAAA", log_msg_get_value(msg, LM_V_MESSAGE, &msglen));
  log_msg_set_value(msg, log_msg_get_value_handle("MESSAGE2"), buf, -1);

  /* add a non-zero terminated indirect value which contains the whole message */
  log_msg_set_value_indirect(msg, nonasciiz, log_msg_get_value_handle("MESSAGE2"), 0, 0, msglen);
  log_matcher_set_flags(m, matcher_flags);

  log_matcher_compile(m, pattern);

  result = log_matcher_match(m, msg, nonasciiz, log_msg_get_value(msg, nonasciiz, &msglen), msglen);

  if (result != expected_result)
    {
      fprintf(stderr, "Testcase match failure. pattern=%s, result=%d, expected=%d\n", pattern, result, expected_result);
      exit(1);
    }

  log_matcher_free(m);
  log_msg_unref(msg);
  return 0;
}

int
testcase_replace(const gchar *log, gint parse_flags, const gchar *re, gchar *replacement, const gchar *expected_result, const gint matcher_flags, LogMatcher *m)
{
  LogMessage *msg;
  LogTemplate *r;
  gchar *result;
  gssize length;
  gchar buf[1024];
  gssize msglen;
  NVHandle nonasciiz = log_msg_get_value_handle("NON-ASCIIZ");
  const gchar *msgbuf;

  msg = log_msg_new(log, strlen(log), g_sockaddr_inet_new("10.10.10.10", 1010), parse_flags, NULL, -1, 0xFFFF);

  /* NOTE: we test how our matchers cope with non-zero terminated values. We don't change message_len, only the value */

  g_snprintf(buf, sizeof(buf), "%sAAAAAAAAAAAA", log_msg_get_value(msg, LM_V_MESSAGE, &msglen));
  log_msg_set_value(msg, log_msg_get_value_handle("MESSAGE2"), buf, -1);

  /* add a non-zero terminated indirect value which contains the whole message */
  log_msg_set_value_indirect(msg, nonasciiz, log_msg_get_value_handle("MESSAGE2"), 0, 0, msglen);

  log_matcher_set_flags(m, matcher_flags);

  log_matcher_compile(m, re);

  r = log_template_new(NULL, replacement);

  result = log_matcher_replace(m, msg, nonasciiz, log_msg_get_value(msg, nonasciiz, &msglen), msglen, r, &length);
  msgbuf = log_msg_get_value(msg, nonasciiz, &msglen);

  if (strncmp(result ? result : msgbuf, expected_result, result ? length : msglen) != 0)
    {
      fprintf(stderr, "Testcase failure. pattern=%s, result=%.*s, expected=%s\n", re, (gint) length, result ? result : msgbuf, expected_result);
      exit(1);
    }

  g_free(result);

  log_template_unref(r);
  log_matcher_free(m);
  log_msg_unref(msg);
  return 0;
}

int
main()
{
  app_startup();

  /* POSIX regexp */
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "árvíz", "favíz", "favíztűrőtükörfúrógép", 0, log_matcher_posix_re_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "^tűrő", "faró", "árvíztűrőtükörfúrógép", 0, log_matcher_posix_re_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "tűrő", "", "árvíztükörfúrógép", 0, log_matcher_posix_re_new());
  /* back references are not portable, they work only on Linux */
#if __linux__
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: wikiwiki", 0, "(wiki)\\1", "", "", LMF_STORE_MATCHES, log_matcher_posix_re_new());
#endif
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: wikiwiki", 0, "wi", "", "kiki", LMF_GLOBAL, log_matcher_posix_re_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: wikiwiki", 0, "wi", "kuku", "kukukikukuki", LMF_GLOBAL, log_matcher_posix_re_new());

  /* empty match with global flag*/
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: aa bb", 0, "c*", "#", "#a#a# #b#b#", LMF_GLOBAL, log_matcher_posix_re_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: aa bb", 0, "a*", "#", "# #b#b#", LMF_GLOBAL, log_matcher_posix_re_new());

  /* string match */

  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "árvíz", "favíz", "favíztűrőtükörfúrógép", LMF_PREFIX, log_matcher_string_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "tűrő", "faró", "árvízfarótükörfúrógép", LMF_SUBSTRING, log_matcher_string_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "tűrő", "", "árvíztükörfúrógép", LMF_SUBSTRING, log_matcher_string_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "árvíztűrőtükörfúrógép", "almafa", "almafa", 0, log_matcher_string_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: ", 0, "valami-amivel-nem-szabadna-matchelni", "almafa", "", 0, log_matcher_string_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: val", 0, "valami-amivel-nem-szabadna-matchelni", 0, FALSE, log_matcher_string_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: ", 0, "valami-amivel-nem-szabadna-matchelni", 0, FALSE, log_matcher_string_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: ", 0, "valami-amivel-nem-szabadna-matchelni", LMF_PREFIX, 0, log_matcher_string_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: ", 0, "valami-amivel-nem-szabadna-matchelni", LMF_SUBSTRING, 0, log_matcher_string_new());

  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: match", 0, "match", 0, TRUE, log_matcher_string_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: match", 0, "ma", LMF_PREFIX, TRUE, log_matcher_string_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: match", 0, "tch", LMF_SUBSTRING, TRUE, log_matcher_string_new());

  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: abcdef", 0, "ABCDEF", "qwerty", "qwerty", LMF_PREFIX | LMF_ICASE, log_matcher_string_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: abcdef", 0, "BCD", "qwerty", "aqwertyef", LMF_SUBSTRING | LMF_ICASE, log_matcher_string_new());

  /* glob match */

  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "árvíz*", 0, TRUE, log_matcher_glob_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "*fúrógép", 0, TRUE, log_matcher_glob_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "*fúró*", 0, TRUE, log_matcher_glob_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "tükör", 0, FALSE, log_matcher_glob_new());
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "viziló", 0, FALSE, log_matcher_glob_new());

  /* match in iso-8859-2 never matches */
  testcase_match("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: \xe1rv\xedzt\xfbr\xf5t\xfck\xf6rf\xfar\xf3g\xe9p", 0, "\xe1rv\xed*", 0, FALSE, log_matcher_glob_new());


#if ENABLE_PCRE
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "árvíz", "favíz", "favíztűrőtükörfúrógép", 0, log_matcher_pcre_re_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "^tűrő", "faró", "árvíztűrőtükörfúrógép", 0, log_matcher_pcre_re_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: árvíztűrőtükörfúrógép", 0, "tűrő", "", "árvíztükörfúrógép", 0, log_matcher_pcre_re_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: wikiwiki", 0, "(wiki)\\1", "", "", 0, log_matcher_pcre_re_new());
  /* back ref with perl style $1 */
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: wikiwiki", 0, "(wiki).+", "#$1#", "#wiki#", 0, log_matcher_pcre_re_new());

  /* empty match with global flag*/
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: aa bb", 0, "c*", "#", "#a#a# #b#b#", LMF_GLOBAL, log_matcher_pcre_re_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: aa bb", 0, "a*", "?", "?? ?b?b?", LMF_GLOBAL, log_matcher_pcre_re_new());

  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: wikiwiki", 0, "wi", "", "kiki", LMF_GLOBAL, log_matcher_pcre_re_new());
  testcase_replace("<155>2006-02-11T10:34:56+01:00 bzorp syslog-ng[23323]: wikiwiki", 0, "wi", "kuku", "kukukikukuki", LMF_GLOBAL, log_matcher_pcre_re_new());
#endif

  return 0;
}
