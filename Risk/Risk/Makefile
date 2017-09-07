CFLAGS = -Wall -std=c99
SOURCES = $(wildcard *.c)
OBJ = $(SOURCES:.c=.o)

Risk : $(OBJ)
	$(CC) -o $@ $^

include depends.txt

.PHONY = clean
clean :
	rm Risk $(OBJ)

depends.txt : $(SOURCES)
	$(CC) -M $(CFLAGS) $(SOURCES) > depends.txt
