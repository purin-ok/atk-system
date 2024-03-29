/* sin波のサンプリングプログラムの主要部(8bit,dt=10ms,t=[0:1000ms]) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"

#define A_BIAS 0x80 /* 直流バイアス */  // 100 3のときは0x80,140 3のときは0xf0
#define DT 10 /* 標本化間隔[ms] */  //ここをどうにかしていじると2-5ができる
#define T_END 1000                  /* 計測終了時刻[ms] */

double rad(double r) {
  double mod;
  mod = fmod(r, 2 * PI);
  if (r < 0) mod = mod + 2 * PI;
  return mod;
}

//?��?��?��K1?��|2
double saw(double r) {
  double saw_blead;
  saw_blead = 1 - rad(r) / PI;
  return saw_blead;
}

double squ(double r) {
  double square;
  square = saw(r);
  if (r > 0) {
    square = 1;
  } else {
    square = -1;
  }
  return square;
}

double tri(double r) {
  int index = 1;
  double triangle, mod;
  mod = fmod(r, PI);
  if (r < 0) mod = mod + PI;
  triangle = mod * 2 / PI;
  //傾きはこれでいいはず．あとはどうやって折り返すか考える．
  if (triangle > 1) triangle = 2 - triangle;
  if (r < 0) {
    r *= (-1);
    index *= (-1);
  }  //弧度を絶対値に
  while (1) {
    r -= PI;
    if (r < 0) break;
    index *= (-1);
  }
  triangle *= index;
  return triangle;
}

double err_sum(double true_value, unsigned char quantization, double e_rms) {
  e_rms = (true_value - quantization) * (true_value - quantization);
  return e_rms;
}

int main(int argc, char **argv) {
  int n = 0;
  double amp, frq, phf, rad, vin, esum = 0, dt, t;
  /* esumは演習2-3,phfは演習2-6で使用 */
  unsigned char vout; /* 出力用: 8ビット符号なし[0:255] */

  if (argc != 4) { /* コマンドライン引数の処理 */
    fprintf(stderr, "Usage: %s amplitude frequency\n", argv[0]);
    return EXIT_FAILURE;
  }

  amp = atof(argv[1]);
  frq = atof(argv[2]);
  dt = atof(argv[3]);
  // printf("%d", atoi(argv[4]));
  printf("#A %f\n", amp); /* サンプリング情報を出力 */
  printf("#F %f\n", frq);
  //#をつけておくとgnuplotの出力には影響しないけど、人間は見ることはできる
  printf("#T %f\n", dt);
  printf("#B %d\n", A_BIAS);
  printf("#N %f\n", T_END / dt + 1);

  for (t = 0; t <= T_END; t += dt) {
    rad = t / (1000 / frq) * 2 * PI;
    vin = amp * tri(rad) + A_BIAS; /* 標本化 */
    vout = (vin < 0) ? 0 : ((vin > 255) ? 225 : ROUND(vin));
    // esum = err_sum(vin, vout, esum);
    printf("%4f, %4d\n", t, vout);
  }
  return EXIT_SUCCESS;
}