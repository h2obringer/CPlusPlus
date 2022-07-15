#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>


void
SysError(
    char *format,
    ...)
{
    va_list ap;

    fprintf(stderr,"System Call Error(pid %d): ", (int)getpid());

    va_start(ap,format);
    vfprintf(stderr,format,ap);
    va_end(ap);

    fprintf(stderr," (%s)\n", strerror(errno));
    exit(-1);
}


void
SysWarn(
    char *format,
    ...)
{
    va_list ap;

    fprintf(stderr,"System Call Warning(pid %d): ", (int)getpid());

    va_start(ap,format);
    vfprintf(stderr,format,ap);
    va_end(ap);

    fprintf(stderr," (%s)\n", strerror(errno));
}


void
Error(
    char *format,
    ...)
{
    va_list ap;

    fprintf(stderr,"ERROR(pid %d): ", (int)getpid());

    va_start(ap,format);
    vfprintf(stderr,format,ap);
    va_end(ap);

    fprintf(stderr,"\n");
    exit(-2);
}



void
Warn(
    char *format,
    ...)
{
    va_list ap;

    fprintf(stderr,"Warning(pid %d): ", (int)getpid());

    va_start(ap,format);
    vfprintf(stderr,format,ap);
    va_end(ap);

    fprintf(stderr,"\n");
}

