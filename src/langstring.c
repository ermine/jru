#include "types.h"

int langstring_decode (xmlTextReaderPtr reader, langstring_t *map) {
  const xmlChar* lang = xmlTextReaderGetAttribute (reader, (const xmlChar*) "xml:lang");
  const xmlChar* value = xmlTextReaderConstValue (reader);
  langstring_add (map, lang, value);
  return 1;
}

int langstring_encode (xmlTextWriterPtr writer, const char* space, const char* local, langstring_t *map) {
  return 1;
}
