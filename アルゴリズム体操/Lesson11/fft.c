/* FFTのプログラム (再帰呼出版) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

/* 複素数型の定義 */
typedef struct COMPLEX_T {
  double real;
  double imag;
} Complex;

/* 複素数値を代入する関数 */
Complex ComplexValue(double real, double imag) {
  Complex c;
  c.real = real;
  c.imag = imag;
  return c;
}

/* 複素数の加算 */
Complex plus(Complex a, Complex b) {
  Complex c;
  c.real = a.real + b.real;
  c.imag = a.imag + b.imag;
  return c;
}

/* 複素数の減算 */
Complex minus(Complex a, Complex b) {
  Complex c;
  c.real = a.real - b.real;
  c.imag = a.imag - b.imag;
  return c;
}

/* 複素数の積 */
Complex multiply(Complex a, Complex b) {
  Complex c;
  c.real = a.real * b.real - a.imag * b.imag;
  c.imag = a.real * b.imag + a.imag * b.real;
  return c;
}

/* 回転演算子w(n,k)の計算 */
Complex w(int n, int k) {
  double theta = 2.0 * PI * k / n;
  Complex val;
  val.real = cos(theta);
  val.imag = -sin(theta);
  return val;
}

/* バタフライ演算 */
void butterfly(int n, Complex x[], Complex y[], Complex z[]) {
  int k;
  for (k = 0; k < n / 2; k++) {
    y[k] = plus(x[k], x[k + n / 2]);
    z[k] = multiply(minus(x[k], x[k + n / 2]), w(n, k));
  }
}

/* 並べ替え */
void shuffle(int n, Complex x[], Complex y[], Complex z[]) {
  int k;
  for (k = 0; k < n / 2; k++) {
    x[2 * k] = y[k];
    x[2 * k + 1] = z[k];
  }
}

/* FFT */
int fft(int n, Complex x[]) {
  int flag = 0;
  Complex *y, *z;

  if (n > 1) {
    y = (Complex *)malloc(n / 2 * sizeof(Complex));
    z = (Complex *)malloc(n / 2 * sizeof(Complex));
    if (y == NULL || z == NULL) {
      fprintf(stderr, "メモリエラー\n");
      if (y != NULL) free(y);
      if (z != NULL) free(z);
      return 1;
    }

    butterfly(n, x, y, z); /* バタフライ演算 */

    if (fft(n / 2, y)) flag = 1;
    if (fft(n / 2, z)) flag = 1;

    shuffle(n, x, y, z); /* 並べ替え */

    free(y);
    free(z);

    if (flag == 1) return 1; /* エラーがあったら戻る */
  }
  return 0;
}

/* テスト用ルーチン */
#define N 64
int main(void) {
  int i;
  Complex x1[N], x2[N];

  for (i = 0; i < N; i++) { /* サンプルデータの用意 */
    x1[i] = x2[i] =
        //      ComplexValue(6.0*cos(2.0*PI*128.0/1024.0*i), 0.0);
        ComplexValue(1.0 * cos(8.0 * PI * i / N), 0.0);
  }
  if (fft(N, x2)) return EXIT_FAILURE;

  printf("      元のデータ        フーリエ変換\n");
  for (i = 0; i < N; i++)
    printf("%4d | %7.3f %7.3f | %7.3f %7.3f\n", i, x1[i].real, x1[i].imag,
           x2[i].real, x2[i].imag);

  return EXIT_SUCCESS;
}