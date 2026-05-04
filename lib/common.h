#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256
#define MAX_VARS 26
#define MAX_FOR_STACK 10
#define MAX_STR_LEN 128

struct Line;
typedef struct Line{
int number;
char code[MAX_LINE_LENGTH];
struct Line *next;
} Line;


typedef struct{
int var_index;
double target_value;
double step_value;
Line *line_to_resume;
} ForLoop;


typedef enum{ TYPE_NUMBER, TYPE_STRING } VarType;
typedef struct{
	VarType type;
	union{
		double number;
		char string[MAX_STR_LEN];
		} value;
	} Variable;




extern double variables [MAX_VARS];
extern Line *program;
extern Line *current_execution_line;
extern ForLoop for_stack[MAX_FOR_STACK];
extern int for_stack_ptr;

extern Variable num_vars[MAX_VARS];
extern Variable str_vars[MAX_VARS];

#endif
