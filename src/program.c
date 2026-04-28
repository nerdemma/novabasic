#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/program.h"


Line *program = NULL;

void insert_line(int num, char *code)
{
Line *new_node = malloc(sizeof(Line));
new_node->number = num;
strncpy(new_node->code, code, MAX_LINE_LENGTH );
new_node->next = NULL;

	if(program == NULL || program -> number > num)
	{
	new_node -> next = program;
	program = new_node;
	return;
	}

	Line *curr=program;
	while(curr->next != NULL && curr->next->number < num){curr=curr->next;}

	if(curr->next != NULL && curr->next->number == num)
	{
	strcpy(curr->next->code, code); free(new_node);
	}
	else
	{
	new_node->next = curr-> next; curr->next = new_node;
	}
}


void list_program()
{
Line *curr = program;
	while(curr != NULL)
	{
	printf("%d %s\n", curr->number, curr->code);
	curr= curr->next;
	}
}

void clear_program()
{
Line *curr = program;
	while(curr != NULL)
	{
	Line *next = curr->next;
	free(curr);
	curr = next;	
	}	
program = NULL;
}
