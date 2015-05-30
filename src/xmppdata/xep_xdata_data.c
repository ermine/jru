#include "xep_xdata_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_xdata = "jabber:x:data";

struct xdata_x_t *
xdata_x_decode (xmlreader_t * reader)
{
  struct xdata_x_t *elm = NULL;
  elm = malloc (sizeof (struct xdata_x_t));
  if (elm == NULL)
    fatal ("xdata_x_t: malloc failed");
  memset (elm, 0, sizeof (struct xdata_x_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "type");
  if (avalue != NULL)
    {
      elm->fType = enum_xdata_x_type_from_string (avalue);
    }
  int type = 0;
  while (1)
    {
      type = xmlreader_next (reader);
      if (type == XML_END_ELEMENT)
	break;
      if (type == XML_ERROR)
	return NULL;
      if (type == XML_START_ELEMENT)
	{
	  const char *namespace = xmlreader_get_namespace (reader);
	  const char *name = xmlreader_get_name (reader);
	  if ((strcmp (name, "title") == 0)
	      && (strcmp (namespace, ns_xdata) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fTitle = (char *) value;
	    }
	  else if ((strcmp (name, "reported") == 0)
		   && (strcmp (namespace, ns_xdata) == 0))
	    {
	      int type = 0;
	      while (1)
		{
		  type = xmlreader_next (reader);
		  if (type == XML_END_ELEMENT)
		    break;
		  if (type == XML_ERROR)
		    return NULL;
		  if (type == XML_START_ELEMENT)
		    {
		      if ((strcmp (namespace, ns_xdata) == 0)
			  && (strcmp (name, "field") == 0))
			{
			  struct xdata_field_t *newel =
			    xdata_field_decode (reader);
			  if (newel != NULL)
			    {
			      return NULL;
			    }
			  if (elm->fReported == NULL)
			    elm->fReported =
			      array_new (sizeof (extension_t), 0);
			  array_append (elm->fReported, newel);
			}
		    }
		}
	    }
	}
    }
  return elm;
}

int
xdata_x_encode (xmlwriter_t * writer, struct xdata_x_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_xdata, "x");
  if (err != 0)
    return err;
  if (elm->fType != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "type",
			     enum_xdata_x_type_to_string (elm->fType));
      if (err != 0)
	return err;
    }
  if (elm->fTitle != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_xdata, "title", elm->fTitle);
      if (err != 0)
	return err;
    }
  err = xmlwriter_start_element (writer, ns_xdata, "reported");
  if (err != 0)
    return err;
  int len = array_length (elm->fReported);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      struct xdata_field_t *data = array_get (elm->fReported, i);
      err = xdata_field_encode (writer, data);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  {
    int len = array_length (elm->fFields);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fFields, i);
	err = xstream_extension_encode (writer, ext->data, ext->type);
	if (err != 0)
	  return -1;
      }
  }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
xdata_x_free (struct xdata_x_t *data)
{
  if (data == NULL)
    return;
  if (data->fTitle != NULL)
    {
      free (data->fTitle);
    }
  int len = array_length (data->fReported);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      struct xdata_field_t *item = array_get (data->fReported, i);
      xdata_field_free (item);
    }
  array_free (data->fReported);
  {
    int len = array_length (data->fFields);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (data->fFields, i);
	xstream_extension_free (ext);
      }
    array_free (data->fFields);
  }
  free (data);
}

struct xdata_field_t *
xdata_field_decode (xmlreader_t * reader)
{
  struct xdata_field_t *elm = NULL;
  elm = malloc (sizeof (struct xdata_field_t));
  if (elm == NULL)
    fatal ("xdata_field_t: malloc failed");
  memset (elm, 0, sizeof (struct xdata_field_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "label");
  if (avalue != NULL)
    {
      elm->fLabel = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "type");
  if (avalue != NULL)
    {
      elm->fType = enum_xdata_field_type_from_string (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "var");
  if (avalue != NULL)
    {
      elm->fVar = (char *) avalue;
    }
  int type = 0;
  while (1)
    {
      type = xmlreader_next (reader);
      if (type == XML_END_ELEMENT)
	break;
      if (type == XML_ERROR)
	return NULL;
      if (type == XML_START_ELEMENT)
	{
	  const char *namespace = xmlreader_get_namespace (reader);
	  const char *name = xmlreader_get_name (reader);
	  if ((strcmp (name, "desc") == 0)
	      && (strcmp (namespace, ns_xdata) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fDesc = (char *) value;
	    }
	  else if ((strcmp (name, "required") == 0)
		   && (strcmp (namespace, ns_xdata) == 0))
	    {
	      elm->fRequired = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "value") == 0)
		   && (strcmp (namespace, ns_xdata) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fValue = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_xdata) == 0)
		   && (strcmp (name, "option") == 0))
	    {
	      struct xdata_option_t *newel = xdata_option_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      if (elm->fOption == NULL)
		elm->fOption = array_new (sizeof (extension_t), 0);
	      array_append (elm->fOption, newel);
	    }
	}
    }
  return elm;
}

int
xdata_field_encode (xmlwriter_t * writer, struct xdata_field_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_xdata, "field");
  if (err != 0)
    return err;
  if (elm->fLabel != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "label", elm->fLabel);
      if (err != 0)
	return err;
    }
  if (elm->fType != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "type",
			     enum_xdata_field_type_to_string (elm->fType));
      if (err != 0)
	return err;
    }
  if (elm->fVar != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "var", elm->fVar);
      if (err != 0)
	return err;
    }
  if (elm->fDesc != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_xdata, "desc", elm->fDesc);
      if (err != 0)
	return err;
    }
  if (elm->fRequired)
    {
      err = xmlwriter_simple_element (writer, ns_xdata, "required", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fValue != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_xdata, "value", elm->fValue);
      if (err != 0)
	return err;
    }
  {
    int len = array_length (elm->fOption);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fOption, i);
	err = xdata_option_encode (writer, ext->data);
	if (err != 0)
	  return err;
      }
  }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
