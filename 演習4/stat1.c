/*オンライン型*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 80  /* 読込バッファサイズ */
#define DATANUM 101 /* 読込データ個数 */
int main(int argc, char **argv) {
  int tm, ain, aout, nmax, n = 2, column;
  int add_n, max, min;
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
  if (argc > 2) {
    n = atoi(argv[2]);
  }
  while (fgets(buf, sizeof(buf), fp) != NULL) { /* 1サンプル読み込み */
    if (buf[0] == '#') {                        /* コメント行の処理 */
      printf("%s", buf);
      continue;
    }

    for (column = 0; column < n; column++) {
      ain = atoi(strtok(NULL, "\r\n\0"));
    }
    tm = atoi(strtok(buf, ",")); /* トークン切り出し処理 */
    add_n += ain;

    n++;
  }
  fclose(fp); /* ファイルを閉じる */
  return EXIT_SUCCESS;
}