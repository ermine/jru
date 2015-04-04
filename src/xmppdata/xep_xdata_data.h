#ifndef _XEP_XDATA_DATA_H_
#define  _XEP_XDATA_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"

struct xdata_field_t;
struct xdata_option_t;

extern const char* ns_xdata;

enum xdata_x_type_t {
  XDATA_X_TYPE_CANCEL,
  XDATA_X_TYPE_FORM,
  XDATA_X_TYPE_RESULT,
  XDATA_X_TYPE_SUBMIT,
};

enum xdata_x_type_t enum_xdata_x_type_from_string(const xmlChar *value);
xmlChar *enum_xdata_x_type_to_string(enum xdata_x_type_t);
enum xdata_field_type_t {
  XDATA_FIELD_TYPE_BOOLEAN,
  XDATA_FIELD_TYPE_FIXED,
  XDATA_FIELD_TYPE_HIDDEN,
  XDATA_FIELD_TYPE_JID_MULTI,
  XDATA_FIELD_TYPE_JID_SINGLE,
  XDATA_FIELD_TYPE_LIST_MULTI,
  XDATA_FIELD_TYPE_LIST_SINGLE,
  XDATA_FIELD_TYPE_TEXT_MULTI,
  XDATA_FIELD_TYPE_TEXT_PRIVATE,
  XDATA_FIELD_TYPE_TEXT_SINGLE,
};

enum xdata_field_type_t enum_xdata_field_type_from_string(const xmlChar *value);
xmlChar *enum_xdata_field_type_to_string(enum xdata_field_type_t);

struct xdata_x_t {
  enum xdata_x_type_t fType;
  const xmlChar * fTitle;
  llist_t *fReported;
 llist_t *fFields;
};


struct xdata_field_t {
  const xmlChar * fLabel;
  enum xdata_field_type_t fType;
  const xmlChar * fVar;
  const xmlChar * fDesc;
  boolean_t fRequired;
  const xmlChar * fValue;
  llist_t *fOption;
};


struct xdata_option_t {
  const xmlChar * fLabel;
  const xmlChar * fValue;
};


struct xdata_x_t* xdata_x_decode(xmlTextReaderPtr reader);
int xdata_x_encode(xmlTextWriterPtr writer, struct xdata_x_t* data);
struct xdata_field_t* xdata_field_decode(xmlTextReaderPtr reader);
int xdata_field_encode(xmlTextWriterPtr writer, struct xdata_field_t* data);
struct xdata_option_t* xdata_option_decode(xmlTextReaderPtr reader);
int xdata_option_encode(xmlTextWriterPtr writer, struct xdata_option_t* data);
#endif
