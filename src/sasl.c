#include <stdio.h>
#include <openssl/md5.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <stdarg.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "helpers.h"
#include "base64.h"
#include "bufio.h"
#include "account.h"
#include "stream.h"
#include "sasl.h"
#include "errors.h"
#include "jid/jid.h"
#include "hex.h"

struct string_t {
  unsigned char* str;
  int len;
};

static int mystrlen (const char* str, int len) {
  int i = 0;
  for (i = 0; i < len && *str != '\0' && *str != ','; i++) str++;
  return i;
}

struct mechanisms_t {
  char* name;
  int (*callback) (stream_t* strm, account_t* account);
};

static int sasl_PLAIN (stream_t* strm, account_t* account);
static int sasl_DIGEST_MD5 (stream_t* strm, account_t* account);
static int sasl_SCRAM_SHA_1 (stream_t* strm, account_t* account);

static struct mechanisms_t known_mechanismss[] = {
  {"SCRAM-SHA-1", sasl_SCRAM_SHA_1},
  {"DIGEST-MD5", sasl_DIGEST_MD5},
  {"PLAIN", sasl_PLAIN},
};
static int known_mechanismss_len = 3;

bool sasl_is_mandatory (stream_t* strm) {
  return true;
}

bool sasl_need_restart () {
  return true;
}

int sasl_negotate (stream_t* strm, account_t* account, struct sasl_mechanisms_t* mechanisms) {
  vlist_t* curr = mechanisms->fMechanism;
  int i = 0;
  for (i = 0; i < known_mechanismss_len; i++) {
    while (curr != NULL) {
      if (strcmp (known_mechanismss[i].name, (const char*) curr->data) == 0)
        return known_mechanismss[i].callback (strm, account);
      curr = curr->next;
    }
  }
  return ERR_SASL_NO_KNOWN_METHOD;
}

int sasl_PLAIN (stream_t* strm, account_t* account) {
  int err = 0;

  char data[2024];
  int len1 = strlen (account->jid->node);
  int len2 = strlen (account->password);
  
  data[0] = '\0';
  memcpy (data+1, account->jid->node, len1);
  data[len1+1] = '\0';
  memcpy (data+2+len1, account->password, len2);
  data[len1+len2+2] = '\0';
          
  struct sasl_auth_t sasl_auth = {"PLAIN", (unsigned char*) data, len1+len2+2};
  err = sasl_auth_encode (strm->writer, &sasl_auth);
  if (err != 0) return err;
  err = xmlwriter_flush (strm->writer);
  if (err != 0) return err;

  extension_t* ext = xstream_read (strm->reader);
  if (strm->reader->err != 0) return strm->reader->err;
  if (ext == NULL) return ERR_BAD_PROTOCOL;
  switch (ext->type) {
  case EXTENSION_TYPE_SASL_SUCCESS:
    return 0;
  case EXTENSION_TYPE_SASL_FAILURE:
  case EXTENSION_TYPE_STREAM_ERROR:
    strm->xmpp_error = ext;
    return ERR_XMPP_ERROR;
  }
  return ERR_BAD_PROTOCOL;
}

static void make_cnonce (char *s, const int len) {
  static const char alphanum[] = "0123456789ABCDEF";

  int i = 0;
  for (i = 0; i < len; i++) {
    *s++ = alphanum[rand() % (sizeof(alphanum) - 1)];
  }
  *s = 0;
}

static void md5_sum (unsigned char* out, int nparams, ...) {
  va_list arg;
  va_start (arg, nparams);
  int i = 0;

  MD5_CTX c;

  MD5_Init (&c);
  for (i = 0; i < nparams; i++) {
    unsigned char* data = va_arg (arg, unsigned char*);
    int len = va_arg (arg, int);
    MD5_Update (&c, data, len);
  }
  va_end (arg);
  MD5_Final (out, &c);
}

