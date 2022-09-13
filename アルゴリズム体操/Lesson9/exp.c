#include <stdio.h>

void ladd(short *a, short *b, short *c);  // c = a + b
void lsub(short *a, short *b, short *c);  // c = a - b
void lmul(short *a, short b, short *c);   // c = a * b
void ldiv(short *a, short b, short *c);   // c = a / b
void printresult(short *c);

#define L 1000           /* 求める桁数 */
#define L1 ((L / 4) + 2) /* 配列のサイズ */
#define L2 (L1 + 1)      /* ひとつ余分にとる */
#define N (short)(451)   /* 計算する項数 */

int main() {
  short s[L2], w[L2], v[L2], q[L2];
  short k;

  for (k = 0; k < L2; k++) s[k] = w[k] = 0;

  w[0] = 1;
  ladd(s, w, s);
  for (k = 1; k <= N; k++) {
    //ここまでは動作する
    ldiv(w, k, w);
    ladd(s, w, s);
  }
  printresult(s);
  return 0;
}

void ladd(short a[], short b[], short c[]) {
  short i, cy = 0;
  for (i = L1 - 1; i >= 0; i--) {
    c[i] = a[i] + b[i] + cy;
    if (c[i] < 10000)
      cy = 0;
    else {
      c[i] = c[i] - 10000;
      cy = 1;
    }
  }
}

void ldiv(short a[], short b, short c[]) {
  short i;
  long d, rem = 0;
  for (i = 0; i < L2; i++) {
    d = a[i];
    c[i] = (d + rem) / b;
    rem = ((d + rem) % b) * 10000;
  }
}

void printresult(short c[]) {
  short i;
  printf("%3d. ", c[0]); /* 最上位桁の表示 */
  for (i = 1; i < L1 - 1; i++) printf("%04d ", c[i]);
  printf("\n");
}
