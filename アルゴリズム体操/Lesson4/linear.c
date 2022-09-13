/* 逐次探索 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)
#define MAXLENGTH 1024

int linear_search(int x, int *a, int num) {
  int n = 0;

  /* 配列の範囲内で，目的の値を探す */
  while (n < num && a[n] != x) n++;

  if (n < num) return n;

  return NOT_FOUND;
}

int main(void) {
  int i, r, array[N];
  char buff[MAXLENGTH];

  srand((unsigned int)time(NULL));

  /* 適当な配列を作る */
  printf("array ");
  for (i = 0; i < N; i++) {
    array[i] = rand() % 20;
    printf("[%d]:%d ", i, array[i]);
  }

  printf("\n何を探しますか:");
  fgets(buff, MAXLENGTH, stdin); /* キーボードから1行読み込む */
  sscanf(buff, "%d", &i); /* 読み込んだ文字列から整数値を取り出す */

  r = linear_search(i, array, N);

  if (r == NOT_FOUND)
    printf("%d は見付かりません\n", i);
  else
    printf("%d は %d 番目です\n", i, r);

  return EXIT_SUCCESS;
}
