/* 必要なヘッダの読み込みを行うこと */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFSIZE 80 /* 読込バッファサイズ */
#define DATANUM 101 /* 読込データ個数 */

int main(int argc, char **argv) {
    int n;
    int tm[DATANUM],amp[DATANUM];
    /* 引数のチェックとargv[1]で指定されたファイルを開く処理を書くこと */
        int ain,aout,nmax;
    double err;
    char buf[BUFSIZE];
    FILE *fp;

    if (argc !=3) {
	fprintf(stderr, "Usage: %s infile max_noise\n", argv[0]);
	return EXIT_FAILURE;
	}
    if ((fp = fopen(argv[1],"r")) == NULL){ /* readモードでテキストファイルを開く */
	fprintf(stderr, "File: %s cannot open\n",argv[1]);
	return EXIT_FAILURE;
	}
    for (n = 0; n < DATANUM; ) { /* ここに　n++ がない理由を考えよ */
    //ここにあると，二個目のif文のcontinue処理をした場合に，n+1されてしまい，配列にうまく読み込めない
        if (fgets(buf, sizeof(buf), fp) == NULL) break;
        if (buf[0] == '#') {
            printf("%s", buf);
            continue;
        }
        tm[n] = atoi(strtok(buf, ","));
        amp[n] = atoi(strtok(NULL, "\r\n\0"));
        n++; /* ここに n++ がある理由を考えよ *//*コメント文字の処理を飛ばすため*/
    }
    fclose(fp);
    /* 時刻,振幅を配列t,ampに読込完了, これ以降で信号処理を行う */
}