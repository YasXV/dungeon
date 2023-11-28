//! C standard
// encoding: utf-8
//------------------------------------------------------------------
// File assemblage_donjon.c
// Date : 27 Nov 2023
//------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "assemblage_donjon.h"
#include "donjon.h"
#include "assemblage_chambre.h"
#include "entites.h"
#include "chambre.h"
//------------------------------------------------------------------

//ajoute une salle dans mon donjon à la position x, y, forcage est un entier qui si il est égal à 0, autorise l'écrasement d'une salle par une autre!
void ajouter_salle(a_donjon mon_donjon, a_salle une_salle, int x, int y, int forcage){	
	//qui vérifie si il y a déjà une salle en superposition de la salle que je veux ajouter
	int present = verifier_salle_presente(mon_donjon, une_salle, x, y);
	

	//cas où il n'y a pas dèjà une entité en x,y
	if(present==-1){
		// creation d'une a_salle_donjon et ajout de ma_salle dans celle-ci
		a_salle_donjon salle_dans = malloc(sizeof(a_salle_donjon));
		if (salle_dans == NULL) {
			fprintf(stderr,"échec de l'allocation de mémoire d'une salle dans un donjon");
		}
		salle_dans->salle = une_salle;

		//ajout des coordonnées dans le donjon de la a_salle_donjon
		salle_dans->x = x;
		salle_dans->y = y;
					
		// ajout de cette a_salle_donjon dans le tableau de a_salle_donjon lié au donjon
		ajouter_tableau_salles(salle_dans, mon_donjon);
		
		// ajout de la a_salle_donjon dans l'enceinte du donjon
		for (int i = 0; i <salle_dans->salle->longueur; i++) {
			for (int j = 0; j <salle_dans->salle->largeur; j++) {
				mon_donjon->enceinte[y+i][x+j] = salle_dans->salle->enceinte[i][j];
			}		 
		}
	}
}

//------------------------------------------------------------------

// ajoute une salle dans le tableau de salle lié au donjon
int ajouter_tableau_salles(a_salle_donjon une_salle, a_donjon mon_donjon){
	
	//on vérifie que l'ajout d'une salle ne nous fait pas arriver à la limite de capacité, si oui, nous faisons une réallocation (2 places en plus)
	if (mon_donjon->nbre_elements_salles == mon_donjon->capacite_salles) {
		mon_donjon->capacite_salles +=2;
    	mon_donjon->salles_donjon = realloc(mon_donjon->salles_donjon, mon_donjon->capacite_salles*sizeof(a_salle_donjon));
    	printf("réallocation dynamique car plus de place, capacité actuelle : %d\n",mon_donjon->capacite_salles);
    }
	printf("capacité actuelle : %d\n",mon_donjon->capacite_salles);
    // Vérifier si la réallocation a réussi
    if (mon_donjon->salles_donjon == NULL) {
        fprintf(stderr, "Échec de la réallocation de mémoire pour le tableau dynamique de salles.\n");
        return 1;  // Code d'erreur
    }
    
	mon_donjon->salles_donjon[mon_donjon->nbre_elements_salles] = une_salle;
	mon_donjon->nbre_elements_salles++;
    return 0;
}

//------------------------------------------------------------------

//ajoute une entité à la position x, y (relative au donjon) , celle-ci va s'attacher automatiquement à une salle si la position x,y est dans une salle
void ajouter_entite_donjon(entite_id mon_entite_id, a_donjon mon_donjon, int x, int y, int interaction, int forcage){
	
	//verifie si l'entité va se trouver dans une salle, si oui, i est l'indice dans le tableau de a_salle_donjon où ajouter l'entité
	int i = verifier_entite_donjon(mon_donjon, x, y);
	if(i != -1){
		//création d'une entité qui va juste nous servir à récupérer le bon symbole pour l'ajouter au donjon ( car ajout_entite s'occupe de tout le reste)
		a_entite nouvelle_entite = creer_entite(mon_entite_id, x, y, interaction);

		//on récupére la bonne a_salle_donjon
		a_salle_donjon ma_salle = mon_donjon->salles_donjon[i];
		
		//on apelle la fonction ajouter_entite, et on fait attention a mettre les positions relatives à la salle maintenant
		ajouter_entite(mon_entite_id, ma_salle->salle, x-ma_salle->x, y-ma_salle->y, interaction, forcage);
		
		//ajout dans l'enceinte du donjon la nouvelle entite
			mon_donjon->enceinte[y][x] = nouvelle_entite->symbole;
	}
	else {
		fprintf(stderr, "Pas de salle là où vous voulez placer l'entité.\n");	
	}
}

//------------------------------------------------------------------
	
