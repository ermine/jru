#ifndef _EXTENSIONS_H_
#define _EXTENSIONS_H_

enum extension_type {
  EXTENSION_TYPE_IQLAST_LAST,
  EXTENSION_TYPE_MOOD_MOOD,
  EXTENSION_TYPE_VCARD_VCARD,
  EXTENSION_TYPE_VCARD_N,
  EXTENSION_TYPE_VCARD_NICKNAME,
  EXTENSION_TYPE_VCARD_PHOTO,
  EXTENSION_TYPE_VCARD_BDAY,
  EXTENSION_TYPE_VCARD_ADR,
  EXTENSION_TYPE_VCARD_LABEL,
  EXTENSION_TYPE_VCARD_TEL,
  EXTENSION_TYPE_VCARD_EMAIL,
  EXTENSION_TYPE_VCARD_JABBERID,
  EXTENSION_TYPE_VCARD_MAILER,
  EXTENSION_TYPE_VCARD_TZ,
  EXTENSION_TYPE_VCARD_GEO,
  EXTENSION_TYPE_VCARD_TITLE,
  EXTENSION_TYPE_VCARD_ROLE,
  EXTENSION_TYPE_VCARD_LOGO,
  EXTENSION_TYPE_VCARD_EXTVAL,
  EXTENSION_TYPE_VCARD_AGENT,
  EXTENSION_TYPE_VCARD_ORG,
  EXTENSION_TYPE_VCARD_CATEGORIES,
  EXTENSION_TYPE_VCARD_NOTE,
  EXTENSION_TYPE_VCARD_PRODID,
  EXTENSION_TYPE_VCARD_REV,
  EXTENSION_TYPE_VCARD_SORT_STRING,
  EXTENSION_TYPE_VCARD_SOUND,
  EXTENSION_TYPE_VCARD_PHONETIC,
  EXTENSION_TYPE_VCARD_UID,
  EXTENSION_TYPE_VCARD_URL,
  EXTENSION_TYPE_VCARD_DESC,
  EXTENSION_TYPE_VCARD_CLASS,
  EXTENSION_TYPE_VCARD_KEY,
  EXTENSION_TYPE_PRIVACY_PRIVACY,
  EXTENSION_TYPE_PRIVACY_ACTIVE,
  EXTENSION_TYPE_PRIVACY_DEFAULT,
  EXTENSION_TYPE_PRIVACY_LIST,
  EXTENSION_TYPE_PRIVACY_ITEM,
  EXTENSION_TYPE_STREAM_FEATURES,
  EXTENSION_TYPE_STREAM_ERROR,
  EXTENSION_TYPE_XOOB_X,
  EXTENSION_TYPE_XDATA_X,
  EXTENSION_TYPE_XDATA_FIELD,
  EXTENSION_TYPE_XDATA_OPTION,
  EXTENSION_TYPE_STARTTLS_STARTTLS,
  EXTENSION_TYPE_STARTTLS_PROCEED,
  EXTENSION_TYPE_STARTTLS_FAILURE,
  EXTENSION_TYPE_PING_PING,
  EXTENSION_TYPE_BIND_BIND,
  EXTENSION_TYPE_SASL_MECHANISMS,
  EXTENSION_TYPE_SASL_AUTH,
  EXTENSION_TYPE_SASL_SUCCESS,
  EXTENSION_TYPE_SASL_CHALLENGE,
  EXTENSION_TYPE_SASL_RESPONSE,
  EXTENSION_TYPE_SASL_FAILURE,
  EXTENSION_TYPE_CAPS_CAPS,
  EXTENSION_TYPE_IQVERSION_VERSION,
  EXTENSION_TYPE_ROSTER_ROSTER,
  EXTENSION_TYPE_ROSTER_ITEM,
  EXTENSION_TYPE_CAPTCHA_CAPTCHA,
  EXTENSION_TYPE_DISCO_INFO_INFO,
  EXTENSION_TYPE_DISCO_INFO_IDENTITY,
  EXTENSION_TYPE_DISCO_INFO_FEATURE,
  EXTENSION_TYPE_IQTIME_TIME,
  EXTENSION_TYPE_IQREGISTER_QUERY,
  EXTENSION_TYPE_PUBSUB_EVENT_EVENT,
  EXTENSION_TYPE_PUBSUB_EVENT_COLLECTION,
  EXTENSION_TYPE_PUBSUB_EVENT_CONFIGURATION,
  EXTENSION_TYPE_PUBSUB_EVENT_DELETE,
  EXTENSION_TYPE_PUBSUB_EVENT_ITEMS,
  EXTENSION_TYPE_PUBSUB_EVENT_ITEM,
  EXTENSION_TYPE_PUBSUB_EVENT_PURGE,
  EXTENSION_TYPE_PUBSUB_EVENT_RETRACT,
  EXTENSION_TYPE_PUBSUB_EVENT_SUBSCRIPTION,
  EXTENSION_TYPE_CLIENT_IQ,
  EXTENSION_TYPE_CLIENT_PRESENCE,
  EXTENSION_TYPE_CLIENT_MESSAGE,
  EXTENSION_TYPE_CLIENT_PRESENCE_SHOW,
  EXTENSION_TYPE_STANZA_ERROR,
  EXTENSION_TYPE_MUC_ENTER,
  EXTENSION_TYPE_MUC_USER_ACTION,
  EXTENSION_TYPE_MUC_USER_STATUS,
  EXTENSION_TYPE_MUC_USER_DECLINE,
  EXTENSION_TYPE_MUC_USER_DESTROY,
  EXTENSION_TYPE_MUC_USER_INVITE,
  EXTENSION_TYPE_MUC_USER_ITEM,
  EXTENSION_TYPE_MUC_OWNER_CONFIGURE,
  EXTENSION_TYPE_MUC_ADMIN_QUERY,
  EXTENSION_TYPE_MUC_ADMIN_ITEM,
  EXTENSION_TYPE_STATS_STATS,
  EXTENSION_TYPE_STATS_STAT,
  EXTENSION_TYPE_TIME_TIME,
  EXTENSION_TYPE_SESSION_SESSION,
};

#endif
