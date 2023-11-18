#include "chambre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Variable statique pour maintenir le dernier identifiant attribué
static int dernierIdAttribue_salle = 0;

//initialisation d'une salle
void init_salle(salle *s, int largeur, int longueur){
	s->largeur = largeur;
	s->longueur = longueur;
	
	//allocation de la mémoire 
	s->enceinte = (char**)malloc(longueur*sizeof(char*));
	for (int i = 0; i < longueur; i++) {
        	(s->enceinte)[i] = (char*)malloc(largeur*sizeof(char));
	}
		
	// attribution de l'identifiant 
	if (s != NULL) {
        s->id_salle = ++dernierIdAttribue_salle;
    	}
    	
	//contour des murs
	for (int i = 0; i <longueur; i++) {
	for (int j = 0; j <largeur; j++) {
		if(j==0 || i==0 || j==largeur-1 || i==longueur-1){
			(s->enceinte)[i][j]='#';
			}
		else {(s->enceinte)[i][j]=' ';}
    		}
  		}
 	}


//afficher la salle dans le terminal
void affiche_salle(salle *s){
    for (int i = 0; i < s->longueur; i++) {
        for (int j = 0; j < s->largeur; j++) {
            printf("%c", (s->enceinte)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//sauvegarder une salle dans un fichier
void sauvegarder_salle(salle *s){
	FILE *fichier;
	
	//erreur d'ouverture fichier
	if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s pour l'écriture.\n", nom_fichier);
        return;
    	}
    	
    	//création du nom du fichier en utilisant l'id de la salle 
	char nom_fichier[20];
	sprintf(nom_fichier,"salle%d.txt",s->id_salle);
	
	//ouverture du fichier 
	fichier = fopen(nom_fichier,"w");
	
	//écriture des dimensions de la salle 
	fprintf(fichier,"%d\n",s->largeur);
	fprintf(fichier,"%d\n", s->longueur);
	
	//écriture de la salle dans le fichier crée	
	for (int i = 0; i < s->longueur; i++) {
        for (int j = 0; j < s->largeur; j++) {
        	if((s->enceinte)[i][j]=='#'){
            		fprintf(fichier,"%c", (s->enceinte)[i][j]);
            	}
            	else {
            	fprintf(fichier,"%c",' ');
            	}
        }
        fprintf(fichier,"\n");
    	}
    fprintf(fichier,"\n");
    
    //fermeture du fichier 
    fclose(fichier);
    printf("Le fichier %s a été sauvegardé.\n", nom_fichier);    
 }
