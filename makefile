%.o: %.c
	gcc -o $@ -c $<

dungeon:couloir.o entites.o chambre.o assemblage_chambre.o fonctions_utiles.o donjon.o  main.o
	gcc couloir.o chambre.o entites.o assemblage_chambre.o main.o fonctions_utiles.o donjon.o -lm -o dungeon
	rm *.o
	./dungeon
	rm dungeon
