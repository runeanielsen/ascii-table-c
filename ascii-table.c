#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char char_format(size_t i) { return i < 33 || i == 127 ? ' ' : i; }

static void ascii_row(size_t i, char *buffer, size_t max_length) {
  for (size_t j = 0; j < 4; j++) {
    unsigned int b = i + 32 * j;
    char block[32] = "";
    snprintf(block, sizeof(block), "%3u %4x %4o %2c", b, b, b, char_format(b));
    strncat(buffer, block, max_length - 1);
    if (j < 3) {
      strncat(buffer, " | ", max_length - 1);
    }
  }
}

static void ascii_body(char *buffer, size_t max_size) {
  for (size_t i = 0; i < 32; i++) {
    char row[128] = "";
    ascii_row(i, row, sizeof(row));
    strncat(buffer, row, max_size - 1);
    strncat(buffer, "\n", max_size - 1);
  }
}

static void ascii_header(char *buffer, size_t max_size) {
  for (size_t i = 0; i < 4; i++) {
    strncat(buffer, "Dec  Hex  Oct  C", max_size - 1);
    if (i < 3) {
      strncat(buffer, " | ", max_size - 1);
    }
  }
}

static void ascii_table(char *buffer, size_t max_size) {
  ascii_header(buffer, max_size);
  strncat(buffer, "\n", max_size - 1);
  ascii_body(buffer, max_size);
}

int main() {
  char ascii_table_buf[4096] = "";
  ascii_table(ascii_table_buf, sizeof(ascii_table_buf));
  printf("%s", ascii_table_buf);
  return EXIT_SUCCESS;
}
