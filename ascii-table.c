#include <stdlib.h>
#include <stdio.h>
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

  s = realloc(s, l + 1);
  if (!s) {
    fprintf(stderr, "pad_left(): Out of memory.\n");
    exit(EXIT_FAILURE);
  }

  strncat(padding, s, l + 1);
  strncpy(s, padding, l + 1);
}

char get_char(size_t i) {
  return i < 33 || i == 127
    ? ' '
    : (char)i;
}

char* get_dec(size_t i) {
  size_t needed = snprintf(NULL, 0, "%zu", i);
  char* s = malloc(needed + 1);
  sprintf(s, "%zu", i);
  return s;
}

char* get_hex(unsigned int i) {
  size_t needed = snprintf(NULL, 0, "%x", i);
  char* s = malloc(needed + 1);
  sprintf(s, "%x", i);
  return s;
}

char* get_octal(unsigned int i) {
  size_t needed = snprintf(NULL, 0, "%d", i);
  char* s = malloc(needed + 1);
  sprintf(s, "%o", i);
  return s;
}

char* create_ascii_row(size_t i) {
  char* s = calloc(73, sizeof(char));

  for (size_t j = 0; j < 4; j++) {
    size_t tmp_i = i + (32 * j);

    char c = get_char(tmp_i);
    char* dec = get_dec(tmp_i);
    pad_left(dec, 4);
    char* hex = get_hex(tmp_i);
    pad_left(hex, 4);
    char* oct = get_octal(tmp_i);
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

int main() {
  for (size_t i = 0; i < 4; i++) {
    printf("Dec  Hex  Oct  C");
    if (i < 3) {
      printf(" | ");
    } else {
      printf("\n");
    }
  }

  for (size_t i = 0; i < 32; i++) {
    char* row = create_ascii_row(i);
    printf("%s\n", row);
    free(row);
  }

  return EXIT_SUCCESS;
}
