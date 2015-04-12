#include "client_data.h"

const char* ns_client = "jabber:client";

struct client_iq_t* client_iq_decode(xmlTextReaderPtr reader) {
  struct client_iq_t *elm = NULL;
 elm = malloc (sizeof (struct client_iq_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "from");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fFrom = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "to");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fTo = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "id");
  if (avalue != NULL) {
  elm->fId = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
//enum
elm->fType = enum_client_iq_type_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "lang");
  if (avalue != NULL) {
elm->fLang = (const char*) avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
if (strcmp ((char*) namespace, ns_client) != 0) {
// zzz
  extension_t* newel = xstream_extension_decode (reader);
  if (newel == NULL) {
if (xstream_skip(reader) != 0) {
    return NULL;
  }
} else {
elm->fPayload = newel;
}
} // end of if strcmp
else  if ((strcmp ((char*) namespace, "urn:ietf:params:xml:ns:xmpp-stanzas") == 0) && (strcmp ((char *) name, "error") == 0)) {
struct stanza_error_t* newel = stanza_error_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
elm->fError = newel;
}
  } // while end
  return elm;
}

int client_iq_encode(xmlWriter_t* writer, struct client_iq_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_client, "iq");
if (err != 0) return err;
if (elm->fFrom != NULL) {
err = xmlwriter_attribute (writer, ns_client, "from", jid_to_string(elm->fFrom));
if (err != 0) return err;
}
if (elm->fTo != NULL) {
err = xmlwriter_attribute (writer, ns_client, "to", jid_to_string(elm->fTo));
if (err != 0) return err;
}
if (elm->fId != NULL) {
err = xmlwriter_attribute (writer, ns_client, "id", elm->fId);
if (err != 0) return err;
}
if (elm->fType != 0) {
err = xmlwriter_attribute (writer, ns_client, "type", enum_client_iq_type_to_string(elm->fType));
if (err != 0) return err;
}
if (elm->fLang != NULL) {
err = xmlwriter_attribute (writer, ns_xml, "lang", elm->fLang);
if (err != 0) return err;
}
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct client_presence_t* client_presence_decode(xmlTextReaderPtr reader) {
  struct client_presence_t *elm = NULL;
 elm = malloc (sizeof (struct client_presence_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "from");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fFrom = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "to");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fTo = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "id");
  if (avalue != NULL) {
  elm->fId = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
//enum
elm->fType = enum_client_presence_type_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "lang");
  if (avalue != NULL) {
elm->fLang = (const char*) avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "show") == 0) && (strcmp ((char*) namespace, ns_client) == 0)) {
 const xmlChar* s = xmlTextReaderConstValue (reader);
//herace1
elm->fShow = enum_client_presence_show_from_string(s);
  } // for end part 1
  else if ((strcmp ((char*) name, "status") == 0) && (strcmp ((char*) namespace, ns_client) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fStatus = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) name, "priority") == 0) && (strcmp ((char*) namespace, ns_client) == 0)) {
 const xmlChar* s = xmlTextReaderConstValue (reader);
  elm->fPriority = strconv_parse_int (s);
  } // for end part 1
else if (strcmp ((char*) namespace, ns_client) != 0) {
  extension_t* newel = xstream_extension_decode (reader);
  if (newel == NULL) {
if (xstream_skip(reader) != 0) {
    return NULL;
  }
} else {
  vlist_append ((vlist_t**)&elm->fX, newel->data, newel->type);
free(newel);
}
}
else  if ((strcmp ((char*) namespace, "urn:ietf:params:xml:ns:xmpp-stanzas") == 0) && (strcmp ((char *) name, "error") == 0)) {
struct stanza_error_t* newel = stanza_error_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
elm->fError = newel;
}
  } // while end
  return elm;
}

