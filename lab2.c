#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *input = NULL;

  while (1) {
    printf("Enter programs to run.\n");
    printf("> ");

    getline(&input, &(size_t){0}, stdin);
    for (int i = 0; input[i]; i++) {
      if (input[i] == '\n') {
        input[i] = '\0';
        break;
      }
    }

    if (fork() == 0) {
      execl(input, input, NULL);
      perror("Exec failure");
      exit(1);
    }
    wait(NULL);
  }
}
