#include "extensions.h"
#include "xstream.h"

#include "xep_iqlast_data.h"
#include "xep_mood_data.h"
#include "xep_vcard_data.h"
#include "xep_privacy_data.h"
#include "stream_data.h"
#include "xep_xoob_data.h"
#include "xep_xdata_data.h"
#include "starttls_data.h"
#include "xep_ping_data.h"
#include "bind_data.h"
#include "sasl_data.h"
#include "xep_caps_data.h"
#include "xep_iqversion_data.h"
#include "roster_data.h"
#include "xep_captcha_data.h"
#include "xep_disco_data.h"
#include "xep_iqtime_data.h"
#include "xep_iqregister_data.h"
#include "xep_pubsub_data.h"
#include "client_data.h"
#include "stanza_data.h"
#include "xep_muc_data.h"
#include "xep_stats_data.h"
#include "xep_time_data.h"
#include "session_data.h"

struct xstream_extension_t extensions[] = {
 {"jabber:iq:last", "query", EXTENSION_TYPE_IQLAST_LAST, (void *(*)(xmlTextReaderPtr)) iqlast_last_decode, (int (*)(xmlTextWriterPtr, void*)) iqlast_last_encode},
 {"http://jabber.org/protocol/mood", "mood", EXTENSION_TYPE_MOOD_MOOD, (void *(*)(xmlTextReaderPtr)) mood_mood_decode, (int (*)(xmlTextWriterPtr, void*)) mood_mood_encode},
 {"vcard-temp", "vCard", EXTENSION_TYPE_VCARD_VCARD, (void *(*)(xmlTextReaderPtr)) vcard_vcard_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_vcard_encode},
 {"vcard-temp", "N", EXTENSION_TYPE_VCARD_N, (void *(*)(xmlTextReaderPtr)) vcard_N_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_N_encode},
 {"vcard-temp", "PHOTO", EXTENSION_TYPE_VCARD_PHOTO, (void *(*)(xmlTextReaderPtr)) vcard_PHOTO_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_PHOTO_encode},
 {"vcard-temp", "ADR", EXTENSION_TYPE_VCARD_ADR, (void *(*)(xmlTextReaderPtr)) vcard_ADR_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_ADR_encode},
 {"vcard-temp", "LABEL", EXTENSION_TYPE_VCARD_LABEL, (void *(*)(xmlTextReaderPtr)) vcard_LABEL_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_LABEL_encode},
 {"vcard-temp", "TEL", EXTENSION_TYPE_VCARD_TEL, (void *(*)(xmlTextReaderPtr)) vcard_TEL_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_TEL_encode},
 {"vcard-temp", "EMAIL", EXTENSION_TYPE_VCARD_EMAIL, (void *(*)(xmlTextReaderPtr)) vcard_EMAIL_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_EMAIL_encode},
 {"vcard-temp", "GEO", EXTENSION_TYPE_VCARD_GEO, (void *(*)(xmlTextReaderPtr)) vcard_GEO_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_GEO_encode},
 {"vcard-temp", "LOGO", EXTENSION_TYPE_VCARD_LOGO, (void *(*)(xmlTextReaderPtr)) vcard_LOGO_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_LOGO_encode},
 {"vcard-temp", "AGENT", EXTENSION_TYPE_VCARD_AGENT, (void *(*)(xmlTextReaderPtr)) vcard_AGENT_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_AGENT_encode},
 {"vcard-temp", "ORG", EXTENSION_TYPE_VCARD_ORG, (void *(*)(xmlTextReaderPtr)) vcard_ORG_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_ORG_encode},
 {"vcard-temp", "CATEGORIES", EXTENSION_TYPE_VCARD_CATEGORIES, (void *(*)(xmlTextReaderPtr)) vcard_CATEGORIES_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_CATEGORIES_encode},
 {"vcard-temp", "SOUND", EXTENSION_TYPE_VCARD_SOUND, (void *(*)(xmlTextReaderPtr)) vcard_SOUND_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_SOUND_encode},
 {"vcard-temp", "CLASS", EXTENSION_TYPE_VCARD_CLASS, (void *(*)(xmlTextReaderPtr)) vcard_CLASS_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_CLASS_encode},
 {"vcard-temp", "KEY", EXTENSION_TYPE_VCARD_KEY, (void *(*)(xmlTextReaderPtr)) vcard_KEY_decode, (int (*)(xmlTextWriterPtr, void*)) vcard_KEY_encode},
 {"jabber:iq:privacy", "query", EXTENSION_TYPE_PRIVACY_PRIVACY, (void *(*)(xmlTextReaderPtr)) privacy_privacy_decode, (int (*)(xmlTextWriterPtr, void*)) privacy_privacy_encode},
 {"jabber:iq:privacy", "active", EXTENSION_TYPE_PRIVACY_ACTIVE, (void *(*)(xmlTextReaderPtr)) privacy_active_decode, (int (*)(xmlTextWriterPtr, void*)) privacy_active_encode},
 {"jabber:iq:privacy", "default", EXTENSION_TYPE_PRIVACY_DEFAULT, (void *(*)(xmlTextReaderPtr)) privacy_default_decode, (int (*)(xmlTextWriterPtr, void*)) privacy_default_encode},
 {"jabber:iq:privacy", "list", EXTENSION_TYPE_PRIVACY_LIST, (void *(*)(xmlTextReaderPtr)) privacy_list_decode, (int (*)(xmlTextWriterPtr, void*)) privacy_list_encode},
 {"jabber:iq:privacy", "item", EXTENSION_TYPE_PRIVACY_ITEM, (void *(*)(xmlTextReaderPtr)) privacy_item_decode, (int (*)(xmlTextWriterPtr, void*)) privacy_item_encode},
 {"http://etherx.jabber.org/streams", "features", EXTENSION_TYPE_STREAM_FEATURES, (void *(*)(xmlTextReaderPtr)) stream_features_decode, (int (*)(xmlTextWriterPtr, void*)) stream_features_encode},
 {"http://etherx.jabber.org/streams", "error", EXTENSION_TYPE_STREAM_ERROR, (void *(*)(xmlTextReaderPtr)) stream_error_decode, (int (*)(xmlTextWriterPtr, void*)) stream_error_encode},
 {"jabber:x:oob", "x", EXTENSION_TYPE_XOOB_X, (void *(*)(xmlTextReaderPtr)) xoob_x_decode, (int (*)(xmlTextWriterPtr, void*)) xoob_x_encode},
 {"jabber:x:data", "x", EXTENSION_TYPE_XDATA_X, (void *(*)(xmlTextReaderPtr)) xdata_x_decode, (int (*)(xmlTextWriterPtr, void*)) xdata_x_encode},
 {"jabber:x:data", "field", EXTENSION_TYPE_XDATA_FIELD, (void *(*)(xmlTextReaderPtr)) xdata_field_decode, (int (*)(xmlTextWriterPtr, void*)) xdata_field_encode},
 {"jabber:x:data", "option", EXTENSION_TYPE_XDATA_OPTION, (void *(*)(xmlTextReaderPtr)) xdata_option_decode, (int (*)(xmlTextWriterPtr, void*)) xdata_option_encode},
 {"urn:ietf:params:xml:ns:xmpp-tls", "starttls", EXTENSION_TYPE_STARTTLS_STARTTLS, (void *(*)(xmlTextReaderPtr)) starttls_starttls_decode, (int (*)(xmlTextWriterPtr, void*)) starttls_starttls_encode},
 {"urn:ietf:params:xml:ns:xmpp-tls", "proceed", EXTENSION_TYPE_STARTTLS_PROCEED, (void *(*)(xmlTextReaderPtr)) starttls_proceed_decode, (int (*)(xmlTextWriterPtr, void*)) starttls_proceed_encode},
 {"urn:ietf:params:xml:ns:xmpp-tls", "failure", EXTENSION_TYPE_STARTTLS_FAILURE, (void *(*)(xmlTextReaderPtr)) starttls_failure_decode, (int (*)(xmlTextWriterPtr, void*)) starttls_failure_encode},
 {"urn:xmpp:ping", "ping", EXTENSION_TYPE_PING_PING, (void *(*)(xmlTextReaderPtr)) ping_ping_decode, (int (*)(xmlTextWriterPtr, void*)) ping_ping_encode},
 {"urn:ietf:params:xml:ns:xmpp-bind", "bind", EXTENSION_TYPE_BIND_BIND, (void *(*)(xmlTextReaderPtr)) bind_bind_decode, (int (*)(xmlTextWriterPtr, void*)) bind_bind_encode},
 {"urn:ietf:params:xml:ns:xmpp-sasl", "mechanisms", EXTENSION_TYPE_SASL_MECHANISMS, (void *(*)(xmlTextReaderPtr)) sasl_mechanisms_decode, (int (*)(xmlTextWriterPtr, void*)) sasl_mechanisms_encode},
 {"urn:ietf:params:xml:ns:xmpp-sasl", "auth", EXTENSION_TYPE_SASL_AUTH, (void *(*)(xmlTextReaderPtr)) sasl_auth_decode, (int (*)(xmlTextWriterPtr, void*)) sasl_auth_encode},
 {"urn:ietf:params:xml:ns:xmpp-sasl", "success", EXTENSION_TYPE_SASL_SUCCESS, (void *(*)(xmlTextReaderPtr)) sasl_success_decode, (int (*)(xmlTextWriterPtr, void*)) sasl_success_encode},
 {"urn:ietf:params:xml:ns:xmpp-sasl", "challenge", EXTENSION_TYPE_SASL_CHALLENGE, (void *(*)(xmlTextReaderPtr)) sasl_challenge_decode, (int (*)(xmlTextWriterPtr, void*)) sasl_challenge_encode},
 {"urn:ietf:params:xml:ns:xmpp-sasl", "response", EXTENSION_TYPE_SASL_RESPONSE, (void *(*)(xmlTextReaderPtr)) sasl_response_decode, (int (*)(xmlTextWriterPtr, void*)) sasl_response_encode},
 {"urn:ietf:params:xml:ns:xmpp-sasl", "failure", EXTENSION_TYPE_SASL_FAILURE, (void *(*)(xmlTextReaderPtr)) sasl_failure_decode, (int (*)(xmlTextWriterPtr, void*)) sasl_failure_encode},
 {"http://jabber.org/protocol/caps", "c", EXTENSION_TYPE_CAPS_CAPS, (void *(*)(xmlTextReaderPtr)) caps_caps_decode, (int (*)(xmlTextWriterPtr, void*)) caps_caps_encode},
 {"jabber:iq:version", "query", EXTENSION_TYPE_IQVERSION_VERSION, (void *(*)(xmlTextReaderPtr)) iqversion_version_decode, (int (*)(xmlTextWriterPtr, void*)) iqversion_version_encode},
 {"jabber:iq:roster", "query", EXTENSION_TYPE_ROSTER_ROSTER, (void *(*)(xmlTextReaderPtr)) roster_roster_decode, (int (*)(xmlTextWriterPtr, void*)) roster_roster_encode},
 {"jabber:iq:roster", "item", EXTENSION_TYPE_ROSTER_ITEM, (void *(*)(xmlTextReaderPtr)) roster_item_decode, (int (*)(xmlTextWriterPtr, void*)) roster_item_encode},
 {"urn:xmpp:captcha", "captcha", EXTENSION_TYPE_CAPTCHA_CAPTCHA, (void *(*)(xmlTextReaderPtr)) captcha_captcha_decode, (int (*)(xmlTextWriterPtr, void*)) captcha_captcha_encode},
 {"http://jabber.org/protocol/disco#info", "query", EXTENSION_TYPE_DISCO_INFO_INFO, (void *(*)(xmlTextReaderPtr)) disco_info_info_decode, (int (*)(xmlTextWriterPtr, void*)) disco_info_info_encode},
 {"http://jabber.org/protocol/disco#info", "identity", EXTENSION_TYPE_DISCO_INFO_IDENTITY, (void *(*)(xmlTextReaderPtr)) disco_info_identity_decode, (int (*)(xmlTextWriterPtr, void*)) disco_info_identity_encode},
 {"http://jabber.org/protocol/disco#info", "feature", EXTENSION_TYPE_DISCO_INFO_FEATURE, (void *(*)(xmlTextReaderPtr)) disco_info_feature_decode, (int (*)(xmlTextWriterPtr, void*)) disco_info_feature_encode},
 {"jabber:iq:time", "query", EXTENSION_TYPE_IQTIME_TIME, (void *(*)(xmlTextReaderPtr)) iqtime_time_decode, (int (*)(xmlTextWriterPtr, void*)) iqtime_time_encode},
 {"jabber:iq:register", "query", EXTENSION_TYPE_IQREGISTER_QUERY, (void *(*)(xmlTextReaderPtr)) iqregister_query_decode, (int (*)(xmlTextWriterPtr, void*)) iqregister_query_encode},
 {"http://jabber.org/protocol/pubsub#event", "event", EXTENSION_TYPE_PUBSUB_EVENT_EVENT, (void *(*)(xmlTextReaderPtr)) pubsub_event_event_decode, (int (*)(xmlTextWriterPtr, void*)) pubsub_event_event_encode},
 {"http://jabber.org/protocol/pubsub#event", "collection", EXTENSION_TYPE_PUBSUB_EVENT_COLLECTION, (void *(*)(xmlTextReaderPtr)) pubsub_event_collection_decode, (int (*)(xmlTextWriterPtr, void*)) pubsub_event_collection_encode},
 {"http://jabber.org/protocol/pubsub#event", "configuration", EXTENSION_TYPE_PUBSUB_EVENT_CONFIGURATION, (void *(*)(xmlTextReaderPtr)) pubsub_event_configuration_decode, (int (*)(xmlTextWriterPtr, void*)) pubsub_event_configuration_encode},
 {"http://jabber.org/protocol/pubsub#event", "delete", EXTENSION_TYPE_PUBSUB_EVENT_DELETE, (void *(*)(xmlTextReaderPtr)) pubsub_event_delete_decode, (int (*)(xmlTextWriterPtr, void*)) pubsub_event_delete_encode},
 {"http://jabber.org/protocol/pubsub#event", "items", EXTENSION_TYPE_PUBSUB_EVENT_ITEMS, (void *(*)(xmlTextReaderPtr)) pubsub_event_items_decode, (int (*)(xmlTextWriterPtr, void*)) pubsub_event_items_encode},
 {"http://jabber.org/protocol/pubsub#event", "item", EXTENSION_TYPE_PUBSUB_EVENT_ITEM, (void *(*)(xmlTextReaderPtr)) pubsub_event_item_decode, (int (*)(xmlTextWriterPtr, void*)) pubsub_event_item_encode},
 {"http://jabber.org/protocol/pubsub#event", "purge", EXTENSION_TYPE_PUBSUB_EVENT_PURGE, (void *(*)(xmlTextReaderPtr)) pubsub_event_purge_decode, (int (*)(xmlTextWriterPtr, void*)) pubsub_event_purge_encode},
 {"http://jabber.org/protocol/pubsub#event", "retract", EXTENSION_TYPE_PUBSUB_EVENT_RETRACT, (void *(*)(xmlTextReaderPtr)) pubsub_event_retract_decode, (int (*)(xmlTextWriterPtr, void*)) pubsub_event_retract_encode},
 {"http://jabber.org/protocol/pubsub#event", "subscription", EXTENSION_TYPE_PUBSUB_EVENT_SUBSCRIPTION, (void *(*)(xmlTextReaderPtr)) pubsub_event_subscription_decode, (int (*)(xmlTextWriterPtr, void*)) pubsub_event_subscription_encode},
 {"jabber:client", "iq", EXTENSION_TYPE_CLIENT_IQ, (void *(*)(xmlTextReaderPtr)) client_iq_decode, (int (*)(xmlTextWriterPtr, void*)) client_iq_encode},
 {"jabber:client", "presence", EXTENSION_TYPE_CLIENT_PRESENCE, (void *(*)(xmlTextReaderPtr)) client_presence_decode, (int (*)(xmlTextWriterPtr, void*)) client_presence_encode},
 {"jabber:client", "message", EXTENSION_TYPE_CLIENT_MESSAGE, (void *(*)(xmlTextReaderPtr)) client_message_decode, (int (*)(xmlTextWriterPtr, void*)) client_message_encode},
 {"urn:ietf:params:xml:ns:xmpp-stanzas", "error", EXTENSION_TYPE_STANZA_ERROR, (void *(*)(xmlTextReaderPtr)) stanza_error_decode, (int (*)(xmlTextWriterPtr, void*)) stanza_error_encode},
 {"http://jabber.org/protocol/muc", "x", EXTENSION_TYPE_MUC_ENTER, (void *(*)(xmlTextReaderPtr)) muc_enter_decode, (int (*)(xmlTextWriterPtr, void*)) muc_enter_encode},
 {"http://jabber.org/protocol/muc#user", "x", EXTENSION_TYPE_MUC_USER_ACTION, (void *(*)(xmlTextReaderPtr)) muc_user_action_decode, (int (*)(xmlTextWriterPtr, void*)) muc_user_action_encode},
 {"http://jabber.org/protocol/muc#user", "status", EXTENSION_TYPE_MUC_USER_STATUS, (void *(*)(xmlTextReaderPtr)) muc_user_status_decode, (int (*)(xmlTextWriterPtr, void*)) muc_user_status_encode},
 {"http://jabber.org/protocol/muc#user", "decline", EXTENSION_TYPE_MUC_USER_DECLINE, (void *(*)(xmlTextReaderPtr)) muc_user_decline_decode, (int (*)(xmlTextWriterPtr, void*)) muc_user_decline_encode},
 {"http://jabber.org/protocol/muc#user", "destroy", EXTENSION_TYPE_MUC_USER_DESTROY, (void *(*)(xmlTextReaderPtr)) muc_user_destroy_decode, (int (*)(xmlTextWriterPtr, void*)) muc_user_destroy_encode},
 {"http://jabber.org/protocol/muc#user", "invite", EXTENSION_TYPE_MUC_USER_INVITE, (void *(*)(xmlTextReaderPtr)) muc_user_invite_decode, (int (*)(xmlTextWriterPtr, void*)) muc_user_invite_encode},
 {"http://jabber.org/protocol/muc#user", "item", EXTENSION_TYPE_MUC_USER_ITEM, (void *(*)(xmlTextReaderPtr)) muc_user_item_decode, (int (*)(xmlTextWriterPtr, void*)) muc_user_item_encode},
 {"http://jabber.org/protocol/muc#owner", "query", EXTENSION_TYPE_MUC_OWNER_CONFIGURE, (void *(*)(xmlTextReaderPtr)) muc_owner_configure_decode, (int (*)(xmlTextWriterPtr, void*)) muc_owner_configure_encode},
 {"http://jabber.org/protocol/muc#admin", "query", EXTENSION_TYPE_MUC_ADMIN_QUERY, (void *(*)(xmlTextReaderPtr)) muc_admin_query_decode, (int (*)(xmlTextWriterPtr, void*)) muc_admin_query_encode},
 {"http://jabber.org/protocol/muc#admin", "item", EXTENSION_TYPE_MUC_ADMIN_ITEM, (void *(*)(xmlTextReaderPtr)) muc_admin_item_decode, (int (*)(xmlTextWriterPtr, void*)) muc_admin_item_encode},
 {"http://jabber.org/protocol/stats", "query", EXTENSION_TYPE_STATS_STATS, (void *(*)(xmlTextReaderPtr)) stats_stats_decode, (int (*)(xmlTextWriterPtr, void*)) stats_stats_encode},
 {"http://jabber.org/protocol/stats", "stat", EXTENSION_TYPE_STATS_STAT, (void *(*)(xmlTextReaderPtr)) stats_stat_decode, (int (*)(xmlTextWriterPtr, void*)) stats_stat_encode},
 {"urn:xmpp:time", "time", EXTENSION_TYPE_TIME_TIME, (void *(*)(xmlTextReaderPtr)) time_time_decode, (int (*)(xmlTextWriterPtr, void*)) time_time_encode},
 {"urn:ietf:params:xml:ns:xmpp-session", "session", EXTENSION_TYPE_SESSION_SESSION, (void *(*)(xmlTextReaderPtr)) session_session_decode, (int (*)(xmlTextWriterPtr, void*)) session_session_encode},
};

int extensions_len = 76;
