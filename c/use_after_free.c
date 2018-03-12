#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

int correct_detection()
{
    int *x = malloc(10 * sizeof(int));
    if(NULL != x) {
        free(x);
        *x = 10;
        return 0;
    } else {
        return -1;
    }
}

int ackermann(int x, int y)
{
    if(x==0) {
        return y + 1;
    } else if (y == 0) {
        return ackermann(x-1,1);
    } else {
        return ackermann(x-1, ackermann(x,y-1));
    }
}

// I use ackermann to interfere with analysis - this was observed in the wild
// when `external_f` was a string parsing function.
int external_f(const char *str, int e, int *arr)
{
    for(int i=0; i < 100; i++) {
        arr[i] = ackermann(i,2);
    }
    return arr[99];
}

static int
missed_bug(const char *str, unsigned long long opslimit, size_t memlimit, int external_thing)
{
    unsigned char  *fodder;
    size_t          fodder_len;
    int             ret = -1;
    int arr[100] = {0};

    fodder_len = strlen(str);
    memlimit /= 1024U;
    if (opslimit > UINT32_MAX || memlimit > UINT32_MAX ||
        fodder_len >= 1000) {
        errno = EINVAL;
        return -1;
    }
    if ((fodder = (unsigned char *) calloc(fodder_len, 1U)) == NULL) {
        return -1; /* LCOV_EXCL_LINE */
    }
    if (external_f(str, external_thing, arr) != 0) {
        errno = EINVAL;
        ret = -1;
    } else if (arr[1] > 100) {
        ret = 1;
    } else {
        ret = 0;
    }
    free(fodder);
    fodder[0] = 0;

    return ret;
}
