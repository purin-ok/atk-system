#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"

double rad(double r) {
  double mod;
  mod = fmod(r, 2 * PI);
  if (r < 0) mod = mod + 2 * PI;
  return mod;
}

//?��?��?��K1?��|2
double saw(double r) {
  double saw_blead;
  saw_blead = 1 - rad(r) / PI;
  return saw_blead;
}

double squ(double r) {
  double square;
  square = saw(r);
  if (r > 0) {
    square = 1;
  } else {
    square = -1;
  }
  return square;
}

double tri(double r) {
  int index = 1;
  double triangle, mod;
  mod = fmod(r, PI);
  if (r < 0) mod = mod + PI;
  triangle = mod * 2 / PI;
  //傾きはこれでいいはず．あとはどうやって折り返すか考える．
  if (triangle > 1) triangle = 2 - triangle;
  if (r < 0) {
    r *= (-1);
    index *= (-1);
  }  //弧度を絶対値に
  while (1) {
    r -= PI;
    if (r < 0) break;
    index *= (-1);
  }
  triangle *= index;
  return triangle;
}

int main(void) {
  double amp, dif, pi2, radi;

  pi2 = 2 * PI;
  dif = PI / 180.0;
  for (radi = -2 * pi2; radi <= 2 * pi2; radi += dif) {
    amp = tri(radi);
    printf("%6.3f, %6.3f\n", radi, amp);
  }
  return EXIT_SUCCESS;
}