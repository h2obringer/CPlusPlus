//********************************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
// 
// Class: Computer Science 442 (Operating Systems)
// Project: The New BASH SHELL (mybash.c)
//
// Description: This program is a subset of the BASH SHELL. It operates 
//   on simple commands typed into the prompt on the terminal. The 
//   command is parsed into tokens with code given by Frank Drews (Professor)
//   in order to populate a CommandData data structure (Parser.h and Parser.c). 
//   The parser code was edited by Randal Mark Obringer to handle appending to a 
//   file for output redirection of commands. The added code is clearly labeled 
//   with inline comments. The code was also edited to allow the command to 
//   become the first argument to allow execution of commands to work properly. 
//   Overall the shell has basic functionality of a regular terminal and 
//   allows for the user to execute simple commands, redirect input/output,
//   and edit environment variables. 
//   
// Input Format: Input to the program must be in the form of a string.
//	The string must only consist of capital or lower case letters, numbers,
//	or the characters: . / - _ = > < |    or >>
//	Spaces will allow the seperation of tokens.
//
// Known Bugs: I was unable to properly set up piping in the program. I tried
//	multiple types of formats and none of them seemed to work for me. 
// 
// NOTE: in order to display debug information you MUST use ALL CAPS for the 
// 	debug variable. Examples: DEBUG=yes , or DEBUG=no
//
//********************************************************************


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser.h"

extern char **environ; 

#define BUFFER_SIZE 1024 //size of the buffer to hold the string of the cwd with
#define CHARACTERS 6 //number of characters to compare for built-in commands
#define OVERWRITE 1 //used to specify overwrite within the setenv system call
#define READ 0 //read end of a pipe
#define WRITE 1 //write end of a pipe
#define FIRST 0 //the first command
#define ZERO 0 //use anywhere a zero is needed for general purposes
#define ONE 1 //use anywhere a one is needed for general purposes
#define NEG_ONE -1 //use anywhere a -one is needed for general purposes
#define FIRST_ARGUMENT 2 //account for adding the command as the first argument
#define PIPE_SIZE 2 //account for read and write end of a pipe

/*LOCAL ROUTINE PROTOTYPES************************************************************/
static int check_for_equalSign(char * word);
static void handle_assignment(char* split_me);
static int checkIfBuiltIn(struct CommandData* cd);
static void execute_set();
static void execute_cd(struct CommandData* cd);
static void execute_exit();
static void execute_pwd();
static void executeBuiltIn(struct CommandData* cd);
static void show_debug_information(struct CommandData* cd);
static void set_terminal(void);
/*************************************************************************************/

/*FUNCTION IMPLEMENTATIONS************************************************************/
/****************************************************** 
check_for_equalSign - check if the word (argument) 
   contains the = character. return 1 if it does, 0 if not

   Arguments: word - character string to check
*******************************************************/
static int check_for_equalSign(char * word){
  int i;
  for(i=ZERO;word[i]!='\0';++i){
    if(word[i]=='='){
      return ONE;
    }
  }
  return ZERO;
}

/****************************************************** 
handle_assignment - in the case of an environment variable
  assignment, this function will split the split_me (argument)
  character string into a variable and a value. The variable 
  is made an environment variable and the value is assigned to the 
  variable. If the variable exists it will be overwritten.
  This function negates needing to edit the parser code.

  Arguments: split_me - the character string to split and perform
  an environment assignment on.
  
*******************************************************/
static void handle_assignment(char* split_me){
  char* variable=malloc(BUFFER_SIZE);
  char* value=malloc(BUFFER_SIZE);
  variable = strtok(split_me,"=");
  value = strtok(NULL,"=");
  if(setenv(variable,value,OVERWRITE)!=0){
    printf("Error setting variable: %s\n",variable);
  }
  
  if(strncmp(variable,"DEBUG",CHARACTERS)==ZERO){
    if(strncmp(getenv("DEBUG"),"yes",CHARACTERS)==ZERO){
      printf("Debugging is on\n\n");
    }else if(strncmp(getenv("DEBUG"),"no",CHARACTERS)==ZERO){
      printf("Debugging is off\n\n");
    }
  }
}

/****************************************************** 
checkIfBuiltIn - checks if the inputed command into the 
  program is a built-in command (needs to be executed by 
  the parent process itself). Checks for assignment, exit,
  cd, pwd, and set. Returns 1 if it is a built-in command
  and 0 if not.

  Arguments: cd - the CommandData structure used to retrieve
  the input command to the program
*******************************************************/
static int checkIfBuiltIn(struct CommandData* cd){
  int equalSign=check_for_equalSign(cd->TheCommands[FIRST].command);

  if(equalSign==ONE){ /*check for assignment first*/
    handle_assignment(cd->TheCommands[FIRST].command);
    return ONE;
  }
  if((strncmp(cd->TheCommands[FIRST].command,"exit",CHARACTERS)==ZERO)||
     (strncmp(cd->TheCommands[FIRST].command,"cd",CHARACTERS)==ZERO)||
     (strncmp(cd->TheCommands[FIRST].command,"pwd",CHARACTERS)==ZERO)||
     (strncmp(cd->TheCommands[FIRST].command,"set",CHARACTERS)==ZERO)){
    return ONE;
  }else{
    return ZERO;
  }
}

