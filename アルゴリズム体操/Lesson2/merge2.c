#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* �f�[�^�̌���(�ȗ���) */
int *buffer; /* �o�b�t�@�p�z��Dmain���Ŋm�� */

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

  j=m;  i=k=0;

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
    k++;  i++;
  }
}

int main(int argc, char *argv[])
{
  int i, n=N;
  int *sort;
  clock_t stime, etime;

  if (argc>1) { n = atoi(argv[1]); }
  if (n>0) {
    if ((sort=(int *)malloc(sizeof(int)*n)) == NULL)
      exit(EXIT_FAILURE);
    if ((buffer=(int *)malloc(sizeof(int)*(n/2+1))) == NULL)
      exit(EXIT_FAILURE);
  }
  srand((unsigned int)time(NULL));

  /* �z��Ƀ����_���Ȓl���i�[ */
  for (i=0; i<n; i++) sort[i]=rand();

  stime = clock(); /* �J�n�������L�^ */
  MergeSort(n,sort);
  etime = clock(); /* �I���������L�^ */

  printf("%d", n);
  printf("%.3f\n", (float)(etime-stime)/CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}
