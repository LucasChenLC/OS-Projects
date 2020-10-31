#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bicomplex{
    int real1;
    int real2;
    int imaginary1;
    int imaginary2;
}Bicomplex;

typedef struct complex{
    int real;
    int imaginary;
}Complex;


void *SumComplex(void * num) {
    Bicomplex *rnum;
    Complex *ans = (Complex *)malloc(sizeof(Complex));
    rnum = (Bicomplex *)num;
    printf("Summing %d + i%d and %d +i%d\n", rnum->real1, rnum->imaginary1, rnum->real2, rnum->imaginary2);
    ans->real = rnum->real1 + rnum->real2;
    ans->imaginary = rnum->imaginary1 + rnum->imaginary2;
    pthread_exit((void *)ans);
}

int main(int argc, char *argv[]) {
    pthread_t myThread;
    int rc;
    Bicomplex num;
    Complex *z;
    void *ans;
    num.real1 = 1;
    num.real2 = 2;
    num.imaginary1 = 3;
    num.imaginary2 = 4;
    rc = pthread_create(&myThread, NULL, SumComplex, &num);
    if (rc) {
        perror("Failed in calling pthread_create");
        exit(-1);
    }
    pthread_join(myThread, &ans);
    z = (Complex *)ans;
    printf("The ans is %d + i%d", z->real, z->imaginary);
    return 0;
}