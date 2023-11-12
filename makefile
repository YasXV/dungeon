%.o: %.c
	gcc -o $@ -c $<

dungeon:couloir.o main.o
	gcc couloir.o main.o -lm -o dungeon
	rm *.o
	./dungeon
	rm dungeon