int sasl_DIGEST_MD5(stream_t* strm, account_t* account) {
  int err = 0;

  extension_t* ext;

  struct sasl_auth_t sasl_auth = {"DIGEST-MD5", NULL, 0};
  err = sasl_auth_encode (strm->writer, &sasl_auth);
  if (err != 0) return err;
  err = xmlwriter_flush (strm->writer);
  if (err != 0) return err;

  ext = xstream_read (strm->reader);
  if (strm->reader->err != 0) return strm->reader->err;
  if (ext == NULL) return ERR_BAD_PROTOCOL;
  switch (ext->type) {
  case EXTENSION_TYPE_SASL_CHALLENGE: {
    struct sasl_challenge_t* sasl_challenge = ext->data;
    char* nonce = NULL;
    char* qop = NULL;

    char* ptr, *key, *value, *sep;

    ptr =  (char*) sasl_challenge->fData;
    while (ptr != NULL) {
      sep = strchr (ptr, '=');
      if (sep == NULL) {
        key = ptr;
        value = NULL;
        ptr = NULL;
      } else {
        key = ptr;
        ptr = sep+1;
        value = ptr;
        *sep = '\0';
        if (value[0] == '"') {
          ++value;
          sep = strchr (value, '"');
          if (sep == NULL)
            return ERR_SASL;
          *sep++ = '\0';
          ptr = sep;
        }
        sep = strchr (ptr, ',');
        if (sep == NULL)
          ptr = NULL;
        else {
          *sep = '\0';
          ptr = sep+1;
        }
      }

      if (strcmp ("nonce", key) == 0)
        nonce = value;
      else if (strcmp ("qop", key) == 0)
        qop = value;
    }

    if (nonce == NULL || qop == NULL)
      return ERR_SASL;

    char cnonce[9];
    make_cnonce (cnonce, 8);
		char* nc = "00000001";

    bool exists = false;
    ptr = qop;
    while (ptr != NULL) {
      if (strncmp (ptr, "auth", 4) == 0 && (ptr[4] == '\0' || ptr[4] == ',')) {
        exists = true;
        break;
      }
      sep = strchr (ptr, ',');
      if (sep == NULL)
        break;
      else
        ptr = sep+1;
    }
		if (!exists) { return ERR_SASL_NO_KNOWN_QOP_METHOD; }

    unsigned char a0[MD5_DIGEST_LENGTH];
    md5_sum (a0, 5, account->jid->node, strlen (account->jid->node), ":", 1,
             account->jid->domain, strlen (account->jid->domain), ":", 1,
             account->password, strlen (account->password));

    unsigned char a1[MD5_DIGEST_LENGTH];
    md5_sum (a1, 5, a0, MD5_DIGEST_LENGTH, ":", 1, nonce, strlen (nonce),
             ":", 1, cnonce, strlen (cnonce));

    unsigned char a2[MD5_DIGEST_LENGTH];
    md5_sum (a2, 2, "AUTHENTICATE:xmpp/", 18,
             account->jid->domain, strlen (account->jid->domain));

    char hex1 [MD5_DIGEST_LENGTH * 2 + 1];
    hex_of_binary (hex1, a1, MD5_DIGEST_LENGTH);

    char hex2 [MD5_DIGEST_LENGTH * 2 + 1];
    hex_of_binary (hex2, a2, MD5_DIGEST_LENGTH);

    unsigned char t[MD5_DIGEST_LENGTH];
    md5_sum (t, 9, hex1, 32, ":", 1, nonce, strlen (nonce), ":", 1, nc, strlen (nc), 
             ":", 1, cnonce, strlen (cnonce), ":auth:", 6, hex2, 32);

    char hext[MD5_DIGEST_LENGTH * 2 + 1];
    hex_of_binary (hext, t, MD5_DIGEST_LENGTH);
    
		char response[4096];
    int len = sprintf (response, 
                       "charset=\"utf-8\",username=\"%s\",realm=\"%s\",nonce=\"%s\",cnonce=\"%s\",nc=\"%s\",qop=\"auth\",digest-uri=\"xmpp/%s\",response=\"%s\"",
                       account->jid->node, account->jid->domain,
                       nonce, cnonce, nc, account->jid->domain, hext);

    struct sasl_response_t sasl_response = { (unsigned char*) response, len};
    err = sasl_response_encode (strm->writer, &sasl_response);
    if (err != 0) return err;
    err = xmlwriter_flush (strm->writer);
    if (err != 0) return err;

    ext = xstream_read (strm->reader);
    if (strm->reader->err != 0) return strm->reader->err;
    if (ext == NULL) return ERR_BAD_PROTOCOL;
    switch (ext->type) {
		case EXTENSION_TYPE_SASL_CHALLENGE: {
      struct sasl_response_t sasl_response = { NULL, 0};
      err = sasl_response_encode (strm->writer, &sasl_response);
      if (err != 0) return err;
      err = xmlwriter_flush (strm->writer);
      if (err != 0) return err;

      ext = xstream_read (strm->reader);
      if (strm->reader->err != 0) return strm->reader->err;
      if (ext == NULL) return ERR_BAD_PROTOCOL;
      switch (ext->type) {
      case EXTENSION_TYPE_SASL_SUCCESS:
        return 0;
      case EXTENSION_TYPE_SASL_FAILURE:
      case EXTENSION_TYPE_STREAM_ERROR:
        strm->xmpp_error = ext;
        return ERR_XMPP_ERROR;
      }
    }
    case EXTENSION_TYPE_SASL_FAILURE:
    case EXTENSION_TYPE_STREAM_ERROR:
        strm->xmpp_error = ext;
        return ERR_XMPP_ERROR;
		}
  }
  }
	return ERR_BAD_PROTOCOL;
}

