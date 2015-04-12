#include "xep_mood_data.h"

const char* ns_mood = "http://jabber.org/protocol/mood";

struct mood_mood_t* mood_mood_decode(xmlTextReaderPtr reader) {
  struct mood_mood_t *elm = NULL;
 elm = malloc (sizeof (struct mood_mood_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "text") == 0) && (strcmp ((char*) namespace, ns_mood) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fText = (const char*) value;
  } // for end part 1
  else if (strcmp ((char*) namespace, ns_mood) != 0) {
//herace3
elm->fMood = enum_mood_mood_mood_from_string(name);
  if (xstream_skip(reader) != 0) {
    return NULL;
  }
      } // any end
  } // while end
  return elm;
}

int mood_mood_encode(xmlWriter_t* writer, struct mood_mood_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_mood, "mood");
if (err != 0) return err;
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

enum mood_mood_mood_t enum_mood_mood_mood_from_string(const xmlChar *value) {
return 0;
}
const char* enum_mood_mood_mood_to_string(enum mood_mood_mood_t value) {
return NULL;
}
