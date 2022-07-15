#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

/*
 * ====================================================================
 * strerror -- standard C library routine, sometimes missing though
 * ====================================================================
 */
char *
strerror(
    int errnum)
{
    extern char *sys_errlist[];

    return(sys_errlist[errno]);
}




/*
 * ====================================================================
 * errexit -- print syscall error and exit
 * ====================================================================
 */
void
errexit(char *msg, ...)
{
    va_list ap;

    /* make the log entry */
    va_start(ap,msg);
    vfprintf(stderr,msg,ap);
    fprintf(stderr,"  (%d: %s)\n", errno, strerror(errno));
    va_end(ap);

    fflush(stderr);

    exit(1);
}
