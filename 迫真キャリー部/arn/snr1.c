#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUFSIZE 80
#define A_BIAS 0x80
#define DATANUM 101
#define ROUND(x) ((x > 0) ? (x + 0.5) : (x - 0.5))

int main(int argc, char **argv) {
	char buf[BUFSIZE];
	int n;
	int tm[DATANUM], noise[DATANUM], no_noise[DATANUM];
     double a_rms=0.0,an,snr;
	FILE *fp;

	if ((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "File: %s cannot open\n", argv[1]);
		return EXIT_SUCCESS;
	}

	for (n=0; n < DATANUM;){
		if(fgets(buf, sizeof(buf), fp) == NULL) break;
		if(buf[0] == '#') {
			continue;
		}

		tm[n] = atoi(strtok(buf,","));
		no_noise[n] = atoi(strtok(NULL,","));
		noise[n] = atoi(strtok(NULL, "\r\n\0"));
		n++;
	}
	
	fclose(fp);
	for (n=0; n < DATANUM; n++){
		a_rms+=((noise[n]-A_BIAS)*(noise[n]-A_BIAS));
		an+=(noise[n]-no_noise[n])*(noise[n]-no_noise[n]);
	}

	a_rms=sqrt(a_rms/DATANUM);

	an=sqrt(an/DATANUM);

	if(an!=0) {
		snr=20*log10(a_rms/an);
	} else {
		snr=0;
	}
	
	printf("an:%.4f\nSNR:%.4f\n", an,snr);
	return EXIT_SUCCESS;
}