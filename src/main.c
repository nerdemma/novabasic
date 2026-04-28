#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/common.h"
#include "../lib/interpreter.h"



int main()
{
char line[MAX_LINE_LENGTH];
printf("Nova-Basic Version 0.1\n");
printf("Ready\n");	

	while(1)
	{
	printf("> ");
	if(fgets(line, sizeof(line), stdin) == NULL) break;
	process_input(line);
	}
	return 0;
}
