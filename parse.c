#include "shellutils.h"
#include <string.h>
#include <stdio.h>

void printCMD(COMMAND* cmd)
{
	printf("background: %d \noutFile: %s \nparseError: %s \ncmdLine: %s\n", 
		cmd->background, cmd->outFile, cmd->parseError, cmd->cmdLine);
	for(int i = 0; cmd->argv[i] != NULL; i++) printf("\targv[%d]: %s\n", i, cmd->argv[i]);
}

int main()
{
	char str[500000];
	prompt();
	printCMD(parseCommandLine(fgets(str, sizeof(str), stdin)));
}
