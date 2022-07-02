#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFSIZE 80 /* ????o?b?t?@?T?C?Y */
#define DATANUM 101
#define ROUND(x) ((x > 0) ? (x + 0.5) : (x - 0.5))

int main(int argc, char **argv){
	char buf[BUFSIZE];
	int i;
	int tm[DATANUM], no_noise[DATANUM], amp[DATANUM], aout[DATANUM];
	double amp_num;
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
		return EXIT_FAILURE;
	}

	if ((fp = fopen(argv[1], "r")) == NULL) { /* read???[?h??e?L?X?g?t?@?C?????J?? */
	fprintf(stderr, "File: %s cannot open\n", argv[1]);
	return EXIT_SUCCESS;
	}

	for (i=0; i < DATANUM;){
		if(fgets(buf, sizeof(buf), fp) == NULL) break;
		if(buf[0] == '#') {
			printf("%s", buf);
			continue;
		}
		tm[i] = atoi(strtok(buf,","));
		no_noise[i] = atoi(strtok(NULL,","));
		amp[i] = atoi(strtok(NULL, "\r\n\0"));
		i++;
	}
	fclose(fp);
		amp_num=amp[0]+amp[1]+amp[2]+amp[3];	
	for (i=0; i < DATANUM; i++) {
		amp_num += amp[i+4];
		aout[i] = ROUND(amp_num * 0.2);
		if(i >= 2 && i < DATANUM-2 ) {
			printf("%4d, %4d, %4d, %4d\n", tm[i], no_noise[i], amp[i], aout[i-2]);
		} else {
			printf("%4d, %4d, %4d, \n", tm[i], no_noise[i], amp[i]);

		}
		amp_num -= amp[i];
	}
	return EXIT_SUCCESS;
}
