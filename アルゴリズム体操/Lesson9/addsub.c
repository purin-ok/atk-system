/*
 * -------------------
 *      多桁計算     *
 * -------------------
 */

#include <stdio.h>

#define KETA 20                /* 桁数 */
#define N ((KETA - 1) / 4 + 1) /* 配列サイズ */

void ladd(short *a, short *b, short *c);  // c = a + b
void lsub(short *a, short *b, short *c);  // c = a - b
void print(short *c);

int main(void) {
  short a[N] = {1999, 4444, 7777, 2222, 9999},
        b[N] = {111, 6666, 3333, 8888, 1111}, c[N];

  ladd(a, b, c);
  print(c);
  lsub(a, b, c);
  print(c);

  return 0;
}

void ladd(short a[], short b[], short c[]) {
  short i, cy = 0;
  for (i = N - 1; i >= 0; i--) {
    c[i] = a[i] + b[i] + cy;
    if (c[i] < 10000)
      cy = 0;
    else {
      c[i] = c[i] - 10000;
      cy = 1;
    }
  }
}

void lsub(short a[], short b[], short c[]) {
  short i, brrw = 0;
  for (i = N - 1; i >= 0; i--) {
    c[i] = a[i] - b[i] - brrw;
    if (c[i] >= 0)
      brrw = 0;
    else {
      c[i] = c[i] + 10000;
      brrw = 1;
    }
  }
}

void print(short c[]) {
  short i;
  for (i = 0; i < N; i++) printf("%04d ", c[i]);
  printf("\n");
}
