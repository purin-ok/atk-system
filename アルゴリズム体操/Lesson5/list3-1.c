/* リスト3-1 入力したいくつかの数値とその合計を出力する */
#include <stdio.h>
#include <stdlib.h>

#define NMAX 10
#define MAXLENGTH 1024

int main(void) {
  char buffer[MAXLENGTH];
  int buf, sum, count, n;
  int array[NMAX];

  count = 0;

  do {
    printf("整数を入力してください (0を入力すると終了) : ");
    fgets(buffer, MAXLENGTH, stdin);
    sscanf(buffer, "%d", &buf);
    if (buf) {
      array[count] = buf;
      count++;
    }
  } while (buf != 0);

  /* 合計値を算出 */
  printf("--入力されたのは以下の数です--\n");
  for (sum = n = 0; n < count; n++) {
    printf("%d \t", array[n]);
    sum += array[n];
  }

  printf("\n----\n以上の数の合計値は %d です．\n", sum);

  return EXIT_SUCCESS;
}
