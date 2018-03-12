#include <stdio.h>


int f()
{
    int *x = malloc(10 * sizeof(int));
    if(NULL != x) {
        free(x);
        return 0;
    } else {
        return -1;
    }
}
