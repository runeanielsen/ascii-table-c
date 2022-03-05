#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void pad_left(char* s, uint l) {
  char* padded = calloc(l, sizeof(char));

  uint iterations = l - strlen(s) - 1;
  for (uint i = 0; i < iterations; i++) {
    padded[i] = ' ';
  }

  strcat(padded, s);
  strcpy(s, padded);
}

char get_char(uint i) {
  if (i <= 31) {
    return '-';
  } else if (i == 32 || i == 127) {
    return ' ';
  } else {
    return (char)i;
  }
}

char* get_dec(uint i) {
  char* s = calloc(4, sizeof(char));
  snprintf(s, 4, "%d", i);
  return s;
}

char* get_hex(uint i) {
  char* s = calloc(2, sizeof(char));
  sprintf(s, "%x", i);
  return s;
}

char* get_octal(uint i) {
  char* s = calloc(3, sizeof(char));
  sprintf(s, "%o", i);
  return s;
}

char* create_ascii_row(uint i) {
  char* s = calloc(73, sizeof(char));

  for (uint j = 0; j < 4; j++) {
    uint tmp_i = i + (32 * j);

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
  for (uint i = 0; i < 4; i++) {
    printf("Dec  Hex  Oct  C   ");
  }
  printf("\n");

  for (uint i = 0; i <= 31; i++) {
    char* row = create_ascii_row(i);
    printf("%s\n", row);
    free(row);
  }

  return EXIT_SUCCESS;
}
