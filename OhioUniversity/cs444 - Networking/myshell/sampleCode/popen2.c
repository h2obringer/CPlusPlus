/* simple popen example */
/* give a file listing of each directory given */

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>


static void
list_dir(
    char *dirname)
{
    FILE *f;
    char *cmd;
    char *pch;
    char line[256];
    
    cmd = malloc(strlen(dirname+10));
    sprintf(cmd,"/bin/ls %s\n", dirname);

    f = popen(cmd, "r");

    printf("Result for directory '%s':\n", dirname);
    while ((fgets(line,sizeof(line),f)) != NULL) {
	if ((pch = strchr(line,'\n')) != NULL) 
	    *pch = '\00';  // nuke the newline
	puts(line);
    }

    pclose(f);
}




int
main(
    int argc,
    char *argv[])
{
    int i;
    
    if (argc < 2) {
	fprintf(stderr,"Usage: %s dir [dirs]'\n", argv[0]);
	exit(-1);
    }

    for (i=1; i < argc; ++i)
	list_dir(argv[i]);

    exit(0);
}