xdata_field_free (struct xdata_field_t *data)
{
  if (data == NULL)
    return;
  if (data->fLabel != NULL)
    {
      free (data->fLabel);
    }
  if (data->fVar != NULL)
    {
      free (data->fVar);
    }
  if (data->fDesc != NULL)
    {
      free (data->fDesc);
    }
  if (data->fRequired)
    {
    }
  if (data->fValue != NULL)
    {
      free (data->fValue);
    }
  {
    int len = array_length (data->fOption);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	xdata_option_free (array_get (data->fOption, i));
      }
    array_free (data->fOption);
  }
  free (data);
}

struct xdata_option_t *
xdata_option_decode (xmlreader_t * reader)
{
  struct xdata_option_t *elm = NULL;
  elm = malloc (sizeof (struct xdata_option_t));
  if (elm == NULL)
    fatal ("xdata_option_t: malloc failed");
  memset (elm, 0, sizeof (struct xdata_option_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "label");
  if (avalue != NULL)
    {
      elm->fLabel = (char *) avalue;
    }
  int type = 0;
  while (1)
    {
      type = xmlreader_next (reader);
      if (type == XML_END_ELEMENT)
	break;
      if (type == XML_ERROR)
	return NULL;
      if (type == XML_START_ELEMENT)
	{
	  const char *namespace = xmlreader_get_namespace (reader);
	  const char *name = xmlreader_get_name (reader);
	  if ((strcmp (name, "value") == 0)
	      && (strcmp (namespace, ns_xdata) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fValue = (char *) value;
	    }
	}
    }
  return elm;
}

int
xdata_option_encode (xmlwriter_t * writer, struct xdata_option_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_xdata, "option");
  if (err != 0)
    return err;
  if (elm->fLabel != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "label", elm->fLabel);
      if (err != 0)
	return err;
    }
  if (elm->fValue != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_xdata, "value", elm->fValue);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
xdata_option_free (struct xdata_option_t *data)
{
  if (data == NULL)
    return;
  if (data->fLabel != NULL)
    {
      free (data->fLabel);
    }
  if (data->fValue != NULL)
    {
      free (data->fValue);
    }
  free (data);
}

enum xdata_x_type_t
enum_xdata_x_type_from_string (const char *value)
{
  if (strcmp (value, "cancel") == 0)
    return XDATA_X_TYPE_CANCEL;
  else if (strcmp (value, "form") == 0)
    return XDATA_X_TYPE_FORM;
  else if (strcmp (value, "result") == 0)
    return XDATA_X_TYPE_RESULT;
  else if (strcmp (value, "submit") == 0)
    return XDATA_X_TYPE_SUBMIT;
  return 0;
}

const char *
enum_xdata_x_type_to_string (enum xdata_x_type_t value)
{
  switch (value)
    {
    case XDATA_X_TYPE_CANCEL:
      return "cancel";
    case XDATA_X_TYPE_FORM:
      return "form";
    case XDATA_X_TYPE_RESULT:
      return "result";
    case XDATA_X_TYPE_SUBMIT:
      return "submit";
    }
  return NULL;
}

enum xdata_field_type_t
enum_xdata_field_type_from_string (const char *value)
{
  if (strcmp (value, "boolean") == 0)
    return XDATA_FIELD_TYPE_BOOLEAN;
  else if (strcmp (value, "fixed") == 0)
    return XDATA_FIELD_TYPE_FIXED;
  else if (strcmp (value, "hidden") == 0)
    return XDATA_FIELD_TYPE_HIDDEN;
  else if (strcmp (value, "jid-multi") == 0)
    return XDATA_FIELD_TYPE_JID_MULTI;
  else if (strcmp (value, "jid-single") == 0)
    return XDATA_FIELD_TYPE_JID_SINGLE;
  else if (strcmp (value, "list-multi") == 0)
    return XDATA_FIELD_TYPE_LIST_MULTI;
  else if (strcmp (value, "list-single") == 0)
    return XDATA_FIELD_TYPE_LIST_SINGLE;
  else if (strcmp (value, "text-multi") == 0)
    return XDATA_FIELD_TYPE_TEXT_MULTI;
  else if (strcmp (value, "text-private") == 0)
    return XDATA_FIELD_TYPE_TEXT_PRIVATE;
  else if (strcmp (value, "text-single") == 0)
    return XDATA_FIELD_TYPE_TEXT_SINGLE;
  return 0;
}

const char *
enum_xdata_field_type_to_string (enum xdata_field_type_t value)
{
  switch (value)
    {
    case XDATA_FIELD_TYPE_BOOLEAN:
      return "boolean";
    case XDATA_FIELD_TYPE_FIXED:
      return "fixed";
    case XDATA_FIELD_TYPE_HIDDEN:
      return "hidden";
    case XDATA_FIELD_TYPE_JID_MULTI:
      return "jid-multi";
    case XDATA_FIELD_TYPE_JID_SINGLE:
      return "jid-single";
    case XDATA_FIELD_TYPE_LIST_MULTI:
      return "list-multi";
    case XDATA_FIELD_TYPE_LIST_SINGLE:
      return "list-single";
    case XDATA_FIELD_TYPE_TEXT_MULTI:
      return "text-multi";
    case XDATA_FIELD_TYPE_TEXT_PRIVATE:
      return "text-private";
    case XDATA_FIELD_TYPE_TEXT_SINGLE:
      return "text-single";
    }
  return NULL;
}
