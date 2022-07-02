#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "pi.h"
#define A_BIAS 0x80
#define DT 10
#define T_END 1000
#define ROUND(x) ((x > 0) ? (x + 0.5) : (x - 0.5))

int main(int argc, char **argv){
	int t, nmax;
	double amp,frq,phf,rad,vin,esum=0,sum=0,err;
	unsigned char vout;

	if (argc !=4) {
		fprintf(stderr, "Usage: %s amplitude frequency\n", argv[0]);
		return EXIT_FAILURE;
	}

	nmax = atoi(argv[3]);
	printf("# WN %d\n", nmax);
	srand((unsigned)time(NULL));

	amp = atof(argv[1]);
	frq = atof(argv[2]);
	printf("#A %f\n", amp);
	printf("#F %f\n", frq);
	printf("#T %d\n", DT);
	printf("#B %d\n", A_BIAS);
	printf("#N %d\n", T_END/DT + 1);
	for (t = 0; t <= T_END; t += DT){
		rad = (t*frq*(2*PI)/1000);
		vin = amp*sin(rad) + A_BIAS;
        err = nmax*(2.0*rand()/RAND_MAX - 1.0);
        vout = vin + ROUND(err);
		if(vout > 255){
			vout = 255;
		}else if(vin < 0){
			vout = 0;
		}
		vout = vin;
		printf("%4d, %d, %4d\n", t, vin, vout);
	}

	return EXIT_SUCCESS;
}