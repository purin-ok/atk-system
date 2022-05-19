#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW 16 /* Rows per page */
#define COL 16 /* Columns per row */

#define H_LEN 4   /* チャンクサイズ */
#define ID_LPCM 1 /* リニアPCMのID */
typedef unsigned short uShort;
typedef unsigned long uLong;

uLong read_head(FILE *fp, uShort *ch, uShort *qbit) {
  char str[H_LEN];
  uLong riffsize, fmtsize, smprate, datasize, bytepersec;
  uShort fid, blksize;

  fread(str, sizeof(char), H_LEN, fp);
  if (memcmp("RIFF", str, H_LEN) != 0) return 0;
  fread(&riffsize, sizeof(uLong), 1, fp);
  printf("# RIFF size: %ld\n", riffsize);
  fread(str, sizeof(char), H_LEN, fp);
  if (memcmp("WAVE", str, H_LEN) != 0) return 0;
  fread(str, sizeof(char), H_LEN, fp);
  if (memcmp("fmt ", str, H_LEN) != 0) return 0;
  fread(&fmtsize, sizeof(uLong), 1, fp);
  printf("# fmt size: %ld\n", fmtsize);
  fread(&fid, sizeof(uShort), 1, fp);
  printf("# fmt ID: %d\n", fid);
  if (fid != ID_LPCM) return 0;
  fread(ch, sizeof(uShort), 1, fp);
  printf("# CH: %d\n", *ch);
  fread(&smprate, sizeof(uLong), 1, fp);
  printf("# Sampling rate: %ld\n", smprate);
  fread(&bytepersec, sizeof(uLong), 1, fp);
  printf("# Bytes per sec: %ld\n", bytepersec);
  fread(&blksize, sizeof(uShort), 1, fp);
  printf("# Block size: %d\n", blksize);
  fread(qbit, sizeof(uShort), 1, fp);
  printf("# Q bit: %d\n", *qbit);
  fread(str, sizeof(char), H_LEN, fp);
  if (memcmp("data", str, H_LEN) != 0) return 0;
  fread(&datasize, sizeof(uLong), 1, fp);
  printf("# datasize: %ld\n", datasize);
  return smprate; /* この戻り値は演習5-2で活用できるはず */
}

int main(int argc, char **argv) {
  double count;
  double tm = 0;
  int dat;
  long start_num = 0L, end_num;
  FILE *fp;
  uLong dsize, sampling_rate;
  uShort ch, qbit;

  if ((argc < 3) || (argc > 4)) {
    fprintf(stderr, "Usage: %s file page\n", argv[0]);
    return EXIT_FAILURE;
  }
  if ((fp = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "File (%s) cannot open\n", argv[1]);
    return EXIT_FAILURE;
  }

  sampling_rate = read_head(fp, &ch, &qbit);
  if (argc > 3) {
    start_num = atol(argv[2]);
    fseek(fp, start_num, SEEK_CUR);
  }
  if (argc == 4) {
    end_num = atoi(argv[3]);
  }
  tm = (double)start_num / sampling_rate * 1000.0;
  printf("%f", tm);
  count = 1000.0 / sampling_rate;
  while ((dat = fgetc(fp)) != EOF) {
    if (count > end_num) break;
    tm += count;
    printf("%0.3f,%4d\n", tm, dat);
  }
  fclose(fp);
  return EXIT_SUCCESS;
}