static void scram_H (unsigned char* data, int data_len, unsigned char* mdkey) {
  SHA_CTX c;
  SHA1_Init (&c);
  SHA1_Update(&c, data, data_len);
  SHA1_Final (mdkey, &c);
}

static void scram_HMAC (const unsigned char* key, const unsigned int key_len,
                        const unsigned char* data, const unsigned int data_len,
                        unsigned char* result) {

  /*
  HMAC (EVP_sha1(), key, key_len, data, data_len, result, 20);
  */
  unsigned int result_len = 20;
  HMAC_CTX hmac;
  HMAC_Init (&hmac, key, key_len, EVP_sha1());
  HMAC_Update (&hmac, data, data_len);
  HMAC_Final (&hmac, result, &result_len);
}

static inline void scram_XOR(unsigned char* x1, const unsigned int x1_len,
                             const unsigned char* x2) {
  int i = 0;
  
  for (i = 0; i < x1_len; i++) {
    x1[i] ^= x2[i];
  }
}

static void scram_Hi (const unsigned char* key, const unsigned int key_len,
                      const unsigned char* salt, const unsigned int salt_len, unsigned int i,
                      unsigned char* result) {

  unsigned char u1[20];
  unsigned int u1_len = 20;

  HMAC_CTX hmac;
  // HMAC_CTX_init (&hmac);
  
  HMAC_Init (&hmac, key, key_len, EVP_sha1());
  HMAC_Update (&hmac, salt, salt_len);
  HMAC_Update (&hmac, (unsigned char*) "\0\0\0\1", 4);
  HMAC_Final (&hmac, u1, &u1_len);

  unsigned char u2[20];
  
  unsigned char x[20];
  memcpy(x, u1, u1_len);
  
  unsigned char* uprev = u1;
  memcpy (uprev, u1, u1_len);
  
  for (; i > 1; i--) {
    scram_HMAC (key, key_len, uprev, u1_len, u2);
    memcpy (uprev, u2, u1_len);
    scram_XOR(x, u1_len, u2);
  }
  memcpy (result, x, 20);
}

