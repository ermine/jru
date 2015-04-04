/*
   RFC3339
   date-fullyear   = 4DIGIT
   date-month      = 2DIGIT  ; 01-12
   date-mday       = 2DIGIT  ; 01-28, 01-29, 01-30, 01-31 based on
                             ; month/year
   time-hour       = 2DIGIT  ; 00-23
   time-minute     = 2DIGIT  ; 00-59
   time-second     = 2DIGIT  ; 00-58, 00-59, 00-60 based on leap second
                             ; rules
   time-secfrac    = "." 1*DIGIT
   time-numoffset  = ("+" / "-") time-hour ":" time-minute
   time-offset     = "Z" / time-numoffset

   partial-time    = time-hour ":" time-minute ":" time-second
                     [time-secfrac]
   full-date       = date-fullyear "-" date-month "-" date-mday
   full-time       = partial-time time-offset

   date-time       = full-date "T" full-time
*/
/*
  Format
  %Y-%m-%dT%TZ
  %Y-%m-%dT%T+%H:%M
  %Y-%m-%dT%T-%H:%M
*/

#include <stdio.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <time.h>
#include <string.h>
#include "types.h"

struct tm* datetime_parse(const xmlChar* value) {
  struct tm *result = NULL;
  char **f;
  char *ret;
  char *formats[] = {
    "%Y-%m-%dT%TZ",
    "%Y-%m-%dT%T+%H:%M",
    "%Y-%m-%dT%T-%H:%M",
    NULL
  };
  
  result = malloc (sizeof (struct tm));
  memset (&result, 0, sizeof(result));
  
  for (f = formats; f && *f; f++) {
    ret = strptime ((char*) value, *f, result);
    if (ret && *ret == '\0')
      return result;
  }
  free (result);
  
  return NULL;
}

const xmlChar* datetime_to_string(struct tm* data) {
  return NULL;
}
