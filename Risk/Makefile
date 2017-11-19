CFLAGS = -std=c99 -g -O3 -Wall -Werror
SOURCES = $(wildcard *.c)
OBJ = $(SOURCES:.c=.o)

all : Risk

model.o : model.c risk_model.h
initializer.o : initializer.c risk_view_initialize.h
view.o : view.c risk_view_initialize.h
main.o : main.c risk_model.h risk_view_initialize.h

Risk : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o Risk

.PHONY = clean
clean :
	rm -f Risk Risk_gdb $(OBJ)
