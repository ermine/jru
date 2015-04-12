#include "sasl_data.h"

const char* ns_sasl = "urn:ietf:params:xml:ns:xmpp-sasl";

struct sasl_mechanisms_t* sasl_mechanisms_decode(xmlTextReaderPtr reader) {
  struct sasl_mechanisms_t *elm = NULL;
 elm = malloc (sizeof (struct sasl_mechanisms_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "mechanism") == 0) && (strcmp ((char*) namespace, ns_sasl) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
  vlist_append ((vlist_t**) &elm->fMechanism, (void*) value, 0);
  } // for end part 1
  } // while end
  return elm;
}

int sasl_mechanisms_encode(xmlWriter_t* writer, struct sasl_mechanisms_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_sasl, "mechanisms");
if (err != 0) return err;
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct sasl_auth_t* sasl_auth_decode(xmlTextReaderPtr reader) {
  struct sasl_auth_t *elm = NULL;
 elm = malloc (sizeof (struct sasl_auth_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "mechanism");
  if (avalue != NULL) {
  elm->fMechanism = (const char*)avalue;
  }
elm->fData = xmlTextReaderReadBase64(reader);
  return elm;
}

int sasl_auth_encode(xmlWriter_t* writer, struct sasl_auth_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_sasl, "auth");
if (err != 0) return err;
if (elm->fMechanism != NULL) {
err = xmlwriter_attribute (writer, ns_sasl, "mechanism", elm->fMechanism);
if (err != 0) return err;
}
if (elm->fData != NULL) {
err = xmlwriter_base64 (writer, (char*)elm->fData);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct sasl_success_t* sasl_success_decode(xmlTextReaderPtr reader) {
  struct sasl_success_t *elm = NULL;
 elm = malloc (sizeof (struct sasl_success_t*));
// element set
elm->fData = xmlTextReaderReadBase64(reader);
  return elm;
}

int sasl_success_encode(xmlWriter_t* writer, struct sasl_success_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_sasl, "success");
if (err != 0) return err;
if (elm->fData != NULL) {
err = xmlwriter_base64 (writer, (char*)elm->fData);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct sasl_challenge_t* sasl_challenge_decode(xmlTextReaderPtr reader) {
  struct sasl_challenge_t *elm = NULL;
 elm = malloc (sizeof (struct sasl_challenge_t*));
// element set
elm->fData = xmlTextReaderReadBase64(reader);
  return elm;
}

int sasl_challenge_encode(xmlWriter_t* writer, struct sasl_challenge_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_sasl, "challenge");
if (err != 0) return err;
if (elm->fData != NULL) {
err = xmlwriter_base64 (writer, (char*)elm->fData);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct sasl_response_t* sasl_response_decode(xmlTextReaderPtr reader) {
  struct sasl_response_t *elm = NULL;
 elm = malloc (sizeof (struct sasl_response_t*));
// element set
elm->fData = xmlTextReaderReadBase64(reader);
  return elm;
}

int sasl_response_encode(xmlWriter_t* writer, struct sasl_response_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_sasl, "response");
if (err != 0) return err;
if (elm->fData != NULL) {
err = xmlwriter_base64 (writer, (char*)elm->fData);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct sasl_failure_t* sasl_failure_decode(xmlTextReaderPtr reader) {
  struct sasl_failure_t *elm = NULL;
 elm = malloc (sizeof (struct sasl_failure_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "text") == 0) && (strcmp ((char*) namespace, ns_sasl) == 0)) {
    langstring_decode (reader, elm->fText);
  } // for end part 1
  else if (strcmp ((char*) namespace, ns_sasl) != 0) {
//herace3
elm->fCondition = enum_sasl_failure_condition_from_string(name);
  if (xstream_skip(reader) != 0) {
    return NULL;
  }
      } // any end
  } // while end
  return elm;
}

int sasl_failure_encode(xmlWriter_t* writer, struct sasl_failure_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_sasl, "failure");
if (err != 0) return err;
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

enum sasl_failure_condition_t enum_sasl_failure_condition_from_string(const xmlChar *value) {
return 0;
}
const char* enum_sasl_failure_condition_to_string(enum sasl_failure_condition_t value) {
return NULL;
}
