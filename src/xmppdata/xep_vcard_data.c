#include "xep_vcard_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_vcard = "vcard-temp";

struct vcard_vcard_t *
vcard_vcard_decode (xmlreader_t * reader)
{
  struct vcard_vcard_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_vcard_t));
  if (elm == NULL)
    fatal ("vcard_vcard_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_vcard_t));
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
	  if ((strcmp (name, "VERSION") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fVERSION = (char *) value;
	    }
	  else if ((strcmp (name, "FN") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFN = (char *) value;
	    }
	}
    }
  return elm;
}

int
vcard_vcard_encode (xmlwriter_t * writer, struct vcard_vcard_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "vCard");
  if (err != 0)
    return err;
  if (elm->fVERSION != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "VERSION", elm->fVERSION);
      if (err != 0)
	return err;
    }
  if (elm->fFN != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "FN", elm->fFN);
      if (err != 0)
	return err;
    }
  if (elm->fN != NULL)
    {
      err = vcard_N_encode (writer, elm->fN);
      if (err != 0)
	return err;
    }
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
vcard_vcard_free (struct vcard_vcard_t *data)
{
  if (data == NULL)
    return;
  if (data->fVERSION != NULL)
    {
      free (data->fVERSION);
    }
  if (data->fFN != NULL)
    {
      free (data->fFN);
    }
  if (data->fN != NULL)
    {
    }
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

struct vcard_N_t *
vcard_N_decode (xmlreader_t * reader)
{
  struct vcard_N_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_N_t));
  if (elm == NULL)
    fatal ("vcard_N_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_N_t));
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
	  if ((strcmp (name, "FAMILY") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fFAMILY = (char *) value;
	    }
	  else if ((strcmp (name, "GIVEN") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fGIVEN = (char *) value;
	    }
	  else if ((strcmp (name, "NIDDLE") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fNIDDLE = (char *) value;
	    }
	  else if ((strcmp (name, "PREFIX") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fPREFIX = (char *) value;
	    }
	  else if ((strcmp (name, "SUFFIX") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fSUFFIX = (char *) value;
	    }
	}
    }
  return elm;
}

int
vcard_N_encode (xmlwriter_t * writer, struct vcard_N_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "N");
  if (err != 0)
    return err;
  if (elm->fFAMILY != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "FAMILY", elm->fFAMILY);
      if (err != 0)
	return err;
    }
  if (elm->fGIVEN != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "GIVEN", elm->fGIVEN);
      if (err != 0)
	return err;
    }
  if (elm->fNIDDLE != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "NIDDLE", elm->fNIDDLE);
      if (err != 0)
	return err;
    }
  if (elm->fPREFIX != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "PREFIX", elm->fPREFIX);
      if (err != 0)
	return err;
    }
  if (elm->fSUFFIX != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "SUFFIX", elm->fSUFFIX);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_N_free (struct vcard_N_t *data)
{
  if (data == NULL)
    return;
  if (data->fFAMILY != NULL)
    {
      free (data->fFAMILY);
    }
  if (data->fGIVEN != NULL)
    {
      free (data->fGIVEN);
    }
  if (data->fNIDDLE != NULL)
    {
      free (data->fNIDDLE);
    }
  if (data->fPREFIX != NULL)
    {
      free (data->fPREFIX);
    }
  if (data->fSUFFIX != NULL)
    {
      free (data->fSUFFIX);
    }
  free (data);
}

vcard_NICKNAME_t *
vcard_NICKNAME_decode (xmlreader_t * reader)
{
  vcard_NICKNAME_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_NICKNAME_t *) value;
  return elm;
}

