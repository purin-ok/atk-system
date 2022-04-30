#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int dnum;
    int *tm=NULL;
    unsigned char *amp=NULL;
    FILE *fp;
    /* 一部省略 */
    /* #Nで始まるコメント行からデータ個数(dnum)を取得 */
    while(fgets(buf, sizeof(buf), fp) != NULL) {
        if ((buf[0] == '#')&&(buf[1] == 'N')) {
            dnum = atoi(&buf[2]);
            break;
        }
    }
    tm = (int *)malloc(sizeof(int)*dnum); /* 時刻格納領域の割当 */
    amp = (unsigned char *)malloc(sizeof(unsigned char)*dnum); /* 振幅値格納領域の割当 */
    for (i = 0; i < dnum; ) {
        if (fgets(buf, sizeof(buf), fp) == NULL) break;
        if (buf[0] == '#') continue;
        tm[i] = atoi(strtok(buf, ","));
        amp[i] = atoi(strtok(NULL, "\r\n\0"));
        i++;
    }
    fclose(fp);
    /* 時刻,振幅を配列tm,ampに読込完了, この後何か処理を行う */
    free(tm); /* 領域開放 */
    free(amp); /* 領域開放 */
    return EXIT_SUCCESS;
}