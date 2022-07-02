#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HEAD_SIZE 44
#define H_LEN 4
#define ID_LPCM 1
typedef unsigned short uShort;
typedef unsigned long uLong;

uLong read_head(FILE *fp, uShort *ch, uShort *qbit) {
	char str[H_LEN];
	uLong riffsize, fmtsize, smprate, bytepersec, datasize;
	uShort fid, blksize;

	fread(str, 1, H_LEN, fp);
	if(memcmp("RIFF", str, H_LEN) != 0) return 0;
	fread(&riffsize, 4, 1, fp);
	printf("# RIFF size: %ld\n", riffsize);

	fread(str, 1, H_LEN, fp);
	if(memcmp("WAVE", str, H_LEN) != 0) return 0;
	fread(str, 1, H_LEN, fp);
	if(memcmp("fmt ", str, H_LEN) != 0) return 0;
	fread(&fmtsize, 4, 1, fp);
	printf("# fmt size: %ld\n", fmtsize);
	fread(&fid, 2, 1, fp);
	printf("# fmt ID: %d\n", fid);

	if(fid != ID_LPCM) return 0;
	fread(ch, 2, 1, fp);
	printf("# CH: %d\n", *ch);
	fread(&smprate, 4, 1, fp);
	printf("# Sampling rate: %1lu\n", smprate);
	fread(&bytepersec, 4, 1, fp);
	printf("# Bytes per sec: %1lu\n", bytepersec);
	fread(&blksize, 2, 1, fp);
	printf("# Block size: %d\n", blksize);
	fread(qbit, 2, 1, fp);
	printf("# Q bit: %d\n", *qbit);

	fread(str, 4, H_LEN, fp);
	if(memcmp("data", str, H_LEN) != 0) return 0;
	fread(&datasize, 4, 1, fp);
	printf("# datasize: %1lu\n", datasize);
	return smprate;
}


	void LRampread(FILE *fp, uLong smprate, int start, int end) {
		int lamp,ramp;
		double t = 0;
	  double dt;
	  dt = 1000.0 / smprate;
		while(fread(&lamp,2,1,fp) && fread(&ramp,2,1,fp)){
			if(t >= start && t <=end)printf("%f,%d,%d\n",t,lamp,ramp );
		}
	}

int main(int argc, char **argv) {
	int start,end;
	uLong dsize;
	uShort ch, qbit;
	FILE *fp;

	if(argc != 4) {
		return EXIT_FAILURE;
	}
	if((fp = fopen(argv[1], "rb")) == NULL) {
		return EXIT_FAILURE;
	}

	start = atoi(argv[2]);
  end =  atoi(argv[3]);

	LRampread(fp, read_head(fp, &ch, &qbit), start, end);
	fclose(fp);
	return EXIT_SUCCESS;
}
