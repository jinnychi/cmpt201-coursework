#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  printf("Enter your text: ");
  nread = getline(&line, &len, stdin);
  if (nread <= -1) {
    perror("getline failed");
    exit(EXIT_FAILURE);
  }

  char *saveptr;
  char *token;

  printf("Tokens: \n");
  token = strtok_r(line, " ", &saveptr);
  while (token != NULL) {
    printf("  %s\n", token);
    token = strtok_r(NULL, " ", &saveptr);
  }

  free(line);
}
