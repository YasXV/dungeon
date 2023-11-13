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
	count_max_width(c);
	printf("%d\n",c->width);
}

//--------------------------------------------------------------------------------

void affiche(couloir *c){
	//création d'un tableau de char à remplir:
	char tab[c->longueur][c->largeur];
	int hauteur = 0;
	int largeur = 0;
	//initialisation du tableau:
	for (int i=0; (c->sequence)[i] != '\0'; i++) {
		int count = count_occurence_direction(c, i, (c->sequence)[i]);
		if ((c->sequence)[i] == 'N'){
			if (count > 1){
				tab[c->longueur - (hauteur + 1)][largeur] = '#';
				tab[c->longueur - (hauteur + 1)][largeur + 1] = ' ';
				tab[c->longueur - (hauteur + 1)][largeur + 2] = '#';
			}
			else{
				if ((c->sequence)[i+1] == 'E'){
					tab[c->longueur - (hauteur + 1)][largeur] = '#';
					tab[c->longueur - (hauteur + 1)][largeur + 1] = ' ';
					tab[c->longueur - (hauteur + 1)][largeur + 2] = ' ';
					tab[c->longueur - (hauteur + 2)][largeur]= '#';
					tab[c->longueur - (hauteur + 2)][largeur + 1]= '#';
					tab[c->longueur - (hauteur + 2)][largeur + 2]= '#';
					largeur++;
					largeur++;
				}
				else if ((c->sequence)[i+1] == 'W'){
					tab[c->longueur - (hauteur + 1)][largeur] = ' ';
					tab[c->longueur - (hauteur + 1)][largeur + 1] = ' ';
					tab[c->longueur - (hauteur + 1)][largeur + 2] = '#';

					tab[c->longueur - (hauteur + 2)][largeur]= '#';
					tab[c->longueur - (hauteur + 2)][largeur + 1]= '#';
					tab[c->longueur - (hauteur + 2)][largeur + 2]= '#';
					largeur++;
					largeur++;
				}
			}
			hauteur++;
		}
		else if ((c->sequence)[i] == 'S'){
			
			if (count > 1){
				tab[hauteur][largeur] = '#';
				tab[hauteur][largeur + 1] = ' ';
				tab[hauteur][largeur + 2] = '#';
			}
			else{
				if ((c->sequence)[i+1] == 'E'){
					tab[hauteur][largeur] = '#';
					tab[hauteur][largeur + 1] = ' ';
					tab[hauteur][largeur + 2] = ' ';
					tab[hauteur + 1][largeur]= '#';
					tab[hauteur + 1][largeur + 1]= '#';
					tab[hauteur + 1][largeur + 2]= '#';
					largeur++;
					largeur++;
				}
				else if ((c->sequence)[i+1] == 'W'){
					tab[hauteur][largeur] = ' ';
					tab[hauteur][largeur + 1] = ' ';
					tab[hauteur][largeur + 2] = '#';

					tab[hauteur + 1][largeur]= '#';
					tab[hauteur + 1][largeur + 1]= '#';
					tab[hauteur + 1][largeur + 2]= '#';
					largeur++;
					largeur++;
				}
			}
			hauteur++;
		}
		else if ((c->sequence)[i] == 'E'){
			if (count > 1){
				//tab[hauteur + 2][largeur + 1] = '#';
				//tab[hauteur + 1][largeur + 1] = ' ';
				//tab[hauteur][largeur + 1] = '#';
			}
			largeur++;
			continue;
		}
		else if ((c->sequence)[i]=='W'){
			largeur++;
			continue;
		}
		else {
			printf("erreur de saisie\n");
		}
	}
	//affichage du tableau:
	for (int i=0; i<c->longueur; i++){
		for (int j=0; j<c->largeur; j++){
			printf("%c", tab[i][j]);
		}
		printf("\n");
	}
	//printf("%d\t%d",count_north(c->sequence),count_west(c->sequence));
	//printf("\n");
	/*printf("%s\n",c->sequence);
	for(int i=0;i<strlen(c->sequence);i++){
	printf("#");
	}
	for(int i=1; i<=c->largeur;i++){
		printf("\n");
	}
	for(int i=0;i<strlen(c->sequence);i++){
	printf("#");
	}
	printf("\n");
	for (int i=0; (c->sequence)[i] != '\0'; i++){
	}*/
}