int
vcard_NICKNAME_encode (xmlwriter_t * writer, vcard_NICKNAME_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "NICKNAME",
			      (vcard_NICKNAME_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_NICKNAME_free (vcard_NICKNAME_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

struct vcard_PHOTO_t *
vcard_PHOTO_decode (xmlreader_t * reader)
{
  struct vcard_PHOTO_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_PHOTO_t));
  if (elm == NULL)
    fatal ("vcard_PHOTO_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_PHOTO_t));
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
	  if ((strcmp (name, "TYPE") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fTYPE = (char *) value;
	    }
	  else if ((strcmp (name, "BINVAL") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fBINVAL = (char *) value;
	    }
	  else if ((strcmp (name, "EXTVAL") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fEXTVAL = (char *) value;
	    }
	}
    }
  return elm;
}

int
vcard_PHOTO_encode (xmlwriter_t * writer, struct vcard_PHOTO_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "PHOTO");
  if (err != 0)
    return err;
  if (elm->fTYPE != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "TYPE", elm->fTYPE);
      if (err != 0)
	return err;
    }
  if (elm->fBINVAL != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "BINVAL", elm->fBINVAL);
      if (err != 0)
	return err;
    }
  if (elm->fEXTVAL != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "EXTVAL", elm->fEXTVAL);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_PHOTO_free (struct vcard_PHOTO_t *data)
{
  if (data == NULL)
    return;
  if (data->fTYPE != NULL)
    {
      free (data->fTYPE);
    }
  if (data->fBINVAL != NULL)
    {
      free (data->fBINVAL);
    }
  if (data->fEXTVAL != NULL)
    {
      free (data->fEXTVAL);
    }
  free (data);
}

vcard_BDAY_t *
vcard_BDAY_decode (xmlreader_t * reader)
{
  vcard_BDAY_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_BDAY_t *) value;
  return elm;
}

int
vcard_BDAY_encode (xmlwriter_t * writer, vcard_BDAY_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "BDAY", (vcard_BDAY_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_BDAY_free (vcard_BDAY_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

enum vcard_DOMINTL_t
enum_vcard_DOMINTL_from_string (const char *value)
{
  if (strcmp (value, "DOM") == 0)
    return VCARD_DOMINTL_DOM;
  else if (strcmp (value, "INTL") == 0)
    return VCARD_DOMINTL_INTL;
  return 0;
}

const char *
enum_vcard_DOMINTL_to_string (enum vcard_DOMINTL_t value)
{
  switch (value)
    {
    case VCARD_DOMINTL_DOM:
      return "DOM";
    case VCARD_DOMINTL_INTL:
      return "INTL";
    }
  return NULL;
}

struct vcard_ADR_t *
vcard_ADR_decode (xmlreader_t * reader)
{
  struct vcard_ADR_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_ADR_t));
  if (elm == NULL)
    fatal ("vcard_ADR_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_ADR_t));
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
	  if ((strcmp (name, "HOME") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fHOME = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "WORK") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fWORK = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "POSTAL") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPOSTAL = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "PARCEL") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPARCEL = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "PREF") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPREF = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "POBOX") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fPOBOX = (char *) value;
	    }
	  else if ((strcmp (name, "EXTADD") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fEXTADD = (char *) value;
	    }
	  else if ((strcmp (name, "STREET") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fSTREET = (char *) value;
	    }
	  else if ((strcmp (name, "LOCALITY") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fLOCALITY = (char *) value;
	    }
	  else if ((strcmp (name, "REGION") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fREGION = (char *) value;
	    }
	  else if ((strcmp (name, "PCODE") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fPCODE = (char *) value;
	    }
	  else if ((strcmp (name, "CTRY") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fCTRY = (char *) value;
	    }
	  else if (strcmp (namespace, ns_vcard) != 0)
	    {
	      elm->fDOMINTL = enum_vcard_DOMINTL_from_string (name);
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	}
    }
  return elm;
}

int
vcard_ADR_encode (xmlwriter_t * writer, struct vcard_ADR_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "ADR");
  if (err != 0)
    return err;
  if (elm->fHOME)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "HOME", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fWORK)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "WORK", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPOSTAL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "POSTAL", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPARCEL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "PARCEL", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fDOMINTL != 0)
    {
      const char *name = enum_vcard_DOMINTL_to_string (elm->fDOMINTL);
      err = xmlwriter_simple_element (writer, ns_vcard, name, NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPREF)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "PREF", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPOBOX != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "POBOX", elm->fPOBOX);
      if (err != 0)
	return err;
    }
  if (elm->fEXTADD != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "EXTADD", elm->fEXTADD);
      if (err != 0)
	return err;
    }
  if (elm->fSTREET != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "STREET", elm->fSTREET);
      if (err != 0)
	return err;
    }
  if (elm->fLOCALITY != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "LOCALITY",
				  elm->fLOCALITY);
      if (err != 0)
	return err;
    }
  if (elm->fREGION != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "REGION", elm->fREGION);
      if (err != 0)
	return err;
    }
  if (elm->fPCODE != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "PCODE", elm->fPCODE);
      if (err != 0)
	return err;
    }
  if (elm->fCTRY != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "CTRY", elm->fCTRY);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_ADR_free (struct vcard_ADR_t *data)
{
  if (data == NULL)
    return;
  if (data->fHOME)
    {
    }
  if (data->fWORK)
    {
    }
  if (data->fPOSTAL)
    {
    }
  if (data->fPARCEL)
    {
    }
  if (data->fDOMINTL != 0)
    {
    }
  if (data->fPREF)
    {
    }
  if (data->fPOBOX != NULL)
    {
      free (data->fPOBOX);
    }
  if (data->fEXTADD != NULL)
    {
      free (data->fEXTADD);
    }
  if (data->fSTREET != NULL)
    {
      free (data->fSTREET);
    }
  if (data->fLOCALITY != NULL)
    {
      free (data->fLOCALITY);
    }
  if (data->fREGION != NULL)
    {
      free (data->fREGION);
    }
  if (data->fPCODE != NULL)
    {
      free (data->fPCODE);
    }
  if (data->fCTRY != NULL)
    {
      free (data->fCTRY);
    }
  free (data);
}

