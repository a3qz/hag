CCFLAGS=-lncurses -g

enemy_test: main.c map.o enemy.o list.o
	$(CC) $^ -o $@ $(CCFLAGS)

%.o: %.c %.h
	$(CC) -c $< -o $@ $(CCFLAGS)

clean:
	rm -rf enemy_test *.o
