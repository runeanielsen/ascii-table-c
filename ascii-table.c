#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_char(size_t i) {
  return i < 33 || i == 127 ? ' ' : i;
}

void create_ascii_row(size_t i, char* buffer, size_t max_length) {
  for (size_t j = 0; j < 4; j++) {
    unsigned int cell = i + (32 * j);

    char tmp_s[32] = "";
    if (j == 3) {
      snprintf(tmp_s, sizeof(tmp_s), "%3u %4x %4o %2c", cell, cell, cell, get_char(cell));
    } else {
      snprintf(tmp_s, sizeof(tmp_s), "%3u %4x %4o %2c | ", cell, cell, cell, get_char(cell));
    }

    strncat(buffer, tmp_s, max_length - 1);
  }
}

void create_ascii_body(char* buffer, size_t max_size) {
  char row[128] = "";
  for (size_t i = 0; i < 32; i++) {
    create_ascii_row(i, row, sizeof(row));
    strncat(buffer, row, max_size - 1);
    strncat(buffer, "\n", max_size - 1);
    memset(row, 0, sizeof(row));
  }
}

void create_ascii_header(char* buffer, size_t max_size) {
  for (size_t i = 0; i < 4; i++) {
    strncat(buffer, "Dec  Hex  Oct  C", max_size - 1);
    if (i < 3) {
      strncat(buffer, " | ", max_size - 1);
    }
  }
  strncat(buffer, "\n", max_size - 1);
}

void create_ascii_table(char* buffer, size_t max_size) {
  create_ascii_header(buffer, max_size);
  create_ascii_body(buffer, max_size);
}

int main() {
  char ascii_table[4096];
  create_ascii_table(ascii_table, sizeof(ascii_table));
  printf("%s", ascii_table);

  return EXIT_SUCCESS;
}
