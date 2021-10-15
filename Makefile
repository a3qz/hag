# File names
EXEC     = out/hag
OUTDIR   = out/
SRCDIR   = src/
OBJDIR   = $(OUTDIR)objects/
SOURCES  = $(wildcard $(SRCDIR)*/*.c)
HEADERS  = $(wildcard $(SRCDIR)*/*.h)
INCLUDE  = $(addprefix "-I", $(wildcard $(SRCDIR)*))
OBJECTS  = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))
 
# Declaration of variables
CC       = gcc 
LINKS    =-lncurses -lpanel
CC_FLAGS =-g -Wall -std=c89 -pedantic -Wextra -Werror \
		  -Wmissing-prototypes -Wstrict-prototypes $(INCLUDE) \
		  -D__NEED_USLEEP__
ID       = uncrustify
ID_FLAGS =-c uncrustify.cfg

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $^ -o $@ $(LINKS) $(CC_FLAGS)

# Obtain object files
$(OBJDIR)%.o: $(SRCDIR)/*/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CC_FLAGS)

# Remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

# Check code formatting
lint: $(SOURCES:.c=.c~uncrust) $(HEADERS:.h=.h~uncrust)
	@rm $^ 

# Run uncrustify and compare to source file
%~uncrust: %
	@$(ID) $(ID_FLAGS) -f $< -o $@
	@diff $< $@
