#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../lib/interpreter.h"
#include "../lib/program.h"


const char *expr_ptr;
double variables[MAX_VARS] = {0}; // TABLA DE SIMBOLOS A-Z
Line *current_execution_line = NULL;


double get_value();
double parse_expression();
double parse_term();
double parse_factor();
double evaluate(const char *s);
double parse_comparison();

double evaluate(const char *s) {
    if (!s || *s == '\0') return 0;
    expr_ptr = s;
    return parse_comparison(); 
}

double parse_comparison() {
    double x = parse_expression();
    while (1) {
        while (isspace(*expr_ptr)) expr_ptr++;
        
        if (strncmp(expr_ptr, "==", 2) == 0) {
            expr_ptr += 2;
            x = (x == parse_expression());
        } else if (strncmp(expr_ptr, "<>", 2) == 0) {
            expr_ptr += 2;
            x = (x != parse_expression());
        } else if (strncmp(expr_ptr, "<=", 2) == 0) {
            expr_ptr += 2;
            x = (x <= parse_expression());
        } else if (strncmp(expr_ptr, ">=", 2) == 0) {
            expr_ptr += 2;
            x = (x >= parse_expression());
        } else if (*expr_ptr == '<') {
            expr_ptr++;
            x = (x < parse_expression());
        } else if (*expr_ptr == '>') {
            expr_ptr++;
            x = (x > parse_expression());
        } else {
            return x;
        }
    }
}


double parse_expression()
{
	double x = parse_term();
	while(1)
	{
	while(isspace(*expr_ptr)) expr_ptr++;
	if(*expr_ptr == '+'){ expr_ptr++; x+= parse_term();}
	else if(*expr_ptr == '-'){ expr_ptr++; x -= parse_term();}
	else return x;
	}
}


double parse_term()
{
double x = parse_factor();
	while(1)
	{
		while(isspace(*expr_ptr)) expr_ptr++;
		if(*expr_ptr == '*'){ expr_ptr++; x *= parse_factor(); }
		else if(*expr_ptr == '/'){ 
		expr_ptr++; 
		double d = parse_factor();
		x = (d!=0) ? x / d : 0;
		} else return x;
	}
}

double parse_factor()
{
while(isspace(*expr_ptr)) expr_ptr++;

	if(isdigit(*expr_ptr) || *expr_ptr == '.'){
	char *end;
	double x = strtod(expr_ptr, &end);
	expr_ptr = end;
	return x;
	}

	if(isalpha(*expr_ptr))
	{
	int index = toupper(*expr_ptr) - 'A';
	expr_ptr++;
	return (index >=0 && index < 26)? variables[index]:0;
	}


	if (*expr_ptr == '(' ){
	expr_ptr++;
	double x = parse_expression();
	if (*expr_ptr == ')') expr_ptr++;
	return x;
	}

return 0;
}


void execute_line(char *code)
{

if (!code || strlen(code) == 0) return;

char temp[MAX_LINE_LENGTH];
strncpy(temp, code, MAX_LINE_LENGTH);
char *cmd = strtok(temp, " ");
if(!cmd) return;

// PRINT: PRINT [VALUE]

	if(strcmp(cmd, "PRINT") == 0)
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
		char *var_part = temp + (cmd - temp) + strlen(cmd);
		while(isspace(*var_part)) var_part++;
		int index = toupper(*var_part) - 'A';
				
			if(index < 0 || index >= 26)
			{
			variables[index] = evaluate(equal_sign + 1);
			return;
			}
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
	char *var_part = strtok(NULL, " ");
	if(var_part){
	int index = toupper(var_part[0]) - 'A';
	double val;
	printf("?");
	scanf("%lf", &val);
	while(getchar() != '\n');
	variables[index] = val;
	}
	}


else if (strcmp(cmd, "REM") == 0) { /* Ignore comments.*/ }
else printf("?Syntax Error\n");
}

void run_program()
{
	current_execution_line = program;
	while ( current_execution_line != NULL )
	{
	Line * to_execute = current_execution_line;
	current_execution_line = current_execution_line->next;
	execute_line(to_execute->code);
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
		else if(strcmp(input, "NEW") == 0) clear_program();
		else if(strcmp(input, "END") == 0 || strcmp(input, "EXIT") == 0) exit(0);
		else execute_line(input);
	}

}
