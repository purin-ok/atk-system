#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FINISH 0
#define MAX_SAI 1

int sai() {
  //
  return (rand() / (MAX_SAI)) + 1;
}

int odd_or_even(int sai1, int sai2) {
  //偶数か奇数か求める.丁：0,半：1を返す
  return (sai1 + sai2) % 2;
}

int main() {
  //
  int sai1, sai2, continue_flag;
  srand((unsigned)time(NULL));
  sai1 = sai();
  sai2 = sai();
  if (odd_or_even(sai1, sai2)) {
  }
}