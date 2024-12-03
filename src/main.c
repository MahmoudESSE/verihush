#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024

void help() {
  printf("Usage: virihush [OPTION] MESSAGE KEY\n");
  printf("Encrypt and Decrypt a message using a key\n");
  printf("\n");
  printf("Options:\n");
  printf("\t-e\t\tencrypt text\n");
  printf("\t-d\t\tdecrypt text\n");
}

int str_new(char **str) {
  int str_len = MAX_STR_LEN * sizeof(char);
  *str = malloc(str_len + 1);
  if (*str == NULL) {
    fprintf(stderr, "error(str): %s\n", strerror(errno));
    return errno;
  }
  memset(*str, '\0', str_len);
  return 0;
}

void ascii_cipher(char *message, char *cipher) {
  for (size_t i = 0; i < strlen(message); ++i) {
    cipher[i] = message[i] + 3;
  }
}

void ascii_decipher(char *message) {
  for (size_t i = 0; i < strlen(message); ++i) {
    message[i] = message[i] - 3;
  }
}

void xor_cipher(char *message, char *key, char *cipher) {
  size_t key_len = strlen(key);
  for (size_t i = 0; i < key_len; ++i) {
    key[i] = toupper(key[i]);
  }

  size_t message_len = strlen(message);
  for (size_t i = 0; i < message_len; ++i) {
    size_t key_idx = i % key_len;
    cipher[i] = message[i] ^ key[key_idx];
  }
}

int main(int argc, char **argv) {

  if (argc != 4) {
    fprintf(stderr, "error: not enough arguments\n");
    printf("\n");
    help();
    return 1;
  }

  if (strlen(argv[2]) != 4) {
    fprintf(stderr, "error: message should be 4 characters long\n");
    return 1;
  }

  if (strlen(argv[3]) != 4) {
    fprintf(stderr, "error: key should be 4 characters long\n");
    return 1;
  }

  int encryption_type;

  if (strcmp(argv[1], "-e") || strcmp(argv[1], "-d")) {
    if (strcmp(argv[1], "-e") == 0) {
      encryption_type = 1;
    }

    if (strcmp(argv[1], "-d") == 0) {
      encryption_type = 2;
    }
  } else {
    fprintf(stderr, "error: arguement %s not found\n", argv[1]);
    printf("\n");
    help();
  }

  char *message = NULL;
  if (str_new(&message) != 0) {
    return errno;
  }

  char *key = NULL;
  if (str_new(&key) != 0) {
    return errno;
  }

  strcpy(key, argv[3]);

  char *ascii_cipher_message = NULL;
  if (str_new(&ascii_cipher_message) != 0) {
    return errno;
  }

  char *xor_cipher_message = NULL;
  if (str_new(&xor_cipher_message) != 0) {
    return errno;
  }

  switch (encryption_type) {
  case 1:
    strcpy(message, argv[2]);

    if (strlen(key) == 0) {
      fprintf(stderr, "error(key): key is empty\n");
      break;
    }

    xor_cipher(message, key, xor_cipher_message);
    ascii_cipher(message, ascii_cipher_message);

    printf("%s\n", xor_cipher_message);
    printf("%s\n", ascii_cipher_message);
    break;
  case 2:
    strcpy(message, argv[2]);
    ascii_decipher(message);
    printf("%s\n", message);
    break;
  }

  free(message);
  message = NULL;

  free(key);
  key = NULL;

  free(ascii_cipher_message);
  ascii_cipher_message = NULL;

  free(xor_cipher_message);
  xor_cipher_message = NULL;

  if (errno != EXIT_SUCCESS) {
    fprintf(stderr, "error: %s\n", strerror(errno));
    return errno;
  }

  return errno;
}
