#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* pad_left(char* s, size_t l) {
  char* padded = calloc(l, sizeof(char));

  size_t iterations = l - strlen(s) - 1;
  for (size_t i = 0; i < iterations; i++) {
    padded[i] = ' ';
  }

  strcat(padded, s);
  return padded;
}

char get_char(size_t i) {
  if (i <= 31) {
    return '-';
  } else if (i == 32) {
    return ' ';
  } else if(i == 127) {
    return ' ';
  }
  else {
    return (char)i;
  }
}

char* get_dec(size_t i) {
  size_t l = 0;
  char* s;

  if (i < 10) {
    l = 2;
  } else if (i < 100) {
    l = 3;
  } else {
    l = 4;
  }

  s = calloc(l, sizeof(char));
  snprintf(s, l, "%zu", i);

  return s;
}

char* create_ascii_row(size_t i) {
  char* s = calloc(156, sizeof(char));

  for (size_t j = 0; j < 4; j++) {
    size_t tmp_i = i + (32 * j);
    char c = get_char(tmp_i);
    char* get_dec_result = get_dec(tmp_i);
    char* dec = pad_left(get_dec_result, 4);

    char* tmp_s = calloc(10, sizeof(char));
    if (j == 3) {
      sprintf(tmp_s, "%s  %s  %s  %c", dec, dec, dec, c);
    } else {
      sprintf(tmp_s, "%s  %s  %s  %c | ", dec, dec, dec, c);
    }

    strcat(s, tmp_s);

    free(dec);
    free(get_dec_result);
  }

  return s;
}

int main() {
  for (size_t i = 0; i < 4; i++) {
    printf("Dec  Hex  Oct  C   ");
  }
  printf("\n");

  for (size_t i = 0; i <= 31; i++) {
    char* x = create_ascii_row(i);
    printf("%s\n", x);
    free(x);
  }

  return EXIT_SUCCESS;
}
