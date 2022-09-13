/* 逐次探索: 番兵バージョン */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)
#define MAXLENGTH 1024

int linear_search2(int x, int *a, int num) {
  int n = 0, t;

  /* 最後の値を x に入れ替える (番兵) */
  t = a[num - 1];
  a[num - 1] = x;

  /* 目的の値を探す */
  while (a[n] != x) n++;

  a[num - 1] = t; /* 配列の最後の値を元に戻す */

  if (n < num - 1) return n; /* 一番最後以外で一致なら */
  if (x == t) return n;      /* 一番最後が一致 */

  /* どれでもなければ, 見付からなかった */
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

  r = linear_search2(i, array, N);

  if (r == NOT_FOUND)
    printf("%d は見付かりません\n", i);
  else
    printf("%d は %d 番目です\n", i, r);

  return EXIT_SUCCESS;
}
