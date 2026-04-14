#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256

typedef struct Line{
int number;
char code[MAX_LINE_LENGTH];
struct Line *next;
} Line;

Line *program = NULL;


void insert_line(int num, char *code);
void list_program();
void run_program();
void execute_line(char *code);



void insert_line(int num, char *code)
{
Line *new_node = malloc(sizeof(Line));
new_node->number = num;
strncpy(new_node->code, code, MAX_LINE_LENGTH );
new_node->next = NULL;

// empty list
	if(program == NULL || program -> number > num)
	{
	new_node -> next = program;
	program = new_node;
	return;
	}

// middle or end file
	Line *curr=program;
	while(curr->next != NULL && curr->next->number < num){curr=curr->next;}

// update list
	if(curr->next != NULL && curr->next->number == num){
		strcpy(curr->next->code, code); free(new_node);}
	else{ new_node->next = curr-> next; curr->next = new_node;}
}


void execute_line(char *code){
char temp[MAX_LINE_LENGTH];
strcpy(temp, code);
char *cmd = strtok(temp, " ");

if(!cmd) return;

	if(strcmp(cmd, "PRINT") == 0)
	{ char *arg = strtok(NULL, " "); printf("%s\n", arg ? arg: "");}
	else{ printf("?Syntax Error %s\n", cmd);}

}

void run_program()
{
Line *curr = program;
while ( curr != NULL )
{
execute_line(curr->code);
curr = curr->next;
}
}


void process_input(char *input)
{
int line_num;
char code[MAX_LINE_LENGTH];

	if(sscanf(input, "%d %[^\n]", &line_num, code) == 2) {insert_line(line_num, code);}
	else{ input[strcspn(input, "\n")] = 0; 
		if(strcmp(input, "RUN") == 0) run_program();
		else if(strcmp(input, "LIST") == 0) list_program();
		else if(strcmp(input, "END") == 0 || strcmp(input, "QUIT") == 0) exit(0);
		else execute_line(input);
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
