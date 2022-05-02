/*オンライン型*/
/*    tm[n] = atoi(strtok(buf, ","));
    amp[n] = atoi(strtok(NULL, "\r\n\0"));*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 80                      /* 読込バッファサイズ */
#define A_BIAS 0x80 /* 直流バイアス */  // 100 3のときは0x80,140 3のときは0xf0
#define DATANUM 101                     /* 読込データ個数 */
int main(int argc, char **argv) {
  int nmax, column = 2, ncolumn, add_square, add_effective;
  int add_n = 0, max, min, n = 0, keep_n;
  int tm[DATANUM], amp[DATANUM], aout[DATANUM];
  double average, standard_deviation, max_amplitude, effective;
  char buf[BUFSIZE];
  FILE *fp;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
    return EXIT_FAILURE;
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    /* readモードでテキストファイルを開く */
    fprintf(stderr, "File: %s cannot open\n", argv[1]);
    return EXIT_FAILURE;
  }
  if (argc > 2) {
    column = atoi(argv[2]);
  }

  for (n = 0; n < DATANUM;) { /* ここに　n++ がない理由を考えよ */
    //ここにあると，二個目のif文のcontinue処理をした場合に，n+1されてしまい，配列にうまく読み込めない
    if (fgets(buf, sizeof(buf), fp) == NULL) break;
    if (buf[0] == '#') {
      printf("%s", buf);
      continue;
    }
    tm[n] = atoi(strtok(buf, ","));
    for (ncolumn = 1; ncolumn < column; ncolumn++) {
      amp[n] = atoi(strtok(NULL, "\r\n\0"));
    }

    n++;
    keep_n = n;

    add_n = amp[n];                //合計値初期化
    max = amp[n];                  //最大値初期化
    min = amp[n];                  //最小値初期化
    add_square = amp[n] * amp[n];  // Xi^2を加算しまくる

    n--;  //加算数カウント
  }
  for (; n >= 0; n--) {
    add_n += amp[n];  //平均を求めるための合計値
    if (max < amp[n]) {
      max = amp[n];
    }  //最大値更新

    if (min > amp[n]) {
      min = amp[n];
    }  //最小値更新

    add_effective = (amp[n] - A_BIAS) * (amp[n] - A_BIAS);

    add_square += amp[n] * amp[n];  //二条めっちゃ足す
  }
  average = (double)add_n / keep_n;  //平均値計算
  standard_deviation =
      sqrt(add_square / keep_n - average * average);  //標準偏差の計算
  max_amplitude = A_BIAS - min;
  if (max - A_BIAS > A_BIAS - min) {
    max_amplitude = max - A_BIAS;  //最大振幅
  }
  effective = max_amplitude / sqrt(2);  //実効値

  printf(
      "最小値  :%d\n最大値  :%d\n平均値  "
      ":%.4f\n標準偏差:%.4f\n最大振幅:%.4f\n実効値  :"
      "%.4f\n",
      min, max, average, standard_deviation, max_amplitude, effective);
  //各値の出力
  fclose(fp); /* ファイルを閉じる */
  return EXIT_SUCCESS;
}