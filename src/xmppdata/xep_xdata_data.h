#ifndef _XEP_XDATA_DATA_H_
#define  _XEP_XDATA_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"

struct xdata_field_t;
struct xdata_option_t;

extern const char *ns_xdata;

enum xdata_x_type_t
{
  XDATA_X_TYPE_CANCEL,
  XDATA_X_TYPE_FORM,
  XDATA_X_TYPE_RESULT,
  XDATA_X_TYPE_SUBMIT,
};

enum xdata_x_type_t enum_xdata_x_type_from_string (const char *value);
const char *enum_xdata_x_type_to_string (enum xdata_x_type_t);
enum xdata_field_type_t
{
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

enum xdata_field_type_t enum_xdata_field_type_from_string (const char *value);
const char *enum_xdata_field_type_to_string (enum xdata_field_type_t);

struct xdata_x_t
{
  enum xdata_x_type_t fType;
  char *fTitle;
  array_t *fReported;
  array_t *fFields;
};


struct xdata_field_t
{
  char *fLabel;
  enum xdata_field_type_t fType;
  char *fVar;
  char *fDesc;
  bool fRequired;
  char *fValue;
  array_t *fOption;
};


struct xdata_option_t
{
  char *fLabel;
  char *fValue;
};


struct xdata_x_t *xdata_x_decode (xmlreader_t * reader);
int xdata_x_encode (xmlwriter_t * writer, struct xdata_x_t *data);
void xdata_x_free (struct xdata_x_t *data);
struct xdata_field_t *xdata_field_decode (xmlreader_t * reader);
int xdata_field_encode (xmlwriter_t * writer, struct xdata_field_t *data);
void xdata_field_free (struct xdata_field_t *data);
struct xdata_option_t *xdata_option_decode (xmlreader_t * reader);
int xdata_option_encode (xmlwriter_t * writer, struct xdata_option_t *data);
void xdata_option_free (struct xdata_option_t *data);
#endif
