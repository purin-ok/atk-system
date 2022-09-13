/* FFT プログラム例 nは2の整数乗で n>=4 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef PI
#define PI 3.14159265358979323846
#endif

/* sin(x) のテーブルを作る */
static void make_sintbl(int n, double sintbl[]) {
  int i, n2, n4, n8;
  double c, s, dc, ds, t;

  n2 = n / 2;
  n4 = n / 4;
  n8 = n / 8;
  t = sin(PI / n);
  dc = 2.0 * t * t;
  ds = sqrt(dc * (2.0 - dc));
  t = 2.0 * dc;
  c = sintbl[n4] = 1;
  s = sintbl[0] = 0;
  for (i = 1; i < n8; i++) {
    c -= dc;
    dc += t * c;
    s += ds;
    ds -= t * s;
    sintbl[i] = s;
    sintbl[n4 - i] = c;
  }
  if (n8 != 0) sintbl[n8] = sqrt(0.5);
  for (i = 0; i < n4; i++) {
    sintbl[n2 - i] = sintbl[i];
    sintbl[i + n2] = -sintbl[i];
  }

  /*  for (i = 0; i < n+n4; i++) printf("%4d | %6.3f\n", i, sintbl[i]); */
}

/* fft()の下請けとしてビット反転表を作る */
static void make_bitrev(int n, int bitrev[]) {
  int i, j, k, n2;

  n2 = n / 2;
  i = j = 0;
  while (1) {
    bitrev[i] = j;
    ++i;
    if (i >= n) break;
    k = n2;
    while (k <= j) {
      j -= k;
      k /= 2;
    }
    j += k;
  }
}

/* 高速フーリエ変換(Cooley-Tukeyのアルゴリズム) */
/* (再帰呼出をせずにfor文で実現) */
int fft(int n, double re[], double im[]) {
  static int last_n = 0; /* 前回呼出時のn */
  /* static とあると、2回目は初期化せず、前の値が使われる */
  static int *bitrev = NULL;    /* ビット反転表 */
  static double *sintbl = NULL; /* 三角関数表 */
  int i, j, k, ik, h, d, k2, n4, inverse = 0;
  double t, s, c, dr, di;

  if (n < 0) { /* n が負のときは、逆変換 */
    n = -n;
    inverse = 1;
  }

  n4 = n / 4;
  if (n != last_n || n == 0) { /* 表の準備 */
    last_n = n;
    if (sintbl != NULL) free(sintbl);
    if (bitrev != NULL) free(bitrev);
    if (n == 0) return 0; /* データ数0なら、記憶領域を開放して戻る */
    sintbl = (double *)malloc(n * sizeof(double));
    bitrev = (int *)malloc(n * sizeof(int));
    if (sintbl == NULL || bitrev == NULL) {
      fprintf(stderr, "記憶領域不足\n");
      return 1;
    }
    make_sintbl(n, sintbl);
    make_bitrev(n, bitrev);
  }
  /* ビット反転 */
  for (i = 0; i < n; i++) {
    j = bitrev[i];
    if (i < j) { /* 入れ替え */
      t = re[i];
      re[i] = re[j];
      re[j] = t;
      t = im[i];
      im[i] = im[j];
      im[j] = t;
    }
  }
  /* 変換 */
  for (k = 1; k < n; k = k2) {
    h = 0;
    k2 = k + k;
    d = n / k2;
    for (j = 0; j < k; j++) {
      c = sintbl[h + n4];
      if (inverse)
        s = -sintbl[h];
      else
        s = sintbl[h];
      for (i = j; i < n; i += k2) { /* バタフライ演算 */
        ik = i + k;
        dr = s * im[ik] + c * re[ik];
        di = c * im[ik] - s * re[ik];
        re[ik] = re[i] - dr;
        re[i] += dr;
        im[ik] = im[i] - di;
        im[i] += di;
      }
      h += d;
    }
  }
  if (!inverse) /* 逆変換でないならば、nで割る */
    for (i = 0; i < n; i++) {
      re[i] /= n;
      im[i] /= n;
    }
  return 0;
}

/* テスト用ルーチン */
#define N 64
int main(void) {
  int i;
  static double re1[N], im1[N], re2[N], im2[N], re3[N], im3[N];

  for (i = 0; i < N; i++) { /* サンプルデータの用意 */
    re1[i] = re2[i] =
        6.0 * cos(6.0 * PI * i / N) + 4.0 * sin(18.0 * PI * i / N);
    im1[i] = im2[i] = 0.0;
  }
  if (fft(N, re2, im2)) return EXIT_FAILURE;

  for (i = 0; i < N; i++) {
    re3[i] = re2[i];
    im3[i] = im2[i];
  }
  if (fft(-N, re3, im3)) return EXIT_FAILURE;

  printf("      元のデータ        フーリエ変換        逆変換\n");
  for (i = 0; i < N; i++)
    printf("%4d | %7.3f %7.3f | %7.3f %7.3f | %7.3f %7.3f\n", i, re1[i], im1[i],
           re2[i], im2[i], re3[i], im3[i]);

  return EXIT_SUCCESS;
}