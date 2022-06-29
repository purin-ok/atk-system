#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"
#define T_END 1000
#define DT 1
#define A_BIAS 0x80
#define FRQ 3
int main(int argc, char *argv[]) {
  int count, amp, m;
  double k, rad, f_1, dif;
  if (argc < 3) {
    fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
    return EXIT_FAILURE;
  }

  amp = atoi(argv[1]);

  m = atoi(argv[2]);
  for (int t = 0; t <= T_END; t += DT) {
    rad = t * FRQ * 2 * PI / 1000;
    f_1 = 0;
    for (count = 1; count <= m; count++) {
      f_1 += sin(count * rad) / count;
    }
    f_1 = 2 / PI * amp * f_1 + A_BIAS;
    printf("%4d,%4d\n", t, (int)f_1);
  }
  return EXIT_SUCCESS;
}