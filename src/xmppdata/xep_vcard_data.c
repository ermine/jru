#include "xep_vcard_data.h"

const char* ns_vcard = "vcard-temp";

struct vcard_vcard_t* vcard_vcard_decode(xmlTextReaderPtr reader) {
  struct vcard_vcard_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_vcard_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "VERSION") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fVERSION = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "FN") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFN = (value);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_vcard_encode(xmlTextWriterPtr writer, struct vcard_vcard_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "vCard", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct vcard_N_t* vcard_N_decode(xmlTextReaderPtr reader) {
  struct vcard_N_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_N_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "FAMILY") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFAMILY = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "GIVEN") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fGIVEN = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "NIDDLE") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fNIDDLE = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "PREFIX") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fPREFIX = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "SUFFIX") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fSUFFIX = (value);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_N_encode(xmlTextWriterPtr writer, struct vcard_N_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "N", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

vcard_NICKNAME_t* vcard_NICKNAME_decode(xmlTextReaderPtr reader) {
  vcard_NICKNAME_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_NICKNAME_t*)(value);
  return elm;
}

int vcard_NICKNAME_encode(xmlTextWriterPtr writer, vcard_NICKNAME_t* elm) {
  return 0;
}

struct vcard_PHOTO_t* vcard_PHOTO_decode(xmlTextReaderPtr reader) {
  struct vcard_PHOTO_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_PHOTO_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "TYPE") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fTYPE = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "BINVAL") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fBINVAL = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "EXTVAL") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fEXTVAL = (value);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_PHOTO_encode(xmlTextWriterPtr writer, struct vcard_PHOTO_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "PHOTO", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

vcard_BDAY_t* vcard_BDAY_decode(xmlTextReaderPtr reader) {
  vcard_BDAY_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_BDAY_t*)(value);
  return elm;
}

int vcard_BDAY_encode(xmlTextWriterPtr writer, vcard_BDAY_t* elm) {
  return 0;
}

enum vcard_DOMINTL_t enum_vcard_DOMINTL_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_vcard_DOMINTL_to_string(enum vcard_DOMINTL_t value) {
return NULL;
}
struct vcard_ADR_t* vcard_ADR_decode(xmlTextReaderPtr reader) {
  struct vcard_ADR_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_ADR_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "HOME") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fHOME = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "WORK") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fWORK = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "POSTAL") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPOSTAL = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "PARCEL") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPARCEL = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "PREF") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPREF = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "POBOX") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fPOBOX = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "EXTADD") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fEXTADD = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "STREET") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fSTREET = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "LOCALITY") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fLOCALITY = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "REGION") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fREGION = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "PCODE") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fPCODE = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "CTRY") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fCTRY = (value);
  } // for end part 1
  else if (strcmp ((char*) namespace, ns_vcard) != 0) {
//herace3
elm->fDOMINTL = enum_vcard_DOMINTL_from_string(name);
  if (xstream_skip(reader) != 0) {
    return NULL;
  }
      } // any end
  } // while end
  return elm;
}

int vcard_ADR_encode(xmlTextWriterPtr writer, struct vcard_ADR_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "ADR", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct vcard_LABEL_t* vcard_LABEL_decode(xmlTextReaderPtr reader) {
  struct vcard_LABEL_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_LABEL_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "HOME") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fHOME = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "WORK") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fWORK = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "POSTAL") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPOSTAL = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "PARCEL") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPARCEL = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "PREF") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPREF = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "LINE") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
  llist_append((llist_t*)elm->fLINE, (void*) value, 0);
  } // for end part 1
  else if (strcmp ((char*) namespace, ns_vcard) != 0) {
//herace3
elm->fDOMINTL = enum_vcard_DOMINTL_from_string(name);
  if (xstream_skip(reader) != 0) {
    return NULL;
  }
      } // any end
  } // while end
  return elm;
}

