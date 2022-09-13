#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  double a, b;

  scanf("%lf%lf", &a, &b);
  // scanf("%lf", &b);
  assert(b != 0);
  printf("%lf\n", a / b);

  return EXIT_SUCCESS;
}