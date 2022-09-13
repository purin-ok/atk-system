/* 二分探索 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)
#define MAXLENGTH 1024

int binary_search(int x, int *a, int left, int right) {
  int mid;

  while (left <= right) {
    mid = (left + right) / 2;

    if (a[mid] == x) return mid; /* 一致したら戻る */

    if (a[mid] < x)
      left = mid + 1; /* mid より左側にxは存在しない */
    else
      right = mid - 1; /* mid より右側にxは存在しない */
  }

  /* サーチ範囲がなくなっても一致するものがなかった */
  return NOT_FOUND;
}

int main(void) {
  int i, r, array[N];
  char buff[MAXLENGTH];

  srand((unsigned int)time(NULL));

  /* 適当なソートされた配列を作る */
  array[0] = rand() % 3;
  printf("[0]:%d ", array[0]);
  for (i = 1; i < N; i++) {
    array[i] = array[i - 1] + rand() % 3;
    printf("[%d]:%d ", i, array[i]);
  }

  printf("\n何を探しますか:");
  fgets(buff, MAXLENGTH, stdin); /* キーボードから1行読み込む */
  sscanf(buff, "%d", &i);

  r = binary_search(i, array, 0, N - 1);

  if (r == NOT_FOUND)
    printf("%d は見付かりません\n", i);
  else
    printf("%d は %d 番目です\n", i, r);

  return EXIT_SUCCESS;
}
