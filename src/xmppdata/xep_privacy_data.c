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
  vlist_append ((vlist_t**)&elm->fList, (void*) newel, EXTENSION_TYPE_PRIVACY_LIST);
  }
  } // while end
  return elm;
}

int privacy_privacy_encode(xmlWriter_t* writer, struct privacy_privacy_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_privacy, "query");
if (err != 0) return err;
//here condition
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct privacy_active_t* privacy_active_decode(xmlTextReaderPtr reader) {
  struct privacy_active_t *elm = NULL;
 elm = malloc (sizeof (struct privacy_active_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "name");
  if (avalue != NULL) {
  elm->fName = (const char*)avalue;
  }
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fExtra = (const char*) value;
  return elm;
}

int privacy_active_encode(xmlWriter_t* writer, struct privacy_active_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_privacy, "active");
if (err != 0) return err;
if (elm->fName != NULL) {
err = xmlwriter_attribute (writer, ns_privacy, "name", elm->fName);
if (err != 0) return err;
}
if (elm->fExtra != NULL) {
err = xmlwriter_text (writer, elm->fExtra);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct privacy_default_t* privacy_default_decode(xmlTextReaderPtr reader) {
  struct privacy_default_t *elm = NULL;
 elm = malloc (sizeof (struct privacy_default_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "name");
  if (avalue != NULL) {
  elm->fName = (const char*)avalue;
  }
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fExtra = (const char*) value;
  return elm;
}

int privacy_default_encode(xmlWriter_t* writer, struct privacy_default_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_privacy, "default");
if (err != 0) return err;
if (elm->fName != NULL) {
err = xmlwriter_attribute (writer, ns_privacy, "name", elm->fName);
if (err != 0) return err;
}
if (elm->fExtra != NULL) {
err = xmlwriter_text (writer, elm->fExtra);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct privacy_list_t* privacy_list_decode(xmlTextReaderPtr reader) {
  struct privacy_list_t *elm = NULL;
 elm = malloc (sizeof (struct privacy_list_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "name");
  if (avalue != NULL) {
  elm->fName = (const char*)avalue;
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
  vlist_append ((vlist_t**)&elm->fItems, (void*) newel, EXTENSION_TYPE_PRIVACY_ITEM);
  }
  } // while end
  return elm;
}

int privacy_list_encode(xmlWriter_t* writer, struct privacy_list_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_privacy, "list");
if (err != 0) return err;
if (elm->fName != NULL) {
err = xmlwriter_attribute (writer, ns_privacy, "name", elm->fName);
if (err != 0) return err;
}
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
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
  elm->fValue = (const char*)avalue;
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

int privacy_item_encode(xmlWriter_t* writer, struct privacy_item_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_privacy, "item");
if (err != 0) return err;
if (elm->fAction != 0) {
err = xmlwriter_attribute (writer, ns_privacy, "action", enum_privacy_item_action_to_string(elm->fAction));
if (err != 0) return err;
}
if (elm->fOrder != NULL) {
err = xmlwriter_attribute (writer, ns_privacy, "order", strconv_format_uint(elm->fOrder));
if (err != 0) return err;
}
if (elm->fType != 0) {
err = xmlwriter_attribute (writer, ns_privacy, "type", enum_privacy_item_type_to_string(elm->fType));
if (err != 0) return err;
}
if (elm->fValue != NULL) {
err = xmlwriter_attribute (writer, ns_privacy, "value", elm->fValue);
if (err != 0) return err;
}
//here condition
//here condition
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

enum privacy_item_action_t enum_privacy_item_action_from_string(const xmlChar *value) {
return 0;
}
const char* enum_privacy_item_action_to_string(enum privacy_item_action_t value) {
return NULL;
}
enum privacy_item_type_t enum_privacy_item_type_from_string(const xmlChar *value) {
return 0;
}
const char* enum_privacy_item_type_to_string(enum privacy_item_type_t value) {
return NULL;
}
