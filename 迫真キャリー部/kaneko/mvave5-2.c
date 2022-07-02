#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFSIZE 80
#define DATANUM 100
#define ROUND(x) ((x > 0) ? (x + 0.5) : (x - 0.5))

int main(int argc, char **argv) {
  double tm[DATANUM];
  int amp[DATANUM];
  char buf[BUFSIZE];
  double vout;
  FILE *fp;

  if (argc != 2) {
    return EXIT_FAILURE;
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    return EXIT_FAILURE;
  }

  srand((unsigned)time(NULL));

  for (int n = 0; n <= DATANUM;) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;
    if (buf[0] == '#') continue;
    tm[n] = atoi(strtok(buf, ","));
    amp[n] = atoi(strtok(NULL, "\r\n\0"));
    n++;
  }
  fclose(fp);

  for (int n = 3; n < DATANUM - 2; n++) {
    vout = ROUND((amp[n - 2] + amp[n - 1] + amp[n] + amp[n + 1] + amp[n + 2]) /
                 5.0);

    printf("%4d, %4d\n", (int)tm[n], (int)vout);
  }
  return EXIT_SUCCESS;
}
