#ifndef _XEP_VCARD_DATA_H_
#define  _XEP_VCARD_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
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

extern const char *ns_vcard;

enum vcard_DOMINTL_t
{
  VCARD_DOMINTL_DOM,
  VCARD_DOMINTL_INTL,
};

enum vcard_DOMINTL_t enum_vcard_DOMINTL_from_string (const char *value);
const char *enum_vcard_DOMINTL_to_string (enum vcard_DOMINTL_t);
enum vcard_SOUND_type_t
{
  VCARD_SOUND_TYPE_PHONETIC,
  VCARD_SOUND_TYPE_BINVAL,
  VCARD_SOUND_TYPE_EXTVAL,
};

enum vcard_SOUND_type_t enum_vcard_SOUND_type_from_string (const char *value);
const char *enum_vcard_SOUND_type_to_string (enum vcard_SOUND_type_t);
enum vcard_CLASS_type_t
{
  VCARD_CLASS_TYPE_PUBLIC,
  VCARD_CLASS_TYPE_PRIVATE,
  VCARD_CLASS_TYPE_CONFIDENTIAL,
};

enum vcard_CLASS_type_t enum_vcard_CLASS_type_from_string (const char *value);
const char *enum_vcard_CLASS_type_to_string (enum vcard_CLASS_type_t);

struct vcard_vcard_t
{
  char *fVERSION;
  char *fFN;
  struct vcard_N_t *fN;
  array_t *fFields;
};


struct vcard_N_t
{
  char *fFAMILY;
  char *fGIVEN;
  char *fNIDDLE;
  char *fPREFIX;
  char *fSUFFIX;
};


typedef char vcard_NICKNAME_t;


struct vcard_PHOTO_t
{
  char *fTYPE;
  char *fBINVAL;
  char *fEXTVAL;
};


typedef char vcard_BDAY_t;


struct vcard_ADR_t
{
  bool fHOME;
  bool fWORK;
  bool fPOSTAL;
  bool fPARCEL;
  enum vcard_DOMINTL_t fDOMINTL;
  bool fPREF;
  char *fPOBOX;
  char *fEXTADD;
  char *fSTREET;
  char *fLOCALITY;
  char *fREGION;
  char *fPCODE;
  char *fCTRY;
};


struct vcard_LABEL_t
{
  bool fHOME;
  bool fWORK;
  bool fPOSTAL;
  bool fPARCEL;
  enum vcard_DOMINTL_t fDOMINTL;
  bool fPREF;
  array_t *fLINE;
};


struct vcard_TEL_t
{
  bool fHOME;
  bool fWORK;
  bool fVOICE;
  bool fFAX;
  bool fPAGER;
  bool fMSG;
  bool fCELL;
  bool fVIDEO;
  bool fBBS;
  bool fMODEM;
  bool fISDN;
  bool fPCS;
  bool fPREF;
  char *fNUMBER;
};


struct vcard_EMAIL_t
{
  bool fHOME;
  bool fWORK;
  bool fINTERNET;
  bool fPREF;
  bool fX400;
  char *fUSERID;
};


typedef char vcard_JABBERID_t;


typedef char vcard_MAILER_t;


typedef char vcard_TZ_t;


struct vcard_GEO_t
{
  char *fLAT;
  char *fLON;
};


typedef char vcard_TITLE_t;


typedef char vcard_ROLE_t;


struct vcard_LOGO_t
{
  char *fTYPE;
  char *fBINVAL;
  char *fEXTVAL;
};


typedef char vcard_EXTVAL_t;


struct vcard_AGENT_t
{
  int type;
  union
  {
    struct vcard_vcard_t *fVcard;
    vcard_EXTVAL_t *fEXTVAL;
  } *u;
};

struct vcard_ORG_t
{
  char *fORGNAME;
  array_t *fORGUNIT;
};


struct vcard_CATEGORIES_t
{
  array_t *fKEYWORD;
};


typedef char vcard_NOTE_t;


typedef char vcard_PRODID_t;


typedef char vcard_REV_t;


typedef char vcard_SORT_STRING_t;


struct vcard_SOUND_t
{
  enum vcard_SOUND_type_t fType;
  char *fValue;
};


