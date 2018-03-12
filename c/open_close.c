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
    do {
        pret = something_external();
    } while (pret < 0 && (errno == EINTR || errno == EAGAIN));
    (void)close(fd);
    return 0;
}

// ------------------------------------------------------------------------------
// Fixed version with models
// ------------------------------------------------------------------------------


// Exactly the same as the model for 'open()'
int myopen(const char* path, int oflag, ...) {
  int* ret = (int*)malloc(sizeof(int));
  if (ret) {
    __set_file_attribute(ret);
    INFER_EXCLUDE_CONDITION(ret < (int*)1); // force result to be > 0
    return (size_t)ret;
  }
  return -1;
}

// Exactly the same as the model for 'close()' except casting to size_t (not
// `long`) and doing so via an intermediate variable (not `(size_t)fildes`).
// Does this imply a bug?
int myclose(int fildes) {
  int n;
  size_t x = (size_t)fildes;
  if (fildes != -1)
    free((int*)x);
  n = __infer_nondet_int();
  if (n > 0)
    return 0;
  else
    return -1;
}

// Fixed false positive using the new models and no other changes.
int open_close_fixed(void)
{
    int           fd;
    int           pret;

    fd = myopen("/dev/random", O_RDONLY);
    do {
        pret = something_external();
    } while (pret < 0 && (errno == EINTR || errno == EAGAIN));
    (void)myclose(fd);
    return 0;
}
