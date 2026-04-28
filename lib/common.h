#ifndef COMMON_H
#define COMMON_H

#define MAX_LINE_LENGTH 256
#define MAX_VARS 26

typedef struct Line{
int number;
char code[MAX_LINE_LENGTH];
struct Line *next;
} Line;


#endif
