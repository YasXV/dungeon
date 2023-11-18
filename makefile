%.o: %.c
	gcc -o $@ -c $<

dungeon:couloir.o chambre.o main.o
	gcc couloir.o chambre.o main.o -lm -o dungeon
	rm *.o
	./dungeon
	rm dungeon
