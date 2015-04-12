#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void fatal(char* msg, ...) {
  va_list arg;
        
  va_start(arg, msg);
  fprintf(stderr, "fatal: ");
  vfprintf(stderr, msg, arg);
  fprintf(stderr, "\n");
  exit(2);
}
