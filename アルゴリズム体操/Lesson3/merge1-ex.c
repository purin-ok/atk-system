/* �}�[�W�\�[�g */
/* ���s���̈���: ��1����:�\�[�g����f�[�^�� */
/*               ��2����:�\�[�g����f�[�^�̎��: 0:�����_��, 1:����, 2:�~�� */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* �f�[�^�̌���(�ȗ���) */
int *buffer; /* �o�b�t�@�p�z��Dmain���Ŋm�� */

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

int main(int argc, char *argv[]) {
  int i, n = N, t = 0, flag;
  int *sort;
  clock_t stime, etime;
  if (argc > 1) {
    n = atoi(argv[1]);
  }
  if (argc > 2) {
    t = atoi(argv[2]);
  }
  if (n > 0) {
    if ((sort = (int *)malloc(sizeof(int) * n)) == NULL) exit(EXIT_FAILURE);
    if ((buffer = (int *)malloc(sizeof(int) * (n / 2 + 1))) == NULL)
      exit(EXIT_FAILURE);
  }

  /* �z��ɒl���i�[: 1:����, 2:�~��, ���̑�:�����_�� */
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

  stime = clock(); /* �J�n�������L�^ */
  MergeSort(n, sort);
  etime = clock(); /* �I���������L�^ */

  switch (t) {
    case 1:
      printf("��������ς݃f�[�^");
      break;
    case 2:
      printf("�~������ς݃f�[�^");
      break;
    default:
      printf("�����_���f�[�^");
      break;
  }
  printf(
      "%d "
      "�̕��בւ����}�[�g�ōs�Ȃ��܂����B",
      n);
  printf("���s���Ԃ́A%.3f�b�ł����B\n", (float)(etime - stime) / CLOCKS_PER_SEC);

  printf("\n����f�[�^�̃`�F�b�N: ");
  flag = 0;
  for (i = 0; i < n - 1; i++) {
    if (sort[i] > sort[i + 1]) {
      flag = 1;
      break;
    }
  }
  if (flag != 0)
    printf("���񂳂�Ă��܂���D\n");
  else
    printf("���������񂳂�Ă��܂����D\n");

  return EXIT_SUCCESS;
}
