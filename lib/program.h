#ifndef PROGRAM_H
#define PROGRAM_H
#include "common.h"

extern Line *program;

void insert_line(int num, char *code);
void list_program();
void clear_program();
Line* find_line(int num);

#endif
