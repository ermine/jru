#include "xep_iqregister_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_iqregister = "jabber:iq:register";

struct iqregister_query_t *
iqregister_query_decode (xmlreader_t * reader)
{
  struct iqregister_query_t *elm = NULL;
  elm = malloc (sizeof (struct iqregister_query_t));
  if (elm == NULL)
    fatal ("iqregister_query_t: malloc failed");
  memset (elm, 0, sizeof (struct iqregister_query_t));
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
	  if ((strcmp (namespace, ns_iqregister) == 0)
	      && (strcmp (name, "registered") == 0))
	    {
	      if (xmlreader_skip_element (reader) == 1)
		return NULL;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "instructions") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fInstructions = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "username") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fUsername = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "nick") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fNick = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "password") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fPassword = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "name") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fName = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "first") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fFirst = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "last") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fLast = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "email") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fEmail = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "address") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fAddress = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "city") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fCity = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "state") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fState = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "zip") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fZip = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "phone") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fPhone = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "url") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fUrl = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "date") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fDate = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "misc") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fMisc = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "text") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fText = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_iqregister) == 0)
		   && (strcmp (name, "key") == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFields.fKey = (char *) value;
	    }
	  else if ((strcmp (name, "remove") == 0)
		   && (strcmp (namespace, ns_iqregister) == 0))
	    {
	      elm->fRemove = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (namespace, "jabber:x:data") == 0)
		   && (strcmp (name, "x") == 0))
	    {
	      struct xdata_x_t *newel = xdata_x_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->fXdata = newel;
	    }
	  else if ((strcmp (namespace, "jabber:x:oob") == 0)
		   && (strcmp (name, "x") == 0))
	    {
	      struct xoob_x_t *newel = xoob_x_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->fXoob = newel;
	    }
	}
    }
  return elm;
}

int
iqregister_query_encode (xmlwriter_t * writer, struct iqregister_query_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_iqregister, "query");
  if (err != 0)
    return err;
  if (elm->fFields.fRegistered)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "registered", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fInstructions != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "instructions",
				  elm->fFields.fInstructions);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fUsername != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "username",
				  elm->fFields.fUsername);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fNick != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "nick",
				  elm->fFields.fNick);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fPassword != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "password",
				  elm->fFields.fPassword);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fName != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "name",
				  elm->fFields.fName);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fFirst != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "first",
				  elm->fFields.fFirst);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fLast != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "last",
				  elm->fFields.fLast);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fEmail != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "email",
				  elm->fFields.fEmail);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fAddress != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "address",
				  elm->fFields.fAddress);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fCity != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "city",
				  elm->fFields.fCity);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fState != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "state",
				  elm->fFields.fState);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fZip != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "zip",
				  elm->fFields.fZip);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fPhone != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "phone",
				  elm->fFields.fPhone);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fUrl != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "url",
				  elm->fFields.fUrl);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fDate != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "date",
				  elm->fFields.fDate);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fMisc != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "misc",
				  elm->fFields.fMisc);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fText != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "text",
				  elm->fFields.fText);
      if (err != 0)
	return err;
    }
  if (elm->fFields.fKey != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqregister, "key",
				  elm->fFields.fKey);
      if (err != 0)
	return err;
    }
  if (elm->fRemove)
    {
      err = xmlwriter_simple_element (writer, ns_iqregister, "remove", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fXdata != NULL)
    {
      err = xdata_x_encode (writer, elm->fXdata);
      if (err != 0)
	return err;
    }
  if (elm->fXoob != NULL)
    {
      err = xoob_x_encode (writer, elm->fXoob);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
iqregister_query_free (struct iqregister_query_t *data)
{
  if (data == NULL)
    return;
  if (data->fFields.fRegistered)
    {
    }
  if (data->fFields.fInstructions != NULL)
    {
      free (data->fFields.fInstructions);
    }
  if (data->fFields.fUsername != NULL)
    {
      free (data->fFields.fUsername);
    }
  if (data->fFields.fNick != NULL)
    {
      free (data->fFields.fNick);
    }
  if (data->fFields.fPassword != NULL)
    {
      free (data->fFields.fPassword);
    }
  if (data->fFields.fName != NULL)
    {
      free (data->fFields.fName);
    }
  if (data->fFields.fFirst != NULL)
    {
      free (data->fFields.fFirst);
    }
  if (data->fFields.fLast != NULL)
    {
      free (data->fFields.fLast);
    }
  if (data->fFields.fEmail != NULL)
    {
      free (data->fFields.fEmail);
    }
  if (data->fFields.fAddress != NULL)
    {
      free (data->fFields.fAddress);
    }
  if (data->fFields.fCity != NULL)
    {
      free (data->fFields.fCity);
    }
  if (data->fFields.fState != NULL)
    {
      free (data->fFields.fState);
    }
  if (data->fFields.fZip != NULL)
    {
      free (data->fFields.fZip);
    }
  if (data->fFields.fPhone != NULL)
    {
      free (data->fFields.fPhone);
    }
  if (data->fFields.fUrl != NULL)
    {
      free (data->fFields.fUrl);
    }
  if (data->fFields.fDate != NULL)
    {
      free (data->fFields.fDate);
    }
  if (data->fFields.fMisc != NULL)
    {
      free (data->fFields.fMisc);
    }
  if (data->fFields.fText != NULL)
    {
      free (data->fFields.fText);
    }
  if (data->fFields.fKey != NULL)
    {
      free (data->fFields.fKey);
    }
  if (data->fRemove)
    {
    }
  if (data->fXdata != NULL)
    {
      xdata_x_free (data->fXdata);
    }
  if (data->fXoob != NULL)
    {
      xoob_x_free (data->fXoob);
    }
  free (data);
}