//verifie si l'entité qu'on veut ajouter à la position x,y dans le donjon sera bien contenu dans une salle, si oui retourne l'indice i de la a_salle_donjon dans le tableau des  a_salles_donjon où l'entité va se retrouver 
int verifier_entite_donjon(a_donjon mon_donjon, int x, int y){
	for(int i = 0;i<mon_donjon->nbre_elements_salles; i++){
		if((x>= mon_donjon->salles_donjon[i]->x && x < mon_donjon->salles_donjon[i]->x + mon_donjon->salles_donjon[i]->salle->largeur) &&
			(y>= mon_donjon->salles_donjon[i]->y && y < mon_donjon->salles_donjon[i]->y + mon_donjon->salles_donjon[i]->salle->longueur))
		{
		 	printf("DANS UNE SALLE OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
			return i;
		}    
	}
	return -1;
}

//------------------------------------------------------------------

// ajoute un couloir dans le tableau de couloir lié au donjon
int ajouter_tableau_couloirs(a_couloir_donjon un_couloir, a_donjon mon_donjon){
	
	//on vérifie que l'ajout d'un couloir ne nous fait pas arriver à la limite de capacité, si oui, nous faisons une réallocation (3 places en plus)
	if (mon_donjon->nbre_elements_couloirs == mon_donjon->capacite_couloirs) {
		mon_donjon->capacite_couloirs +=3;
    	mon_donjon->couloirs_donjon = realloc(mon_donjon->couloirs_donjon, mon_donjon->capacite_couloirs*sizeof(a_couloir_donjon));
    	printf("réallocation dynamique car plus de place, capacité actuelle : %d\n",mon_donjon->capacite_couloirs);
    	}

    // Vérifier si la réallocation a réussi
    if (mon_donjon->couloirs_donjon == NULL) {
        fprintf(stderr, "Échec de la réallocation de mémoire pour le tableau dynamique de couloirs.\n");
        return 1;  // Code d'erreur
    }


	mon_donjon->couloirs_donjon[mon_donjon->nbre_elements_couloirs++] = un_couloir;

    
    return 0;
}

//------------------------------------------------------------------

//vérifie si il y a possiblement superposition de salle lors de l'ajout d'une salle en x,y, si oui retourne l'indice i de la salle dans le tableau des salles lié au donjon (pour pouvoir l'écraser si besoin), si non, retourne -1 
int verifier_salle_presente(a_donjon mon_donjon, a_salle une_salle, int x, int y){
	for(int i =0;i<mon_donjon->nbre_elements_salles; i++){
		if(((x >= mon_donjon->salles_donjon[i]->x && x < mon_donjon->salles_donjon[i]->x + mon_donjon->salles_donjon[i]->salle->largeur)  &&
		 (y >= mon_donjon->salles_donjon[i]->y && y < mon_donjon->salles_donjon[i]->y + mon_donjon->salles_donjon[i]->salle->longueur)) || 
		 (x < mon_donjon->salles_donjon[i]->x && (y >= mon_donjon->salles_donjon[i]->y && y < mon_donjon->salles_donjon[i]->y + mon_donjon->salles_donjon[i]->salle->longueur)) ||
		 ((x >= mon_donjon->salles_donjon[i]->x && x < mon_donjon->salles_donjon[i]->x + mon_donjon->salles_donjon[i]->salle->largeur) && y < mon_donjon->salles_donjon[i]->y)
		 ){
		 	printf("OUHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHou superposition\n");
			return i;
			}    
	}
	return -1;
}

//------------------------------------------------------------------

//récupération d'un dnjon depuis un fichier dans un a_donjon
a_donjon recup_donjon(char* nom_fichier){
	FILE *fichier;
	
	//ouverture du fichier 
	fichier = fopen(nom_fichier,"r");
	
	//erreur d'ouverture fichier
	if (fichier == NULL) {
        fprintf(stderr,"Impossible d'ouvrir le fichier %s pour la lecture.\n",
				 nom_fichier);
    }
	
    //lecture des dimensions
    int largeur, longueur;
    fscanf(fichier, "%d\n%d\n", &(largeur), &(longueur));
    
    //création du donjon
    a_donjon d = creer_donjon(largeur, longueur);
    
    //lecture de la capacité du tableau de salles_donjon
    fscanf(fichier,"%d\n", &(d->capacite_salles));
    //printf("capacité du tableau de salles : %d\n",d->capacite_salles);
    //allocation de la mémoire pour le tableau de a_salle_donjon avec la capacité récupérer du fichier
    d->salles_donjon = (salle_donjon**)realloc(d->salles_donjon,(d->capacite_salles)*sizeof(a_salle_donjon));
	//lecture des salles, création de celles-ci et ajout dans le tableau de a_salle_donjon lié au donjon
	int boucle = d->capacite_salles;
	int largeur2,longueur2,x,y;
    for(int i=0;i<boucle;i++){ 
    	fscanf(fichier,"%d\t%d\t%d\t%d\n",&largeur2,&longueur2,&x,&y);
    	a_salle s = creer_salle(largeur2,longueur2);

    	//lecture des entités, création de celles-ci et ajout dans la salle
		int boucle2;
		int capacite;
		fscanf(fichier,"%d\n",&(s->capacite_actuelle));
		boucle2 = s->capacite_actuelle;
		int x_entite,y_entite,id,interaction;
    	for(int j=0;j<boucle2;j++){
			fscanf(fichier,"%d\t%d\t%d\t%d\n",&id,&x_entite,&y_entite,&interaction);
			ajouter_entite(id, s, x_entite, y_entite, interaction,0);
    	}
    	//ajout de la salle rempli de ses entités dans le donjon
    	ajouter_salle(d, s, x, y, 0);
    }
   
	return d;
}

//------------------------------------------------------------------
//End OF File
//------------------------------------------------------------------