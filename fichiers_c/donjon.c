#include "donjon.h"
#include "fonctions_utiles.h"
#include "entites.h"
#include "couloir.h"
#include <stdio.h>
#include <stdlib.h>


a_donjon creer_donjon(int largeur, int longueur){
//allocation de la mémoire pour le donjon	
	a_donjon d = malloc(sizeof(donjon));
	if (d == NULL) {
        fprintf(stderr,"échec de l'allocation de mémoire d'un donjon");
        return NULL;
    	}
    
	// alloaction des dimensions 
	d->largeur = largeur;
	d->longueur = longueur;
	
	//allocation de la mémoire pour l'enceinte
	d->enceinte = (char**)malloc(longueur*sizeof(char*));
	for (int i = 0; i < longueur; i++){
		(d->enceinte)[i] = (char*)malloc(largeur*sizeof(char));
	}
	
	//gardons en mémoire la capacite et et le nbre d'éléments du tableau de couloirs pour gérer les realloc
	d->capacite_couloirs=1;
	d->nbre_elements_couloirs=0;
	
	//gardons en mémoire la capacite et et le nbre d'éléments du tableau de salles pour gérer les realloc
	d->capacite_salles=1;
	d->nbre_elements_salles=0;
	
	//tableau qui contient les a_entite entree et sortie du donjon, donc 2 éléments max!
	d->entree_sortie = (entite**)malloc(2*sizeof(a_entite));
	
	//allocation de mémoire pour les tableaux de salle** et couloir**
	d->salles_donjon = (salle_donjon**)malloc((d->capacite_salles)*sizeof(a_salle_donjon));
	d->couloirs_donjon = (couloir_donjon**)malloc((d->capacite_couloirs)*sizeof(a_couloir_donjon));
		
	// attribution de l'identifiant et mise à jour dans le fichier de configuration externe
	if (d != NULL) {
		int nouveau_id = lire_int("donjons/config.txt");
	   	d->id_donjon = ++nouveau_id;
	   	mettre_ajour_int("donjons/config.txt", d->id_donjon);
	}
		
	//remplissage des murs du donjon
	remplir_mur_donjon(d);
	  		
  	return d;
}


//remplissage des murs du donjon(contour du donjon)
void remplir_mur_donjon(a_donjon mon_donjon){
	//vérification
	if(mon_donjon==NULL){
		fprintf(stderr,"échec du remplissage des murs du donjon");
	}
	else {
		//remplissage des murs
		for (int i = 0; i <mon_donjon->longueur; i++) {
			for (int j = 0; j <mon_donjon->largeur; j++) {
				if(j==0 || i==0 || j==mon_donjon->largeur-1 || i==mon_donjon->longueur-1){
					(mon_donjon->enceinte)[i][j]='#';
					}
				else {
					(mon_donjon->enceinte)[i][j]=' ';
					 }
				}
  			}	
		}
}

//affiche un donjon dans le terminal
void affiche_donjon(a_donjon mon_donjon){
    for (int i = 0; i < mon_donjon->longueur; i++) {
        for (int j = 0; j < mon_donjon->largeur; j++) {
            printf("%c", (mon_donjon->enceinte)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


//affiche toutes les a_salle_donjon contenu dans le donjon, avec avec entier "entités" (si mi à 1, alors cela affiche aussi toutes les entités contenu dans les salles)
void affiche_salles_donjon(a_donjon mon_donjon){
	printf("Nombre de salles contenu dans le donjon : %d\n",mon_donjon->nbre_elements_salles);
	for(int i=0;i<mon_donjon->nbre_elements_salles;i++){
		affiche_salle_donjon(mon_donjon->salles_donjon[i]);
		}
}


//affcihe une a_salle_donjon et ses propriétes
void affiche_salle_donjon(a_salle_donjon une_salle){
	printf("dimensions : (%d,%d) | position: (%d,%d)\n",
		une_salle->salle->largeur, une_salle->salle->longueur, 
		une_salle->x, une_salle->y
		);
	affiche_entites_salle(une_salle->salle);
}			
	
	

//sauvegarde un donjon dans un fichier txt
int sauvegarder_donjon(a_donjon mon_donjon){
	FILE *fichier;
	
	//création du nom du fichier en utilisant l'id du donjon 
	char nom_fichier[50];
	sprintf(nom_fichier,"donjons/donjon%d.txt",mon_donjon->id_donjon);
	
	//ouverture du fichier 
	fichier = fopen(nom_fichier,"w+");
	+
	//erreur d'ouverture fichier
	if (fichier == NULL) {
        fprintf(stderr,"Impossible d'ouvrir le fichier %s pour l'écriture.\n",
			 nom_fichier);
        return 1;
    	}

	//écriture des dimensions du donjon 
	fprintf(fichier,"%d\n%d\n",mon_donjon->largeur,mon_donjon->longueur);
	
	//ecriture des salles contenu dans le donjon
	fprintf(fichier,"%d\n",mon_donjon->nbre_elements_salles);
	for(int i=0; i<mon_donjon->nbre_elements_salles; i++){
		fprintf(fichier,"%d\t%d\t%d\t%d\n",
		(mon_donjon->salles_donjon[i]->salle)->largeur,
		(mon_donjon->salles_donjon[i]->salle)->longueur,
		(mon_donjon->salles_donjon[i])->x,
		(mon_donjon->salles_donjon[i])->y
		);
		fprintf(fichier,"NORMALEMENT\n");
		
		//entites contenu dans la salle
		fprintf(fichier,"%d\n",mon_donjon->salles_donjon[i]->salle->nbre_elements);
		for(int j=0;i<mon_donjon->salles_donjon[i]->salle->nbre_elements;i++){
			fprintf(fichier,"%d\t%d\t%d\t%d\n",
			(mon_donjon->salles_donjon[i]->salle->entites_contenu[j])->id_entite,
			(mon_donjon->salles_donjon[i]->salle->entites_contenu[j])->x,
			(mon_donjon->salles_donjon[i]->salle->entites_contenu[j])->y,
			(mon_donjon->salles_donjon[i]->salle->entites_contenu[j])->interaction
			);
			}	
		}
	
	//ecriture des couloirs contenu dans le donjon 
	fprintf(fichier,"%d\n",mon_donjon->nbre_elements_couloirs);
	for(int i=0; i<mon_donjon->nbre_elements_couloirs; i++){
		fprintf(fichier,"%s\t%d\t%d\n",
		(mon_donjon->couloirs_donjon[i]->couloir)->sequence,
		(mon_donjon->couloirs_donjon[i])->x,
		(mon_donjon->couloirs_donjon[i])->y
		);
		}
	
	
	/*//écriture de la salle dans le fichier crée	
	for (int i = 0; i < s->longueur; i++) {
        for (int j = 0; j < s->largeur; j++) {
            	fprintf(fichier,"%c", (s->enceinte)[i][j]);
        }
        fprintf(fichier,"\n");
    	}
    fprintf(fichier,"\n");*/
    
    //fermeture du fichier 
    fclose(fichier);
    printf("Le fichier %s a été sauvegardé.\n", nom_fichier);
    return 0;    
}
