CC = cc
CFLAGS = -O2 -Wall -std=c11
INCLUDES = -Ilib

# Nombre del ejecutable
TARGET = nvbasic

# Directorios
SRCDIR = src
LIBDIR = lib

# Lista de objetos (ahora asociados a su fuente en src/)
OBJS = interpreter.o program.o main.o parser.o

all: $(TARGET)

# Enlace final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) -lm

# Regla de compilación de objetos
# Usamos VPATH para que encuentre los .c en src/
VPATH = $(SRCDIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# --- Gestión de dependencias ---
# Esto asegura que si tocas un .h, se recompilen los .c afectados
interpreter.o: interpreter.c $(LIBDIR)/interpreter.h $(LIBDIR)/common.h
program.o: program.c $(LIBDIR)/program.h $(LIBDIR)/common.h
parser.o: parser.c $(LIBDIR)/parser.h $(LIBDIR)/common.h
main.o: main.c $(LIBDIR)/common.h

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
