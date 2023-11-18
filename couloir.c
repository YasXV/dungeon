// C File standard
//--------------------------------------------------------------------------------
//  File couloir.c
// Date: 12 Nov 2023
//--------------------------------------------------------------------------------

#include "couloir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------

void init(couloir *c, int largeur, const char *sequence){
	c->largeur = largeur;
	c->sequence = malloc(strlen(sequence) + 1);
	strcpy(c->sequence,sequence);
	count_max_length(c);
	count_max_ligne(c);
	    // Allouer de la mémoire pour les lignes
    c->tableau = (char**)malloc(c->hauteur * sizeof(char*));

    // Allouer de la mémoire pour les colonnes
    for (int i = 0; i < c->hauteur; i++) {
        c->tableau[i] = (char*)malloc(c->largeur * sizeof(char));
    }

	create_tableau(c);
}

//--------------------------------------------------------------------------------

void affiche(couloir *c){
    for (int i = 0; i < c->hauteur; i++) {
        for (int j = 0; j < c->ligne; j++) {
			if (c->tableau[i][j] == '-'){
				printf("  ");
			}
			else{
            	printf("%c ", c->tableau[i][j]);
			}
        }
        printf("\n");
    }
}

//--------------------------------------------------------------------------------

void create_tableau(couloir *c){
	for (int i = 0; i < c->hauteur; i++) {
        for (int j = 0; j < c->ligne; j++) {
            c->tableau[i][j] = '#';
        }
    }
	fill_couloir(c);
}

//--------------------------------------------------------------------------------

int count_occurence(char *direction,couloir *c){
	int occurence = 0;
	for (int i=0; (c->sequence)[i] != '\0'; i++){
		if((c->sequence)[i] == *direction){
			occurence++;
		}
	}
	return occurence;
}

//--------------------------------------------------------------------------------

void fill_couloir(couloir *c){
	int x = 0;
	int y = 0;
	start_placement(c,&x,&y);

	int longueurSequence = strlen(c->sequence);

    for (int i = 0; i < longueurSequence; i++) {
        char direction = c->sequence[i];

        if (direction == 'E') {
            y += 1;
        } else if (direction == 'W') {
            y -= 1;
        } else if (direction == 'S') {
            x += 1;
        } else if (direction == 'N') {
            x -= 1;
        }

        // Assurez-vous que les nouvelles coordonnées sont valides
        if (x >= 0 && x < c->hauteur && y >= 0 && y < c->ligne) {
            c->tableau[x][y] = ' ';
        }
    }
	//clean_tableau(c);
}

//--------------------------------------------------------------------------------

void start_placement(couloir *c, int *x, int *y){
	int nb_est = count_occurence("E",c);
	int nb_west = count_occurence("W",c);
	int nb_sud = count_occurence("S",c);
	int nb_nord = count_occurence("N",c);
	
	//calcul de la position de départ
	if ((nb_est == 0)&&(nb_west != 0)){
		if (c->sequence[0] == 'W'){
			*y = c->ligne;
		}
		else{
			*y = (c->ligne) - 2;
		}

	}
	else if ((nb_est != 0)&&(nb_west == 0)){
		if (c->sequence[0] == 'E'){
			*y = -1;
		}
		else{
			*y = 1;
		}
	}
	else{
		if ((nb_est != 0 ) && (nb_west != 0)){
			if (nb_est > nb_west){
				*y = nb_est/2 - nb_west - 1;
			}
			else{
				*y = c->ligne - 2;
			}
		}
		else{
			*y = 1;
		}
	}
	//----------------------------------------
	if ((nb_nord == 0)&&(nb_sud != 0)){
		*x = -1;
	}
	else if ((nb_nord != 0)&&(nb_sud == 0)){
		if (c->sequence[0] == 'N'){
			*x = c->hauteur;
		}
		else{
			*x = c->hauteur -1;
		}
	}
	else{
		if ((nb_nord != 0 ) && (nb_sud != 0)){
			if (nb_nord > nb_sud){
				*x = nb_nord - nb_sud - 1;
			}
			else{
				*x = - 1;
			}
		}
		else{
			*x = 1;
		}
	}
}

//--------------------------------------------------------------------------------

void count_max_length(couloir *c){
	int max_length=0;
	int length_sud = count_occurence("S",c);
	int length_nord = count_occurence("N",c);

	int gain = 1;
	if ((length_sud != strlen(c->sequence)) && (length_nord != strlen(c->sequence))){
		if ((length_sud == 0)||(length_nord == 0)){
			if ((c->sequence[strlen(c->sequence)-1] == 'S') && (c->sequence[0] == 'S')){
				gain = 0;
			}
			else if ((c->sequence[strlen(c->sequence) - 1] == 'N') && (c->sequence[0] == 'N')){
				gain = 0;
			}
			else{
				gain = 1;
			}
		}
		else{
			gain = 1;
		}
	}
	else{
		gain = 0;
	}

	if (length_sud > length_nord){
		max_length = length_sud + gain;
	}
	else{
		max_length = length_nord + gain;
	}
	if ((length_sud == 0) && (length_nord == 0)){
		max_length = 3;
	}
	c->hauteur = max_length;
}

//--------------------------------------------------------------------------------

void count_max_ligne(couloir *c){
	int max_ligne=0;
	int ligne_est = count_occurence("E",c);
	int ligne_west = count_occurence("W",c);

	int gain = 1;
	if ((ligne_est != strlen(c->sequence)) && (ligne_west != strlen(c->sequence))){
		if ((ligne_est == 0)||(ligne_west == 0)){
			if ((c->sequence[strlen(c->sequence) - 1] == 'E')||(c->sequence[strlen(c->sequence) - 1] == 'W')){
				gain = 1;
			}
			else{
				gain = 3;
			}
		}
		else{
			gain = 3;
		}
	}
	else{
		gain = 0;
	}

	if (ligne_est > ligne_west){
		max_ligne = ligne_est + gain;
	}
	else{
		max_ligne = ligne_west + gain;
	}
	if ((ligne_est == 0) && (ligne_west == 0)){
		max_ligne = 3;
	}
	c->ligne = max_ligne;
}

//--------------------------------------------------------------------------------

void clean_tableau(couloir *c){
	for (int i = 0; i < c->hauteur; i++){
		for (int j = 0; j < c->ligne; j++){
			if ((c->tableau[i][j] != ' ') || (c->tableau[i+1][j] != ' ') || (c->tableau[i-1][j] != ' ') ||	(c->tableau[i][j+1] != ' ') || (c->tableau[i][j-1] != ' ') || (c->tableau[i+1][j+1] != ' ') || (c->tableau[i-1][j-1] != ' ')){
				c->tableau[i][j] = '-';
			}
		}
	}
}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------