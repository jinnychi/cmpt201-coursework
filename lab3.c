#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *lines[5] = {NULL};
int current_index = 0;
int line_count = 0;

void add_line(char *line) {
  // Clear non empty line
  if (lines[current_index] != NULL) {
    free(lines[current_index]);
  }

  // Replace with new line
  lines[current_index] = malloc(strlen(line) + 1);
  if (lines[current_index] != NULL) {
    strcpy(lines[current_index], line);
  }

  // Cycle the index between 0-4
  current_index = (current_index + 1) % 5;
  if (line_count < 5) {
    line_count++;
  }
}

void cleanup() {
  for (int i = 0; i < 5; i++) {
    if (lines[i] != NULL) {
      free(lines[i]);
    }
  }
}

int main() {
  char *input = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter input: ");

    getline(&input, &size, stdin);

    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "print") == 0) {
      for (int i = 0; i < line_count; i++) {
        printf("%s\n", lines[i]);
      }
    } else {
      add_line(input);
    }
  }

  free(input);
  cleanup();
  return 0;
}
