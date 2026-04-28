CC = cc
CFLAGS = -O2 -Wall -std=c11

INCLUDES = -Ilib 
OBJ = nvbasic

OBJS = interpreter.o program.o main.o 

all: $(OBJ)

$(OBJ): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OBJ) $(OBJS)


VPATH = src

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o $(OBJ)

.PHONY: all clean debug