struct vcard_LABEL_t *
vcard_LABEL_decode (xmlreader_t * reader)
{
  struct vcard_LABEL_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_LABEL_t));
  if (elm == NULL)
    fatal ("vcard_LABEL_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_LABEL_t));
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
	  if ((strcmp (name, "HOME") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fHOME = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "WORK") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fWORK = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "POSTAL") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPOSTAL = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "PARCEL") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPARCEL = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "PREF") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPREF = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "LINE") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      if (elm->fLINE == NULL)
		elm->fLINE = array_new (sizeof (char *), 0);
	      array_append (elm->fLINE, (void *) &value);
	    }
	  else if (strcmp (namespace, ns_vcard) != 0)
	    {
	      elm->fDOMINTL = enum_vcard_DOMINTL_from_string (name);
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	}
    }
  return elm;
}

int
vcard_LABEL_encode (xmlwriter_t * writer, struct vcard_LABEL_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "LABEL");
  if (err != 0)
    return err;
  if (elm->fHOME)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "HOME", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fWORK)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "WORK", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPOSTAL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "POSTAL", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPARCEL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "PARCEL", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fDOMINTL != 0)
    {
      const char *name = enum_vcard_DOMINTL_to_string (elm->fDOMINTL);
      err = xmlwriter_simple_element (writer, ns_vcard, name, NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPREF)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "PREF", NULL);
      if (err != 0)
	return err;
    }
  int len = array_length (elm->fLINE);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (elm->fLINE, i);
      err =
	xmlwriter_simple_element (writer, ns_vcard, "LINE", (char *) value);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_LABEL_free (struct vcard_LABEL_t *data)
{
  if (data == NULL)
    return;
  if (data->fHOME)
    {
    }
  if (data->fWORK)
    {
    }
  if (data->fPOSTAL)
    {
    }
  if (data->fPARCEL)
    {
    }
  if (data->fDOMINTL != 0)
    {
    }
  if (data->fPREF)
    {
    }
  int len = array_length (data->fLINE);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (data->fLINE, i);
      free (*value);
    }
  array_free (data->fLINE);
  free (data);
}

