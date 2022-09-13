/* 超整理法的探索法 <自己組織化探索> */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)
#define MAXLENGTH (1024)

/* 自己組織化探索関数 (基本となる方法は，逐次探索) */
int organization_search(int x, int *a, int num) {
  int n = 0, t;

  while (n < num && a[n] != x) n++;

  if (n < num) { /* 値が見付かった */
    if (n > 0) {
      /* 1つ前の値と入れ替える */
      t = a[n - 1];
      a[n - 1] = a[n];
      a[n] = t;
      return n - 1; /* 目的の値が1つ前に移動しているので、n-1を返す */
    }
    return n;
  }
  return NOT_FOUND;
}

int main(void) {
  int i, r, array[N];
  char buff[MAXLENGTH];

  srand((unsigned int)time(NULL));

  /* 適当な配列を作る */
  for (i = 0; i < N; i++) array[i] = rand() % 20;

  while (1) { /* 無限ループ */
    printf("\narray ");
    for (i = 0; i < N; i++) printf("[%d]:%d ", i, array[i]);

    printf("\n何を探しますか(-1で終了): ");
    fgets(buff, MAXLENGTH, stdin);
    sscanf(buff, "%d", &i);

    if (i == -1) break;

    r = organization_search(i, array, N);

    if (r == NOT_FOUND)
      printf("%d は見付かりません．\n", i);
    else
      printf("%d は %d 番目にあります．\n", i, r);
  }

  return EXIT_SUCCESS;
}
