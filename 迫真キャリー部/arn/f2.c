/* sin�g�̃T���v�����O�v���O�����̎�v��(8bit,dt=10ms.,t=[0:1000ms]) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"
#define A_BIAS 0x80 /* �����o�C�A�X */
#define DT 10       /* �W�{���Ԋu[ms] */
#define T_END 50
#define FRQ 10 /*周波数*/

int main(int argc, char **argv) {
  int t, k, m;
  double a, amp = 0, rad; /* esum�͉��K2-3,phf�͉��K2-6�Ŏg�p */
  unsigned int vout; /* �o��: 8�r�b�g�����Ȃ�[0:255] */

  if (argc != 3) { /* �R�}���h���C�������̏��� */
    fprintf(stderr, "Usage: %s amplitude frequency\n", argv[0]);
    return EXIT_FAILURE;
  }
  a = atof(argv[1]); /* �U�� */
  m = atof(argv[2]); /* ���g�� */

  printf("#A %f\n", a);
  printf("#T %d\n", DT);
  printf("#B %d\n", A_BIAS);
  printf("#M %d\n", m);

  for (t = 0; t <= T_END; t += DT) {
    for (k = 1; k <= m; k++) {
      rad = 2 * PI * FRQ * t / 1000.0;
      amp += (sin((2 * k - 1) * rad) / (2 * k - 1));
    }
    vout = round((a * 4 * amp / PI) + A_BIAS);
    amp = 0;
    printf("%4d, %4d\n", t, vout);
  }

  return EXIT_SUCCESS;
}
