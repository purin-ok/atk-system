#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define ROW 16 /* Rows per page */
#define COL 16 /* Columns per row */

int main(int argc, char** argv) {
    int i,j,e;
    int dat[COL];
    long addr=0L;
    FILE* fp;

    if ((argc < 2)||(argc > 3)) {
        fprintf(stderr, "Usage: %s file page\n", argv[0]);
        return EXIT_FAILURE;
    }
    if ((fp = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "File (%s) cannot open\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (argc == 3) {
        addr = atol(argv[2])*ROW*COL;
        fseek(fp, addr, SEEK_CUR);
    }
    for (i = 0; i < ROW; i++, addr += COL) {
        printf("%041X : ", addr);
        for (j = 0; j < COL; j++) {
            if ((dat[j] = fgetc(fp)) == EOF) break;
            printf("%02X ", dat[j]);
        }
        for (e = j; j < COL; j++) printf("   ");
        printf(": ");
        for (j = 0; j < e; j++) putchar(isprint(dat[j]) ? dat[j] : '.');
        putchar('\n');
        if (e != COL) break;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}