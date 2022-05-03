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
  padding[padding_count] = '\0';
  for (size_t i = 0; i < padding_count; i++) {
    padding[i] = ' ';
  }

  strncat(padding, s, l);
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

char* create_ascii_row(size_t i) {
  size_t s_l = 128;
  char* s = calloc(s_l, sizeof(char));

  for (size_t j = 0; j < 4; j++) {
    size_t tmp_i = i + (32 * j);

    char c = get_char(tmp_i);
    char dec[5];
    get_dec(tmp_i, dec, sizeof(dec));
    pad_left(dec, 4);
    char hex[5];
    get_hex(tmp_i, hex, sizeof(hex));
    pad_left(hex, 4);
    char oct[5];
    get_octal(tmp_i, oct, sizeof(oct));
    pad_left(oct, 4);

    char tmp_s[32];
    if (j == 3) {
      snprintf(tmp_s, sizeof(tmp_s), "%s  %s  %s  %c", dec, hex, oct, c);
    } else {
      snprintf(tmp_s, sizeof(tmp_s), "%s  %s  %s  %c | ", dec, hex, oct, c);
    }

    strncat(s, tmp_s, s_l);
  }

  return s;
}

char* create_ascii_body() {
  size_t l = 4096;
  char* body = calloc(l, sizeof(char));

  for (size_t i = 0; i < 32; i++) {
    char* row = create_ascii_row(i);
    strncat(body, row, l);
    strncat(body, "\n", l);
    free(row);
    row = NULL;
  }

  return body;
}

char* create_ascii_header() {
  size_t l = 128;
  char* header = calloc(l, sizeof(char));

  for (size_t i = 0; i < 4; i++) {
    strncat(header, "Dec  Hex  Oct  C", l);
    if (i < 3) {
      strncat(header, " | ", l);
    }
  }

  strncat(header, "\n", l);

  return header;
}

char* create_ascii_table() {
  size_t l = 4096;
  char* table = calloc(4096, sizeof(char));

  char* ascii_header = create_ascii_header();
  char* ascii_body = create_ascii_body();

  strncat(table, create_ascii_header(), l);
  strncat(table, create_ascii_body(), l);

  free(ascii_header);
  ascii_header = NULL;
  free(ascii_body);
  ascii_body = NULL;

  return table;
}

int main() {
  char* ascii_table = create_ascii_table();
  printf("%s", ascii_table);

  free(ascii_table);
  ascii_table = NULL;

  return EXIT_SUCCESS;
}
