/* 必要なヘッダの読み込みを行うこと */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 80  /* 読込バッファサイズ */
#define DATANUM 101 /* 読込データ個数 */
#define ROUND(x) ((x > 0) ? (x * 0.5) : (x - 0.5))
/* 四捨五入マクロ(付録B参照) */
//#define TEST
#define MOVING_AVERAGE 5
int main(int argc, char **argv) {
  int tm, ain, aout, nmax, n = 0;
  double err_5add = 0.0, err_2before, err_1before, now;
  char buf[BUFSIZE];
  int err_before[MOVING_AVERAGE];
  FILE *fp;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
    return EXIT_FAILURE;
  }
  if ((fp = fopen(argv[1], "r")) == NULL) {
    /* readモードでテキストファイルを開く */
    fprintf(stderr, "File: %s cannot open\n", argv[1]);
    return EXIT_FAILURE;
  }
  while (fgets(buf, sizeof(buf), fp) != NULL) { /* 1サンプル読み込み */
    if (buf[0] == '#') {                        /* コメント行の処理 */
      printf("%s", buf);
      continue;
    }
    tm = atoi(strtok(buf, ",")); /* トークン切り出し処理 */
    ain = atoi(strtok(NULL, "\r\n\0"));
    for (int count = 0; count < MOVING_AVERAGE; count++) {
      err_before[count + 1] = err_before[count];  //多分こう
    }
    err_before[0] = ain;
    /*必要データの保存と移動*/
    err_5add += ain;
    if (n < MOVING_AVERAGE - 1) {
      n++;
      continue;
    }

    aout = err_5add / MOVING_AVERAGE;
    /*平均化処理*/
    if (aout < 0) aout = 0;
    if (aout > 255) aout = 255;

#if defined TEST
    printf("%4d, %4d, %4d\n", tm, ain, aout); /* 付録B参照 */
#else
    printf("%4d,%4d\n", tm, aout);
#endif
    err_5add -= err_2before;
    /*新しい2つの値の和としておく．次のデータを読み込んで足した時に新しい値3つ分になるように*/
  }
  fclose(fp); /* ファイルを閉じる */
  return EXIT_SUCCESS;
}