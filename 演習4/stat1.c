/*オンライン型*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 80                      /* 読込バッファサイズ */
#define A_BIAS 0x80 /* 直流バイアス */  // 100 3のときは0x80,140 3のときは0xf0
#define DATANUM 101                     /* 読込データ個数 */
int main(int argc, char **argv) {
  int tm, ain, nmax, column = 2, ncolumn, add_square, a_rms_add;
  int add_n = 0, max, min, n = 0;
  double average, standard_deviation, max_amplitude, a_rms;
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

  while (fgets(buf, sizeof(buf), fp) != NULL) { /* 1サンプル読み込み */
    if (buf[0] == '#') {                        /* コメント行の処理 */
      printf("%s", buf);
      continue;
    }
    tm = atoi(strtok(buf, ",")); /* トークン切り出し処理 */
    for (ncolumn = 1; ncolumn < column; ncolumn++) {
      ain = atoi(strtok(NULL, "\r\n\0"));
    }
    printf("%d\n", ain);
    add_n = ain;             //合計値初期化
    max = ain;               //最大値初期化
    min = ain;               //最小値初期化
    add_square = ain * ain;  // Xi^2を加算しまくる
    a_rms_add = (ain - A_BIAS) * (ain - A_BIAS);
    n++;    //加算数カウント
    break;  //上の処理は一回でいいけどコメント行どうにかしないといけないから
  }

  while (fgets(buf, sizeof(buf), fp) != NULL) { /* 1サンプル読み込み */
    if (buf[0] == '#') {                        /* コメント行の処理 */
      printf("%s", buf);
      continue;
    }
    tm = atoi(strtok(buf, ","));
    for (ncolumn = 1; ncolumn < column; ncolumn++) {
      ain = atoi(strtok(NULL, "\r\n\0"));
    }  //たくさん列ある行は最後までって考えるなら多分こうやってやりたい所を最後までやるべき
    printf("%d\n", ain);
    add_n += ain;  //平均を求めるための合計値
    if (max < ain) {
      max = ain;
    }  //最大値更新

    if (min > ain) {
      min = ain;
    }  //最小値更新

    add_square += ain * ain;                       //二条めっちゃ足す
    a_rms_add += (ain - A_BIAS) * (ain - A_BIAS);  //実効値求めるための加算
    n++;                                           //カウント
  }

  average = (double)add_n / n;  //平均値計算

  standard_deviation =
      sqrt(add_square / n - average * average);  //標準偏差の計算

  max_amplitude = A_BIAS - min;
  if (max - A_BIAS > A_BIAS - min) {
    max_amplitude = max - A_BIAS;  //最大振幅
  }

  a_rms = sqrt(a_rms_add / n);  //実効値

  printf(
      "最小値  :%d\n最大値  :%d\n平均値  "
      ":%.4f\n標準偏差:%.4f\n最大振幅:%.4f\n実効値  :"
      "%.4f\n",
      min, max, average, standard_deviation, max_amplitude, a_rms);
  //各値の出力
  fclose(fp); /* ファイルを閉じる */
  return EXIT_SUCCESS;
}