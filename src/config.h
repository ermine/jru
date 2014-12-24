#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "account.h"

typedef struct {
  account_t *accounts;
  size_t account_count;
} config_t;

config_t *config_load (const char* filename);
void config_destroy (config_t *config);

#endif
