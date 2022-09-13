#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* �f�[�^�̌��� */

int buffer[N];

void MergeSort(int n, int x[])
{
  int i, j, k, m;

  if (n<=1) return; /* �P�ȉ��Ȃ�߂� */

  m=n/2;

  /* �u���b�N��O���ƌ㔼�ɕ����� */
  MergeSort(m, x);     /* �z��x��m�ڂ܂� */
  MergeSort(n-m, x+m); /* �z��x��m�Ԃ̗v�f���� */

  /* ����(�}�[�W)���� */
  for (i=0; i<m; i++) buffer[i]=x[i];

  j=m;
  i=k=0;

  while (i<m && j<n) {
    /* �O���O���[�v(buffer)�ƌ㔼�Ƃŏ����������ɋl�߂Ă��� */
    if (buffer[i]<=x[j]) {
      x[k]=buffer[i];  i++;
    } else {
      x[k]=x[j];       j++;
    }
    k++;
  }

  while (i<m) { /* buffer�Ƀf�[�^���c���Ă����, x�̌��ɋl�߂� */
    x[k]=buffer[i];
    k++; i++;
  }
}

int main(void)
{
  int i;
  int sort[N];

  srand((unsigned int)time(NULL));

  printf(":\n");
  for (i=0; i<N; i++) {
    /* �z��Ƀ����_���Ȓl���i�[ */
    sort[i]=rand();
    printf("%10d ", sort[i]);
  }

  printf("\n\n");
  MergeSort(N,sort);

  printf("\n\n");
  for (i=0; i<N; i++) printf("%10d ",sort[i]);
  printf("\n");

  return EXIT_SUCCESS;
}