//--------------------------------------------------------------------------------

int count_occurence_direction(couloir *c, int index, char direction){
	int count_occurence = 0;
	for (int i = index; (c->sequence)[i] != '\0'; i++){
		if ((c->sequence)[i] == direction){
			count_occurence++;
		}
		else{
			return count_occurence;
		}
	}
	return count_occurence;
}

//--------------------------------------------------------------------------------


void orientation(const char *sequence){
/*E S W N */
	
}


//--------------------------------------------------------------------------------

int count_north(const char *sequence){
	int north=0;
	for (int i=0; (sequence)[i] != '\0'; i++){
		if((sequence)[i]=='N'){
		north++;
		}
	}
	return north;
}

//--------------------------------------------------------------------------------

int count_west(const char *sequence){
	int west=0;
	for (int i=0; (sequence)[i] != '\0'; i++){
		if((sequence)[i]=='W'){
		west++;
		}
	}
	return west;
}

//--------------------------------------------------------------------------------

void count_max_length(couloir *c){
	int max_length=0;
	int length_sud = 0;
	int length_nord = 0;
	int length_total_sud = 0;
	int length_total_nord = 0;
	int max_length_nord = 0;
	int max_length_sud = 0;
	
	char dernier_char;

	for (int i=0; (c->sequence)[i] != '\0'; i++){
		if((c->sequence)[i]=='S'){
			length_sud++;
			length_total_sud++;
		}
		else{
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
			length_total_nord++;
		}
		else{
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

	if ((max_length_nord ==0)||(max_length_sud == 0)){
		if (max_length_nord == 0){
			if (dernier_char == 'S'){
				c->longueur = length_total_sud - 1;
			}
			else{
				c->longueur = length_total_sud + 1;
			}
		}
		if (max_length_sud == 0){
			if (dernier_char == 'N'){
				c->longueur = length_total_nord - 1;
			}
			else{
				c->longueur = length_total_nord + 1;
			}
		}
	}
	else{
		if (max_length_nord > max_length_sud){
			c->longueur = max_length_nord + 2;
		}
		else{
			c->longueur = max_length_sud + 1;
		}
	}
}

//--------------------------------------------------------------------------------

void count_max_width(couloir *c){
	int max_width=0;
	int width_est = 0;
	int width_west = 0;
	int width_total_est = 0;
	int width_total_west = 0;
	int max_width_west = 0;
	int max_width_est = 0;
	
	char dernier_char;

	for (int i=0; (c->sequence)[i] != '\0'; i++){
		if((c->sequence)[i]=='E'){
			width_est++;
			width_total_est++;
		}
		else{
			if (width_est > max_width_est){
				max_width_est = width_est;
				width_est = 0;
			}
			else{
				width_est = 0;
			}
		}
		//------------------------------------------------
		if((c->sequence)[i] == 'N'){
			width_west++;
			width_total_west++;
		}
		else{
			if (width_west > max_width_west){
				max_width_west = width_west;
				width_west = 0;
			}
			else{
				width_west = 0;
			}
		}
		dernier_char = (c->sequence)[i];
	}

	if ((max_width_west ==0)||(max_width_est == 0)){
		if (max_width_west == 0){
			if (dernier_char == 'E'){
				c->width = width_total_est - 1;
			}
			else{
				c->width = width_total_est + 1;
			}
		}
		if (max_width_est == 0){
			if (dernier_char == 'W'){
				c->width = width_total_west - 1;
			}
			else{
				c->width = width_total_west + 1;
			}
		}
	}
	else{
		if (max_width_west > max_width_est){
			c->longueur = max_width_west + 2;
		}
		else{
			c->longueur = max_width_est + 1;
		}
	}
}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------