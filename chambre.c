// C File standard
//--------------------------------------------------------------------------------
//  File chambre.c
// Date: 19 Nov 2023
//--------------------------------------------------------------------------------

#include "chambre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entites.h"
#include "fonctions_utiles.h"
//--------------------------------------------------------------------------------

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
	
	//gardons en mémoire la capacite et et le nbre d'éléments du tableau gérer les realloc
	s->capacite_actuelle=1;
	s->nbre_elements=0;

	//allocation de la mémoire pour le tableau d'entites, qui n'a de la place pour contenir qu'un seul élément par defaut, on fera des realloc en fonction des ajouts
	s->entites_contenu = (entite**)malloc((s->capacite_actuelle)*sizeof(a_entite));
	
	// attribution de l'identifiant et mise à jour dans le fichier de configuration externe
	if (s != NULL) {
		int nouveau_id = lire_int("config.txt");
	   	s->id_salle = ++nouveau_id;
	   	mettre_ajour_int("config.txt", s->id_salle);
	}
		
	//remplissage des murs
	remplir_mur_salle(s);
	  		
  	return s;
}

//--------------------------------------------------------------------------------

//remplis les murs d'une salle (contour de la salle)
void remplir_mur_salle(a_salle salle){
	//vérification
	if(salle==NULL){
		fprintf(stderr,"échec du remplissage des murs de la salle");
	}
	
	//remplissage des murs
	for (int i = 0; i <salle->longueur; i++) {
	for (int j = 0; j <salle->largeur; j++) {
		if(j==0 || i==0 || j==salle->largeur-1 || i==salle->longueur-1){
			(salle->enceinte)[i][j]='#';
			}
		else {
			(salle->enceinte)[i][j]=' ';
			 }
		}
  	}	
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

// afficher toutes les entités, et leurs propriétes, contenu dans une salle
void affiche_entites_salle(a_salle ma_salle){
	printf("Nombre d'entités contenu dans la salle : %d\n",ma_salle->nbre_elements);
	for(int i=0;i<ma_salle->nbre_elements;i++){
		affiche_entite(ma_salle->entites_contenu[i]);
		}
}

//--------------------------------------------------------------------------------

//sauvegarder une salle dans un fichier
int sauvegarder_salle(a_salle s){
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
	
	//ecriture des entités contenu dans la salle
	fprintf(fichier,"%d\n",s->nbre_elements);
	for(int i=0;i<s->nbre_elements;i++){
		fprintf(fichier,"%d\t%d\t%d\t%d\n",
		(s->entites_contenu[i])->id_entite,
		(s->entites_contenu[i])->x,
		(s->entites_contenu[i])->y,
		(s->entites_contenu[i])->interaction
		);
	}
	
	//écriture de la salle dans le fichier crée	
	for (int i = 0; i < s->longueur; i++) {
        for (int j = 0; j < s->largeur; j++) {
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



//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------
