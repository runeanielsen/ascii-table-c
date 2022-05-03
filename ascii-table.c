#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pad_left(char* s, size_t l) {
  /* If there is no difference, do not pad. */
  if (l == strlen(s)) {
    return;
  }

  size_t padding_count = l - strlen(s) - 1;

  char padding[l];
  memset(padding, 0, l);
  padding[padding_count] = '\0';
  for (size_t i = 0; i < padding_count; i++) {
    padding[i] = ' ';
  }

  strncat(padding, s, l - 1);
  strncpy(s, padding, l);
}

char get_char(size_t i) {
  return i < 33 || i == 127 ? ' ' : (char)i;
}

void get_dec(size_t i, char* buffer, size_t max_length) {
  snprintf(buffer, max_length, "%zu", i);
}

void get_hex(unsigned int i, char* buffer, size_t max_length) {
  snprintf(buffer, max_length, "%x", i);
}

void get_octal(unsigned int i, char* buffer, size_t max_length) {
  snprintf(buffer, max_length, "%o", i);
}

void create_ascii_row(size_t i, char* buffer, size_t max_length) {
  for (size_t j = 0; j < 4; j++) {
    size_t tmp_i = i + (32 * j);

    char c = get_char(tmp_i);
    char dec[5] = "";
    get_dec(tmp_i, dec, sizeof(dec));
    pad_left(dec, 4);
    char hex[5] = "";
    get_hex(tmp_i, hex, sizeof(hex));
    pad_left(hex, 4);
    char oct[5] = "";
    get_octal(tmp_i, oct, sizeof(oct));
    pad_left(oct, 4);

    char tmp_s[32] = "";
    if (j == 3) {
      snprintf(tmp_s, sizeof(tmp_s), "%s  %s  %s  %c", dec, hex, oct, c);
    } else {
      snprintf(tmp_s, sizeof(tmp_s), "%s  %s  %s  %c | ", dec, hex, oct, c);
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
  char header[128] = "";
  create_ascii_header(header, sizeof(header));

  char body[4096] = "";
  create_ascii_body(body, sizeof(body));

  strncat(buffer, header, max_size - 1);
  strncat(buffer, body, max_size - 1);
}

int main() {
  char ascii_table[5124];
  create_ascii_table(ascii_table, sizeof(ascii_table));
  printf("%s", ascii_table);
  return EXIT_SUCCESS;
}
