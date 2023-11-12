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
}

//--------------------------------------------------------------------------------

void affiche(couloir *c){
	for (int i=0; (c->sequence)[i] != '\0'; i++) {
		printf("%c\n", (c->sequence)[i]);
		int count = count_occurence_direction(c, i, (c->sequence)[i]);
		if ((c->sequence)[i] == 'N'){
			continue;
		}
		else if ((c->sequence)[i]=='S'){
			if (count > 1){
				printf("# #\n");
			}
			else{
				printf("#\n");
			}
			continue;
		}
		else if ((c->sequence)[i]=='E'){
			continue;
		}
		else if ((c->sequence)[i]=='W'){
			continue;
		}
		else {
			printf("erreur de saisie\n");
		}
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
// end file
//--------------------------------------------------------------------------------