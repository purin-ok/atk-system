/*
モノラル音声のWAVEファイルをステレオ音声のWAVEファイルに変換する．
その際，Lはもとのモノラル音声のまま保存し，RはΔtだけ遅らせるようにする
モノラル音声のWAVEファイル，Δtはコマンドライン引数として与える．
*/
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define H_LEN 4   /* チャンクサイズ */
#define ID_LPCM 1 /* リニアPCMのID */
#define CH 2      //ステレオに変換するからこれでいい．
typedef unsigned short uShort;
typedef unsigned long uLong;

/* ファイル*fpからヘッダ情報を読み取り*ch, *qbitに値をセットして
   データサイズを戻り値とする（WAVEファイルでなければ0を戻り値とする） */
uLong header_data(FILE *fp, FILE *fp_write) {
  char str[H_LEN];
  uLong riff_size, fmt_size, sampling_rate, data_speed, datasize;
  uShort fid, block_size, q_bit, ch, data_size;

  fread(str, sizeof(char), H_LEN, fp);
  if (memcmp("RIFF", str, H_LEN) != 0) return 0;
  fread(&riff_size, sizeof(uLong), 1, fp);
  printf("# RIFF size: %ld\n", riff_size);
  fread(str, sizeof(char), H_LEN, fp);
  if (memcmp("WAVE", str, H_LEN) != 0) return 0;
  fread(str, sizeof(char), H_LEN, fp);
  if (memcmp("fmt ", str, H_LEN) != 0) return 0;
  fread(&fmt_size, sizeof(uLong), 1, fp);
  printf("# fmt size: %ld\n", fmt_size);
  fread(&fid, sizeof(uShort), 1, fp);
  printf("# fmt ID: %d\n", fid);
  if (fid != ID_LPCM) return 0;
  fread(&ch, sizeof(uShort), 1, fp);
  printf("# CH: %d\n", ch);
  fread(&sampling_rate, sizeof(uLong), 1, fp);
  printf("# Sampling rate: %ld\n", sampling_rate);
  fread(&data_speed, sizeof(uLong), 1, fp);
  printf("# Bytes per sec: %ld\n", data_speed);
  fread(&block_size, sizeof(uShort), 1, fp);
  printf("# Block size: %d\n", block_size);
  fread(&q_bit, sizeof(uShort), 1, fp);
  printf("# Q bit: %d\n", q_bit);
  fread(str, sizeof(char), H_LEN, fp);
  if (memcmp("data", str, H_LEN) != 0) return 0;
  fread(&datasize, sizeof(uLong), 1, fp);
  printf("# datasize: %ld\n", datasize);

  fwrite("RIFF", sizeof(char), 4, fp_write);
  fwrite(&riff_size, sizeof(int), 1, fp_write);
  fwrite("WAVE", sizeof(char), 4, fp_write);
  fwrite("fmt ", sizeof(char), 4, fp_write);
  fwrite(&fmt_size, sizeof(int), 1, fp_write);
  fwrite(ID_LPCM, sizeof(short), 1, fp_write);
  fwrite(CH, sizeof(short), 1, fp_write);
  fwrite(&sampling_rate, sizeof(int), 1, fp_write);
  fwrite(&data_speed, sizeof(int), 1, fp_write);
  fwrite(&block_size, sizeof(short), 1, fp_write);
  fwrite(&q_bit, sizeof(short), 1, fp_write);
  fwrite("data", sizeof(char), 4, fp_write);
  fwrite(&data_size, sizeof(int), 1, fp_write);
  return datasize; /* この戻り値は演習5-2で活用できるはず */
}

int main(int argc, char argv[]) {
  int dt;

  FILE *fp;
  if (argc < 3) {
    fprintf(stderr, "Usage: %s file page\n", argv[0]);
    return EXIT_FAILURE;
  }
  if ((fp = fopen(argv[1], "wb+")) == NULL) {
    fprintf(stderr, "File (%s) cannot open\n", argv[1]);
    return EXIT_FAILURE;
  }
}