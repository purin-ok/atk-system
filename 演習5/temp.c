#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"
typedef unsigned short uShort;
typedef unsigned long uLong;
int main() {
  uLong amp[4];
  char a;
  a = "W";
  amp[0] = (uLong)a;
  for (int i = 0; i < 4; i++) {
    printf("%x,", amp[i]);
  }
  return 0;
}