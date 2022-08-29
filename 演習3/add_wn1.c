#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TEST
#define BUFSIZE 80 /* 読込バッファサイズ */
#define ROUND(x) ((x > 0) ? (x * 0.5) : (x - 0.5))
/* 四捨五入マクロ(付録B参照) */

int main(int argc, char **argv) {
  int tm, ain, aout, nmax;
  double err;
  char buf[BUFSIZE];
  FILE *fp;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
    return EXIT_FAILURE;
  }
  if ((fp = fopen(argv[1], "r")) == NULL) {
    /* readモードでテキストファイルを開く */
    fprintf(stderr, "File: %s cannot open\n", argv[1]);
    return EXIT_FAILURE;
  }
  nmax = atoi(argv[2]); /* 白色雑音の最大振幅を設定 */
  printf("# WN %d\n", nmax);
  srand((unsigned)time(NULL));                  /* 乱数初期化 */
  while (fgets(buf, sizeof(buf), fp) != NULL) { /* 1サンプル読み込み */
    if (buf[0] == '#') {                        /* コメント行の処理 */
      printf("%s", buf);
      continue;
    }
    tm = atoi(strtok(buf, ",")); /* トークン切り出し処理 */
    ain = atoi(strtok(NULL, "\r\n\0"));
    err = nmax * (2.0 * rand() / RAND_MAX - 1.0); /* 雑音生成 */
    aout = ain + ROUND(err);
    /* ここで出力範囲が[0:255]になるようクリッピング処理すること */
    if (aout < 0) aout = 0;
    if (aout > 255) aout = 255;

#if defined TEST
    printf("%4d, %4d, %4d\n", tm, ain, aout); /* 付録B参照 */
#else
    printf("%4d,%4d\n", tm, aout);
#endif
  }
  fclose(fp); /* ファイルを閉じる */
  return EXIT_SUCCESS;
}