struct vcard_TEL_t *
vcard_TEL_decode (xmlreader_t * reader)
{
  struct vcard_TEL_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_TEL_t));
  if (elm == NULL)
    fatal ("vcard_TEL_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_TEL_t));
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
	  if ((strcmp (name, "HOME") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fHOME = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "WORK") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fWORK = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "VOICE") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fVOICE = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "FAX") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fFAX = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "PAGER") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPAGER = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "MSG") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fMSG = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "CELL") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fCELL = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "VIDEO") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fVIDEO = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "BBS") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fBBS = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "MODEM") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fMODEM = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "ISDN") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fISDN = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "PCS") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPCS = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "PREF") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPREF = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "NUMBER") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fNUMBER = (char *) value;
	    }
	}
    }
  return elm;
}

int
vcard_TEL_encode (xmlwriter_t * writer, struct vcard_TEL_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "TEL");
  if (err != 0)
    return err;
  if (elm->fHOME)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "HOME", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fWORK)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "WORK", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fVOICE)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "VOICE", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fFAX)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "FAX", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPAGER)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "PAGER", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fMSG)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "MSG", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fCELL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "CELL", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fVIDEO)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "VIDEO", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fBBS)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "BBS", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fMODEM)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "MODEM", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fISDN)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "ISDN", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPCS)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "PCS", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPREF)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "PREF", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fNUMBER != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "NUMBER", elm->fNUMBER);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_TEL_free (struct vcard_TEL_t *data)
{
  if (data == NULL)
    return;
  if (data->fHOME)
    {
    }
  if (data->fWORK)
    {
    }
  if (data->fVOICE)
    {
    }
  if (data->fFAX)
    {
    }
  if (data->fPAGER)
    {
    }
  if (data->fMSG)
    {
    }
  if (data->fCELL)
    {
    }
  if (data->fVIDEO)
    {
    }
  if (data->fBBS)
    {
    }
  if (data->fMODEM)
    {
    }
  if (data->fISDN)
    {
    }
  if (data->fPCS)
    {
    }
  if (data->fPREF)
    {
    }
  if (data->fNUMBER != NULL)
    {
      free (data->fNUMBER);
    }
  free (data);
}

struct vcard_EMAIL_t *
vcard_EMAIL_decode (xmlreader_t * reader)
{
  struct vcard_EMAIL_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_EMAIL_t));
  if (elm == NULL)
    fatal ("vcard_EMAIL_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_EMAIL_t));
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
	  if ((strcmp (name, "HOME") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fHOME = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "WORK") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fWORK = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "INTERNET") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fINTERNET = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "PREF") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fPREF = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "X400") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      elm->fX400 = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	  else if ((strcmp (name, "USERID") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fUSERID = (char *) value;
	    }
	}
    }
  return elm;
}

int
vcard_EMAIL_encode (xmlwriter_t * writer, struct vcard_EMAIL_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "EMAIL");
  if (err != 0)
    return err;
  if (elm->fHOME)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "HOME", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fWORK)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "WORK", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fINTERNET)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "INTERNET", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPREF)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "PREF", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fX400)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "X400", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fUSERID != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "USERID", elm->fUSERID);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_EMAIL_free (struct vcard_EMAIL_t *data)
{
  if (data == NULL)
    return;
  if (data->fHOME)
    {
    }
  if (data->fWORK)
    {
    }
  if (data->fINTERNET)
    {
    }
  if (data->fPREF)
    {
    }
  if (data->fX400)
    {
    }
  if (data->fUSERID != NULL)
    {
      free (data->fUSERID);
    }
  free (data);
}

vcard_JABBERID_t *
vcard_JABBERID_decode (xmlreader_t * reader)
{
  vcard_JABBERID_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_JABBERID_t *) value;
  return elm;
}

