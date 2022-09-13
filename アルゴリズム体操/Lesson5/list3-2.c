/* リスト3-2 入力する数値の数を最初に確認する */
#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 1024

int main(void) {
  char buffer[MAXLENGTH];
  int buf, sum, count, n, i;
  int *array;

  /* 入力するデータの個数を最初に聞いて，必要なメモリを確保 */
  printf("何個の数値を入力しますか: ");
  fgets(buffer, MAXLENGTH, stdin);
  sscanf(buffer, "%d", &count);

  array = (int *)malloc(sizeof(int) * count);

  n = 0;

  do {
    printf("整数を入力してください (0を入力すると終了) : ");
    fgets(buffer, MAXLENGTH, stdin);
    sscanf(buffer, "%d", &buf);
    if (buf) {
      array[n] = buf;
      n++;
    }
  } while (buf != 0);

  /* 合計値を算出 */
  printf("--入力されたのは以下の数です--\n");
  for (sum = i = 0; i < n; i++) {
    printf("%d \t", array[i]);
    sum += array[i];
  }

  printf("\n----\n以上の数の合計値は %d です．\n", sum);

  return EXIT_SUCCESS;
}