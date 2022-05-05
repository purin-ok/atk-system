/* sin波のサンプリングプログラムの主要部(8bit,dt=10ms,t=[0:1000ms]) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"
#define A_BIAS 0x80 /* 直流バイアス */  // 100 3のときは0x80,140 3のときは0xf0
#define DT 10                           /* 標本化間隔[ms] */
#define T_END 1000                      /* 計測終了時刻[ms] */

int main(int argc, char **argv) {
  int t;
  double amp, frq, phf, rad, vin, esum = 0;
  /* esumは演習2-3,phfは演習2-6で使用 */
  unsigned char vout; /* 出力用: 8ビット符号なし[0:255] */

  if (argc != 3) { /* コマンドライン引数の処理 */
    fprintf(stderr, "Usage: %s amplitude frequency\n", argv[0]);
    return EXIT_FAILURE;
  }

  amp = atof(argv[1]);
  frq = atof(argv[2]);

  printf("#A %f\n", amp); /* サンプリング情報を出力 */
  printf("#F %f\n", frq);
  //#をつけておくとgnuplotの出力には影響しないけど、人間は見ることはできる
  printf("#T %d\n", DT);
  printf("#B %d\n", A_BIAS);
  printf("#N %d\n", T_END / DT + 1);

  for (t = 0; t <= T_END; t += DT) {
    rad = t / (1000 / frq) * 2 * PI;
    /* 時刻t[ms]を弧度に変換する式を考えること（式を必ず報告すること） */
    vin = amp * sin(rad) + A_BIAS; /* 標本化 */
    if (vin < 0) vin = 0;
    if (vin > 255) vin = 255;
    vout = vin; /* 量子化・符号化 */
    printf("%4d, %4d\n", t, vout);
  }
  printf("#E %g\n", esum);  //演習2-4かなかな
  return EXIT_SUCCESS;
}
//[0,255]超えたらラインの値にすりゃいいんじゃね |
//波形が超越した．理由:vinの値がunsigned charで表せる値を飛び越えたけど，
//無理やり表そうとしたから，modを取った形になってるのでは
//戻り値で異常終了か正常に終わったかやるらしい