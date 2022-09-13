#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 80 /* 読込バッファサイズ */
#define DATANUM 101
#define ROUND(x) ((x > 0) ? (x + 0.5) : (x - 0.5))

int main(int argc, char **argv){
	char buf[BUFSIZE];
	int ain,nmax;
	double err;
	int n;
	int tm[DATANUM], amp[DATANUM], aout[DATANUM];
	FILE *fp;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
		return EXIT_FAILURE;
	}
	nmax = atoi(argv[2]); /* 白色雑音の最大振幅を設定 */
	printf("# WN %d\n", nmax);
	srand((unsigned)time(NULL));

	if ((fp = fopen(argv[1], "r")) == NULL) { /* readモードでテキストファイルを開く */
	fprintf(stderr, "File: %s cannot open\n", argv[1]);
	return EXIT_SUCCESS;
	}

	for (n=0; n < DATANUM;){
		if(fgets(buf, sizeof(buf), fp) == NULL) break;
		if(buf[0] == '#') {
			printf("%s", buf);
			continue;
		}
		tm[n] = atoi(strtok(buf,","));
		amp[n] = atoi(strtok(NULL, "\r\n\0"));
		n++;
	}
	fclose(fp);

	for (n=0; n < DATANUM; n++){
		err = nmax*(2.0*rand()/RAND_MAX-1.0);
		aout[n] = amp[n] + ROUND(err);
		if(aout[n]>255)aout[n]=255;
		if(aout[n]<0)aout[n]=0;
		printf("%4d, %4d, %4d\n", tm[n], amp[n], aout[n]);
	}
	return EXIT_SUCCESS;
}
