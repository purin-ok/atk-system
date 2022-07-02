#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pi.h"

#define BIAS 0x80
#define RIFF_SIZE 11061
#define FMT_SIZE 16
#define FORMAT_ID 1
#define SAMPLING_RATE 11025
#define CHANNEL_N 1
#define BLOCK_SIZE 1
#define Q_BIT 8


void write_head(FILE *fp) {
    int riff_size     = RIFF_SIZE,
        fmt_size      = FMT_SIZE,
        format_id     = FORMAT_ID,
        channel_n     = CHANNEL_N,
        sampling_rate = SAMPLING_RATE,
        block_size    = BLOCK_SIZE,
        q_bit         = Q_BIT;

    fwrite("RIFF",         sizeof(char),  4, fp);
    fwrite(&riff_size,     sizeof(int),   1, fp);
    fwrite("WAVE",         sizeof(char),  4, fp);
    fwrite("fmt ",         sizeof(char),  4, fp);
    fwrite(&fmt_size,      sizeof(int),   1, fp);
    fwrite(&format_id,     sizeof(short), 1, fp);
    fwrite(&channel_n,     sizeof(short), 1, fp);
    fwrite(&sampling_rate, sizeof(int),   1, fp);
    fwrite(&sampling_rate, sizeof(int),   1, fp);
    fwrite(&block_size,    sizeof(short), 1, fp);
    fwrite(&q_bit,         sizeof(short), 1, fp);
    fwrite("data",         sizeof(char),  4, fp);
    fwrite(&sampling_rate, sizeof(int),   1, fp);
}

int main(int argc,char **argv){
	int t;
	double rad, frq, amp,ut=0,Vout,Amp,a,b;
  double dt = (double)SAMPLING_RATE;
	unsigned char vout;
	FILE *fp;

	if (argc != 6) {
      printf("a\n");
			return EXIT_FAILURE;
	}

	amp = atof(argv[1]);
	frq = atof(argv[2]);
  a   = atof(argv[4]);
  b   = atof(argv[5]);
  if(a+b > 100){
    printf("not successful\n");
    return  0;
  }
	if ((fp = fopen(argv[3], "a+b")) == NULL) {
			return EXIT_FAILURE;
	}

	write_head(fp);

	for (t = 0; t <= SAMPLING_RATE; t++) {
			rad = 2 * PI * frq * t / dt;
			Amp = amp;
			if(t<=SAMPLING_RATE*a/100)Amp = amp * t*t/(SAMPLING_RATE*SAMPLING_RATE*pow(a/100,2));
			if(t>=SAMPLING_RATE*(1-b/100))Amp = amp * (SAMPLING_RATE-t)*(SAMPLING_RATE-t)/(SAMPLING_RATE*SAMPLING_RATE*pow(b/100,2));
			vout = Amp * sin(rad) + BIAS;
			Vout = Amp * sin(rad) + BIAS;
			fwrite(&vout, 1, 1, fp);
			printf("%4f,%4f\n",(double)t*1000/SAMPLING_RATE,Vout);
	}
	printf("success\n");
  fclose(fp);
  return EXIT_SUCCESS;
}
