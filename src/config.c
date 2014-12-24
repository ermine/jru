#include <yaml.h>

#include "config.h"
#include "jid/jid.h"

static void process_accounts(yaml_document_t *yaml_document, yaml_node_t *node, config_t *config) {
  int i;
  
  if (node->type == YAML_SEQUENCE_NODE) {
    // count
    for (i = 0; node->data.sequence.items.start + i < node->data.sequence.items.top; i++);
    if (i == 0)
      return;

    config->account_count = i;
    config->accounts = malloc (sizeof (account_t) * i);
    memset (config->accounts, 0, (sizeof (account_t) * i));
    account_t *accounts = config->accounts;
      
    for (i = 0; node->data.sequence.items.start + i < node->data.sequence.items.top; i++) {
      yaml_node_t *subnode =
        yaml_document_get_node (yaml_document, node->data.sequence.items.start[i]);
      if (subnode->type == YAML_MAPPING_NODE) {
        yaml_node_pair_t *pair = subnode->data.mapping.pairs.start;
        do {
          yaml_node_t *key_node = yaml_document_get_node (yaml_document, pair->key);
          if (strcmp ("jid", (char *) key_node->data.scalar.value) == 0) {
            yaml_node_t *value_node = yaml_document_get_node (yaml_document, pair->value);
            jid_t *jid = jid_of_string ((char *) value_node->data.scalar.value);
            accounts[i].jid = jid;
          } else if (strcmp ("password", (char *) key_node->data.scalar.value) == 0) {
            yaml_node_t *value_node = yaml_document_get_node (yaml_document, pair->value);
            accounts[i].password = strdup ((char *) value_node->data.scalar.value);
          } else if (strcmp ("ip", (char *) key_node->data.scalar.value) == 0) {
            yaml_node_t *value_node = yaml_document_get_node (yaml_document, pair->value);
            accounts[i].ip = strdup ((char *) value_node->data.scalar.value);
          } else if (strcmp ("port", (char *) key_node->data.scalar.value) == 0) {
            yaml_node_t *value_node = yaml_document_get_node (yaml_document, pair->value);
            accounts[i].port = atoi ((char *) value_node->data.scalar.value);
          }
        } while (pair++, pair < subnode->data.mapping.pairs.top);
      } 
    }
  }
}

config_t *config_load (const char* filename) {
  FILE *fh;
  yaml_parser_t yaml_parser;
  yaml_document_t yaml_document;
  config_t *config;

  fh = fopen ("config.yaml", "r");
  if (fh == NULL) {
    fputs ("Failed to open file!\n", stderr);
    return NULL;
  }

  if (!yaml_parser_initialize (&yaml_parser)) {
    fputs ("Failed to initialize parser!\n", stderr);
    goto error;
  }
  yaml_parser_set_input_file (&yaml_parser, fh);
  yaml_parser_load(&yaml_parser, &yaml_document);

  config = malloc (sizeof (config_t));

  yaml_node_t *root = yaml_document_get_root_node (&yaml_document);
  if (!root)
    goto error;
  
  if (root->type == YAML_MAPPING_NODE) {
    yaml_node_pair_t *pair = root->data.mapping.pairs.start;
    do {
      yaml_node_t *key_node = yaml_document_get_node (&yaml_document, pair->key);
      if (strcmp ("accounts", (char *) key_node->data.scalar.value) >= 0) {
        yaml_node_t *node = yaml_document_get_node (&yaml_document, pair->value);
        process_accounts (&yaml_document, node, config);
      }

    } while (pair++, pair < root->data.mapping.pairs.top);
  } 

  fclose (fh);
  yaml_document_delete( &yaml_document);
  yaml_parser_delete (&yaml_parser);

  return config;

 error:

  fclose (fh);
  yaml_document_delete( &yaml_document);
  yaml_parser_delete (&yaml_parser);
  config_destroy (config);
  return NULL;
}

void config_destroy (config_t *config) {
  if (config != NULL) {
    if (config->accounts != NULL) {
      int i;
      for (i = 0; i < config->account_count; i++) {
        account_t *account = &config->accounts[i];
        if (account->jid != NULL)
          jid_free (account->jid);
        if (account->password != NULL)
          free (account->password);
        if (account->ip != NULL)
          free (account->ip);
      }
      free (config->accounts);
    }
    free (config);
  }
}
