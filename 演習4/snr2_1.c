#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pi.h"

#define BUFSIZE 80                      /* 読込バッファサイズ */
#define A_BIAS 0x80 /* 直流バイアス */  // 100 3のときは0x80,140 3のときは0xf0
#define DATANUM 101                     /* 読込データ個数 */
int main(int argc, char **argv) {
  int tm[DATANUM], aerr[DATANUM] = {0}, edit[DATANUM] = {0};
  int column = 2, ncolumn, sn = 0, nn = 0;
  double add_n = 0, add_s = 0, snr_db;
  double amp[DATANUM] = {0.0};
  char buf1[BUFSIZE], buf2[BUFSIZE];
  int ampli;
  char frq;
  double rad;
  FILE *fp1, *fp2;
  int adjustment;  // n点平均のファイルか

  if (argc < 3) {
    fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
    return EXIT_FAILURE;
  }

  if ((fp1 = fopen(argv[1], "r")) == NULL) {
    /* readモードでテキストファイルを開く */
    fprintf(stderr, "File: %s cannot open\n", argv[1]);
    return EXIT_FAILURE;
  }
  if ((fp2 = fopen(argv[2], "r")) == NULL) {
    /* readモードでテキストファイルを開く */
    fprintf(stderr, "File: %s cannot open\n", argv[2]);
    return EXIT_FAILURE;
  }

  adjustment = atoi(argv[3]);
  while (fgets(buf2, sizeof(buf2), fp2) != NULL) { /* 1サンプル読み込み */
    if (buf2[0] == '#') { /* コメント行の処理 */
      printf("%s", buf2);
      // if (buf[1] == 'A') {
      //   ampli = atoi(strtok((buf + 3), "\r\n\0"));
      // } else if (buf[1] == 'F') {
      //   frq = atoi(strtok((buf + 3), "\r\n\0"));
      // }
      continue;
    }
    tm[sn] = atoi(strtok(buf2, ",")); /* トークン切り出し処理 */

    // rad = tm[n] / (1000 / (double)frq) * 2 * PI;
    // printf("%f,", rad);
    // amp[n] = (double)ampli * sin(rad) + A_BIAS;

    aerr[sn] = atoi(strtok(NULL, ","));
    amp[sn] = atoi(strtok(NULL, "\r\n\0"));
    // printf("%4d,%4f,%4d\n", tm[n], amp[n], edit[n]);
    add_s += (amp[sn] - A_BIAS) * (amp[sn] - A_BIAS);
    sn++;  //加算数カウント
    //上の処理は一回でいいけどコメント行どうにかしないといけないから
  }
  nn = adjustment / 2;
  while (fgets(buf1, sizeof(buf1), fp1) != NULL) { /* 1サンプル読み込み */
    if (buf1[0] == '#') { /* コメント行の処理 */
      printf("%s", buf1);
      // if (buf[1] == 'A') {
      //   ampli = atoi(strtok((buf + 3), "\r\n\0"));
      // } else if (buf[1] == 'F') {
      //   frq = atoi(strtok((buf + 3), "\r\n\0"));
      // }
      continue;
    }
    tm[nn] = atoi(strtok(buf1, ",")); /* トークン切り出し処理 */

    // rad = tm[n] / (1000 / (double)frq) * 2 * PI;
    // printf("%f,", rad);
    // amp[n] = (double)ampli * sin(rad) + A_BIAS;

    aerr[nn] = atoi(strtok(NULL, ","));
    edit[nn] = atoi(strtok(NULL, "\r\n\0"));
    // printf("%4d,%4f,%4d\n", tm[n], amp[n], edit[n]);
    add_n += (edit[nn] - amp[nn]) * (edit[nn] - amp[nn]);  //ザッツォンの導出
    nn++;
    //上の処理は一回でいいけどコメント行どうにかしないといけないから
  }
  // printf("%d", ampli);
  snr_db = 10 * log10((add_s / sn) / (add_n / (nn - adjustment / 2)));
  // printf("%f,%f", add_s, add_n);
  printf("%f", snr_db);
  fclose(fp1); /* ファイルを閉じる */
  fclose(fp2);
  return EXIT_SUCCESS;
}
