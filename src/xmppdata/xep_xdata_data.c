#include "xep_xdata_data.h"

const char* ns_xdata = "jabber:x:data";

struct xdata_x_t* xdata_x_decode(xmlTextReaderPtr reader) {
  struct xdata_x_t *elm = NULL;
 elm = malloc (sizeof (struct xdata_x_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
//enum
elm->fType = enum_xdata_x_type_from_string(avalue);
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "title") == 0) && (strcmp ((char*) namespace, ns_xdata) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fTitle = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) name, "reported") == 0) && (strcmp ((char*) namespace, ns_xdata) == 0)) {
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here2
  if (xmlTextReaderNodeType (reader) == XML_ELEMENT_NODE) {
  if ((strcmp((char *) namespace, ns_xdata) == 0) && (strcmp ((char*) name, "field") == 0)) {
struct xdata_field_t* newel = xdata_field_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  vlist_append ((vlist_t**) &elm->fReported, (void*) newel, EXTENSION_TYPE_XDATA_FIELD);
}
  if (xmlTextReaderNodeType (reader) == 15) {
break;
  }
}
}
  } // for end part 1
  } // while end
  return elm;
}

int xdata_x_encode(xmlWriter_t* writer, struct xdata_x_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_xdata, "x");
if (err != 0) return err;
if (elm->fType != 0) {
err = xmlwriter_attribute (writer, ns_xdata, "type", enum_xdata_x_type_to_string(elm->fType));
if (err != 0) return err;
}
//here condition
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct xdata_field_t* xdata_field_decode(xmlTextReaderPtr reader) {
  struct xdata_field_t *elm = NULL;
 elm = malloc (sizeof (struct xdata_field_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "label");
  if (avalue != NULL) {
  elm->fLabel = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
//enum
elm->fType = enum_xdata_field_type_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "var");
  if (avalue != NULL) {
  elm->fVar = (const char*)avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "desc") == 0) && (strcmp ((char*) namespace, ns_xdata) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fDesc = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) name, "required") == 0) && (strcmp ((char*) namespace, ns_xdata) == 0)) {
    elm->fRequired = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "value") == 0) && (strcmp ((char*) namespace, ns_xdata) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fValue = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) namespace, ns_xdata) == 0) && (strcmp ((char*) name, "option") == 0)) {
//here
struct xdata_option_t* newel = xdata_option_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  vlist_append ((vlist_t**)&elm->fOption, (void*) newel, EXTENSION_TYPE_XDATA_OPTION);
  }
  } // while end
  return elm;
}

int xdata_field_encode(xmlWriter_t* writer, struct xdata_field_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_xdata, "field");
if (err != 0) return err;
if (elm->fLabel != NULL) {
err = xmlwriter_attribute (writer, ns_xdata, "label", elm->fLabel);
if (err != 0) return err;
}
if (elm->fType != 0) {
err = xmlwriter_attribute (writer, ns_xdata, "type", enum_xdata_field_type_to_string(elm->fType));
if (err != 0) return err;
}
if (elm->fVar != NULL) {
err = xmlwriter_attribute (writer, ns_xdata, "var", elm->fVar);
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

struct xdata_option_t* xdata_option_decode(xmlTextReaderPtr reader) {
  struct xdata_option_t *elm = NULL;
 elm = malloc (sizeof (struct xdata_option_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "label");
  if (avalue != NULL) {
  elm->fLabel = (const char*)avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "value") == 0) && (strcmp ((char*) namespace, ns_xdata) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fValue = (const char*) value;
  } // for end part 1
  } // while end
  return elm;
}

int xdata_option_encode(xmlWriter_t* writer, struct xdata_option_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_xdata, "option");
if (err != 0) return err;
if (elm->fLabel != NULL) {
err = xmlwriter_attribute (writer, ns_xdata, "label", elm->fLabel);
if (err != 0) return err;
}
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

enum xdata_x_type_t enum_xdata_x_type_from_string(const xmlChar *value) {
return 0;
}
const char* enum_xdata_x_type_to_string(enum xdata_x_type_t value) {
return NULL;
}
enum xdata_field_type_t enum_xdata_field_type_from_string(const xmlChar *value) {
return 0;
}
const char* enum_xdata_field_type_to_string(enum xdata_field_type_t value) {
return NULL;
}
