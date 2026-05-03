#ifndef PROGRAM_H
#define PROGRAM_H
#include "common.h"

extern Line *program;

void insert_line(int num, char *code);

void list_program();
void clear_program();
void run_program();

void save_program(const char *filename);
void load_program(const char *filename);

Line* find_line(int num);

#endif
