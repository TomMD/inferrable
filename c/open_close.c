#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern int something_external();

int
open_close(void)
{
    int           fd;
    int           pret;

    fd = open("/dev/random", O_RDONLY);
    if (fd == -1) {
        return 0;
    }
    // This do-while loop seems to break the analysis
    // Commenting out the loop (keeping the body) results in a correct analysis
    do {
        pret = something_external();
    } while (pret < 0 && (errno == EINTR || errno == EAGAIN));
    if (pret != 1) {
        (void) close(fd);
        return -1;
    }
    return close(fd);
}
