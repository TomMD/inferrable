#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern int something_external();

// False positive
int open_close(void)
{
    int           fd;
    int           pret;

    fd = open("/dev/random", O_RDONLY);
    if (fd == -1) {
        return 0;
    }
    // This do-while loop seems to break the analysis
    // if we set errno at some point to any value:
    //
    // > errno = EAGAIN;
    //
    // or
    //
    // > errno = EINVAL;
    //
    // then the error disappers
    do {
        pret = something_external();
    } while (pret < 0 && (errno == EINTR || errno == EAGAIN)); // XXX because errno never changes?!!?
    if (pret != 1) {
        (void) close(fd);
        return -1;
    }
    return close(fd);
}
