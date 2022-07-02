/*
参考文献:http://www.t-net.ne.jp/~cyfis/c/stdlib/system.html

*/
#include <stdio.h>
#include <stdlib.h>
int main() {
  char load[] = "12";
  char path[] =
      "\"cd CSV && hello.exe 12 && cd .. && hello.exe"
      "\"";
  system(path);
  return 0;
}