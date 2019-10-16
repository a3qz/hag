# Declaration of variables
CC       = gcc 
ID       = uncrustify
CC_FLAGS =-lpanel -lncurses -g -Wall -std=c89 -pedantic -Wextra -Wmissing-prototypes -Wstrict-prototypes 
ID_FLAGS =-c uncrustify.cfg
 
# File names
EXEC     = out/hag
OUTDIR   = out/
OBJDIR   = $(OUTDIR)objects/
SRCDIR   = src/
SOURCES  = $(wildcard $(SRCDIR)*.c)
OBJECTS  = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $^ -o $@ $(CC_FLAGS)
 
# To obtain object files
$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(SRCDIR)%.c~: $(SRCDIR)%.c
	@$(ID) $(ID_FLAGS) -f $< -o $@
	@diff $< $@

lint: $(SOURCES:.c=.c~)
	@rm $^

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)


