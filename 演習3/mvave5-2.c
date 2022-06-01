/* 必要なヘッダの読み込みを行うこと */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 80  /* 読込バッファサイズ */
#define DATANUM 101 /* 読込データ個数 */
#define ROUND(x) ((x > 0) ? (x + 0.5) : (x - 0.5))
/* 四捨五入マクロ(付録B参照) */
// #define TEST
#define MOVING_AVERAGE 5
int main(int argc, char **argv) {
  int n, i;
  int tm[DATANUM], amp[DATANUM], aout[DATANUM] = {0}, editing[DATANUM - 1];
  /* 引数のチェックとargv[1]で指定されたファイルを開く処理を書くこと */
  int nmax;
  double err, err_5add = 0;
  char buf[BUFSIZE];
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
  for (n = 0; n < DATANUM;) { /* ここに　n++ がない理由を考えよ */
    //ここにあると，二個目のif文のcontinue処理をした場合に，n+1されてしまい，配列にうまく読み込めない
    if (fgets(buf, sizeof(buf), fp) == NULL) break;
    if (buf[0] == '#') {
      printf("%s", buf);
      continue;
    }
    tm[n] = atoi(strtok(buf, ","));
    amp[n] = atoi(strtok(NULL, "\r\n\0")) / MOVING_AVERAGE;
    n++; /* ここに n++ がある理由を考えよ */ /*コメント文字の処理を飛ばすため*/
  }
  fclose(fp);
  for (n = 0; n < MOVING_AVERAGE - 1; n++) {
    err_5add += amp[n];
    // printf("%d,%f\n", amp[n], err_5add);
  }  // 0~3のデータ4つ分足している
  /*err_3add = amp[0] + amp[1] + amp[2] + amp[3];
  実質これとやってる事同じ
  */
  for (n = MOVING_AVERAGE / 2; n < DATANUM - 1; n++) {
    // 5つ足して5で割った値をaoutに入れる．
    err_5add += amp[n + MOVING_AVERAGE / 2];
    aout[n] = (err_5add < 0) ? 0 : ROUND(err_5add);
    aout[n] = (err_5add > 255) ? 225 : ROUND(err_5add);
    err_5add -= amp[n - MOVING_AVERAGE / 2];
    /* ここで出力範囲が[0:255]になるようクリッピング処理すること */
  }
  for (n = MOVING_AVERAGE / 2; n < DATANUM - (MOVING_AVERAGE / 2); n++) {
#if defined TEST
    printf("%4d, %4d, %4d\n", tm[n], amp[n], aout[n]); /* 付録B参照 */
#else
    printf("%4d,%4d\n", tm[n], aout[n]);
#endif
  }
  return EXIT_SUCCESS;
}