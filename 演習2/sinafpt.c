/* sin波のサンプリングプログラムの主要部(8bit,dt=10ms,t=[0:1000ms]) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"

#define A_BIAS 0x80 /* 直流バイアス */  // 100 3のときは0x80,140 3のときは0xf0
#define DT 10 /* 標本化間隔[ms] */  //ここをどうにかしていじると2-5ができる
#define T_END 1000                  /* 計測終了時刻[ms] */

double err_sum(double true_value, unsigned char quantization, double e_rms) {
  e_rms = (true_value - quantization) * (true_value - quantization);
  return e_rms;
}

int main(int argc, char **argv) {
  int t, n = 0;
  double amp, frq, phf, rad, vin, esum = 0, dt, phase;
  /* esumは演習2-3,phfは演習2-6で使用 */
  unsigned char vout; /* 出力用: 8ビット符号なし[0:255] */

  if (argc != 5) { /* コマンドライン引数の処理 */
    fprintf(stderr, "Usage: %s amplitude frequency\n", argv[0]);
    return EXIT_FAILURE;
  }

  amp = atof(argv[1]);
  frq = atof(argv[2]);
  phase = atof(argv[3]);  //単位は[ms]
  // printf("a");
  dt = atof(argv[4]);
  // printf("%d", atoi(argv[4]));
  printf("#A %f\n", amp); /* サンプリング情報を出力 */
  printf("#F %f\n", frq);
  //#をつけておくとgnuplotの出力には影響しないけど、人間は見ることはできる
  printf("#T %f\n", dt);
  printf("#B %d\n", A_BIAS);
  printf("#N %f\n", T_END / dt + 1);

  for (t = 0; t <= T_END; t += dt) {
    rad = (t + phase) / (1000 / frq) * 2 * PI;
    vin = amp * sin(rad) + A_BIAS; /* 標本化 */
    vin += 0.5;
    vout = vin; /* 量子化・符号化 */
    if (vout < 0) vout = 0;
    if (vout > 255) vout = 255;
    esum = err_sum(vin, vout, esum);
    printf("%4d, %4d\n", t, vout);
  }
  return EXIT_SUCCESS;
}