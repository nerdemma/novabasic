#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/common.h"
#include "../lib/program.h"
#include "../lib/interpreter.h"

Line *program = NULL;

void insert_line(int num, char *code) {
    Line *new_node = malloc(sizeof(Line));
    if (!new_node) return; 

    new_node->number = num;
    strncpy(new_node->code, code, MAX_LINE_LENGTH - 1);
    new_node->code[MAX_LINE_LENGTH - 1] = '\0'; 
    new_node->next = NULL;

    
    if (program == NULL || program->number > num) {
        new_node->next = program;
        program = new_node;
        return;
    }

    
    Line *curr = program;
    while (curr->next != NULL && curr->next->number < num) {
        curr = curr->next;
    }

    
    if (curr->next != NULL && curr->next->number == num) {
        strncpy(curr->next->code, code, MAX_LINE_LENGTH - 1);
        curr->next->code[MAX_LINE_LENGTH - 1] = '\0';
        free(new_node);
    } 
    
    else {
        new_node->next = curr->next;
        curr->next = new_node;
    }
}

void list_program() {
    Line *curr = program;
    while (curr != NULL) {
        printf("%d %s\n", curr->number, curr->code);
        curr = curr->next;
    }
}

void clear_program() {
    Line *curr = program;
    while (curr != NULL) {
        Line *next = curr->next;
        free(curr);
        curr = next;
    }
    program = NULL;
}

void save_program(const char *filename) {
if (!filename || strlen(filename) == 0) { printf("?Missing filename\n"); return; }
	FILE *file = fopen(filename, "w");
	if(!file){ printf("?Missing filename\n"); return;}
   
Line *curr = program;
int count = 0;

    while (curr) {
        fprintf(file, "%d %s\n", curr->number, curr->code);
        curr = curr->next;
	count++;
    }

    fflush(file);	
    fclose(file);
    printf("Program saved to %s\n", filename);
}

void load_program(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) { 
        printf("?Error: File not found\n"); 
        return; 
    }
    clear_program();
    char line_buf[MAX_LINE_LENGTH + 20];

    while (fgets(line_buf, sizeof(line_buf), file)) {
        int num;
        char code[MAX_LINE_LENGTH];
        if (sscanf(line_buf, "%d %[^\n]", &num, code) == 2) {
            insert_line(num, code);
        }
    }
    fclose(file);
    printf("Program loaded from %s\n", filename);
}

void run_program() {
    for_stack_ptr = 0;
    current_execution_line = program;
    
    while (current_execution_line != NULL) {
        Line *to_execute = current_execution_line;
        current_execution_line = current_execution_line->next;
        execute_line(to_execute->code);
    }
}
