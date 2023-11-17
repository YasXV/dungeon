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
	printf("%d\n",c->hauteur);
	printf("%d\n",c->ligne);
}

//--------------------------------------------------------------------------------

void affiche(couloir *c){
    for (int i = 0; i < c->hauteur; i++) {
        for (int j = 0; j < c->ligne; j++) {
            printf("%c ", c->tableau[i][j]);
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
	int nb_est = count_occurence("E",c);
	int nb_west = count_occurence("W",c);
	int nb_sud = count_occurence("S",c);
	int nb_nord = count_occurence("N",c);
	
	int x = 0;
	int y = 0;
	if ((nb_est != 0)&&(nb_west != 0)){
		if (nb_west == 0){
			y = 0;
		}
		else if (nb_est == 0){
			y = c->ligne - 1;
		}
		if ((nb_est != 0) && (nb_west != 0)){
			if (nb_est > nb_west){
				y = nb_est/2 - nb_west - 1;
			}
			else{
				y = nb_west - nb_est - 1;
			}
		}
	}
	else{
		if (nb_west == 0){
			y = -1;
		}
		else if (nb_est == 0){
			y = c->ligne - 1;
		}
	}
	if ((nb_nord != 0)&&(nb_sud != 0)){
		if (nb_nord > nb_sud){
			x = nb_nord/2 - nb_sud - 1;
		}
		else{
			x = nb_sud - nb_nord - 1;
		}
	}
	else if ((nb_nord == 0)&& (nb_sud != 0)){
		x = -1;
	}
	else if ((nb_sud == 0)&&(nb_nord != 0)){
		x = c->hauteur - 1;
	}
	else if ((nb_nord == 0)&&(nb_sud == 0)){
		x = 1;
	}
	printf("x = %d\n",x);
	printf("y = %d\n",y);
    int longueurSequence = sizeof(c->sequence) - 1;

    for (int i = 0; c->sequence[i] != '\0'; i++) {
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
	
}


//--------------------------------------------------------------------------------

void count_max_length(couloir *c){
	int max_length=0;
	int length_sud = 0;
	int length_nord = 0;

	int max_length_nord = 0;
	int max_length_sud = 0;
	
	char dernier_char;

	for (int i=0; (c->sequence)[i] != '\0'; i++){
		if((c->sequence)[i]=='S'){
			length_sud++;
		}
		else if (c->sequence[i] == 'N'){
			length_sud++;
			if (length_sud > max_length_sud){
				max_length_sud = length_sud;
				length_sud = 0;
			}
			else{
				length_sud = 0;
			}
		}
		//------------------------------------------------
		if((c->sequence)[i] == 'N'){
			length_nord++;
		}
		else if (c->sequence[i] == 'S'){
			if (length_nord > max_length_nord){
				max_length_nord = length_nord;
				length_nord = 0;
			}
			else{
				length_nord = 0;
			}
		}
		dernier_char = (c->sequence)[i];
	}

	if (length_sud > max_length_sud){
		max_length_sud = length_sud;
	}
	if (length_nord > max_length_nord){
		max_length_nord = length_nord;
	}


	if ((max_length_nord ==0)||(max_length_sud == 0)){
		if ((max_length_nord == 0) && (max_length_sud == 0)){
			c->hauteur = 3;
		}
		else if (max_length_nord == 0){
			if (dernier_char == 'S'){
				c->hauteur = max_length_sud - 1;
			}
			else{
				c->hauteur = max_length_sud - 1;
			}
		}
		else if (max_length_sud == 0){
			if (dernier_char == 'N'){
				c->hauteur = max_length_nord - 1;
			}
			else{
				c->hauteur = max_length_nord + 1;
			}
		}
	}
	else{
		if (max_length_nord > max_length_sud){
			c->hauteur = max_length_nord + 2;
		}
		else{
			c->hauteur = max_length_sud + 2;
		}
	}
}

//--------------------------------------------------------------------------------

void count_max_ligne(couloir *c){
	int ligne_est = 0;
	int ligne_west = 0;

	int max_ligne_west = 0;
	int max_ligne_est = 0;
	
	char dernier_char;

	for (int i=0; (c->sequence)[i] != '\0'; i++){
		if((c->sequence)[i]=='E'){
			ligne_est++;
		}
		else if (c->sequence[i] == 'W'){
			if (ligne_est > max_ligne_est){
				max_ligne_est = ligne_est;
				ligne_est = 0;
			}
			else{
				ligne_est = 0;
			}
		}
		//------------------------------------------------
		if((c->sequence)[i] == 'W'){
			ligne_west++;
		}
		else if (c->sequence[i] == 'E'){
			if (ligne_west > max_ligne_west){
				max_ligne_west = ligne_west;
				ligne_west = 0;
			}
			else{
				ligne_west = 0;
			}
		}
		dernier_char = (c->sequence)[i];
	}

	if (ligne_est > max_ligne_est){
		max_ligne_est = ligne_est;
	}
	if (ligne_west > max_ligne_west){
		max_ligne_west = ligne_west;
	}
	if ((max_ligne_west ==0)||(max_ligne_est == 0)){
		if (max_ligne_west == 0){
			if (dernier_char == 'E'){
				c->ligne = max_ligne_est;
			}
			else{
				c->ligne = max_ligne_est + 3;
			}
		}
		if (max_ligne_est == 0){
			if (dernier_char == 'W'){
				c->ligne = max_ligne_west;
			}
			else{
				c->ligne = max_ligne_west + 3;
			}
		}
	}
	else{
		if (max_ligne_west > max_ligne_est){
			c->ligne = max_ligne_west + 3;
		}
		else{
			c->ligne = max_ligne_est + 3;
		}
	}
}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------