#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define BUFSIZE 80 /* ????o?b?t?@?T?C?Y */
#define A_BIAS 0x80 //?????o?C?A?X
#define DATANUM 101
#define ROUND(x) ((x > 0) ? (x + 0.5) : (x - 0.5))

int main(int argc, char **argv){
	char buf[BUFSIZE];
	int tm,i;
    int min=0, max=0, loopnum=0, maxamp,no_noise,in_noise,de_noise;
    double ave=0.0, sdv=0.0, a_rms=0.0,denoise_an,noise_an,denoise_snr,noise_snr;
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
		return EXIT_FAILURE;
	}

	if ((fp = fopen(argv[1], "r")) == NULL) { /* read???[?h??e?L?X?g?t?@?C?????J?? */
	fprintf(stderr, "File: %s cannot open\n", argv[1]);
	return EXIT_SUCCESS;
	}


	while(fgets(buf, sizeof(buf), fp) != NULL) { /* 1?T???v???????? */
		if (buf[0] == '#') { /* ?R?????g?s????? */
			continue;
		}

		tm = atoi(strtok(buf,","));
		no_noise = atoi(strtok(NULL,","));
        in_noise = atoi(strtok(NULL,","));
        if((de_noise = atoi(strtok(NULL, "\r\n\0")))==NULL) continue;
 
		//????????????v?Z?V???[?Y
		if(loopnum==0) {
			min=de_noise;
			max=de_noise;
		}

        if(min>de_noise) min=de_noise;
        if(max<de_noise) max=de_noise;
        ave=ave+de_noise;
        sdv+=(de_noise*de_noise);
        a_rms+=(de_noise-A_BIAS)*(de_noise-A_BIAS);
		denoise_an+=(de_noise-no_noise)*(de_noise-no_noise);
		noise_an+=(in_noise-no_noise)*(in_noise-no_noise);
        loopnum++;
	}
    //????l??v?Z
	ave=ROUND(ave/DATANUM);

    //?W???????v?Z
    sdv=sqrt((sdv - ave)*(sdv - ave)/DATANUM);

    //???U????v?Z
    if((A_BIAS-min)>(max-A_BIAS)){
        maxamp=A_BIAS-min;
    }else{
        maxamp=max-A_BIAS;
    }
    //?????l??v?Z
    a_rms=sqrt(a_rms/loopnum);

	denoise_an=sqrt(denoise_an/loopnum);
	noise_an=sqrt(noise_an/loopnum);
	
	if(denoise_an!=0) {
		denoise_snr=10*log10((a_rms/denoise_an)*(a_rms/denoise_an));
	} else {
		denoise_snr=0;
	}

	//if(noise_an!=0) {
	//	noise_snr=10*log10((a_rms/noise_an)*(a_rms/noise_an));
	//} else {
	//	noise_snr=0;
	//}

    printf("min:%d\nmax:%d\nave:%.4f\nsdv:%.4f\nmaxamp:%d\na_rms:%f\n", min, max, ave, sdv, maxamp, a_rms);
	//printf("noise_an:%.4f\nSNR:%.4f\n",noise_an,noise_snr);
	printf("denoise_an:%.4f\nSNR:%.4f\n", denoise_an,denoise_snr);
	return EXIT_SUCCESS;
}