typedef char vcard_PHONETIC_t;


typedef char vcard_UID_t;


typedef char vcard_URL_t;


typedef char vcard_DESC_t;


struct vcard_CLASS_t
{
  enum vcard_CLASS_type_t fType;
};


struct vcard_KEY_t
{
  char *fTYPE;
  char *fCRED;
};


struct vcard_vcard_t *vcard_vcard_decode (xmlreader_t * reader);
int vcard_vcard_encode (xmlwriter_t * writer, struct vcard_vcard_t *data);
void vcard_vcard_free (struct vcard_vcard_t *data);
struct vcard_N_t *vcard_N_decode (xmlreader_t * reader);
int vcard_N_encode (xmlwriter_t * writer, struct vcard_N_t *data);
void vcard_N_free (struct vcard_N_t *data);
vcard_NICKNAME_t *vcard_NICKNAME_decode (xmlreader_t * reader);
int vcard_NICKNAME_encode (xmlwriter_t * writer, vcard_NICKNAME_t * data);
void vcard_NICKNAME_free (vcard_NICKNAME_t * data);
struct vcard_PHOTO_t *vcard_PHOTO_decode (xmlreader_t * reader);
int vcard_PHOTO_encode (xmlwriter_t * writer, struct vcard_PHOTO_t *data);
void vcard_PHOTO_free (struct vcard_PHOTO_t *data);
vcard_BDAY_t *vcard_BDAY_decode (xmlreader_t * reader);
int vcard_BDAY_encode (xmlwriter_t * writer, vcard_BDAY_t * data);
void vcard_BDAY_free (vcard_BDAY_t * data);
struct vcard_ADR_t *vcard_ADR_decode (xmlreader_t * reader);
int vcard_ADR_encode (xmlwriter_t * writer, struct vcard_ADR_t *data);
void vcard_ADR_free (struct vcard_ADR_t *data);
struct vcard_LABEL_t *vcard_LABEL_decode (xmlreader_t * reader);
int vcard_LABEL_encode (xmlwriter_t * writer, struct vcard_LABEL_t *data);
void vcard_LABEL_free (struct vcard_LABEL_t *data);
struct vcard_TEL_t *vcard_TEL_decode (xmlreader_t * reader);
int vcard_TEL_encode (xmlwriter_t * writer, struct vcard_TEL_t *data);
void vcard_TEL_free (struct vcard_TEL_t *data);
struct vcard_EMAIL_t *vcard_EMAIL_decode (xmlreader_t * reader);
int vcard_EMAIL_encode (xmlwriter_t * writer, struct vcard_EMAIL_t *data);
void vcard_EMAIL_free (struct vcard_EMAIL_t *data);
vcard_JABBERID_t *vcard_JABBERID_decode (xmlreader_t * reader);
int vcard_JABBERID_encode (xmlwriter_t * writer, vcard_JABBERID_t * data);
void vcard_JABBERID_free (vcard_JABBERID_t * data);
vcard_MAILER_t *vcard_MAILER_decode (xmlreader_t * reader);
int vcard_MAILER_encode (xmlwriter_t * writer, vcard_MAILER_t * data);
void vcard_MAILER_free (vcard_MAILER_t * data);
vcard_TZ_t *vcard_TZ_decode (xmlreader_t * reader);
int vcard_TZ_encode (xmlwriter_t * writer, vcard_TZ_t * data);
void vcard_TZ_free (vcard_TZ_t * data);
struct vcard_GEO_t *vcard_GEO_decode (xmlreader_t * reader);
int vcard_GEO_encode (xmlwriter_t * writer, struct vcard_GEO_t *data);
void vcard_GEO_free (struct vcard_GEO_t *data);
vcard_TITLE_t *vcard_TITLE_decode (xmlreader_t * reader);
int vcard_TITLE_encode (xmlwriter_t * writer, vcard_TITLE_t * data);
void vcard_TITLE_free (vcard_TITLE_t * data);
vcard_ROLE_t *vcard_ROLE_decode (xmlreader_t * reader);
int vcard_ROLE_encode (xmlwriter_t * writer, vcard_ROLE_t * data);
void vcard_ROLE_free (vcard_ROLE_t * data);
struct vcard_LOGO_t *vcard_LOGO_decode (xmlreader_t * reader);
int vcard_LOGO_encode (xmlwriter_t * writer, struct vcard_LOGO_t *data);
void vcard_LOGO_free (struct vcard_LOGO_t *data);
vcard_EXTVAL_t *vcard_EXTVAL_decode (xmlreader_t * reader);
int vcard_EXTVAL_encode (xmlwriter_t * writer, vcard_EXTVAL_t * data);
void vcard_EXTVAL_free (vcard_EXTVAL_t * data);
struct vcard_AGENT_t *vcard_AGENT_decode (xmlreader_t * reader);
int vcard_AGENT_encode (xmlwriter_t * writer, struct vcard_AGENT_t *data);
void vcard_AGENT_free (struct vcard_AGENT_t *data);
struct vcard_ORG_t *vcard_ORG_decode (xmlreader_t * reader);
int vcard_ORG_encode (xmlwriter_t * writer, struct vcard_ORG_t *data);
void vcard_ORG_free (struct vcard_ORG_t *data);
struct vcard_CATEGORIES_t *vcard_CATEGORIES_decode (xmlreader_t * reader);
int vcard_CATEGORIES_encode (xmlwriter_t * writer,
			     struct vcard_CATEGORIES_t *data);
