#include "xep_privacy_data.h"

const char* ns_privacy = "jabber:iq:privacy";

struct privacy_privacy_t* privacy_privacy_decode(xmlTextReaderPtr reader) {
  struct privacy_privacy_t *elm = NULL;
 elm = malloc (sizeof (struct privacy_privacy_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) namespace, ns_privacy) == 0) && (strcmp ((char*) name, "list") == 0)) {
//here
struct privacy_list_t* newel = privacy_list_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fList, (void*) newel, EXTENSION_TYPE_PRIVACY_LIST);
  }
  } // while end
  return elm;
}

int privacy_privacy_encode(xmlTextWriterPtr writer, struct privacy_privacy_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "query", BAD_CAST ns_privacy) == -1)
 return -1;
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct privacy_active_t* privacy_active_decode(xmlTextReaderPtr reader) {
  struct privacy_active_t *elm = NULL;
 elm = malloc (sizeof (struct privacy_active_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "name");
  if (avalue != NULL) {
  elm->fName = avalue;
  }
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fExtra = (value);
  return elm;
}

int privacy_active_encode(xmlTextWriterPtr writer, struct privacy_active_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "active", BAD_CAST ns_privacy) == -1)
 return -1;
if (elm->fName != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "name", BAD_CAST "ns_privacy", elm->fName) == -1)
 return -1;
}
if (elm->fExtra != NULL) {
if (xmlTextWriterWriteCDATA(writer, elm->fExtra) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct privacy_default_t* privacy_default_decode(xmlTextReaderPtr reader) {
  struct privacy_default_t *elm = NULL;
 elm = malloc (sizeof (struct privacy_default_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "name");
  if (avalue != NULL) {
  elm->fName = avalue;
  }
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fExtra = (value);
  return elm;
}

int privacy_default_encode(xmlTextWriterPtr writer, struct privacy_default_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "default", BAD_CAST ns_privacy) == -1)
 return -1;
if (elm->fName != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "name", BAD_CAST "ns_privacy", elm->fName) == -1)
 return -1;
}
if (elm->fExtra != NULL) {
if (xmlTextWriterWriteCDATA(writer, elm->fExtra) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct privacy_list_t* privacy_list_decode(xmlTextReaderPtr reader) {
  struct privacy_list_t *elm = NULL;
 elm = malloc (sizeof (struct privacy_list_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "name");
  if (avalue != NULL) {
  elm->fName = avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) namespace, ns_privacy) == 0) && (strcmp ((char*) name, "item") == 0)) {
//here
struct privacy_item_t* newel = privacy_item_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fItems, (void*) newel, EXTENSION_TYPE_PRIVACY_ITEM);
  }
  } // while end
  return elm;
}

int privacy_list_encode(xmlTextWriterPtr writer, struct privacy_list_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "list", BAD_CAST ns_privacy) == -1)
 return -1;
if (elm->fName != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "name", BAD_CAST "ns_privacy", elm->fName) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct privacy_item_t* privacy_item_decode(xmlTextReaderPtr reader) {
  struct privacy_item_t *elm = NULL;
 elm = malloc (sizeof (struct privacy_item_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "action");
  if (avalue != NULL) {
//enum
elm->fAction = enum_privacy_item_action_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "order");
  if (avalue != NULL) {
  elm->fOrder = strconv_parse_uint (avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
//enum
elm->fType = enum_privacy_item_type_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "value");
  if (avalue != NULL) {
  elm->fValue = avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "iq") == 0) && (strcmp ((char*) namespace, ns_privacy) == 0)) {
    elm->fIq = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "message") == 0) && (strcmp ((char*) namespace, ns_privacy) == 0)) {
    elm->fMessage = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "presence-in") == 0) && (strcmp ((char*) namespace, ns_privacy) == 0)) {
    elm->fPresence_in = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "presence-out") == 0) && (strcmp ((char*) namespace, ns_privacy) == 0)) {
    elm->fPresence_out = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  } // while end
  return elm;
}

int privacy_item_encode(xmlTextWriterPtr writer, struct privacy_item_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "item", BAD_CAST ns_privacy) == -1)
 return -1;
if (elm->fAction != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "action", BAD_CAST "ns_privacy", BAD_CAST elm->fAction) == -1)
 return -1;
}
if (elm->fOrder != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "order", BAD_CAST "ns_privacy", strconv_format_uint(elm->fOrder)) == -1)
 return -1;
}
if (elm->fType != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "type", BAD_CAST "ns_privacy", BAD_CAST elm->fType) == -1)
 return -1;
}
if (elm->fValue != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "value", BAD_CAST "ns_privacy", elm->fValue) == -1)
 return -1;
}
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

enum privacy_item_action_t enum_privacy_item_action_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_privacy_item_action_to_string(enum privacy_item_action_t value) {
return NULL;
}
enum privacy_item_type_t enum_privacy_item_type_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_privacy_item_type_to_string(enum privacy_item_type_t value) {
return NULL;
}