int vcard_LABEL_encode(xmlTextWriterPtr writer, struct vcard_LABEL_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "LABEL", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct vcard_TEL_t* vcard_TEL_decode(xmlTextReaderPtr reader) {
  struct vcard_TEL_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_TEL_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "HOME") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fHOME = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "WORK") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fWORK = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "VOICE") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fVOICE = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "FAX") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fFAX = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "PAGER") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPAGER = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "MSG") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fMSG = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "CELL") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fCELL = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "VIDEO") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fVIDEO = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "BBS") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fBBS = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "MODEM") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fMODEM = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "ISDN") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fISDN = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "PCS") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPCS = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "PREF") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPREF = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "NUMBER") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fNUMBER = (value);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_TEL_encode(xmlTextWriterPtr writer, struct vcard_TEL_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "TEL", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct vcard_EMAIL_t* vcard_EMAIL_decode(xmlTextReaderPtr reader) {
  struct vcard_EMAIL_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_EMAIL_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "HOME") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fHOME = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "WORK") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fWORK = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "INTERNET") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fINTERNET = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "PREF") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fPREF = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "X400") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
    elm->fX400 = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  else if ((strcmp ((char*) name, "USERID") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fUSERID = (value);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_EMAIL_encode(xmlTextWriterPtr writer, struct vcard_EMAIL_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "EMAIL", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

vcard_JABBERID_t* vcard_JABBERID_decode(xmlTextReaderPtr reader) {
  vcard_JABBERID_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_JABBERID_t*)(value);
  return elm;
}

int vcard_JABBERID_encode(xmlTextWriterPtr writer, vcard_JABBERID_t* elm) {
  return 0;
}

vcard_MAILER_t* vcard_MAILER_decode(xmlTextReaderPtr reader) {
  vcard_MAILER_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_MAILER_t*)(value);
  return elm;
}

int vcard_MAILER_encode(xmlTextWriterPtr writer, vcard_MAILER_t* elm) {
  return 0;
}

vcard_TZ_t* vcard_TZ_decode(xmlTextReaderPtr reader) {
  vcard_TZ_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_TZ_t*)(value);
  return elm;
}

int vcard_TZ_encode(xmlTextWriterPtr writer, vcard_TZ_t* elm) {
  return 0;
}

struct vcard_GEO_t* vcard_GEO_decode(xmlTextReaderPtr reader) {
  struct vcard_GEO_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_GEO_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "LAT") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fLAT = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "LON") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fLON = (value);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_GEO_encode(xmlTextWriterPtr writer, struct vcard_GEO_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "GEO", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

vcard_TITLE_t* vcard_TITLE_decode(xmlTextReaderPtr reader) {
  vcard_TITLE_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_TITLE_t*)(value);
  return elm;
}

int vcard_TITLE_encode(xmlTextWriterPtr writer, vcard_TITLE_t* elm) {
  return 0;
}

vcard_ROLE_t* vcard_ROLE_decode(xmlTextReaderPtr reader) {
  vcard_ROLE_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_ROLE_t*)(value);
  return elm;
}

int vcard_ROLE_encode(xmlTextWriterPtr writer, vcard_ROLE_t* elm) {
  return 0;
}

struct vcard_LOGO_t* vcard_LOGO_decode(xmlTextReaderPtr reader) {
  struct vcard_LOGO_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_LOGO_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "TYPE") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fTYPE = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "BINVAL") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fBINVAL = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "EXTVAL") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fEXTVAL = (value);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_LOGO_encode(xmlTextWriterPtr writer, struct vcard_LOGO_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "LOGO", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

vcard_EXTVAL_t* vcard_EXTVAL_decode(xmlTextReaderPtr reader) {
  vcard_EXTVAL_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_EXTVAL_t*)(value);
  return elm;
}

int vcard_EXTVAL_encode(xmlTextWriterPtr writer, vcard_EXTVAL_t* elm) {
  return 0;
}

struct vcard_AGENT_t* vcard_AGENT_decode(xmlTextReaderPtr reader) {
  struct vcard_AGENT_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_AGENT_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char *) namespace, ns_vcard) == 0) && (strcmp ((char*) name, "vCard") == 0)) {
struct vcard_vcard_t* newel = vcard_vcard_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
//tut
//Choice
elm->type = EXTENSION_TYPE_VCARD_VCARD;
elm->u->fVcard = newel;
  }
  else if ((strcmp ((char *) namespace, ns_vcard) == 0) && (strcmp ((char*) name, "EXTVAL") == 0)) {
vcard_EXTVAL_t* newel = vcard_EXTVAL_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
//tut
//Choice
elm->type = EXTENSION_TYPE_VCARD_EXTVAL;
elm->u->fEXTVAL = newel;
  }
  } // while end
  return elm;
}

