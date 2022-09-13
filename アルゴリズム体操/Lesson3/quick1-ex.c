/* クイックソート (実行時間計測用) */
/* 実行時の引数: 第1引数:ソートするデータ数 */
/*               第2引数:ソートするデータの種類: 0:ランダム, 1:昇順, 2:降順 */
/**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* �f�[�^�̌��� (�ȗ���) */
void BubbleSort(int *data, int n) {
  int i, j, flag, k;
  k = 0;
  do {
    flag = 0;
    for (i = 0; i < n - 1 - k;
         i++) { /* 最後からk番目までは整列済みなので省く */
      if (data[i] > data[i + 1]) {
        /* 左右の並びがおかしければ入れ替える */
        flag = 1;
        j = data[i];
        data[i] = data[i + 1];
        data[i + 1] = j;
      }
    }
    k++;
  } while (flag == 1); /* 入れ替えがある間，繰り返す．*/
}

void QuickSort(int bottom, int top, int *data) {
  int lower, upper, div, temp;
  if (top - bottom < 10) BubbleSort(data, top - bottom);
  if (bottom >= top) return;

  div = data
      [(top + bottom) /
       2]; /* �z��̐^�񒆂��������l�ɂ���*/

  lower = bottom;
  upper = top;
  while (1) {
    while (data[lower] < div) lower++;
    while (data[upper] > div) upper--;
    if (lower >= upper) break;
    /* �l�̌��� */
    temp = data[lower];
    data[lower] = data[upper];
    data[upper] = temp;
    lower++;
    upper--;
  }
  QuickSort(bottom, lower - 1, data);
  QuickSort(upper + 1, top, data);
}

int main(int argc, char *argv[]) {
  int *sort, i, n = N, t = 0, flag;
  clock_t stime, etime;

  if (argc > 1) {
    n = atoi(argv[1]);
  }
  if (argc > 2) {
    t = atoi(argv[2]);
  }
  if (n > 0) {
    if ((sort = (int *)malloc(sizeof(int) * n)) == NULL) exit(EXIT_FAILURE);
  }
  /* 配列に値を格納: 1:昇順, 2:降順, その他:ランダム */
  switch (t) {
    case 1:
      for (i = 0; i < n; i++) sort[i] = i + 1;
      break;
    case 2:
      for (i = 0; i < n; i++) sort[i] = n - i;
      break;
    default:
      srand((unsigned int)time(NULL));
      for (i = 0; i < n; i++) sort[i] = rand();
  }

  stime = clock();           /* 開始時刻を記録 */
  QuickSort(0, n - 1, sort); /* QuickSort呼出 */
  etime = clock();           /* 終了時刻を記録 */

  switch (t) {
    case 1:
      printf("up");
      break;
    case 2:
      printf("down");
      break;
    default:
      printf("randome");
  }
  printf(" %d quick_bubble", n);
  printf("%.3f[sec]\n", (float)(etime - stime) / CLOCKS_PER_SEC);

  printf("\n: ");
  flag = 0;
  for (i = 0; i < n - 1; i++) {
    if (sort[i] > sort[i + 1]) {
      flag = 1;
      break;
    }
  }
  if (flag != 0)
    printf("NO\n");
  else
    printf("OK\n");

  return EXIT_SUCCESS;
}