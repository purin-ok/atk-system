#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pi.h"

//ヘッダファイル
#define BIAS 0x80
#define RIFF_SIZE 11061
#define FMT_SIZE 16
#define FORMAT_ID 1
#define SAMPLING_RATE 11025
#define CHANNEL_N 1
#define BLOCK_SIZE 1
#define Q_BIT 8
#define WAVE_SECOND 1
int data_size = SAMPLING_RATE * WAVE_SECOND;

void header_data(FILE *fp) {
  int riff_size = RIFF_SIZE;
  int fmt_size = FMT_SIZE;
  int format_id = FORMAT_ID;
  int channel_n = CHANNEL_N;
  int sampling_rate = SAMPLING_RATE;
  int block_size = BLOCK_SIZE;
  int q_bit = Q_BIT;
  int data_speed = sampling_rate * block_size;

  fwrite("RIFF", sizeof(char), 4, fp);
  fwrite(&riff_size, sizeof(int), 1, fp);
  fwrite("WAVE", sizeof(char), 4, fp);
  fwrite("fmt ", sizeof(char), 4, fp);
  fwrite(&fmt_size, sizeof(int), 1, fp);
  fwrite(&format_id, sizeof(short), 1, fp);
  fwrite(&channel_n, sizeof(short), 1, fp);
  fwrite(&sampling_rate, sizeof(int), 1, fp);
  fwrite(&data_speed, sizeof(int), 1, fp);
  fwrite(&block_size, sizeof(short), 1, fp);
  fwrite(&q_bit, sizeof(short), 1, fp);
  fwrite("data", sizeof(char), 4, fp);
  fwrite(&data_size, sizeof(int), 1, fp);
}

int main(int argc, char **argv) {
  //ファイル名，振幅，振幅，書き込みファイル
  int t;
  double amp, frq, rad, vin;
  unsigned char vout[SAMPLING_RATE];

  FILE *fp;
  if (argc < 4) {
    fprintf(stderr, "Usage: %s file page\n", argv[0]);
    return EXIT_FAILURE;
  }
  if ((fp = fopen(argv[3], "wb+")) == NULL) {
    fprintf(stderr, "File (%s) cannot open\n", argv[1]);
    return EXIT_FAILURE;
  }

  amp = atof(argv[1]);
  frq = atof(argv[2]);

  for (t = 0; t <= data_size; t++) {
    rad = t * (frq / SAMPLING_RATE) * 2 * PI;
    vin = amp * sin(rad) + BIAS; /* 標本化 */
    if (vin < 0) vin = 0;
    if (vin > 255) vin = 255;
    vout[t] = vin; /* 量子化・符号化 */
    //    printf("%4d, %4d\n", t, vout[t]);  //ここをfwrite関数使って出力......?
  }

  header_data(fp);
  fwrite(vout, sizeof(unsigned char), data_size, fp);
  fclose(fp);
  return EXIT_SUCCESS;
}