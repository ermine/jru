#ifndef _XEP_VCARD_DATA_H_
#define  _XEP_VCARD_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"

struct vcard_N_t;
struct vcard_PHOTO_t;
struct vcard_ADR_t;
struct vcard_LABEL_t;
struct vcard_TEL_t;
struct vcard_EMAIL_t;
struct vcard_GEO_t;
struct vcard_LOGO_t;
struct vcard_AGENT_t;
struct vcard_ORG_t;
struct vcard_CATEGORIES_t;
struct vcard_SOUND_t;
struct vcard_CLASS_t;
struct vcard_KEY_t;
struct vcard_vcard_t;

extern const char* ns_vcard;

enum vcard_DOMINTL_t {
  VCARD_DOMINTL_DOM,
  VCARD_DOMINTL_INTL,
};

enum vcard_DOMINTL_t enum_vcard_DOMINTL_from_string(const xmlChar *value);
xmlChar *enum_vcard_DOMINTL_to_string(enum vcard_DOMINTL_t);
enum vcard_SOUND_type_t {
  VCARD_SOUND_TYPE_PHONETIC,
  VCARD_SOUND_TYPE_BINVAL,
  VCARD_SOUND_TYPE_EXTVAL,
};

enum vcard_SOUND_type_t enum_vcard_SOUND_type_from_string(const xmlChar *value);
xmlChar *enum_vcard_SOUND_type_to_string(enum vcard_SOUND_type_t);
enum vcard_CLASS_type_t {
  VCARD_CLASS_TYPE_PUBLIC,
  VCARD_CLASS_TYPE_PRIVATE,
  VCARD_CLASS_TYPE_CONFIDENTIAL,
};

enum vcard_CLASS_type_t enum_vcard_CLASS_type_from_string(const xmlChar *value);
xmlChar *enum_vcard_CLASS_type_to_string(enum vcard_CLASS_type_t);

struct vcard_vcard_t {
  const xmlChar * fVERSION;
  const xmlChar * fFN;
  struct vcard_N_t* fN;
 llist_t *fFields;
};


struct vcard_N_t {
  const xmlChar * fFAMILY;
  const xmlChar * fGIVEN;
  const xmlChar * fNIDDLE;
  const xmlChar * fPREFIX;
  const xmlChar * fSUFFIX;
};


typedef const xmlChar *vcard_NICKNAME_t;


struct vcard_PHOTO_t {
  const xmlChar * fTYPE;
  const xmlChar * fBINVAL;
  const xmlChar * fEXTVAL;
};


typedef const xmlChar *vcard_BDAY_t;


struct vcard_ADR_t {
  boolean_t fHOME;
  boolean_t fWORK;
  boolean_t fPOSTAL;
  boolean_t fPARCEL;
  enum vcard_DOMINTL_t fDOMINTL;
  boolean_t fPREF;
  const xmlChar * fPOBOX;
  const xmlChar * fEXTADD;
  const xmlChar * fSTREET;
  const xmlChar * fLOCALITY;
  const xmlChar * fREGION;
  const xmlChar * fPCODE;
  const xmlChar * fCTRY;
};


struct vcard_LABEL_t {
  boolean_t fHOME;
  boolean_t fWORK;
  boolean_t fPOSTAL;
  boolean_t fPARCEL;
  enum vcard_DOMINTL_t fDOMINTL;
  boolean_t fPREF;
  llist_t *fLINE;
};


struct vcard_TEL_t {
  boolean_t fHOME;
  boolean_t fWORK;
  boolean_t fVOICE;
  boolean_t fFAX;
  boolean_t fPAGER;
  boolean_t fMSG;
  boolean_t fCELL;
  boolean_t fVIDEO;
  boolean_t fBBS;
  boolean_t fMODEM;
  boolean_t fISDN;
  boolean_t fPCS;
  boolean_t fPREF;
  const xmlChar * fNUMBER;
};


struct vcard_EMAIL_t {
  boolean_t fHOME;
  boolean_t fWORK;
  boolean_t fINTERNET;
  boolean_t fPREF;
  boolean_t fX400;
  const xmlChar * fUSERID;
};


