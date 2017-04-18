/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_syslog_ng_InternalMessageSender */

#ifndef _Included_org_syslog_ng_InternalMessageSender
#define _Included_org_syslog_ng_InternalMessageSender
#ifdef __cplusplus
extern "C" {
#endif
#undef org_syslog_ng_InternalMessageSender_MsgFatal
#define org_syslog_ng_InternalMessageSender_MsgFatal 2L
#undef org_syslog_ng_InternalMessageSender_MsgError
#define org_syslog_ng_InternalMessageSender_MsgError 3L
#undef org_syslog_ng_InternalMessageSender_MsgWarning
#define org_syslog_ng_InternalMessageSender_MsgWarning 4L
#undef org_syslog_ng_InternalMessageSender_MsgNotice
#define org_syslog_ng_InternalMessageSender_MsgNotice 5L
#undef org_syslog_ng_InternalMessageSender_MsgInfo
#define org_syslog_ng_InternalMessageSender_MsgInfo 6L
#undef org_syslog_ng_InternalMessageSender_MsgDebug
#define org_syslog_ng_InternalMessageSender_MsgDebug 7L
/*
 * Class:     org_syslog_ng_InternalMessageSender
 * Method:    createInternalMessage
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_syslog_1ng_InternalMessageSender_createInternalMessage
  (JNIEnv *, jclass, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif