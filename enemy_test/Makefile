CCFLAGS=-lncurses

input_test: main.c map.o list.h
	$(CC) $^ -o $@ $(CCFLAGS)

%.o: %.c %.h
	$(CC) -c $< -o $@ $(CCFLAGS)

clean:
	rm -rf input_test *.o
