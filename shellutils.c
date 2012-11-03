#include <stdlib.h>     //ctandard ibrary for memory management and type conversion
#include <string.h>     //s-functions for handling character strings and memory manipulation of array elements
#include <limits.h>	//defines constants for minimal sizes of integer variables
#include <stdio.h> 	//standard input/output library functions
#include <sys/wait.h>	//declarations for waiting
#include <unistd.h>     //Posix Operating System API

#include "shellutils.h" 

/* Bitte schreiben Sie ihren Code nur im markierten Bereich 
 * (BEGIN TODO...END TODO) und lassen sie den vorgegebenen
 * Quellcode so wie er ist. 
 * Falls Sie einen Bug in dieser Implementierung finden, 
 * melden Sie diesen bitte an martens@ibr.cs.tu-bs.de.
 */

COMMAND *parseCommandLine(char *cmdLine) 
{
	COMMAND *cmd;			//COMMAND struct ptr (see shellutils.h)
	size_t cmdsize; 		//actual size of command structure (including all data pointed at)
	size_t realsize;		//the size of memory space allocated for command structure (including all data pointed at)
	size_t len = strlen(cmdLine); 	//length of command line
	size_t ceillen; 		//length of command line ceiled to multiples of sizeof(int)
	int argc = 0;   		//argument counter

	//replace possible newline(\n) with end of string (and shorten the length by 1) 
	if(cmdLine[len-1] == '\n') 
	{
		cmdLine[--len] = '\0';
	}

	// calculate the necessary space for the whole command structure (including data pointed at)
	ceillen = ((len+1)/sizeof(int) + 1) * sizeof(int); //round len up to multiples of sizeof(int)
	cmdsize = sizeof(*cmd);			// space for pure cmd struct (struct with one int and some char*)
	cmdsize += ceillen;             	// + space for cmdLine copy
	cmdsize += sizeof(char*);       	// + space for argv array (first element)
	cmdsize += sizeof(char*);		// + space for argv array (Null pointer = last element)
	realsize = cmdsize+32*sizeof(char*); 	// + tentative space for 32 additional array elements 

	// allocate memory
	cmd = calloc(1, realsize);	
	if(cmd == NULL) { return NULL; }

	// create copy of commandLine and store it under cmd->cmdLine
	char *cmdLineCopy = ((char*)cmd)+sizeof(*cmd); // calc address from cmd pointer where to store cmdLineCopy 
	memcpy(cmdLineCopy, cmdLine, len+1);
	cmd->cmdLine = cmdLineCopy;

        // argvPos points to the space where you can store the tokenized commandline 
	char** argvPos = (char**) (cmdLineCopy+ceillen); //set initial adress of argvPos cmdLineCopy+ceillen

	/** BEGIN TODO: */ 
        int i = -1;
        while(i < 128 && (argvPos[i]!=NULL)) {
            argvPos[i++] = strtok(cmdLine," ");
        }
	
	/** END TODO */
       
	cmd->argv = argvPos;
	
	// check for empty command
	if( argc < 1) 
	{
		cmd->parseError = "empty command line";
		return cmd;
	}
	// check last argument for "&"
	if(strcmp(argvPos[argc-1], "&") == 0) 
	{
		cmd->background = 1;
		argc--;
		if( argc < 1 ) 
		{
			cmd->parseError = "background execution of empty command requested";
			return cmd;
		}
		argvPos[argc] = NULL;
	}
	//check last argument for ">"
	if ( argvPos[argc-1][0] == '>' ) 
	{
		cmd->outFile = &(argvPos[argc-1][1]);

		if ( strlen(cmd->outFile) < 1 ) 
		{
			cmd->parseError = "stdout redirection to zero length filename requested";
			return cmd;
		}

		argc--;
		if( argc < 1 ) 
		{
			cmd->parseError = "stdout redirection of empty command requested";
			return cmd;
		}
		argvPos[argc] = NULL;
	}

	return cmd;
}

/* prints status of terminated child processes */
void printStat(const char *cmdLine, int status) 
{
	if (WIFSIGNALED(status)) 
	{
		fprintf(stderr,"Signal [%s] = %d\n",cmdLine,WTERMSIG(status));
	} 
	else if(WIFEXITED(status)) 
	{ 
		fprintf(stderr,"Exitstatus [%s] = %d\n",cmdLine,WEXITSTATUS(status));
	} 
	else if(WIFSTOPPED(status)) 
	{
		fprintf(stderr, "Stopped [%s] = %d\n", cmdLine, WSTOPSIG(status));
	}
}

void prompt() 
{
#define BUFLEN 5000
    char w[BUFLEN];
    if (getcwd(w,BUFLEN)) {
        printf("%s:",w);
    }
}

