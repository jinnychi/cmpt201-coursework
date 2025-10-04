#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 64
#define STDOUT_FILENO 1

struct header {
  uint64_t size;
  struct header *next;
};
void handle_error(const char *msg) {
  write(STDOUT_FILENO, msg, strlen(msg));
  write(STDOUT_FILENO, "\n", 1);
  _exit(1);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}
int main() {
  void *heap_start = sbrk(256);
  size_t block_data_size = 128;

  // First block
  struct header *block1 = (struct header *)heap_start;
  block1->size = block_data_size;
  block1->next = NULL;

  // Second block
  struct header *block2 =
      (struct header *)((char *)block1 + sizeof(struct header) +
                        block_data_size);
  block2->size = block_data_size;
  block2->next = block1;

  // Get data pointers
  char *data1 = (char *)block1 + sizeof(struct header);
  char *data2 = (char *)block2 + sizeof(struct header);

  // Initialize data (0 for block 1, 1 for block 2)
  memset(data1, 0, block_data_size);
  memset(data2, 1, block_data_size);

  // Print everything
  write(STDOUT_FILENO, "first block:      ", 18);
  print_out("%p", &block1, sizeof(void *));
  write(STDOUT_FILENO, "\n", 1);

  write(STDOUT_FILENO, "second block:     ", 18);
  print_out("%p", &block2, sizeof(void *));
  write(STDOUT_FILENO, "\n", 1);

  write(STDOUT_FILENO, "first block size: ", 18);
  print_out("%lu", &block1->size, sizeof(uint64_t));
  write(STDOUT_FILENO, "\n", 1);

  write(STDOUT_FILENO, "first block next: ", 18);
  print_out("%p", &block1->next, sizeof(void *));
  write(STDOUT_FILENO, "\n", 1);

  write(STDOUT_FILENO, "second block size: ", 19);
  print_out("%lu", &block2->size, sizeof(uint64_t));
  write(STDOUT_FILENO, "\n", 1);

  write(STDOUT_FILENO, "second block next: ", 19);
  print_out("%p", &block2->next, sizeof(void *));
  write(STDOUT_FILENO, "\n", 1);

  for (int i = 0; i < block_data_size; i++) {
    char digit = '0' + data1[i];
    write(STDOUT_FILENO, &digit, 1);
    write(STDOUT_FILENO, "\n", 1);
  }

  for (int i = 0; i < block_data_size; i++) {
    char digit = '0' + data2[i];
    write(STDOUT_FILENO, &digit, 1);
    write(STDOUT_FILENO, "\n", 1);
  }
  return 0;
}