int client_presence_encode(xmlWriter_t* writer, struct client_presence_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_client, "presence");
if (err != 0) return err;
if (elm->fFrom != NULL) {
err = xmlwriter_attribute (writer, ns_client, "from", jid_to_string(elm->fFrom));
if (err != 0) return err;
}
if (elm->fTo != NULL) {
err = xmlwriter_attribute (writer, ns_client, "to", jid_to_string(elm->fTo));
if (err != 0) return err;
}
if (elm->fId != NULL) {
err = xmlwriter_attribute (writer, ns_client, "id", elm->fId);
if (err != 0) return err;
}
if (elm->fType != 0) {
err = xmlwriter_attribute (writer, ns_client, "type", enum_client_presence_type_to_string(elm->fType));
if (err != 0) return err;
}
if (elm->fLang != NULL) {
err = xmlwriter_attribute (writer, ns_xml, "lang", elm->fLang);
if (err != 0) return err;
}
//here condition
//here condition
//here condition
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct client_message_t* client_message_decode(xmlTextReaderPtr reader) {
  struct client_message_t *elm = NULL;
 elm = malloc (sizeof (struct client_message_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "from");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fFrom = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "to");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fTo = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "id");
  if (avalue != NULL) {
  elm->fId = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
//enum
elm->fType = enum_client_message_type_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "lang");
  if (avalue != NULL) {
elm->fLang = (const char*) avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "thread") == 0) && (strcmp ((char*) namespace, ns_client) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fThread = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) name, "subject") == 0) && (strcmp ((char*) namespace, ns_client) == 0)) {
    langstring_decode (reader, elm->fSubject);
  } // for end part 1
  else if ((strcmp ((char*) name, "body") == 0) && (strcmp ((char*) namespace, ns_client) == 0)) {
    langstring_decode (reader, elm->fBody);
  } // for end part 1
else if (strcmp ((char*) namespace, ns_client) != 0) {
  extension_t* newel = xstream_extension_decode (reader);
  if (newel == NULL) {
if (xstream_skip(reader) != 0) {
    return NULL;
  }
} else {
  vlist_append ((vlist_t**)&elm->fX, newel->data, newel->type);
free(newel);
}
}
else  if ((strcmp ((char*) namespace, "urn:ietf:params:xml:ns:xmpp-stanzas") == 0) && (strcmp ((char *) name, "error") == 0)) {
struct stanza_error_t* newel = stanza_error_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
elm->fError = newel;
}
  } // while end
  return elm;
}

int client_message_encode(xmlWriter_t* writer, struct client_message_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_client, "message");
if (err != 0) return err;
if (elm->fFrom != NULL) {
err = xmlwriter_attribute (writer, ns_client, "from", jid_to_string(elm->fFrom));
if (err != 0) return err;
}
if (elm->fTo != NULL) {
err = xmlwriter_attribute (writer, ns_client, "to", jid_to_string(elm->fTo));
if (err != 0) return err;
}
if (elm->fId != NULL) {
err = xmlwriter_attribute (writer, ns_client, "id", elm->fId);
if (err != 0) return err;
}
if (elm->fType != 0) {
err = xmlwriter_attribute (writer, ns_client, "type", enum_client_message_type_to_string(elm->fType));
if (err != 0) return err;
}
if (elm->fLang != NULL) {
err = xmlwriter_attribute (writer, ns_xml, "lang", elm->fLang);
if (err != 0) return err;
}
//here condition
//here condition
//here condition
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

enum client_iq_type_t enum_client_iq_type_from_string(const xmlChar *value) {
return 0;
}
const char* enum_client_iq_type_to_string(enum client_iq_type_t value) {
return NULL;
}
enum client_presence_type_t enum_client_presence_type_from_string(const xmlChar *value) {
return 0;
}
const char* enum_client_presence_type_to_string(enum client_presence_type_t value) {
return NULL;
}
enum client_presence_show_t enum_client_presence_show_from_string(const xmlChar *value) {
return 0;
}
const char* enum_client_presence_show_to_string(enum client_presence_show_t value) {
return NULL;
}
enum client_message_type_t enum_client_message_type_from_string(const xmlChar *value) {
return 0;
}
const char* enum_client_message_type_to_string(enum client_message_type_t value) {
return NULL;
}
