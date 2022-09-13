/* πを1000桁まで求めるプログラム */
#include <stdio.h>

void ladd(short *a, short *b, short *c);
void lsub(short *a, short *b, short *c);
void ldiv(short *a, short b, short *c);
void printresult(short *c);

#define L 1000                     /* 求める桁数 */
#define L1 ((L / 4) + 1)           /* 配列のサイズ */
#define L2 (L1 + 2)                /* ひとつ余分にとる */
#define N (short)(L / 1.39794 + 1) /* 計算する項数 */

int main(void) {
  short s[L2], w[L2], v[L2], q[L2];
  short k;

  for (k = 0; k < L2; k++) s[k] = w[k] = v[k] = q[k] = 0;

  w[0] = 16 * 5;
  v[0] = 4 * 239;

  for (k = 1; k <= N; k++) {
    ldiv(w, 25, w);
    ldiv(v, 239, v);
    ldiv(v, 239, v);
    lsub(w, v, q);
    ldiv(q, 2 * k - 1, q);
    if (k % 2 != 0)
      ladd(s, q, s); /* 奇数項なら加える */
    else
      lsub(s, q, s); /* 偶数項なら引く */
  }
  printresult(s);
  return 0;
}

void printresult(short c[]) {
  short i;
  printf("%3d. ", c[0]); /* 最上位桁の表示 */
  for (i = 1; i < L1; i++) printf("%04d ", c[i]);
  printf("\n");
}

void ladd(short a[], short b[], short c[]) {
  short i, cy = 0;
  for (i = L1; i >= 0; i--) {
    c[i] = a[i] + b[i] + cy;
    if (c[i] < 10000) {
      cy = 0;
    } else {
      c[i] = c[i] - 10000;
      cy = 1;
    }
  }
}

void lsub(short a[], short b[], short c[]) {
  short i, brrw = 0;
  for (i = L1; i >= 0; i--) {
    c[i] = a[i] - b[i] - brrw;
    if (c[i] >= 0) {
      brrw = 0;
    } else {
      c[i] = c[i] + 10000;
      brrw = 1;
    }
  }
}

void ldiv(short a[], short b, short c[]) {
  short i;
  long d, rem = 0;
  for (i = 0; i < L2; i++) {
    printf("a");
    d = a[i];
    c[i] = (d + rem) / b;
    rem = ((d + rem) % b) * 10000;
  }
  printf(",");
}
