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
	int tm[DATANUM], amp[DATANUM], no_noise[DATANUM], aout[DATANUM];
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
		no_noise[i] = atoi(strtok(NULL, ","));
		amp[i] = atoi(strtok(NULL, "\r\n\0"));
		i++;
	}
	fclose(fp);

	printf("%4d, %d, %d, \n", tm[0], no_noise[0], amp[0]);

	for (i=1; i < DATANUM-1; i++) {
		aout[i-1]=(amp[i-1]+amp[i]+amp[i+1])/3;
		printf("%4d, %d, %d, %4d\n", tm[i], no_noise[i], amp[i], aout[i-1]);
	}
	printf("%4d, %d, %d, \n", tm[i], no_noise[i], amp[i]);

	return EXIT_SUCCESS;
}
