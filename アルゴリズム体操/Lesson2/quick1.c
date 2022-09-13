/* �N�C�b�N�\�[�g */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* �f�[�^�̌��� */

void QuickSort(int bottom, int top, int *data)
{
  int lower, upper, div, temp;

  if (bottom>=top) return;

  /* �擪�̒l���u�K���Ȓl�v�Ƃ��� */
  div = data[bottom];

  for (lower=bottom, upper=top; lower<upper; ) {
    while (lower<=upper && data[lower]<=div) lower++;
    while (lower<=upper && data[upper]>div)  upper--;

    if (lower<upper) {
      temp = data[lower];
      data[lower] = data[upper];
      data[upper] = temp;
    }
  }
  /* �ŏ��ɑI�������l�𒆉��Ɉړ����� */
  temp=data[bottom];
  data[bottom]=data[upper];
  data[upper]=temp;

  QuickSort(bottom, upper-1, data);
  QuickSort(upper+1, top, data);
}

int main(void)
{
  int sort[N];
  int i;

  srand((unsigned int)time(NULL));

  for (i=0; i<N; i++) {
    /* �z��Ƀ����_���Ȓl���i�[ */
    sort[i] = rand();
    printf("%d ", sort[i]);
  }

  printf("\n�[�g�J�n:\n");

  QuickSort(0,N-1,sort);

  printf("�[�g�I��:\n");
  for (i=0; i<N; i++)
    printf("%d ", sort[i]);

  return EXIT_SUCCESS;
}
