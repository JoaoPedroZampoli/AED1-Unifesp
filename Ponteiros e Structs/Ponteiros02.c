#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int *p, i;
    p = &i;

    i = 1;
    printf("*p = %d\n", *p);
    *p = 2;
    printf("*p = %d\n", *p);
}