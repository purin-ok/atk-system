/*
モノラル音声のWAVEファイルをステレオ音声のWAVEファイルに変換する．
その際，Lはもとのモノラル音声のまま保存し，RはΔtだけ遅らせるようにする
モノラル音声のWAVEファイル，ステレオ音声のWAVEファイル，Δtはコマンドライン引数として与える．
*/
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define H_LEN 4   /* チャンクサイズ */
#define ID_LPCM 1 /* リニアPCMのID */
#define CH 2      //ステレオに変換するからこれでいい．
#define DT 4      //どれくらいずらすか
typedef unsigned short uShort;
typedef unsigned long uLong;

/* ファイル*fpからヘッダ情報を読み取り*ch, *qbitに値をセットして
   データサイズを戻り値とする（WAVEファイルでなければ0を戻り値とする） */
uLong header_data(FILE *fp, FILE *fp_write, short *q_bit, int *data_size) {
  char str[H_LEN];
  unsigned int h_len = H_LEN;
  uLong riff_size, fmt_size, sampling_rate, data_speed;
  uShort fid, block_size, ch;

  fread(str, sizeof(char), h_len, fp);
  if (memcmp("RIFF", str, h_len) != 0) return 0;
  fread(&riff_size, sizeof(uLong), 1, fp);
  printf("# RIFF size: %ld\n", riff_size);
  fread(str, sizeof(char), h_len, fp);
  if (memcmp("WAVE", str, h_len) != 0) return 0;
  fread(str, sizeof(char), h_len, fp);
  if (memcmp("fmt ", str, h_len) != 0) return 0;
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
  fread(q_bit, sizeof(uShort), 1, fp);
  printf("# Q bit: %d\n", *q_bit);
  fread(str, sizeof(char), h_len, fp);
  if (memcmp("data", str, h_len) != 0) return 0;
  fread(data_size, sizeof(uLong), 1, fp);
  printf("# datasize: %ld\n", *data_size);
  *data_size *= 2;
  ch = CH;
  fwrite("RIFF", sizeof(char), 4, fp_write);
  fwrite(&riff_size, sizeof(int), 1, fp_write);
  fwrite("WAVE", sizeof(char), 4, fp_write);
  fwrite("fmt ", sizeof(char), 4, fp_write);
  fwrite(&fmt_size, sizeof(int), 1, fp_write);
  fwrite(&fid, sizeof(short), 1, fp_write);
  fwrite(&ch, sizeof(short), 1, fp_write);
  fwrite(&sampling_rate, sizeof(int), 1, fp_write);
  fwrite(&data_speed, sizeof(int), 1, fp_write);
  fwrite(&block_size, sizeof(short), 1, fp_write);
  fwrite(q_bit, sizeof(short), 1, fp_write);
  fwrite("data", sizeof(char), 4, fp_write);
  fwrite(data_size, sizeof(int), 1, fp_write);
  // *data_size /= 2;
  return sampling_rate; /* この戻り値は演習5-2で活用できるはず */
}

int main(int argc, char **argv) {
  int sampling_rate, count = 0, data_size;
  unsigned short data_dt[DT] = {0};  //ずらしてる間は0を出力する．
  unsigned short datL, datR;
  uShort q_bit;
  FILE *fp;
  FILE *fp_write;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s file page\n", argv[0]);
    return EXIT_FAILURE;
  }
  if ((fp = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "File (%s) cannot open\n", argv[1]);
    return EXIT_FAILURE;
  }  //読み込み先のモノラルファイル
  if ((fp_write = fopen(argv[2], "wb")) == NULL) {
    fprintf(stderr, "File (%s) cannot open\n", argv[2]);
    return EXIT_FAILURE;
  }  //書き込み先のステレオファイル
  int countp = 0;
  sampling_rate = header_data(fp, fp_write, &q_bit, &data_size);
  while ((data_dt[0] = fgetc(fp)) != EOF) {
    if (countp * 2 >= data_size) break;
    datL = data_dt[0];
    datR = data_dt[DT - 1];
    fwrite(&datL, sizeof(unsigned char), 1, fp_write);
    fwrite(&datR, sizeof(unsigned char), 1, fp_write);
    printf("%d,%d\n", datL, datR);
    for (count = 1; count < DT; count++) {
      data_dt[DT - count] = data_dt[DT - count - 1];
    }
    countp++;
  }
  fclose(fp);
  fclose(fp_write);
  return EXIT_SUCCESS;
}