#include "assemblage_chambre.h"
#include "fonctions_utiles.h"
#include "entites.h"
#include "chambre.h"
#include <stdio.h>
#include <stdlib.h>



// ajouter une entité dans une salle
void ajout_entite(entite_id mon_entite_id, a_salle ma_salle, int x, int y, int interaction){
	//création de l'entité
	a_entite nouvelle_entite = creer_entite(mon_entite_id, x, y, interaction);
	
	// ajout de cette entité dans le tableau d'entité lié à la salle
	ajout_tableau_entite(nouvelle_entite, ma_salle);
	
	// ajout du symbole de l'entité dans l'enceinte de la salle
	ma_salle->enceinte[y][x]=nouvelle_entite->symbole;
}


// fonction qui ajoute une entite dans l'attribut tableau entites lié à une salle
int ajout_tableau_entite(a_entite mon_entite, a_salle ma_salle){

	//on ajoute notre entite dans le tableau d'entites lié à la salle
	ma_salle->entites_contenu[ma_salle->nbre_elements++]=mon_entite;
	
	//on vérifie que l'ajout d'une nouvelle entité ne nous fait pas arriver à la limite de capacité, si oui, nous faisons une réallocation en fonction de la dimension de la salle
	if (ma_salle->nbre_elements == ma_salle->capacite_actuelle) {
		ma_salle->capacite_actuelle +=(int)((ma_salle->largeur*ma_salle->longueur)/100);
    	ma_salle->entites_contenu = realloc(ma_salle->entites_contenu, ma_salle->capacite_actuelle*sizeof(entite));
    	printf("réallocation dynamique car plus de place, capacité actuelle : %d\n",ma_salle->capacite_actuelle);
    	}

    // Vérifier si la réallocation a réussi
    if (ma_salle->entites_contenu == NULL) {
        fprintf(stderr, "Échec de la réallocation de mémoire pour le tableau dynamique d'entités.\n");
        return 1;  // Code d'erreur
    }
    
    return 0;
}

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
	
	//creation d'une salle complétement vide
	//allocation de la mémoire pour la salle 	
	a_salle s = malloc(sizeof(salle));
	if (s == NULL) {
        printf("échec de l'allocation de mémoire d'une salle");
        return NULL;
    }
    
    //lecture des dimensions
    fscanf(fichier, "%d\n%d\n", &(s->largeur), &(s->longueur));
    
    //lecture de la capacité du tableau
    fscanf(fichier,"%d\n", &(s->capacite_actuelle));
    
    //le nombre d'éléments est pour l'instant égal à 0 car nours n'avons pas encore rempli le tableau d'entités
    s->nbre_elements = 0;

    //allocation de la mémoire pour le tableau d'entités
    s->entites_contenu = (entite**)malloc((s->capacite_actuelle)*sizeof(a_entite));
	
	//allocation de la mémoire pour l'enceinte
	s->enceinte = (char**)malloc(s->longueur*sizeof(char*));
	for (int i = 0; i < s->longueur; i++){
		(s->enceinte)[i] = (char*)malloc(s->largeur*sizeof(char));
	}
	
	// remplissage des murs 
	remplir_mur_salle(s);
	
	//lecture des entités, création de celles-ci et ajout dans le tableau d'entités lié à la salle
	int boucle = s->capacite_actuelle;
	int x,y,id,interaction;
    for(int i=0;i<boucle;i++){ 	
    	fscanf(fichier,"%d\t%d\t%d\t%d\n",&id,&x,&y,&interaction);
    	ajout_entite(id,s,x,y,interaction);
    }
		
	// attribution de l'identifiant et mise à jour dans le fichier de configuration externe
	if (s != NULL) {
		int nouveau_id = lire_int("config.txt");
	   	s->id_salle = ++nouveau_id;
	   	mettre_ajour_int("config.txt", s->id_salle);
	}
   
	return s;
}