int sasl_SCRAM_SHA_1 (stream_t* strm, account_t* account) {
  int err = 0;
  
  char cnonce[9];
  make_cnonce(cnonce, 8);

  char clientFirstMessageBare[1054];
  int clientFirstMessageBare_len =
    sprintf (clientFirstMessageBare, "n=%s,r=%s", account->jid->node, cnonce);

	char data[1040];
  int len = sprintf (data, "n,,%s", clientFirstMessageBare);

  struct sasl_auth_t sasl_auth = {"SCRAM-SHA-1", (unsigned char*) data, len};
  err = sasl_auth_encode (strm->writer, &sasl_auth);
  if (err != 0) return err;
  err = xmlwriter_flush (strm->writer);
  if (err != 0) return err;

  extension_t* ext = xstream_read (strm->reader);
  if (strm->reader->err != 0) return strm->reader->err;
  if (ext == NULL) return ERR_BAD_PROTOCOL;
  switch (ext->type) {
  case EXTENSION_TYPE_SASL_CHALLENGE: {
    struct sasl_challenge_t* sasl_challenge = ext->data;

		const char* serverFirstMessage = (const char*) sasl_challenge->fData;
    int serverFirstMessage_len = sasl_challenge->fData_len;

    char key;
    char* value;
    char* ptr = (char*) sasl_challenge->fData;
    int len = 0, l = 0;

    struct string_t salt, r;
    unsigned int iteration = 0;
    
    while (len < sasl_challenge->fData_len) {
      key = ptr[0];
      ptr++; len++;
      value = NULL;
      l = 0;
      if (len < sasl_challenge->fData_len) {
        if (*ptr == '=') {
          ptr++; len++;
        }
        l = mystrlen (ptr, sasl_challenge->fData_len - len);
      }
      if (l > 0) {
        value = ptr;
      }
      ptr += l;
      len += l;
      switch (key) {
      case 's': {
        err = base64_decode (value, l, &salt.str, &salt.len);
        if (err != 0) return err;
        break;
      }
      case 'i': {
        char tmp[10];
        memcpy (tmp, value, l);
        tmp[l] = 0;
        iteration = atoi (tmp);
        break;
      }
      case 'r':
        r.str = (unsigned char*) value; r.len = l;
        break;
      }
      if (len + 1 < sasl_challenge->fData_len) {
        if (*ptr == ',') {
          ptr++; len++;
        } else
          return ERR_SASL;
      }
    }
        
    char* str = NULL;
    err = jid_resourceprep (account->password, &str);
    if (err != 0) return err;

    unsigned char saltedpassword[20];
    scram_Hi ((unsigned char*) str, strlen (str), salt.str, salt.len, iteration, saltedpassword);

    unsigned char clientKey[20];
		scram_HMAC (saltedpassword, 20, (unsigned char*) "Client Key",10, clientKey);

		unsigned char storedKey[20];
    scram_H (clientKey, 20, storedKey);

    int clientFinalMessageWithoutProof_len = 9 + r.len;
		char* clientFinalMessageWithoutProof = malloc (clientFinalMessageWithoutProof_len);
    if (clientFinalMessageWithoutProof == NULL)
      fatal ("sasl_SCRAM_SHA_1: malloc failed");
    memcpy (clientFinalMessageWithoutProof, "c=biws,r=", 9);
    memcpy (clientFinalMessageWithoutProof + 9, r.str, r.len);
    
		char authMessage[4096];
    memcpy (authMessage, clientFirstMessageBare, clientFirstMessageBare_len);
    authMessage[clientFirstMessageBare_len] = ',';
    memcpy (authMessage + clientFirstMessageBare_len + 1,
            serverFirstMessage, serverFirstMessage_len);
    authMessage[clientFirstMessageBare_len + 1 + serverFirstMessage_len] = ',';
    memcpy (authMessage + clientFirstMessageBare_len + serverFirstMessage_len + 2,
            clientFinalMessageWithoutProof, clientFinalMessageWithoutProof_len);
    int authMessage_len = clientFirstMessageBare_len + serverFirstMessage_len +
      clientFinalMessageWithoutProof_len + 2;
    
		unsigned char clientSignature[20];
    scram_HMAC (storedKey, 20, (unsigned char*) authMessage, authMessage_len, clientSignature);
    
      unsigned char clientProof[20];
      memcpy (clientProof, clientKey, 20);
      scram_XOR (clientProof, 20, clientSignature);

      unsigned char serverKey[20];
      scram_HMAC (saltedpassword, 20, (unsigned char*) "Server Key", 10, serverKey);
    
      unsigned char serverSignature[20];
      scram_HMAC (serverKey, 20, (unsigned char*) authMessage,authMessage_len,  serverSignature);

      char* encoded_prof = base64_encode(clientProof, 20);
      int encoded_prof_len = strlen (encoded_prof);

      char response[4096];
      memcpy (response, clientFinalMessageWithoutProof, clientFinalMessageWithoutProof_len);
      memcpy (response + clientFinalMessageWithoutProof_len, ",p=", 3);
      memcpy (response + clientFinalMessageWithoutProof_len + 3, encoded_prof, encoded_prof_len);
      len = clientFinalMessageWithoutProof_len + 3 + encoded_prof_len;
              
      free (encoded_prof);
      
      struct sasl_response_t sasl_response = { (unsigned char*) response , len};
      err = sasl_response_encode (strm->writer, &sasl_response);
      if (err != 0) return err;
      err = xmlwriter_flush (strm->writer);
      if (err != 0) return err;

      ext = xstream_read (strm->reader);
      if (strm->reader->err != 0) return strm->reader->err;
      if (ext == NULL) return ERR_BAD_PROTOCOL;
      switch (ext->type) {
      case EXTENSION_TYPE_SASL_SUCCESS: {
        struct sasl_success_t* sasl_success = ext->data;

        char key;
        char* value;
        char* ptr = (char*) sasl_success->fData;
        int len = 0, l = 0;
        
        while (len < sasl_success->fData_len) {
          key = ptr[0];
          ptr++; len++;
          value = NULL;
          l = 0;
          if (len < sasl_success->fData_len) {
            if (ptr[0] == '=') {
              ptr++; len++;
            } else
              return ERR_SASL;
            l = mystrlen (ptr, sasl_success->fData_len - len);
            if (l > 0) {
              value = ptr;
              ptr += l;
              len += l;
            }
          }
              
          switch (key) {
          case 'v': {
            if (value == NULL) return ERR_SASL;
            struct string_t v;
            err = base64_decode (value, l, &v.str, &v.len);
            if (err != 0) return err;
            
            if (strncmp ((char*) v.str, (char*) serverSignature, v.len) != 0)
              return ERR_SASL_SERVER_SIGNATURE_MISMATCH;
          }
          }
          if (len + 1 < sasl_success->fData_len) {
            if (*ptr == ',') {
              ptr++; len++;
            } else
              return ERR_SASL;
          }
        }
        return 0;
      }        
      case EXTENSION_TYPE_SASL_FAILURE:
      case EXTENSION_TYPE_STREAM_ERROR:
        strm->xmpp_error = ext;
        return ERR_XMPP_ERROR;
      }
  }
	case EXTENSION_TYPE_SASL_FAILURE:
	case EXTENSION_TYPE_STREAM_ERROR:
    strm->xmpp_error = ext;
    return ERR_XMPP_ERROR;
	}
	return ERR_BAD_PROTOCOL;
}

