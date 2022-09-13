/* sin�g��CSV�f�[�^���� */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pi.h" /* �t�^B�Q�� */
//���K1�|1
double rad(double r){
	double mod;
	mod = fmod(r,2*PI);
	if(r<0)mod = mod+2*PI;
return mod;
}

//���K1�|2
double saw(double e){
    double saw_blead;
    saw_blead = 1 - rad(e) / PI;
return saw_blead;
}

int main(void) {
    double amp,dif,pi2,radi;

    pi2 = 2*PI;
    dif = PI/180.0;
    for (radi = 0; radi <= 2*pi2; radi += dif) {
        amp = saw(radi);
        printf("%6.3f, %6.3f\n", radi, amp);
    }
    return EXIT_SUCCESS;
}