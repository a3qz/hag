CCFLAGS=-lncurses

input_test: main.c map.o
	$(CC) $^ -o $@ $(CCFLAGS)

%.o: %.c
	$(CC) -c $^ -o $@ $(CCFLAGS)
clean:
	rm -rf input_test *.o
