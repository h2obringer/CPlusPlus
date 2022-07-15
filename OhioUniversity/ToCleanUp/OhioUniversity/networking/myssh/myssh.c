/****************************************
* Author: Randal Mark Obringer
* CoAuthor: Dr. Ostermann
*
* Description: This is the client program of the 
*   myssh project. It must be run after and only
*   after starting the server program.
*
*
*****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libnet.h"


#define LINELEN         256    /*size of a line*/
#define BUFFERSIZE	4092   /*size of the buffer to use*/

static int startClient(char *host, char *service);
static int debug=0;

/*------------------------------------------------------------------------
 * main -client program
 *------------------------------------------------------------------------
 */
int main(int argc, char **argv){
	int i=0;
	char    *host = "localhost";    /* host to use if none supplied */
	char    *service = "5000";      /* default service name         */

	for(i=0;i<argc;++i){
		/*SPECIFY THE PORT OPTION*/
		if(strcmp(argv[i],"-port")==0){	
			if(i+1<argc){
				if(strcmp(argv[i+1],"-")==0){
					service=NULL;
				}else{
					service=argv[i+1];
				}
				++i;
			}
		}

		/*SPECIFY THE HOST OPTION*/
		else if(strcmp(argv[i],"-host")==0){
			if(i+1<argc){
				host=argv[i+1];
				++i;
			}
		}

		/*DEBUG OPTION*/
		else if(strcmp(argv[i],"-d")==0){
			++debug;
		}

		/*HELP OPTION*/            
		else if(strcmp(argv[i],"-h")==0){ 
			mysshHelp(); /*myssh print help function*/
			printf("Arguments given were:\n");
			for (i=1; i < argc; ++i) {
				printf("argv[%d]: '%s'\n", i, argv[i]);
			}
			exit(1);
		}
	}

	startClient(host, service); /*send the password then send command and read its output*/

	exit(1);
}

/*------------------------------------------------------------------------
 * startClient - send the password then send command and read its output
 *------------------------------------------------------------------------
 */
int startClient(char *host, char *service){
	int j;
	char buf[LINELEN+1];	/* buffer for one line of text  */
	int s; /* socket descriptor */
	int len; /*size of read or written data*/
	char password[LINELEN+1]; /*string to hold the password that the server is requesting*/
	char confirmation[LINELEN+1]; /*string to hold the confirmation that a good password was received*/

	confirmation[0] = 'N';/*initialize the string*/
	confirmation[1] = 'O';
	confirmation[2] = '\00';

	s = connectTCP(host, service); /* connect as a Unix file descriptor (fd) */

	while(strcmp((char*)confirmation,"YES")!=0){ /*keep sending passwords until it is correct by the server's standards*/
		fprintf(stdout,"Enter the password:\n>>");
		fgets((char*)password, sizeof(password), stdin); /*retreive the password to send to the server*/
		if(debug>0){/*reassure the password you entered was indeed what you entered*/
			fprintf(stdout,"The password you entered was: %s\n",password);
		}
		password[strlen(password)-1]='\00'; /*null terminate the password*/
		strncat(password,"\r\n",sizeof((char*)password));   /* tack on the official end of line sequence */
		encrypt_data(password); /*encrypt the password*/
		write(s, password, strlen(password)); /*finally send over the password*/

		len=read(s,confirmation,sizeof(confirmation)); /*read a confirmation of the password*/
		decrypt_data((char*)confirmation);  /*decrypt confirmation*/
		
		for(j=0;confirmation[j]!=NULL;++j){ /*NULL terminate the confirmation for comparison (if good we leave the while loop)*/
			if(confirmation[j]=='\r'){
				confirmation[j]='\00';
				break;
			}
		}
	}
	if(debug>0){
		fprintf(stdout,"The password was accepted!\n");
	}
	fprintf(stdout,"Enter a command:\n");
	fprintf(stdout,">>");/*print a prompt to tell us we are expecting something from the client at their terminal*/
	if (fgets(buf, sizeof(buf), stdin) == NULL)
		exit(0);

	/* remove the newline */
	buf[strlen(buf)-1] = '\00';

	/* send the characters down the TCP connection */
	strncat(buf,"\r\n",sizeof(buf));   /* tack on the official end of line sequence */
	encrypt_data(buf);
	write(s,buf,BUFFERSIZE);

	/* read back an answer */
	while(1){
		len=read(s,buf,sizeof(buf)); /*read a line from the executed command on the server side*/
		decrypt_data(buf); /*decrypt that line*/
		if (len == 0){ /*exit if EOF*/
			break;
		}else if(len == -1){/*print error message if something went wrong*/
			perror("read");
		}
		
		/*buf[strlen(buf)] = '\00';*/
		for(j=0;buf[j]!=NULL;++j){/*NULL terminate the line*/
			if((buf[j]=='\r')||(buf[j]=='\n')){ /*get rid of the return carriage and new line characters*/
				buf[j]='\00';
			}
		}
		fprintf(stdout,"%s\n",buf); /*finally print out the line received from the executed command*/
	}

	return(0);
}
