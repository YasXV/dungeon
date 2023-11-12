#include "couloir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void init(couloir *c, int largeur, const char *sequence){
	c->largeur = largeur;
	c->sequence = malloc(strlen(sequence) + 1);
	strcpy(c->sequence,sequence);
}

void affiche(couloir *c){
	for (int i=0; (c->sequence)[i] != '\0'; i++) {
	printf("%c\n",(c->sequence)[i]);
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

void orientation(const char *sequence){
/*E S W N */
	
}

int count_north(const char *sequence){
	int north=0;
	for (int i=0; (sequence)[i] != '\0'; i++){
		if((sequence)[i]=='N'){
		north++;
		}
	}
	return north;
}

int count_west(const char *sequence){
	int west=0;
	for (int i=0; (sequence)[i] != '\0'; i++){
		if((sequence)[i]=='W'){
		west++;
		}
	}
	return west;
}
