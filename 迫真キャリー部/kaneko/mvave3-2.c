#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFSIZE 80
#define DATANUM 100
#define ROUND(x) ((x > 0) ? (x + 0.5) : (x - 0.5))

int main(int argc, char **argv) {
  double tm[DATANUM];
  int amp[DATANUM], Amp[DATANUM];
  char buf[BUFSIZE];
  double vout;
  FILE *fp;

  if (argc != 2) {
    printf("a");
    return EXIT_FAILURE;
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    printf("b");
    return EXIT_FAILURE;
  }

  srand((unsigned)time(NULL));
  printf("abc");
  for (int n = 0; n <= DATANUM;) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;
    if (buf[0] == '#') continue;
    tm[n] = atoi(strtok(buf, ","));
    amp[n] = atoi(strtok(NULL, "\r\n\0"));
    Amp[n] = amp[n - 2] + amp[n - 1] + amp[n];
    n++;
  }
  for (int n = 0; n <= DATANUM;) {
    vout = ROUND(Amp[n] / 3);
    if (n > 2) printf("%4d,%4d, %4d\n", (int)tm[n - 1], amp[n], (int)vout);
    n++;
  }

  fclose(fp);

  return EXIT_SUCCESS;
}
