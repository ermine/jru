#include "types.h"

int langstring_decode (xmlreader_t* reader, langstring_t *map) {
  const char* lang = xmlreader_attribute (reader, ns_xml, "lang");
  const char* value = xmlreader_text (reader);
  langstring_add (map, lang, value);
  return 1;
}

int langstring_encode (xmlwriter_t* writer, const char* space, const char* local, langstring_t *map) {
  return 1;
}

void langstring_free (langstring_t* map) {
}