/****************************************************** 
execute_set - outputs the global and local environment
  variables of the current process. Effectively implements
  the "set" built-in command.
*******************************************************/
static void execute_set(){
  int a;
  for(a=ZERO;environ[a]!=NULL;a++){ //show environment
    printf("%s\n",environ[a]);
  }
}

/****************************************************** 
execute_cd - change the current working directory to 
  of the argument of the command which is given by cd, the 
  argument to the function. If the command has no argument,
  the HOME directory will become the current working directory.
  Effectively implements the "cd" built-in command.
  
  Arguments: cd - the CommandData structure used to retrieve
  the input command to the program
*******************************************************/
static void execute_cd(struct CommandData* cd){
  if(cd->TheCommands[FIRST].numargs==ONE){ //no arguments for cd to execute
    if(chdir(getenv("HOME"))!=0){
      printf("Failed to change to the HOME directory\n");
    }
  }else if(cd->TheCommands[FIRST].numargs==FIRST_ARGUMENT){
    if(chdir(cd->TheCommands[FIRST].args[ONE])!=0){
      printf("Failed to change directories\n");
    }
  }
}

/****************************************************** 
execute_exit - exit out of the program (the shell).
  Effectively implements the "exit" built-in command.
*******************************************************/
static void execute_exit(){
  exit(ZERO);
}

/****************************************************** 
execute_pwc - print out the PWD environment variable.
  Effectively implements the "pwd" built-in command.
*******************************************************/
static void execute_pwd(){
  printf("%s\n",getenv("PWD"));
}


/****************************************************** 
executeBuiltIn - in the case that the command input to the 
  program is a built-in command, the function will choose
  the correct command to execute. 

  Arguments: cd - the structure holding the input command 
    to the program. The command will be compared against
    the built-in commands in order to choose the correct one
    to execute.
*******************************************************/
static void executeBuiltIn(struct CommandData* cd){
  if(strncmp(cd->TheCommands[FIRST].command,"set",CHARACTERS)==ZERO){
    execute_set();
  }else if(strncmp(cd->TheCommands[FIRST].command,"cd",CHARACTERS)==ZERO){
    execute_cd(cd);
  }else if(strncmp(cd->TheCommands[FIRST].command,"exit",CHARACTERS)==ZERO){
    execute_exit();
  }else if(strncmp(cd->TheCommands[FIRST].command,"pwd",CHARACTERS)==ZERO){
    execute_pwd();
  }
}

/****************************************************** 
show_debug_information - print out to the terminal all of 
  the data held within cd (the argument) as well as the
  environment variables to help the programmer or user better
  understand the processes of the program. 

  Arguments: cd - the data to print to the terminal
*******************************************************/
static void show_debug_information(struct CommandData* cd){
  int l,m;

  execute_set(cd); //show environment data

  printf("\nNumber of simple commands : %d\n",cd->numcommands);
  for(l=ZERO;l<cd->numcommands;l++){
    printf("command%d     : ",(l+ONE));
    if(cd->TheCommands[l].command == NULL){
      printf("(NULL)\n");
    }else{
      printf("%s\n",cd->TheCommands[l].command);
    }
    for(m=ZERO;m<cd->TheCommands[l].numargs;m++){
      printf("arg[%d]       : %s\n",m,cd->TheCommands[l].args[m]);
    }
  }
  
  printf("Input file   : ");
  if(cd->infile == NULL){
    printf("(NULL)\n");
  }else{
    printf("%s\n",cd->infile);
  }

  printf("Output file  : ");
  if(cd->outfile == NULL){
    printf("(NULL)\n");
  }else{
    printf("%s\n",cd->outfile);
  }

  printf("Background option : ");
  if(cd->background == ZERO){
    printf("OFF\n");
  }else{
    printf("ON\n");
  }

  printf("Built-in command  : ");
  if(checkIfBuiltIn(cd)==ONE){
    printf("YES\n\n");
  }else{
    printf("NO\n\n");
  }
}
/****************************************************** 
set_terminal - sets the DEBUG environment variable (local) 
  to default at "no". Clears the terminal and prints to the
  terminal that the Shell is in fact being run.
*******************************************************/
static void set_terminal(void){
  setenv("DEBUG","no",OVERWRITE);

  if(system("clear")){}; //clear the terminal to only show my shell
  printf("\n The RMO Bash Shell - CS 442 (Operating Systems)\n");
  printf("          Randal Mark Obringer\n\n");
}



