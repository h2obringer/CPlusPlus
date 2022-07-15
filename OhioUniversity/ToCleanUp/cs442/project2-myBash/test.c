#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //Needed for getcwd()
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser.h"

extern char **environ; 

#define BUFFER_SIZE 1024 //size of the buffer to hold the string of the cwd with
#define CHARACTERS 6 //number of characters to compare for built-in commands
#define OVERWRITE 1
#define READ 0
#define WRITE 1


int main(int argc, char *argv[]){

pid_t pid,ret_pid; //process identification
int i=0;
int j=0;
int status;
/*
if(fork()==0){
  i=1;
  if(fork()==0){
    i=2;
    if(fork()==0){
      i=3;
    }else{
      ret_pid=wait(&status);
    }
  }else{
    ret_pid=wait(&status);
  }
}else{
  ret_pid=wait(&status);
}*/

if(fork()==0){
  for(i=0;i<3;i++){
    if(fork()==0){
      execlp("ls","ls",NULL);
    }else{
      ret_pid=wait(&status);
    }
  }
}else{
  ret_pid=wait(&status);
}

pid=getpid();
printf("pid:%d\n",(int)pid);
printf("%d\n",j);

}
