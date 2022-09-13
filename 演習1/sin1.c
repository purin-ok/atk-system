/* sin波のCSVデータ生成 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pi.h" /* 付録B参照 */
//演習1－1
double rad(double r){

return 0;
}

//演習1－2
double saw(double e){

return 0;
}

int main(void) {
    double amp,dif,pi2,rad;

    pi2 = 2*PI;
    dif = PI/180.0;
    for (rad = -pi2; rad <= pi2; rad += dif) {
        amp = sin(rad);
        printf("%6.3f, %6.3f\n", rad, amp);
    }
    return EXIT_SUCCESS;
}