typedef const xmlChar *vcard_JABBERID_t;


typedef const xmlChar *vcard_MAILER_t;


typedef const xmlChar *vcard_TZ_t;


struct vcard_GEO_t {
  const xmlChar * fLAT;
  const xmlChar * fLON;
};


typedef const xmlChar *vcard_TITLE_t;


typedef const xmlChar *vcard_ROLE_t;


struct vcard_LOGO_t {
  const xmlChar * fTYPE;
  const xmlChar * fBINVAL;
  const xmlChar * fEXTVAL;
};


typedef const xmlChar *vcard_EXTVAL_t;


struct vcard_AGENT_t {
  int type;
  union {
    struct vcard_vcard_t*fVcard;
    vcard_EXTVAL_t*fEXTVAL;
  } *u;
};

struct vcard_ORG_t {
  const xmlChar * fORGNAME;
  llist_t *fORGUNIT;
};


struct vcard_CATEGORIES_t {
  llist_t *fKEYWORD;
};


typedef const xmlChar *vcard_NOTE_t;


typedef const xmlChar *vcard_PRODID_t;


typedef const xmlChar *vcard_REV_t;


typedef const xmlChar *vcard_SORT_STRING_t;


struct vcard_SOUND_t {
  enum vcard_SOUND_type_t fType;
  const xmlChar * fValue;
};


typedef const xmlChar *vcard_PHONETIC_t;


typedef const xmlChar *vcard_UID_t;


typedef const xmlChar *vcard_URL_t;


typedef const xmlChar *vcard_DESC_t;


struct vcard_CLASS_t {
  enum vcard_CLASS_type_t fType;
};


struct vcard_KEY_t {
  const xmlChar * fTYPE;
  const xmlChar * fCRED;
};


