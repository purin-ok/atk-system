#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 80                      /* 読込バッファサイズ */
#define A_BIAS 0x80 /* 直流バイアス */  // 100 3のときは0x80,140 3のときは0xf0
#define DATANUM 1001                    /* 読込データ個数 */
int main(int argc, char **argv) {
  int tm[DATANUM], amp[DATANUM] = {0}, aerr[DATANUM] = {0};
  int column = 2, ncolumn, n = 0;
  double add_n = 0, add_s = 0, snr_db;
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
    tm[n] = atoi(strtok(buf, ",")); /* トークン切り出し処理 */
    amp[n] = atoi(strtok(NULL, ","));
    aerr[n] = atoi(strtok(NULL, "\r\n\0"));
    add_s += (amp[n] - A_BIAS) * (amp[n] - A_BIAS);
    add_n += (aerr[n] - amp[n]) * (aerr[n] - amp[n]);  //ザッツォンの導出
    n++;                                               //加算数カウント
    //上の処理は一回でいいけどコメント行どうにかしないといけないから
  }
  snr_db = 10 * log10(add_s / add_n);
  // printf("%f,%f", add_s, add_n);
  printf("%f", snr_db);
  fclose(fp); /* ファイルを閉じる */
  return EXIT_SUCCESS;
}
