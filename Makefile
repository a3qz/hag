# File names
EXEC     = out/hag
OUTDIR   = out/
OBJDIR   = $(OUTDIR)objects/
SRCDIR   = src/
SOURCES  = $(wildcard $(SRCDIR)*/*.c)
INCLUDE  = $(addprefix "-I", $(wildcard $(SRCDIR)*))
OBJECTS  = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))
 
# Declaration of variables
CC       = gcc 
CC_FLAGS =-lpanel -lncurses -g -Wall -std=c89 -pedantic -Wextra -Wmissing-prototypes -Wstrict-prototypes $(INCLUDE)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $^ -o $@ $(CC_FLAGS)
 
# To obtain object files
$(OBJDIR)%.o: $(SRCDIR)/*/%.c
	mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CC_FLAGS)

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
