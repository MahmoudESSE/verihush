#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024

void help() {
  printf("Usage: virihush [OPTION] TEXT\n");
  printf("Encrypt and Decrypt a text input\n");
  printf("\n");
  printf("Options:\n");
  printf("\t-e\t\tencrypt text\n");
  printf("\t-d\t\tdecrypt text\n");
}

int main(int argc, char **argv) {

  if (argc != 3) {
    fprintf(stderr, "error: not enough arguments\n");
    printf("\n");
    help();
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

  int message_len = MAX_STR_LEN * sizeof(char);
  char *message = malloc(message_len + 1);
  if (message == NULL) {
    fprintf(stderr, "error: %s\n", strerror(errno));
    return errno;
  }
  memset(message, 0, message_len);

  switch (encryption_type) {
  case 1:
    strcpy(message, argv[2]);
    for (int i = 0; i < strlen(message); ++i) {
      message[i] = message[i] + 3;
    }
    printf("%s\n", message);
    break;
  case 2:
    strcpy(message, argv[2]);
    for (int i = 0; i < strlen(message); ++i) {
      message[i] = message[i] - 3;
    }
    printf("%s\n", message);
    break;
  }

  free(message);
  message = NULL;

  if (errno != EXIT_SUCCESS) {
    fprintf(stderr, "error: %s\n", strerror(errno));
    return errno;
  }

  return errno;
}
