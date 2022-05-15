#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"

#define A_BIAS 0x80
#define F_S 11025
#define H_LEN 4   /* チャンクサイズ */
#define ID_LPCM 1 /* リニアPCMのID */
typedef unsigned short uShort;
typedef unsigned long uLong;
char wave[] = "WAVE";
char riff[] = "RIFF";
char fmt[] = "fmt ";
char a;

void write_head(FILE *fp, uLong *header) {
  fwrite("RIFF", sizeof(char), H_LEN, fp);
  fwrite(header, sizeof(uLong), 4, fp);
  fwrite("WAVE", sizeof(char), H_LEN, fp);
  fwrite("fmt ", sizeof(char), H_LEN, fp);
}

int main(int argc, char **argv) {
  //ファイル名，振幅，振幅，書き込みファイル
  int t;
  double amp, frq, rad, vin;
  int vout[F_S];
  uLong header[32] = 0;
  FILE *fp;
  if (argc < 4) {
    printf("ちゃんと入力してね");
    return EXIT_FAILURE;
  }
  if ((fp = fopen(argv[3], "wb+")) == NULL) {
    printf("ないよファイルないよ");
    return EXIT_FAILURE;
  }

  amp = atof(argv[1]);
  frq = atof(argv[2]);

  for (t = 0; t <= F_S; t++) {
    rad = t / (1000 / frq) * 2 * PI;
    vin = amp * sin(rad) + A_BIAS; /* 標本化 */
    if (vin < 0) vin = 0;
    if (vin > 255) vin = 255;
    vout[t] = vin; /* 量子化・符号化 */
    //    printf("%4d, %4d\n", t, vout[t]);  //ここをfwrite関数使って出力......?
  }
  header[0] = F_S;
  header[4] = "WAVE";
  write_head(fp, header);
  fwrite(vout, sizeof(int), F_S, fp);
  fclose(fp);
  return EXIT_SUCCESS;
}