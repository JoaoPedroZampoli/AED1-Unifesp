#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int i, j;
    int *p, *q;
    i = 2;
    j = 1;
    p = &i;
    q = &j;
    q = p;
    printf("%d", *q);   
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int i = 2, j = 1;
    int *p = &i, *q = &j;
    //q = p;
    *q = *p;
    printf("%d\n", *q);
    printf("%d\n", i);
    printf("%d\n", j);  
}
*/