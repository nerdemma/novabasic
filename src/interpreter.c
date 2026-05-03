#include "../lib/common.h"
#include "../lib/interpreter.h"
#include "../lib/parser.h"
#include "../lib/program.h"



double variables[MAX_VARS] = {0};
int for_stack_ptr = 0;
ForLoop for_stack[MAX_FOR_STACK];
Line *current_execution_line = NULL;



void execute_line(char *code)
{

if (!code || strlen(code) == 0) return;
	char temp[MAX_LINE_LENGTH];
	strncpy(temp, code, MAX_LINE_LENGTH);
	char *cmd = strtok(temp, " ");
	if(!cmd) return;


/* SAVE: SAVE [FILE_NAME]*/

	if (strcmp(cmd, "SAVE") == 0)
	{
	char *file = strtok(NULL," ");
		if (file)
		{
			if(file[0]=='"')
			{
			file++;
			char *end = strrchr(file,'"');
			if(end) *end ='\0';
			}
			save_program(file);
		} 
		 else
		{
		printf("?Filename required\n");
		}
	}

/* LOAD: LOAD [FILE_NAME]*/	

	else if (strcmp(cmd, "LOAD") == 0)
	{
	char *file = strtok(NULL," ");
	if (file) load_program(file);
	}


// PRINT: PRINT [VALUE]

	else if(strcmp(cmd, "PRINT") == 0)
	{ 
	char *arg = code + (cmd - temp) + strlen(cmd);
	while (isspace(*arg)) arg++;
		if (*arg == '"')
		{
			arg++;
			char *end = strchr(arg, '"');
			if(end) *end = '\0';
			printf("%s\n",arg);
		}
		else 
		{
		printf("%g\n", evaluate(arg));	
		}
		
	}
	

// LET: LET = [VALUE]	
	else if(strcmp(cmd , "LET") == 0)
	{
	char *equal_sign = strchr(code, '=');
		if (equal_sign)
		{
		char *var_part = code + 4;
		while(isspace(*var_part)) var_part++;
		int index = toupper(*var_part) - 'A';
				
			if(index >= 0 && index < 26)
			//if(index < 0 || index >= 26)
			{
			variables[index] = evaluate(equal_sign + 1);
			return;
			}
			else{printf("Variable Error\n");}
		}
	
	}

// IF: IF [exp] THEN [instructions]
	else if(strcmp(cmd, "IF") == 0)
	{
	char *then_ptr = strstr(code, "THEN");	
		if(then_ptr)
		{
		char condition_str[MAX_LINE_LENGTH];
		int cond_len = then_ptr - (code + 3);
		strncpy(condition_str, code + 3, cond_len);
		condition_str[cond_len] = '\0';
			
			if(evaluate(condition_str))
			{
			execute_line(then_ptr + 5);
			}
			
		}
	
	}


// GOTO: GOTO [LINE]
	else if(strcmp(cmd, "GOTO") == 0)
	{
	char *line_str = strtok(NULL, " ");
	
	if (line_str)
	{
	int target = atoi(line_str);
	Line *found = program;
	while(found && found -> number != target) found = found-> next;
		if(found){ current_execution_line = found; }
		else { printf("?Line %d not found\n", target); 
		}	
	}	

	}


/*INPUT: INPUT [VALUE]*/
	else if (strcmp(cmd, "INPUT") == 0)
	{
	char *var_name = strtok(NULL, " ");
	if(var_name){
	int index = toupper(var_name[0]) - 'A';
	double val;
	printf("?");
	if (scanf("%lf", &val) == 1) variables[index] = val; 
	while(getchar() != '\n');
	}
	}



/*FOR */

else if (strcmp(cmd, "FOR") == 0) {
        char *equal_ptr = strchr(code, '=');
        char *to_ptr = strstr(code, " TO "); 

        if (equal_ptr && to_ptr) {
            char *var_part = code + 4;
            while (isspace(*var_part)) var_part++;
            int index = toupper(*var_part) - 'A';

			if( index >=0 && index < 26)
				{
				variables[index] = evaluate(equal_ptr + 1);	
					if (for_stack_ptr < MAX_FOR_STACK)
					{
					for_stack[for_stack_ptr].var_index = index;
					for_stack[for_stack_ptr].target_value = evaluate(to_ptr + 4);
					for_stack[for_stack_ptr].step_value = 1.0;
					
					for_stack[for_stack_ptr].line_to_resume = current_execution_line;
					for_stack_ptr++;
					} 
					
				}
	
        }
        else
		{
		printf("?Syntax Error in FOR: Missing '=' or 'TO'\n");
		}
    }

/* NEXT */

else if (strcmp(cmd, "NEXT") == 0) {
        char *var_name = strtok(NULL, " ");
        if (var_name) {
            int index = toupper(var_name[0]) - 'A';
            if (for_stack_ptr > 0 && for_stack[for_stack_ptr - 1].var_index == index) {
                int current_loop = for_stack_ptr - 1;
                variables[index] += for_stack[current_loop].step_value;

                if (variables[index] <= for_stack[current_loop].target_value) {
                    current_execution_line = for_stack[current_loop].line_to_resume;
                } else {
                    for_stack_ptr--; 
                }
            }
        } else {
            printf("?Next without For Error\n");
        }
    }




/*HELP*/

else if(strcmp(cmd, "HELP") == 0)
{
	printf("---NOVABASIC-HELP-------------------------------------------\n\n");
	printf("PRINT: Displays text or the result of an expression\n");
	printf("LET: Assigns a value or expression to a variable (A-Z).\n");
	printf("IF: Conditional execution based on a comparison.\n");
	printf("GOTO: Jumps execution to a specific line number.\n");
	printf("INPUT: Prompts the user to enter a numeric value.\n");
	printf("LIST: Prints the current program in memory.\n");
	printf("RUN: Executes the program from the first line. \n");
	printf("NEW: Clears all lines from the current program.\n");
	printf("REM: Adds a comment (ignored during execution). \n");
	printf("EXIT: Quits the interpreter. \n");
	printf("FOR NEXT: Initialize a loop.\n");
	printf("HELP: Show all commands available.\n"); 
	printf("ABOUT: Name, Version, License and Information about the Author.\n\n");
	printf("Ready\n");
}


/* About */

else if(strcmp(cmd, "ABOUT") == 0)
{
	printf("-----------------------------------------------------\n\n");
	printf("NOVABASIC Version 1.0\n");
	printf("Develop with <3 <3 <3 By Emmanuel D. Breyaue.\n");
	printf("For more information, sugest and feedback hello[at]emmanuelbreyaue[dot]com \n\n");
	printf("Ready\n");
}


/* REM */

	else if (strcmp(cmd, "REM") == 0) { /* Ignore comments.*/ } 
	else printf("?Syntax Error\n");

/*END COMMANDS FUNCTION*/
}





void process_input(char *input)
{
int line_num;
char code[MAX_LINE_LENGTH];

	if(sscanf(input, "%d %[^\n]", &line_num, code) == 2) {insert_line(line_num, code);}
	else{ input[strcspn(input, "\n")] = 0; 
		if(strcmp(input, "RUN") == 0) run_program();
		else if(strcmp(input, "LIST") == 0) list_program();
		else if(strcmp(input, "NEW") == 0) clear_program();
		else if(strcmp(input, "QUIT") == 0 || strcmp(input, "EXIT") == 0 || strcmp(input, "END") == 0) exit(0);
		else execute_line(input);
	}

}

