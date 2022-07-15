/*
 * Provided by Professor Fank Drews
 * CS 442/542
 * FQ 11 - Ohio University
 * 
 * Student Name: Randal Mark Obringer 
 * Date Last Modified: ~2012
 */

/* the states */
#define COMMAND 1
#define ARG 2
#define INFILE 3
#define OUTFILE 4
#define UNDEF 5

struct Command {
	char *command;
	char *args[11];
	int numargs;
};

struct CommandData {
	struct Command TheCommands[20];  /* the commands to be
          executed.  TheCommands[0] is the first command
          to be executed.  Its output is piped to
          TheCommands[1], etc. */
	int numcommands; /* the number of commands in the above array */
	char *infile;   /* the file for input redirection, NULL if none */
	char *outfile;  /* the file for output redirection, NULL if none */
	int  background;  /* 0 if process is to run in foreground, 1 if in background */
	int append_it; //ADDED THIS, 1 for append, 0 if no append **Randal Obringer
};


extern int ParseCommandLine(char *line, struct CommandData *data); 