void vcard_CATEGORIES_free (struct vcard_CATEGORIES_t *data);
vcard_NOTE_t *vcard_NOTE_decode (xmlreader_t * reader);
int vcard_NOTE_encode (xmlwriter_t * writer, vcard_NOTE_t * data);
void vcard_NOTE_free (vcard_NOTE_t * data);
vcard_PRODID_t *vcard_PRODID_decode (xmlreader_t * reader);
int vcard_PRODID_encode (xmlwriter_t * writer, vcard_PRODID_t * data);
void vcard_PRODID_free (vcard_PRODID_t * data);
vcard_REV_t *vcard_REV_decode (xmlreader_t * reader);
int vcard_REV_encode (xmlwriter_t * writer, vcard_REV_t * data);
void vcard_REV_free (vcard_REV_t * data);
vcard_SORT_STRING_t *vcard_SORT_STRING_decode (xmlreader_t * reader);
int vcard_SORT_STRING_encode (xmlwriter_t * writer,
			      vcard_SORT_STRING_t * data);
void vcard_SORT_STRING_free (vcard_SORT_STRING_t * data);
struct vcard_SOUND_t *vcard_SOUND_decode (xmlreader_t * reader);
int vcard_SOUND_encode (xmlwriter_t * writer, struct vcard_SOUND_t *data);
void vcard_SOUND_free (struct vcard_SOUND_t *data);
vcard_PHONETIC_t *vcard_PHONETIC_decode (xmlreader_t * reader);
int vcard_PHONETIC_encode (xmlwriter_t * writer, vcard_PHONETIC_t * data);
void vcard_PHONETIC_free (vcard_PHONETIC_t * data);
vcard_UID_t *vcard_UID_decode (xmlreader_t * reader);
int vcard_UID_encode (xmlwriter_t * writer, vcard_UID_t * data);
void vcard_UID_free (vcard_UID_t * data);
vcard_URL_t *vcard_URL_decode (xmlreader_t * reader);
int vcard_URL_encode (xmlwriter_t * writer, vcard_URL_t * data);
void vcard_URL_free (vcard_URL_t * data);
vcard_DESC_t *vcard_DESC_decode (xmlreader_t * reader);
int vcard_DESC_encode (xmlwriter_t * writer, vcard_DESC_t * data);
void vcard_DESC_free (vcard_DESC_t * data);
struct vcard_CLASS_t *vcard_CLASS_decode (xmlreader_t * reader);
int vcard_CLASS_encode (xmlwriter_t * writer, struct vcard_CLASS_t *data);
void vcard_CLASS_free (struct vcard_CLASS_t *data);
struct vcard_KEY_t *vcard_KEY_decode (xmlreader_t * reader);
int vcard_KEY_encode (xmlwriter_t * writer, struct vcard_KEY_t *data);
void vcard_KEY_free (struct vcard_KEY_t *data);
#endif
