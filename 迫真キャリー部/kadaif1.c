#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pi.h"
#define A_BIAS 0x80
#define T_END 1000
#define DT 10
#define FREQUENCY 2.0

int main(int argc, char **argv) {
  int t, M, k;
  double fi = 0, f, rad, A;
  unsigned char aout;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
    return EXIT_FAILURE;
  }

  A = atof(argv[1]);
  M = atof(argv[2]);

  for (t = 0; t <= T_END; t += DT) {
    fi = 0;
    for (k = 1; k <= M; k++) {
      rad = (t * FREQUENCY * (2.0 * PI) / 1000);
      fi += sin((double)k * rad) / (double)k;
    }
    f = 2 / PI * A * fi + A_BIAS;
    // if(f > 255){
    // 	aout = 255;
    // }else if(f < 0){
    // 	aout = 0;
    // }else{
    aout = f;
    // }
    printf("%4d, %4d\n", t, aout);
  }
  return EXIT_SUCCESS;
}