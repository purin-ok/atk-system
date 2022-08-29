#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"

#define T_END 1000
#define DT 1
#define A_BIAS 0x80
#define FRQ 3
int main(int argc, char *argv[]) {
  int count, amp;
  double k, m, rad, f_3, dif;
  if (argc < 3) {
    fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
    return EXIT_FAILURE;
  }

  amp = atoi(argv[1]);

  m = atoi(argv[2]);
  for (int t = 0; t <= T_END; t += DT) {
    rad = t * FRQ * 2 * PI / 1000;
    f_3 = 0;
    for (count = 1; count <= m; count++) {
      f_3 += sin(count * PI / 2) * sin(count * rad) / (count * count);
    }
    f_3 = 8 / (PI * PI) * amp * f_3 + A_BIAS;
    printf("%4d,%4d\n", t, (int)f_3);
  }
  return EXIT_SUCCESS;
}