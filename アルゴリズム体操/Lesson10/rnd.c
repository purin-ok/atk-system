#include <stdio.h>

long x = 1; /* 省略時の乱数の種は 1 */

short int rnd() {
  x = x * 1103515245 + 12345;
  return (short int)(x >> 16) & 32767;
}

void seed(unsigned short s) { x = s; }

int main(void) {
  int i;
  seed(123); /* 種を設定*/
  for (i = 1; i < 100; i++) {
    printf("%d: %d\n", i, rnd());
  }
  return 0;
}
