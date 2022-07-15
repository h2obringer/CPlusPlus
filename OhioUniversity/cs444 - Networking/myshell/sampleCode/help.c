#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

static void printHelp(void){
  fprintf(stderr, "\n\nmysshell help: Program usage depends on whether a \n");
  fprintf(stderr, "\tserver or a host is desired to be set up\n\n");
  fprintf(stderr, "Usage if server is desired: ./mysshell -t s [-d] [-e] [-h] [-port P]\n");
  fprintf(stderr, "Usage if host is desired: ./mysshell -t h [-d] [-e] [-h] [-host H [port P]]\n\n");
  fprintf(stderr, "Please note that -host and -port options must be the last arguments given.\n\n");
  fprintf(stderr, "-t s: set up a server.\n");
  fprintf(stderr, "-t h: set up a host.\n");
  fprintf(stderr, "[-d]: debug mode.\n");
  fprintf(stderr, "[-e]: set up connection as an echo service instead of as a command prompt.\n");
  fprintf(stderr, "[-h]: print the help screen and exit.\n");
  fprintf(stderr, "[-host] H: set up a host on H.\n");
  fprintf(stderr, "[-port] P: set up a port on P (Use '-' to specify a random port.\n");
}
