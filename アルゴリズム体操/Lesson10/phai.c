/* モンテカルロシミュレーションの例 */
/* sin(x) x=0～π/2の面積 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000 /* 点の数 */
// #ifndef M_PI
// #define M_PI 3.14159265358979323846
// #endif

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

  seed((unsigned int)time(NULL)); /* 種を設定 */

  m = 0;
  for (i = 0; i < N; i++) {
    x = rnd() / 32767.0; /* 乱数を 0～1の範囲にする */
    y = rnd() / 32767.0; /* 乱数を 0～1の範囲にする */
    z = 1 - x * x;

    if (y * y <= z) m++; /* 領域内ならカウントアップ */

    printf("%4d: x:%lf, y:%lf, 1-x^2:%lf, m:%d %s\n", i, x, y, z, m,
           (y * y <= z) ? "in" : "out");
  }
  printf("%4d: I=%d/%d*4=%lf\n", N, m, N, (double)m / N * 4.0);

  return 0;
}