int vcard_AGENT_encode(xmlTextWriterPtr writer, struct vcard_AGENT_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "AGENT", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
if (elm->u != NULL) {
if (xstream_extension_encode(writer, (void*)elm->u, elm->type) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct vcard_ORG_t* vcard_ORG_decode(xmlTextReaderPtr reader) {
  struct vcard_ORG_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_ORG_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "ORGNAME") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fORGNAME = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "ORGUNIT") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
  llist_append((llist_t*)elm->fORGUNIT, (void*) value, 0);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_ORG_encode(xmlTextWriterPtr writer, struct vcard_ORG_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "ORG", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct vcard_CATEGORIES_t* vcard_CATEGORIES_decode(xmlTextReaderPtr reader) {
  struct vcard_CATEGORIES_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_CATEGORIES_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "KEYWORD") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
  llist_append((llist_t*)elm->fKEYWORD, (void*) value, 0);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_CATEGORIES_encode(xmlTextWriterPtr writer, struct vcard_CATEGORIES_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "CATEGORIES", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

vcard_NOTE_t* vcard_NOTE_decode(xmlTextReaderPtr reader) {
  vcard_NOTE_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_NOTE_t*)(value);
  return elm;
}

int vcard_NOTE_encode(xmlTextWriterPtr writer, vcard_NOTE_t* elm) {
  return 0;
}

vcard_PRODID_t* vcard_PRODID_decode(xmlTextReaderPtr reader) {
  vcard_PRODID_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_PRODID_t*)(value);
  return elm;
}

int vcard_PRODID_encode(xmlTextWriterPtr writer, vcard_PRODID_t* elm) {
  return 0;
}

vcard_REV_t* vcard_REV_decode(xmlTextReaderPtr reader) {
  vcard_REV_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_REV_t*)(value);
  return elm;
}

int vcard_REV_encode(xmlTextWriterPtr writer, vcard_REV_t* elm) {
  return 0;
}

vcard_SORT_STRING_t* vcard_SORT_STRING_decode(xmlTextReaderPtr reader) {
  vcard_SORT_STRING_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_SORT_STRING_t*)(value);
  return elm;
}

int vcard_SORT_STRING_encode(xmlTextWriterPtr writer, vcard_SORT_STRING_t* elm) {
  return 0;
}

struct vcard_SOUND_t* vcard_SOUND_decode(xmlTextReaderPtr reader) {
  struct vcard_SOUND_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_SOUND_t*));
// element set
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fValue = (value);
  return elm;
}

int vcard_SOUND_encode(xmlTextWriterPtr writer, struct vcard_SOUND_t* elm) {
const xmlChar* name = enum_vcard_SOUND_type_to_string(elm->fType);
if (xmlTextWriterStartElementNS(writer, NULL, name, BAD_CAST ns_vcard) == -1)
 return -1;
if (elm->fValue != NULL) {
if (xmlTextWriterWriteCDATA(writer, elm->fValue) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

vcard_PHONETIC_t* vcard_PHONETIC_decode(xmlTextReaderPtr reader) {
  vcard_PHONETIC_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_PHONETIC_t*)(value);
  return elm;
}

int vcard_PHONETIC_encode(xmlTextWriterPtr writer, vcard_PHONETIC_t* elm) {
  return 0;
}

vcard_UID_t* vcard_UID_decode(xmlTextReaderPtr reader) {
  vcard_UID_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_UID_t*)(value);
  return elm;
}

int vcard_UID_encode(xmlTextWriterPtr writer, vcard_UID_t* elm) {
  return 0;
}

vcard_URL_t* vcard_URL_decode(xmlTextReaderPtr reader) {
  vcard_URL_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_URL_t*)(value);
  return elm;
}

int vcard_URL_encode(xmlTextWriterPtr writer, vcard_URL_t* elm) {
  return 0;
}

vcard_DESC_t* vcard_DESC_decode(xmlTextReaderPtr reader) {
  vcard_DESC_t *elm = NULL;
const xmlChar *value = xmlTextReaderConstValue (reader);
elm = (vcard_DESC_t*)(value);
  return elm;
}

int vcard_DESC_encode(xmlTextWriterPtr writer, vcard_DESC_t* elm) {
  return 0;
}

struct vcard_CLASS_t* vcard_CLASS_decode(xmlTextReaderPtr reader) {
  struct vcard_CLASS_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_CLASS_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
  if  (strcmp ((char*) namespace, ns_vcard) != 0) {
//herace3
elm->fType = enum_vcard_CLASS_type_from_string(name);
  if (xstream_skip(reader) != 0) {
    return NULL;
  }
      } // any end
  } // while end
  return elm;
}

int vcard_CLASS_encode(xmlTextWriterPtr writer, struct vcard_CLASS_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "CLASS", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct vcard_KEY_t* vcard_KEY_decode(xmlTextReaderPtr reader) {
  struct vcard_KEY_t *elm = NULL;
 elm = malloc (sizeof (struct vcard_KEY_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "TYPE") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fTYPE = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "CRED") == 0) && (strcmp ((char*) namespace, ns_vcard) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fCRED = (value);
  } // for end part 1
  } // while end
  return elm;
}

int vcard_KEY_encode(xmlTextWriterPtr writer, struct vcard_KEY_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "KEY", BAD_CAST ns_vcard) == -1)
 return -1;
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

enum vcard_SOUND_type_t enum_vcard_SOUND_type_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_vcard_SOUND_type_to_string(enum vcard_SOUND_type_t value) {
return NULL;
}
enum vcard_CLASS_type_t enum_vcard_CLASS_type_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_vcard_CLASS_type_to_string(enum vcard_CLASS_type_t value) {
return NULL;
}
