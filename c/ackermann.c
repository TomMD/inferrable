#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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

void ackermann_close()
{
    int fd = open("foobar", O_CREAT);
    if (ackermann(1,2) > 0) {
        return;
    }
    close(fd);
}