struct vcard_vcard_t* vcard_vcard_decode(xmlTextReaderPtr reader);
int vcard_vcard_encode(xmlTextWriterPtr writer, struct vcard_vcard_t* data);
struct vcard_N_t* vcard_N_decode(xmlTextReaderPtr reader);
int vcard_N_encode(xmlTextWriterPtr writer, struct vcard_N_t* data);
vcard_NICKNAME_t* vcard_NICKNAME_decode(xmlTextReaderPtr reader);
int vcard_NICKNAME_encode(xmlTextWriterPtr writer, vcard_NICKNAME_t* data);
struct vcard_PHOTO_t* vcard_PHOTO_decode(xmlTextReaderPtr reader);
int vcard_PHOTO_encode(xmlTextWriterPtr writer, struct vcard_PHOTO_t* data);
vcard_BDAY_t* vcard_BDAY_decode(xmlTextReaderPtr reader);
int vcard_BDAY_encode(xmlTextWriterPtr writer, vcard_BDAY_t* data);
struct vcard_ADR_t* vcard_ADR_decode(xmlTextReaderPtr reader);
int vcard_ADR_encode(xmlTextWriterPtr writer, struct vcard_ADR_t* data);
struct vcard_LABEL_t* vcard_LABEL_decode(xmlTextReaderPtr reader);
int vcard_LABEL_encode(xmlTextWriterPtr writer, struct vcard_LABEL_t* data);
struct vcard_TEL_t* vcard_TEL_decode(xmlTextReaderPtr reader);
int vcard_TEL_encode(xmlTextWriterPtr writer, struct vcard_TEL_t* data);
struct vcard_EMAIL_t* vcard_EMAIL_decode(xmlTextReaderPtr reader);
int vcard_EMAIL_encode(xmlTextWriterPtr writer, struct vcard_EMAIL_t* data);
vcard_JABBERID_t* vcard_JABBERID_decode(xmlTextReaderPtr reader);
int vcard_JABBERID_encode(xmlTextWriterPtr writer, vcard_JABBERID_t* data);
vcard_MAILER_t* vcard_MAILER_decode(xmlTextReaderPtr reader);
int vcard_MAILER_encode(xmlTextWriterPtr writer, vcard_MAILER_t* data);
vcard_TZ_t* vcard_TZ_decode(xmlTextReaderPtr reader);
int vcard_TZ_encode(xmlTextWriterPtr writer, vcard_TZ_t* data);
struct vcard_GEO_t* vcard_GEO_decode(xmlTextReaderPtr reader);
int vcard_GEO_encode(xmlTextWriterPtr writer, struct vcard_GEO_t* data);
vcard_TITLE_t* vcard_TITLE_decode(xmlTextReaderPtr reader);
int vcard_TITLE_encode(xmlTextWriterPtr writer, vcard_TITLE_t* data);
vcard_ROLE_t* vcard_ROLE_decode(xmlTextReaderPtr reader);
int vcard_ROLE_encode(xmlTextWriterPtr writer, vcard_ROLE_t* data);
struct vcard_LOGO_t* vcard_LOGO_decode(xmlTextReaderPtr reader);
int vcard_LOGO_encode(xmlTextWriterPtr writer, struct vcard_LOGO_t* data);
vcard_EXTVAL_t* vcard_EXTVAL_decode(xmlTextReaderPtr reader);
int vcard_EXTVAL_encode(xmlTextWriterPtr writer, vcard_EXTVAL_t* data);
struct vcard_AGENT_t* vcard_AGENT_decode(xmlTextReaderPtr reader);
int vcard_AGENT_encode(xmlTextWriterPtr writer, struct vcard_AGENT_t* data);
struct vcard_ORG_t* vcard_ORG_decode(xmlTextReaderPtr reader);
int vcard_ORG_encode(xmlTextWriterPtr writer, struct vcard_ORG_t* data);
struct vcard_CATEGORIES_t* vcard_CATEGORIES_decode(xmlTextReaderPtr reader);
int vcard_CATEGORIES_encode(xmlTextWriterPtr writer, struct vcard_CATEGORIES_t* data);
vcard_NOTE_t* vcard_NOTE_decode(xmlTextReaderPtr reader);
int vcard_NOTE_encode(xmlTextWriterPtr writer, vcard_NOTE_t* data);
vcard_PRODID_t* vcard_PRODID_decode(xmlTextReaderPtr reader);
int vcard_PRODID_encode(xmlTextWriterPtr writer, vcard_PRODID_t* data);
vcard_REV_t* vcard_REV_decode(xmlTextReaderPtr reader);
int vcard_REV_encode(xmlTextWriterPtr writer, vcard_REV_t* data);
vcard_SORT_STRING_t* vcard_SORT_STRING_decode(xmlTextReaderPtr reader);
int vcard_SORT_STRING_encode(xmlTextWriterPtr writer, vcard_SORT_STRING_t* data);
struct vcard_SOUND_t* vcard_SOUND_decode(xmlTextReaderPtr reader);
int vcard_SOUND_encode(xmlTextWriterPtr writer, struct vcard_SOUND_t* data);
vcard_PHONETIC_t* vcard_PHONETIC_decode(xmlTextReaderPtr reader);
int vcard_PHONETIC_encode(xmlTextWriterPtr writer, vcard_PHONETIC_t* data);
vcard_UID_t* vcard_UID_decode(xmlTextReaderPtr reader);
int vcard_UID_encode(xmlTextWriterPtr writer, vcard_UID_t* data);
vcard_URL_t* vcard_URL_decode(xmlTextReaderPtr reader);
int vcard_URL_encode(xmlTextWriterPtr writer, vcard_URL_t* data);
vcard_DESC_t* vcard_DESC_decode(xmlTextReaderPtr reader);
int vcard_DESC_encode(xmlTextWriterPtr writer, vcard_DESC_t* data);
struct vcard_CLASS_t* vcard_CLASS_decode(xmlTextReaderPtr reader);
int vcard_CLASS_encode(xmlTextWriterPtr writer, struct vcard_CLASS_t* data);
struct vcard_KEY_t* vcard_KEY_decode(xmlTextReaderPtr reader);
int vcard_KEY_encode(xmlTextWriterPtr writer, struct vcard_KEY_t* data);
#endif
