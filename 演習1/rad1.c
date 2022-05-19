/* sin?申g?申?申CSV?申f?申[?申^?申?申?申?申 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"
//?申?申?申K1?申|1
double rad(double r) {
  double mod;
  mod = fmod(r, 2 * PI);
  if (r < 0) mod = mod + 2 * PI;
  return mod;
}

//?申?申?申K1?申|2
double saw(double e) {
  double saw_blead;
  saw_blead = 1 - rad(e) / PI;
  return saw_blead;
}

int main(void) {
  double amp, dif, pi2, radi;

  pi2 = 2 * PI;
  dif = PI / 180.0;
  for (radi = -2 * pi2; radi <= 2 * pi2; radi += dif) {
    amp = saw(radi);
    printf("%6.3f, %6.3f\n", radi, amp);
  }
  return EXIT_SUCCESS;
}