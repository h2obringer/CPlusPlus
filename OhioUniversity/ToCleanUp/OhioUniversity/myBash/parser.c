/*
 * Parser.c provided by Professor Frank Drews
 * CS 442/542
 * WQ 12 - Ohio University
 * 
 * Student Name: Randal Mark Obringer 
 *	*Added some code. My additions are labeled in line below.
 *
 * Date Last Modified: ~2012
 */

#include <stdio.h>
#include <string.h> /* for strdup */
#include "parser.h"

static int IsAlphaNum(char c)  /* is this a valid char for a pathname or filename? */
{
	if (c >= 'A' && c <= 'Z') return 1;
	if (c >= 'a' && c <= 'z') return 1;
	if (c >= '0' && c <= '9') return 1;
	if (c == '.' || c == '_' || c == '/' || c == '-' || c == '=') return 1;
	return 0;
}

/************** COPYWORD **************
  This function copies a word (token) to the appropriate field
  of the struct CommandData data, and resets state. It
  returns 1 if successful, 0 if it detects an error.
  This is called from the function ParseCommandLine
**************************************************/
static int CopyWord(char *token, struct CommandData *data, int *state)
{
    switch (*state) {
		case COMMAND: //CALEB CODE ADDITION (not Randal Obringer)
			data->TheCommands[data->numcommands].command = strdup(token);
			data->TheCommands[data->numcommands].numargs = 0;
				/*make the first argument the command*/
			data->TheCommands[data->numcommands].args[0] = strdup(token);
				/*always make argument array NULL terminating*/
			data->TheCommands[data->numcommands].args[1] = NULL;
				/*edit number of arguments to account for adding command as an argument*/
			data->TheCommands[data->numcommands].numargs += 1;
			*state = ARG;
			return 1;
		case ARG: 
            data->TheCommands[data->numcommands].args[data->TheCommands[data->numcommands].numargs] = strdup(token);
                /*if more arguments added then still makes sure the array is NULL terminating*/
            data->TheCommands[data->numcommands].args[data->TheCommands[data->numcommands].numargs+1] = NULL; 
            data->TheCommands[data->numcommands].numargs++;
            if (data->TheCommands[data->numcommands].numargs > 10) {
				fprintf(stderr,"Error, too many arguments\n");
                return 0;
			}
            return 1;
        case INFILE: 
            if (data->infile != NULL) {
                fprintf(stderr,"Error, stdin redirected twice\n");
                return 0;
			}
			data->infile = strdup(token);
            *state = UNDEF;
            return 1;
        case OUTFILE: 
            if (data->outfile != NULL) {
                fprintf(stderr,"Error, stdout is redirected twice\n");
                return 0;
			}
			data->outfile = strdup(token);
            *state = UNDEF;
            return 1; 
        case UNDEF:
            fprintf(stderr,"Error, bad syntax on the command line\n");
            return 0;
    };
	
    /* we should never get here */
    fprintf(stderr,"Error in CopyWord\n");
    return 0;
}

/********* PARSECOMMANDLINE ***********************************
   This function parses the commandline line, and populates
   the struct CommandData data.  

   Returns 1 if it successfully parsed the command line,
   Returns 0 if it found an error 

   Logic - it passes through the while loop once for each character
   in the line.
   It copies string names into token, and when it gets to the end,
   it calls CopyWord to copy token to the appropriate field in data based on the
   state.   White spaces are ignored, the < and > characters change
   the state, & sets the background flag to 1.
*************************************************************/
int ParseCommandLine(char *line, struct CommandData *data)
{
    int i, j;
    char token[256];
    int inaword;
    int state;

    i=0;
    j=0;
    inaword = 0;
    state = COMMAND;
    data->numcommands = 0;
    data->TheCommands[0].command=NULL;
    data->infile = data->outfile = NULL;
    data->background = 0;
    data->append_it = 0; //ADD THIS TO MAKE SURE INITIALIZATION


    while (line[i] != '\0' && line[i] != '\n') {
        if (IsAlphaNum(line[i])) {
            if (inaword) {
				token[j++]=line[i];
            } else { /* starting a new word */
				j = 0;
                token[j++] = line[i];
                inaword = 1;
            }
        } else {  /* not an alphanumeric character */
            if (inaword) { /* we have found the end of a token */
				token[j]='\0';
                inaword = 0;
                if (CopyWord(token,data,&state)==0) //PICK UP FROM HERE
					return 0;
			}
                     
            switch (line[i]) {
                case ' ': 
                    break;
				case '>': 
					/*ADDED CODE SEGMENT TO SUPPORT APPENDING TO FILES*/
					/*NOTE: append_it was added to the CommandData struct to support this*/
					/*RANDAL MARK OBRINGER*/
                    if(line[i+1]=='>'){
						i+=1; //if next code segment was infact '>' then skip over it
						data->append_it=1;
                    }else{
						data->append_it=0;
                    }
					/*END CODE ADDITION SEGMENT - RANDAL MARK OBRINGER*/
                    if (state == OUTFILE || state == INFILE || state == COMMAND) {
                        fprintf(stderr, "Error, bad syntax on the command line\n");
                        return 0;
					}
                    state = OUTFILE;
					break;
                case '<': 
                    if (state == OUTFILE || state == INFILE || state == COMMAND) {
                        fprintf(stderr, "Error, bad syntax on the command line\n");
                        return 0;
					}
                    state = INFILE;
					break;
				case '|':
					if (state == COMMAND || state == INFILE || state == OUTFILE) {
                        fprintf(stderr, "Error, bad syntax on the command line\n");
                        return 0;
					}
					data->numcommands++;
					state = COMMAND;
					data->TheCommands[data->numcommands].command = NULL;
					data->TheCommands[data->numcommands].numargs = 0;
					break;
                   
                case '&': 
                    if (state == OUTFILE || state == INFILE || state == COMMAND) {
                        fprintf(stderr, "Error, bad syntax on the command line\n");    
                        return 0;
					}
                    data->background = 1;
                    break;
                default : 
                    fprintf(stderr,"Error, invalid character on command line %c\n",line[i]);
                    return 0;
            }; /* end of switch */
        } /* end of else */
        i++;
    } /* end of while loop */
    /* we have gotten to the end of the line, there may still be a
       string that has not been processed */

    if (inaword) {
        token[j]='\0';
        if (CopyWord(token,data,&state)==0) {
            return 0;
		}
    }

    /* do some final error checking */
    if (state == INFILE && data->infile == NULL) {
        fprintf(stderr,"Error, < but no filename\n");
        return 0;
    }
    if (state == OUTFILE && data->outfile == NULL) {
        fprintf(stderr,"Error, > but no filename\n");
        return 0;
    }
    if (state == COMMAND) {
      fprintf(stderr,"Error, bad syntax on command line\n");
      return 0;
    }
      
    if (data->TheCommands[0].command == NULL) {
        fprintf(stderr, "Error, no command\n");
        return 0;
    }
    data->numcommands++;
    return 1;
}



       
  


