/* tcpecho.c - main, tcpecho */

#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "libnet.h"

int handleCommands(int fd,char* pword){
  int j;
  char buf[BUFSIZ];
  int cc;
  FILE *f;
  char *cmd;
  char *pch;
  char line[256];
  char compare[BUFSIZ];
  char confirmation[BUFSIZ];
  compare[0]='N';
  compare[1]='O';
  compare[2]='\00';
  confirmation[0]='N';
  confirmation[1]='O';
  confirmation[2]='\00';
  while(1){
    fprintf(stdout,"compare string = %s before reading it\n",compare);
    cc=read(fd,compare,sizeof(compare)); /*read in the password*/
    decrypt_data(compare); /*decrypt the password*/
    for(j=0;compare[j]!=NULL;++j){ /*NULL terminate the password*/
      if((compare[j]=='\r')||(compare[j]=='\n')){
        compare[j]='\00';
      }
    }
    if(strcmp(pword,compare)==0){
      fprintf(stdout,"Send YES!\n");
      confirmation[0]='Y';
      confirmation[1]='E';
      confirmation[2]='S';
      confirmation[3]='\r';
      confirmation[4]='\n';
      confirmation[5]='\00';
      encrypt_data(confirmation);
      write(fd, (char*)confirmation, strlen(confirmation));
      break;
    }
  }

  cc = read(fd, buf, sizeof buf);
  fprintf(stdout,"before decrypting command: %s\n",buf);
  decrypt_data(buf);
  fprintf(stdout,"after decrypting command: %s\n", buf);
	
    
  if (cc < 0)
  {
      Error("myssh read: %s\n", strerror(errno));
  } 
  else if( cc != 0 ) 
  {
    cmd = malloc(strlen(buf+10));
    for(j=0;buf[j]!=NULL;++j){
      if(buf[j]=='\r'){
        fprintf(stdout,"Found it");
        buf[j]='\00';
        break;
      }
    }

    sprintf(cmd,"/bin/%s\n", buf);

    f = popen(cmd, "r");

    while ((fgets(line,sizeof(line),f)) != NULL) {
	if ((pch = strchr(line,'\n')) != NULL) 
	    *pch = '\00';  /* nuke the newline*/
	puts(line); /*display on the server side before adding official end of line characters*/
        strncat(line,"\r\n",sizeof(line));/*add end of line characters*/ /*was sizeof buf*/
        fprintf(stdout,"before encrypting: %s\n",line);
        encrypt_data(line);
        fprintf(stdout,"after encrypting: %s\n",line);
        write(fd, line, strlen(line));/*send them to the host*/
    }

    pclose(f);
    close(fd);
    fprintf(stdout,"closed the file descriptor\n");
  }
  return 0;
}
