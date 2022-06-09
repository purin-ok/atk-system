#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"

#define BUFSIZE 80 /* 読込バッファサイズ */
#define A_BIAS 0x80
int main(int argc, char *argv[]) {
  int count, amp;
  double k, m, rad, f_1, dif;
  FILE *fp;
  if (argc < 3) {
    fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
    return EXIT_FAILURE;
  }

  amp = atoi(argv[1]);

  if (m > 0) m = atoi(argv[2]);
  dif = PI / 180.0;
  for (rad = 0; rad < 2 * PI; rad += dif) {
    f_1 = 0;
    for (count = 1; count < m; count++) {
      f_1 += sin((2 * count - 1) * rad) / (2 * count - 1);
    }
    f_1 = 4 / PI * amp * f_1 + A_BIAS;
    printf("%f,%f\n", rad, f_1);
  }
  fclose(fp);
  return EXIT_SUCCESS;
}