int
vcard_JABBERID_encode (xmlwriter_t * writer, vcard_JABBERID_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "JABBERID",
			      (vcard_JABBERID_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_JABBERID_free (vcard_JABBERID_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

vcard_MAILER_t *
vcard_MAILER_decode (xmlreader_t * reader)
{
  vcard_MAILER_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_MAILER_t *) value;
  return elm;
}

int
vcard_MAILER_encode (xmlwriter_t * writer, vcard_MAILER_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "MAILER",
			      (vcard_MAILER_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_MAILER_free (vcard_MAILER_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

vcard_TZ_t *
vcard_TZ_decode (xmlreader_t * reader)
{
  vcard_TZ_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_TZ_t *) value;
  return elm;
}

int
vcard_TZ_encode (xmlwriter_t * writer, vcard_TZ_t * elm)
{
  int err = 0;
  err = xmlwriter_simple_element (writer, ns_vcard, "TZ", (vcard_TZ_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_TZ_free (vcard_TZ_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

struct vcard_GEO_t *
vcard_GEO_decode (xmlreader_t * reader)
{
  struct vcard_GEO_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_GEO_t));
  if (elm == NULL)
    fatal ("vcard_GEO_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_GEO_t));
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
	  if ((strcmp (name, "LAT") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fLAT = (char *) value;
	    }
	  else if ((strcmp (name, "LON") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fLON = (char *) value;
	    }
	}
    }
  return elm;
}

int
vcard_GEO_encode (xmlwriter_t * writer, struct vcard_GEO_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "GEO");
  if (err != 0)
    return err;
  if (elm->fLAT != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "LAT", elm->fLAT);
      if (err != 0)
	return err;
    }
  if (elm->fLON != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "LON", elm->fLON);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_GEO_free (struct vcard_GEO_t *data)
{
  if (data == NULL)
    return;
  if (data->fLAT != NULL)
    {
      free (data->fLAT);
    }
  if (data->fLON != NULL)
    {
      free (data->fLON);
    }
  free (data);
}

vcard_TITLE_t *
vcard_TITLE_decode (xmlreader_t * reader)
{
  vcard_TITLE_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_TITLE_t *) value;
  return elm;
}

int
vcard_TITLE_encode (xmlwriter_t * writer, vcard_TITLE_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "TITLE",
			      (vcard_TITLE_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_TITLE_free (vcard_TITLE_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

vcard_ROLE_t *
vcard_ROLE_decode (xmlreader_t * reader)
{
  vcard_ROLE_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_ROLE_t *) value;
  return elm;
}

int
vcard_ROLE_encode (xmlwriter_t * writer, vcard_ROLE_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "ROLE", (vcard_ROLE_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_ROLE_free (vcard_ROLE_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

struct vcard_LOGO_t *
vcard_LOGO_decode (xmlreader_t * reader)
{
  struct vcard_LOGO_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_LOGO_t));
  if (elm == NULL)
    fatal ("vcard_LOGO_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_LOGO_t));
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
	  if ((strcmp (name, "TYPE") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fTYPE = (char *) value;
	    }
	  else if ((strcmp (name, "BINVAL") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fBINVAL = (char *) value;
	    }
	  else if ((strcmp (name, "EXTVAL") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fEXTVAL = (char *) value;
	    }
	}
    }
  return elm;
}

int
vcard_LOGO_encode (xmlwriter_t * writer, struct vcard_LOGO_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "LOGO");
  if (err != 0)
    return err;
  if (elm->fTYPE != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "TYPE", elm->fTYPE);
      if (err != 0)
	return err;
    }
  if (elm->fBINVAL != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "BINVAL", elm->fBINVAL);
      if (err != 0)
	return err;
    }
  if (elm->fEXTVAL != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "EXTVAL", elm->fEXTVAL);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_LOGO_free (struct vcard_LOGO_t *data)
{
  if (data == NULL)
    return;
  if (data->fTYPE != NULL)
    {
      free (data->fTYPE);
    }
  if (data->fBINVAL != NULL)
    {
      free (data->fBINVAL);
    }
  if (data->fEXTVAL != NULL)
    {
      free (data->fEXTVAL);
    }
  free (data);
}

vcard_EXTVAL_t *
vcard_EXTVAL_decode (xmlreader_t * reader)
{
  vcard_EXTVAL_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_EXTVAL_t *) value;
  return elm;
}

int
vcard_EXTVAL_encode (xmlwriter_t * writer, vcard_EXTVAL_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "EXTVAL",
			      (vcard_EXTVAL_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_EXTVAL_free (vcard_EXTVAL_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

struct vcard_AGENT_t *
vcard_AGENT_decode (xmlreader_t * reader)
{
  struct vcard_AGENT_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_AGENT_t));
  if (elm == NULL)
    fatal ("vcard_AGENT_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_AGENT_t));
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
	  if ((strcmp (namespace, ns_vcard) == 0)
	      && (strcmp (name, "vCard") == 0))
	    {
	      struct vcard_vcard_t *newel = vcard_vcard_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->type = EXTENSION_TYPE_VCARD_VCARD;
	      elm->u->fVcard = newel;
	    }
	  else if ((strcmp (namespace, ns_vcard) == 0)
		   && (strcmp (name, "EXTVAL") == 0))
	    {
	      vcard_EXTVAL_t *newel = vcard_EXTVAL_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->type = EXTENSION_TYPE_VCARD_EXTVAL;
	      elm->u->fEXTVAL = newel;
	    }
	}
    }
  return elm;
}

int
vcard_AGENT_encode (xmlwriter_t * writer, struct vcard_AGENT_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "AGENT");
  if (err != 0)
    return err;
  if (elm->u != NULL)
    {
      err = xstream_extension_encode (writer, (void *) elm->u, elm->type);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_AGENT_free (struct vcard_AGENT_t *data)
{
  if (data == NULL)
    return;
  if (data->u != NULL)
    {
      extension_t ext = { data->type, data->u };
      xstream_extension_free (&ext);
    }
  free (data);
}

struct vcard_ORG_t *
vcard_ORG_decode (xmlreader_t * reader)
{
  struct vcard_ORG_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_ORG_t));
  if (elm == NULL)
    fatal ("vcard_ORG_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_ORG_t));
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
	  if ((strcmp (name, "ORGNAME") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fORGNAME = (char *) value;
	    }
	  else if ((strcmp (name, "ORGUNIT") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      if (elm->fORGUNIT == NULL)
		elm->fORGUNIT = array_new (sizeof (char *), 0);
	      array_append (elm->fORGUNIT, (void *) &value);
	    }
	}
    }
  return elm;
}

int
vcard_ORG_encode (xmlwriter_t * writer, struct vcard_ORG_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "ORG");
  if (err != 0)
    return err;
  if (elm->fORGNAME != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_vcard, "ORGNAME", elm->fORGNAME);
      if (err != 0)
	return err;
    }
  int len = array_length (elm->fORGUNIT);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (elm->fORGUNIT, i);
      err =
	xmlwriter_simple_element (writer, ns_vcard, "ORGUNIT",
				  (char *) value);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_ORG_free (struct vcard_ORG_t *data)
{
  if (data == NULL)
    return;
  if (data->fORGNAME != NULL)
    {
      free (data->fORGNAME);
    }
  int len = array_length (data->fORGUNIT);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (data->fORGUNIT, i);
      free (*value);
    }
  array_free (data->fORGUNIT);
  free (data);
}

struct vcard_CATEGORIES_t *
vcard_CATEGORIES_decode (xmlreader_t * reader)
{
  struct vcard_CATEGORIES_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_CATEGORIES_t));
  if (elm == NULL)
    fatal ("vcard_CATEGORIES_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_CATEGORIES_t));
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
	  if ((strcmp (name, "KEYWORD") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      if (elm->fKEYWORD == NULL)
		elm->fKEYWORD = array_new (sizeof (char *), 0);
	      array_append (elm->fKEYWORD, (void *) &value);
	    }
	}
    }
  return elm;
}

int
vcard_CATEGORIES_encode (xmlwriter_t * writer, struct vcard_CATEGORIES_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "CATEGORIES");
  if (err != 0)
    return err;
  int len = array_length (elm->fKEYWORD);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (elm->fKEYWORD, i);
      err =
	xmlwriter_simple_element (writer, ns_vcard, "KEYWORD",
				  (char *) value);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_CATEGORIES_free (struct vcard_CATEGORIES_t *data)
{
  if (data == NULL)
    return;
  int len = array_length (data->fKEYWORD);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (data->fKEYWORD, i);
      free (*value);
    }
  array_free (data->fKEYWORD);
  free (data);
}

vcard_NOTE_t *
vcard_NOTE_decode (xmlreader_t * reader)
{
  vcard_NOTE_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_NOTE_t *) value;
  return elm;
}

int
vcard_NOTE_encode (xmlwriter_t * writer, vcard_NOTE_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "NOTE", (vcard_NOTE_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_NOTE_free (vcard_NOTE_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

vcard_PRODID_t *
vcard_PRODID_decode (xmlreader_t * reader)
{
  vcard_PRODID_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_PRODID_t *) value;
  return elm;
}

int
vcard_PRODID_encode (xmlwriter_t * writer, vcard_PRODID_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "PRODID",
			      (vcard_PRODID_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_PRODID_free (vcard_PRODID_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

vcard_REV_t *
vcard_REV_decode (xmlreader_t * reader)
{
  vcard_REV_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_REV_t *) value;
  return elm;
}

int
vcard_REV_encode (xmlwriter_t * writer, vcard_REV_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "REV", (vcard_REV_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_REV_free (vcard_REV_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

vcard_SORT_STRING_t *
vcard_SORT_STRING_decode (xmlreader_t * reader)
{
  vcard_SORT_STRING_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_SORT_STRING_t *) value;
  return elm;
}

int
vcard_SORT_STRING_encode (xmlwriter_t * writer, vcard_SORT_STRING_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "SORT-STRING",
			      (vcard_SORT_STRING_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_SORT_STRING_free (vcard_SORT_STRING_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

struct vcard_SOUND_t *
vcard_SOUND_decode (xmlreader_t * reader)
{
  struct vcard_SOUND_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_SOUND_t));
  if (elm == NULL)
    fatal ("vcard_SOUND_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_SOUND_t));
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm->fValue = (char *) value;
  return elm;
}

int
vcard_SOUND_encode (xmlwriter_t * writer, struct vcard_SOUND_t *elm)
{
  int err = 0;
  const char *name = enum_vcard_SOUND_type_to_string (elm->fType);
  err = xmlwriter_start_element (writer, ns_vcard, name);
  if (err != 0)
    return err;
  if (elm->fValue != NULL)
    {
      err = xmlwriter_text (writer, elm->fValue);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_SOUND_free (struct vcard_SOUND_t *data)
{
  if (data == NULL)
    return;
  if (data->fValue != NULL)
    {
      free (data->fValue);
    }
  free (data);
}

vcard_PHONETIC_t *
vcard_PHONETIC_decode (xmlreader_t * reader)
{
  vcard_PHONETIC_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_PHONETIC_t *) value;
  return elm;
}

int
vcard_PHONETIC_encode (xmlwriter_t * writer, vcard_PHONETIC_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "PHONETIC",
			      (vcard_PHONETIC_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_PHONETIC_free (vcard_PHONETIC_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

vcard_UID_t *
vcard_UID_decode (xmlreader_t * reader)
{
  vcard_UID_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_UID_t *) value;
  return elm;
}

int
vcard_UID_encode (xmlwriter_t * writer, vcard_UID_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "UID", (vcard_UID_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_UID_free (vcard_UID_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

vcard_URL_t *
vcard_URL_decode (xmlreader_t * reader)
{
  vcard_URL_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_URL_t *) value;
  return elm;
}

int
vcard_URL_encode (xmlwriter_t * writer, vcard_URL_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "URL", (vcard_URL_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_URL_free (vcard_URL_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

vcard_DESC_t *
vcard_DESC_decode (xmlreader_t * reader)
{
  vcard_DESC_t *elm = NULL;
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm = (vcard_DESC_t *) value;
  return elm;
}

int
vcard_DESC_encode (xmlwriter_t * writer, vcard_DESC_t * elm)
{
  int err = 0;
  err =
    xmlwriter_simple_element (writer, ns_vcard, "DESC", (vcard_DESC_t *) elm);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_DESC_free (vcard_DESC_t * data)
{
  if (data == NULL)
    return;
  free (data);
  free (data);
}

struct vcard_CLASS_t *
vcard_CLASS_decode (xmlreader_t * reader)
{
  struct vcard_CLASS_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_CLASS_t));
  if (elm == NULL)
    fatal ("vcard_CLASS_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_CLASS_t));
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
	  if (strcmp (namespace, ns_vcard) != 0)
	    {
	      elm->fType = enum_vcard_CLASS_type_from_string (name);
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	}
    }
  return elm;
}

int
vcard_CLASS_encode (xmlwriter_t * writer, struct vcard_CLASS_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "CLASS");
  if (err != 0)
    return err;
  if (elm->fType != 0)
    {
      const char *name = enum_vcard_CLASS_type_to_string (elm->fType);
      err = xmlwriter_simple_element (writer, ns_vcard, name, NULL);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_CLASS_free (struct vcard_CLASS_t *data)
{
  if (data == NULL)
    return;
  if (data->fType != 0)
    {
    }
  free (data);
}

struct vcard_KEY_t *
vcard_KEY_decode (xmlreader_t * reader)
{
  struct vcard_KEY_t *elm = NULL;
  elm = malloc (sizeof (struct vcard_KEY_t));
  if (elm == NULL)
    fatal ("vcard_KEY_t: malloc failed");
  memset (elm, 0, sizeof (struct vcard_KEY_t));
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
	  if ((strcmp (name, "TYPE") == 0)
	      && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fTYPE = (char *) value;
	    }
	  else if ((strcmp (name, "CRED") == 0)
		   && (strcmp (namespace, ns_vcard) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fCRED = (char *) value;
	    }
	}
    }
  return elm;
}

int
vcard_KEY_encode (xmlwriter_t * writer, struct vcard_KEY_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_vcard, "KEY");
  if (err != 0)
    return err;
  if (elm->fTYPE != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "TYPE", elm->fTYPE);
      if (err != 0)
	return err;
    }
  if (elm->fCRED != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_vcard, "CRED", elm->fCRED);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
vcard_KEY_free (struct vcard_KEY_t *data)
{
  if (data == NULL)
    return;
  if (data->fTYPE != NULL)
    {
      free (data->fTYPE);
    }
  if (data->fCRED != NULL)
    {
      free (data->fCRED);
    }
  free (data);
}

enum vcard_SOUND_type_t
enum_vcard_SOUND_type_from_string (const char *value)
{
  if (strcmp (value, "PHONETIC") == 0)
    return VCARD_SOUND_TYPE_PHONETIC;
  else if (strcmp (value, "BINVAL") == 0)
    return VCARD_SOUND_TYPE_BINVAL;
  else if (strcmp (value, "EXTVAL") == 0)
    return VCARD_SOUND_TYPE_EXTVAL;
  return 0;
}

const char *
enum_vcard_SOUND_type_to_string (enum vcard_SOUND_type_t value)
{
  switch (value)
    {
    case VCARD_SOUND_TYPE_PHONETIC:
      return "PHONETIC";
    case VCARD_SOUND_TYPE_BINVAL:
      return "BINVAL";
    case VCARD_SOUND_TYPE_EXTVAL:
      return "EXTVAL";
    }
  return NULL;
}

enum vcard_CLASS_type_t
enum_vcard_CLASS_type_from_string (const char *value)
{
  if (strcmp (value, "PUBLIC") == 0)
    return VCARD_CLASS_TYPE_PUBLIC;
  else if (strcmp (value, "PRIVATE") == 0)
    return VCARD_CLASS_TYPE_PRIVATE;
  else if (strcmp (value, "CONFIDENTIAL") == 0)
    return VCARD_CLASS_TYPE_CONFIDENTIAL;
  return 0;
}

const char *
enum_vcard_CLASS_type_to_string (enum vcard_CLASS_type_t value)
{
  switch (value)
    {
    case VCARD_CLASS_TYPE_PUBLIC:
      return "PUBLIC";
    case VCARD_CLASS_TYPE_PRIVATE:
      return "PRIVATE";
    case VCARD_CLASS_TYPE_CONFIDENTIAL:
      return "CONFIDENTIAL";
    }
  return NULL;
}
