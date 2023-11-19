// C File standard
//--------------------------------------------------------------------------------
//  File chambre.c
// Date: 19 Nov 2023
//--------------------------------------------------------------------------------

#include "chambre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------

//Variable statique pour maintenir le dernier identifiant attribué
static int dernierIdAttribue_salle = 0;

//--------------------------------------------------------------------------------

//creation et initialisation d'une salle
a_salle creer_salle(int largeur, int longueur){
	
	//allocation de la mémoire pour la salle 	
	a_salle s = malloc(sizeof(salle));
	if (s == NULL) {
        printf("échec de l'allocation de mémoire d'une salle");
        return NULL;
    	}
    
    // alloaction des dimensions 
	s->largeur = largeur;
	s->longueur = longueur;
	
	//allocation de la mémoire pour l'enceinte
	s->enceinte = (char**)malloc(longueur*sizeof(char*));
	for (int i = 0; i < longueur; i++){
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
		else {
			(s->enceinte)[i][j]=' ';
			}
    	}
  	}
  		
  	return s;
}

//--------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------

//sauvegarder une salle dans un fichier
int sauvegarder_salle(salle *s){
	FILE *fichier;
	
	//création du nom du fichier en utilisant l'id de la salle 
	char nom_fichier[50];
	sprintf(nom_fichier,"chambres/salle%d.txt",s->id_salle);
	
	//ouverture du fichier 
	fichier = fopen(nom_fichier,"w+");
	
	//erreur d'ouverture fichier
	if (fichier == NULL) {
        fprintf(stderr,"Impossible d'ouvrir le fichier %s pour l'écriture.\n",
			 nom_fichier);
        return 1;
    	}

	//écriture des dimensions de la salle 
	fprintf(fichier,"%d\n%d\n",s->largeur,s->longueur);
	
	//écriture de la salle dans le fichier crée	
	for (int i = 0; i < s->longueur; i++) {
        for (int j = 0; j < s->largeur; j++) {
        	/*if((s->enceinte)[i][j]!=' '){
            		fprintf(fichier,"%c", (s->enceinte)[i][j]);
            	}
            	else{
            	fprintf(fichier,"%c",' ');
            	}*/
            	fprintf(fichier,"%c", (s->enceinte)[i][j]);
        }
        fprintf(fichier,"\n");
    	}
    fprintf(fichier,"\n");
    
    //fermeture du fichier 
    fclose(fichier);
    printf("Le fichier %s a été sauvegardé.\n", nom_fichier);
    return 0;    
}

//--------------------------------------------------------------------------------

//récupération d'une salle depuis un fichier dans un a_salle
a_salle recup_salle(char* nom_fichier){
	FILE *fichier;
	
	//ouverture du fichier 
	fichier = fopen(nom_fichier,"r");
	
	//erreur d'ouverture fichier
	if (fichier == NULL) {
        fprintf(stderr,"Impossible d'ouvrir le fichier %s pour la lecture.\n",
				 nom_fichier);
    }
	
	//creation d'une salle complétement vide (sans mur, car ces informations sont contenu dans le fichier)
	//allocation de la mémoire pour la salle 	
	a_salle s = malloc(sizeof(salle));
	if (s == NULL) {
        printf("échec de l'allocation de mémoire d'une salle");
        return NULL;
    }
    
    //lecture des dimensions
    fscanf(fichier, "%d\n%d", &(s->largeur), &(s->longueur));
	
	//allocation de la mémoire pour l'enceinte
	s->enceinte = (char**)malloc(s->longueur*sizeof(char*));
	for (int i = 0; i < s->longueur; i++){
		(s->enceinte)[i] = (char*)malloc(s->largeur*sizeof(char));
	}
		
	// attribution de l'identifiant 
	if (s != NULL) {
       	s->id_salle = ++dernierIdAttribue_salle;
    }

	char _[256];
	fgets(_, 256, fichier);

	//remplissage de la salle
	char caractere_actuel=' ';
	for (int i = 0; i < s->longueur; i++) {
		fgets(s->enceinte[i], s->largeur+2, fichier);
	} // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
    
	return s;
}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------