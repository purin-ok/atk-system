#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* �f�[�^�̌��� */

int *buffer;

void MergeSort(int n, int x[]) {
  int i, j, k, m;

  if (n <= 1) return; /* �P�ȉ��Ȃ�߂� */

  m = n / 2;

  /* �u���b�N��O���ƌ㔼�ɕ����� */
  MergeSort(m, x);         /* �z��x��m�ڂ܂� */
  MergeSort(n - m, x + m); /* �z��x��m�Ԃ̗v�f���� */

  /* ����(�}�[�W)���� */
  for (i = 0; i < m; i++) buffer[i] = x[i];

  j = m;
  i = k = 0;

  while (i < m && j < n) {
    /* �O���O���[�v(buffer)�ƌ㔼�Ƃŏ����������ɋl�߂Ă��� */
    if (buffer[i] <= x[j]) {
      x[k] = buffer[i];
      i++;
    } else {
      x[k] = x[j];
      j++;
    }
    k++;
  }

  while (i < m) { /* buffer�Ƀf�[�^���c���Ă����, x�̌��ɋl�߂� */
    x[k] = buffer[i];
    k++;
    i++;
  }
}

void QuickSort(int bottom, int top, int *data) {
  int lower, upper, div, temp;

  if (bottom >= top) return;

  div = data[(top + bottom) / 2]; /* �z��̐^�񒆂��������l�ɂ���
                                   */

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

int main(void) {
  int j, dat[9] = {1000,     10000,    100000,   1000000, 10000000,
                   20000000, 30000000, 40000000, 50000000};
  int *sort = NULL;
  int i, n, k = 0, tmp, select;
  clock_t stime, etime;
  printf("Mereg:1 or Quick:0");
  scanf("%d", &select);
  for (j = 0; j < 9; j++) {
    n = dat[j];
    sort = (int *)malloc(sizeof(int) * n);
    if (sort == NULL) exit(EXIT_FAILURE);
    if ((buffer = (int *)malloc(sizeof(int) * (n / 2 + 1))) == NULL)
      exit(EXIT_FAILURE);
    srand((unsigned int)time(NULL));
    for (i = 0; i < n; i++) {
      /* code */

      /* �z��Ƀ����_���Ȓl���i�[ */
      sort[i] = rand();
      /* printf("%d ", sort[i]); */
    }
    for (k = 0; k < 3; k++) {
      printf("%d", j);
      switch (k) {
        case 0:
          break;
        case 1:
          break;
        case 2:
          for (i = 0; i < (n / 2); i++) {
            tmp = sort[i];
            sort[i] = sort[n - 1 - i];
            sort[n - 1 - i] = tmp;
          }
          break;
        default:
          break;
      }

      /*printf("\n�\�[�g�J�n:\n");*/
      if (select) {
        if ((buffer = (int *)malloc(sizeof(int) * (n / 2 + 1))) == NULL)
          exit(EXIT_FAILURE);
        stime = clock(); /* �J�n�������L�^ */
        MergeSort(n, sort);
        etime = clock(); /* �I���������L�^ */
        buffer = NULL;
      } else {
        if ((buffer = (int *)malloc(sizeof(int) * (n / 2 + 1))) == NULL)
          exit(EXIT_FAILURE);
        stime = clock(); /* �J�n�������L�^ */
        QuickSort(0, n - 1, sort);
        etime = clock();
        buffer = NULL;
      }
      /*printf("�\�[�g�I��:\n");*/
      /* for (i=0; i<n; i++)
        printf("%d ", sort[i]);  */
      printf(" of %d", k);
      printf("%10d: ", n);
      if (select) {
        printf("Mergesort_time:");
      } else {
        printf("Quicksort_time:");
      }
      printf("%.4f\n", (float)(etime - stime) / CLOCKS_PER_SEC);
    }
    free(sort);
    sort = NULL;
  }

  return EXIT_SUCCESS;
}
