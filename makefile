fichiers_o/%.o: fichiers_c/%.c
	gcc -o $@ -c $<

dungeon:fichiers_o/couloir.o fichiers_o/entites.o fichiers_o/chambre.o fichiers_o/assemblage_chambre.o fichiers_o/fonctions_utiles.o fichiers_o/donjon.o  main.o
	gcc fichiers_o/couloir.o fichiers_o/entites.o fichiers_o/chambre.o fichiers_o/assemblage_chambre.o fichiers_o/fonctions_utiles.o fichiers_o/donjon.o main.o -lm -o donjon
	rm *.o
	rm fichiers_o/*.o
	./donjon
	rm donjon
