/* �N�C�b�N�\�[�g �i���s���Ԍv���p�j */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* �f�[�^�̌��� */

void QuickSort(int bottom, int top, int *data)
{
  int lower, upper, div, temp;

  if (bottom >= top)
    return;

  /* �擪�̒l���u�K���Ȓl�v�Ƃ��� */
  div = data[bottom];

  for (lower = bottom, upper = top; lower < upper;)
  {
    while (lower <= upper && data[lower] <= div)
      lower++;
    while (lower <= upper && data[upper] > div)
      upper--;

    if (lower < upper)
    {
      temp = data[lower];
      data[lower] = data[upper];
      data[upper] = temp;
    }
  }
  /* �ŏ��ɑI�������l�𒆉��Ɉړ����� */
  temp = data[bottom];
  data[bottom] = data[upper];
  data[upper] = temp;

  QuickSort(bottom, upper - 1, data);
  QuickSort(upper + 1, top, data);
}

int main(void)
{
  int j, dat[9] = {1000, 10000, 100000, 1000000, 10000000, 20000000, 30000000, 40000000, 50000000};
  int *sort = NULL;
  int i, n;
  clock_t stime, etime;

  for (j = 0; j < 9; j++)
  {
    n = dat[j];
    sort = (int *)malloc(sizeof(int) * n);
    if (sort == NULL)
      exit(EXIT_FAILURE);

    srand((unsigned int)time(NULL));

    for (i = 0; i < n; i++)
    {
      /* �z��Ƀ����_���Ȓl���i�[ */
      sort[i] = rand();
      /* printf("%d ", sort[i]); */
    }

    /*printf("\n�\�[�g�J�n:\n");*/

    stime = clock(); /* �J�n�������L�^ */
    QuickSort(0, n - 1, sort);
    etime = clock(); /* �I���������L�^ */

    /*printf("�\�[�g�I��:\n");*/
    /* for (i=0; i<n; i++)
      printf("%d ", sort[i]);  */

    printf("%10d ", n);
    printf(" %.4f\n", (float)(etime - stime) / CLOCKS_PER_SEC);

    free(sort);
    sort = NULL;
  }
  return EXIT_SUCCESS;
}
