#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

void mysshdHelp(void){
  fprintf(stderr, "\n\nmysshd help:\n\n");
  fprintf(stderr, "Usage: ./myssh [-d] [-h] [-port P]\n");
  fprintf(stderr, "[-d]: debug mode.\n");
  fprintf(stderr, "[-h]: print the help screen and exit.\n");
  fprintf(stderr, "[-port] P: set up a port on P (Use '-' to specify a random port.\n\n");
  fprintf(stderr, "myssh defaults to port 5000\n");
}

void mysshHelp(void){
  fprintf(stderr, "\n\nmyssh help:\n\n");
  fprintf(stderr, "Usage: ./myssh [-d] [-e] [-h] [-port P]\n");
  fprintf(stderr, "[-d]: debug mode.\n");
  fprintf(stderr, "[-h]: print the help screen and exit.\n");
  fprintf(stderr, "[-host] H: set up a host on H.\n");
  fprintf(stderr, "[-port] P: set up a port on P (Use '-' to specify a random port.\n");
}