/*MAIN FUNCTION OF THE PROGRAM*************************************************/
int main(int argc, char *argv[]){
  int i; //used for the for loop
  int restore_in_fd=dup(STDIN_FILENO); //SAVE STANDARD IN
  int restore_out_fd=dup(STDOUT_FILENO); //SAVE STANDARD OUT
  int in_fd=restore_in_fd; //input file descriptor
  int out_fd=restore_out_fd; //output file descriptor

/*rights of the file. read rights given to user/group/others -- write rights given to user*/
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 

  char* command_line = malloc(BUFFER_SIZE); //will hold inputted commands from terminal
  struct CommandData* data_command = malloc(BUFFER_SIZE); //will hold the data from the command
  char* current_working_directory = malloc(BUFFER_SIZE); //will hold the current working directory
  pid_t ret_pid; //process identification
  int status; //status of process

  set_terminal();

  

  while(ONE){

    /*OUTPUT PROMPT*/
    if(getcwd(current_working_directory,BUFFER_SIZE)==NULL){
      printf("Error recieving the current working directory\n");
    }
    printf("%s>",current_working_directory); //print prompt
    if(gets(command_line)==NULL){ //get command
      printf("Recieved no command\n");
    }

    if(ParseCommandLine(command_line, data_command)!=ONE){ 
      printf("Unparsable Command Given\n");
    }
    if(checkIfBuiltIn(data_command)==ONE){
      executeBuiltIn(data_command);
    }else{
      if(fork()==ZERO){
        for (i = ZERO; i < data_command->numcommands; ++i) {
          if(i==ZERO){
            if(data_command->infile!=NULL){
              in_fd=open(data_command->infile,O_RDONLY,READ);
              if(dup2(in_fd,STDIN_FILENO)==NEG_ONE){
                printf("Failed to redirect input to file\n");
              }
              if(close(in_fd)!=ZERO){
                printf("Failed to close file descriptor\n");
              }
            }else{
              in_fd=dup(restore_in_fd);
            }
          }
          
          if(i==data_command->numcommands-ONE){
            if(data_command->outfile!=NULL){
              if(data_command->append_it==ZERO){ //no append
                out_fd=open(data_command->outfile, O_WRONLY | O_CREAT | O_TRUNC, mode);
              }else if(data_command->append_it==ONE){ //append
                out_fd=open(data_command->outfile, O_APPEND | O_WRONLY | O_CREAT, mode);
              }
              if(dup2(out_fd,STDOUT_FILENO)==NEG_ONE){
                printf("Failed to redirect output to file\n");
              }
              if(close(out_fd)!=ZERO){
                printf("Failed to close file descriptor\n");
              }
            }else{
              out_fd=dup(restore_out_fd);
            }
          }
          if((i>ZERO)&&(i<data_command->numcommands-ONE)){
            int pipefd[PIPE_SIZE];
            if(pipe(pipefd)!=ZERO){
              printf("Failed to create pipe\n");
            }
            if(fork()==ZERO){
              if(close(pipefd[WRITE])!=ZERO){
                printf("Failed to close write file descriptor\n");
              }
              if(dup2(pipefd[READ],STDIN_FILENO)==NEG_ONE){
                printf("Failed to redirect pipe\n");
              }
              if(close(pipefd[READ])!=ZERO){
                printf("Failed to close read file descriptor\n");
              }
              if(execvp(data_command->TheCommands[i].command,data_command->TheCommands[i].args)==NEG_ONE){
                printf("Command didn't work\n");
              }
            }else{
              if(close(pipefd[READ])!=ZERO){
                printf("Failed to close read file descriptor\n");
              }
              if(dup2(pipefd[WRITE],STDOUT_FILENO)==NEG_ONE){
                printf("Failed to redirect pipe\n");
              }
              if(close(pipefd[WRITE])!=ZERO){
                printf("Failed to close write file descriptor\n");
              }
              ret_pid=wait(&status);
            }
          }else{
            if(execvp(data_command->TheCommands[i].command,data_command->TheCommands[i].args)==NEG_ONE){
              printf("Command didn't work\n");
            }
          }
        }

      }else{ //parent process
        if(data_command->background==ZERO){
          ret_pid=wait(&status);
          in_fd=restore_in_fd; /*RESTORE STDIN*/
          out_fd=restore_out_fd; /*RESTORE STDOUT*/
        }
      }
    }//end execute command

    if(strncmp(getenv("DEBUG"),"yes",CHARACTERS)==ZERO){
      show_debug_information(data_command);
    }
  }//END LOOP HERE
  
  exit(ZERO);
}
