#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pad_left(char *s, size_t l) {
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

  s = realloc(s, l + 1);
  if (!s) {
    fprintf(stderr, "pad_left(): Out of memory.\n");
    exit(EXIT_FAILURE);
  }

  strncat(padding, s, l + 1);
  strncpy(s, padding, l + 1);
}

char get_char(size_t i) { return i < 33 || i == 127 ? ' ' : (char)i; }

char *get_dec(size_t i) {
  size_t needed = snprintf(NULL, 0, "%zu", i);
  char *s = malloc(needed + 1);
  sprintf(s, "%zu", i);
  return s;
}

char *get_hex(unsigned int i) {
  size_t needed = snprintf(NULL, 0, "%x", i);
  char *s = malloc(needed + 1);
  sprintf(s, "%x", i);
  return s;
}

char *get_octal(unsigned int i) {
  size_t needed = snprintf(NULL, 0, "%d", i);
  char *s = malloc(needed + 1);
  sprintf(s, "%o", i);
  return s;
}

char *create_ascii_row(size_t i) {
  char *s = calloc(128, sizeof(char));

  for (size_t j = 0; j < 4; j++) {
    size_t tmp_i = i + (32 * j);

    char c = get_char(tmp_i);
    char *dec = get_dec(tmp_i);
    pad_left(dec, 4);
    char *hex = get_hex(tmp_i);
    pad_left(hex, 4);
    char *oct = get_octal(tmp_i);
    pad_left(oct, 4);

    char tmp_s[16];
    if (j == 3) {
      sprintf(tmp_s, "%s  %s  %s  %c", dec, hex, oct, c);
    } else {
      sprintf(tmp_s, "%s  %s  %s  %c | ", dec, hex, oct, c);
    }

    strcat(s, tmp_s);

    free(dec);
    free(hex);
    free(oct);
  }

  return s;
}

char *create_ascii_body() {
  char *body = calloc(4096, sizeof(char));

  for (size_t i = 0; i < 32; i++) {
    char *row = create_ascii_row(i);
    strcat(body, row);
    strcat(body, "\n");
    free(row);
    row = NULL;
  }

  return body;
}

char *create_ascii_header() {
  char *header = calloc(128, sizeof(char));

  for (size_t i = 0; i < 4; i++) {
    strcat(header, "Dec  Hex  Oct  C");
    if (i < 3) {
      strcat(header, " | ");
    }
  }

  strcat(header, "\n");

  return header;
}

char *create_ascii_table() {
  char *table = calloc(4096, sizeof(char));

  char *ascii_header = create_ascii_header();
  char *ascii_body = create_ascii_body();

  strcat(table, create_ascii_header());
  strcat(table, create_ascii_body());

  free(ascii_header);
  ascii_header = NULL;
  free(ascii_body);
  ascii_body = NULL;

  return table;
}

int main() {
  char *ascii_table = create_ascii_table();
  printf("%s", ascii_table);

  free(ascii_table);
  ascii_table = NULL;

  return EXIT_SUCCESS;
}
