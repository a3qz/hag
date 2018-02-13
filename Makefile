# Declaration of variables
CC = gcc 
CC_FLAGS=-lpanel -lncurses
 
# File names
EXEC = tests
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(CC_FLAGS)
 
# To obtain object files
%.o: %.c
	$(CC) -c $< -o $@ $(CC_FLAGS)
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
