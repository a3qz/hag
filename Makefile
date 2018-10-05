# Declaration of variables
CC = gcc 
CC_FLAGS=-lpanel -lncurses -g -Wall -std=c89
 
# File names
EXEC = out/hag
OBJDIR  = out/objects/
SRCDIR  = src/
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $^ -o $@ $(CC_FLAGS)
 
# To obtain object files
$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $< -o $@ $(CC_FLAGS)
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
