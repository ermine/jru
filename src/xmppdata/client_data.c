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
  elm->fId = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
//enum
elm->fType = enum_client_iq_type_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "xml:lang");
  if (avalue != NULL) {
elm->fLang = avalue;
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

int client_iq_encode(xmlTextWriterPtr writer, struct client_iq_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "iq", BAD_CAST ns_client) == -1)
 return -1;
if (elm->fFrom != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "from", BAD_CAST "ns_client", BAD_CAST jid_to_string(elm->fFrom)) == -1)
 return -1;
}
if (elm->fTo != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "to", BAD_CAST "ns_client", BAD_CAST jid_to_string(elm->fTo)) == -1)
 return -1;
}
if (elm->fId != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "id", BAD_CAST "ns_client", elm->fId) == -1)
 return -1;
}
if (elm->fType != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "type", BAD_CAST "ns_client", BAD_CAST elm->fType) == -1)
 return -1;
}
if (elm->fLang != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "xml", BAD_CAST "lang", BAD_CAST "http://www.w3.org/XML/1998/namespace", BAD_CAST elm->fLang) == -1)
 return -1;
}
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
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
  elm->fId = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
//enum
elm->fType = enum_client_presence_type_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "xml:lang");
  if (avalue != NULL) {
elm->fLang = avalue;
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
elm->fStatus = (value);
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
  llist_append((llist_t*)elm->fX, newel->data, newel->type);
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

int client_presence_encode(xmlTextWriterPtr writer, struct client_presence_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "presence", BAD_CAST ns_client) == -1)
 return -1;
if (elm->fFrom != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "from", BAD_CAST "ns_client", BAD_CAST jid_to_string(elm->fFrom)) == -1)
 return -1;
}
if (elm->fTo != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "to", BAD_CAST "ns_client", BAD_CAST jid_to_string(elm->fTo)) == -1)
 return -1;
}
if (elm->fId != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "id", BAD_CAST "ns_client", elm->fId) == -1)
 return -1;
}
if (elm->fType != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "type", BAD_CAST "ns_client", BAD_CAST elm->fType) == -1)
 return -1;
}
if (elm->fLang != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "xml", BAD_CAST "lang", BAD_CAST "http://www.w3.org/XML/1998/namespace", BAD_CAST elm->fLang) == -1)
 return -1;
}
//here condition
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
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
  elm->fId = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
//enum
elm->fType = enum_client_message_type_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "xml:lang");
  if (avalue != NULL) {
elm->fLang = avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "thread") == 0) && (strcmp ((char*) namespace, ns_client) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fThread = (value);
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
  llist_append((llist_t*)elm->fX, newel->data, newel->type);
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

int client_message_encode(xmlTextWriterPtr writer, struct client_message_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "message", BAD_CAST ns_client) == -1)
 return -1;
if (elm->fFrom != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "from", BAD_CAST "ns_client", BAD_CAST jid_to_string(elm->fFrom)) == -1)
 return -1;
}
if (elm->fTo != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "to", BAD_CAST "ns_client", BAD_CAST jid_to_string(elm->fTo)) == -1)
 return -1;
}
if (elm->fId != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "id", BAD_CAST "ns_client", elm->fId) == -1)
 return -1;
}
if (elm->fType != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "type", BAD_CAST "ns_client", BAD_CAST elm->fType) == -1)
 return -1;
}
if (elm->fLang != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "xml", BAD_CAST "lang", BAD_CAST "http://www.w3.org/XML/1998/namespace", BAD_CAST elm->fLang) == -1)
 return -1;
}
//here condition
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

enum client_iq_type_t enum_client_iq_type_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_client_iq_type_to_string(enum client_iq_type_t value) {
return NULL;
}
enum client_presence_type_t enum_client_presence_type_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_client_presence_type_to_string(enum client_presence_type_t value) {
return NULL;
}
enum client_presence_show_t enum_client_presence_show_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_client_presence_show_to_string(enum client_presence_show_t value) {
return NULL;
}
enum client_message_type_t enum_client_message_type_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_client_message_type_to_string(enum client_message_type_t value) {
return NULL;
}
