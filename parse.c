#include "shellutils.h"
#include <string.h>

void printCMD(COMMAND* cmd)
{
	printf("background: %d\n", cmd->background);
	printf("outFile: %s\n", cmd->outFile);
	printf("parseError: %s\n", cmd->parseError);
	printf("cmdLine: %s\n", cmd->cmdLine);
	for(int i = 0; cmd->argv[i] != NULL; i++)
	{
		printf("\targv[%d]: %s\n", i, cmd->argv[i]);
	}
}

int main()
{
	char str[] = "ls -l -a";
	printCMD(parseCommandLine(str));
}
