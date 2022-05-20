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

int main(void) {
  double amp, dif, pi2, radi;

  pi2 = 2 * PI;
  dif = PI / 180.0;
  for (radi = -2 * pi2; radi <= 2 * pi2; radi += dif) {
    amp = squ(radi);
    printf("%6.3f, %6.3f\n", radi, amp);
  }
  return EXIT_SUCCESS;
}