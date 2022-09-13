/* モンテカルロシミュレーションの例 */
/* sin(x) x=0～π/2の面積 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000 /* 点の数 */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* 乱数生成ルーチン */
long x = 1;

short int rnd() {
  x = x * 1103515245 + 12345;
  return (short int)(x >> 16) & 32767;
}

void seed(unsigned short s) { x = s; }

/* メインルーチン */
int main(void) {
  int m, i;
  double x, y, z;

  seed(123); /* 種を設定 */

  m = 0;
  for (i = 0; i < N; i++) {
    x = M_PI / 2.0 * rnd() / 32767.0; /* 乱数を 0～π/2の範囲にする */
    y = rnd() / 32767.0;              /* 乱数を 0～1の範囲にする */
    z = sin(x);

    if (y <= z) m++; /* 領域内ならカウントアップ */

    printf("%4d: x:%lf, y:%lf, sin(x):%lf, m:%d %s\n", i, x, y, z, m,
           (y <= z) ? "in" : "out");
  }
  printf("%4d: I=%d/%d*π/2=%lf\n", N, m, N, (double)m / N * M_PI / 2.0);

  return 0;
}
