#include <stdio.h>
#include <stdlib.h>
#include "assemblage_donjon.h"
#include "donjon.h"
#include "assemblage_chambre.h"
#include "entites.h"
#include "chambre.h"


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

// ajoute une salle dans le tableau de salle lié au donjon
int ajouter_tableau_salles(a_salle_donjon une_salle, a_donjon mon_donjon){
	mon_donjon->salles_donjon[mon_donjon->nbre_elements_salles++] = une_salle;
	
	//on vérifie que l'ajout d'une salle ne nous fait pas arriver à la limite de capacité, si oui, nous faisons une réallocation (2 places en plus)
	if (mon_donjon->nbre_elements_salles == mon_donjon->capacite_salles) {
		mon_donjon->capacite_salles +=2;
    	mon_donjon->salles_donjon = realloc(mon_donjon->salles_donjon, mon_donjon->capacite_salles*sizeof(a_salle_donjon));
    	printf("réallocation dynamique car plus de place, capacité actuelle : %d\n",mon_donjon->capacite_salles);
    	}

    // Vérifier si la réallocation a réussi
    if (mon_donjon->salles_donjon == NULL) {
        fprintf(stderr, "Échec de la réallocation de mémoire pour le tableau dynamique de salles.\n");
        return 1;  // Code d'erreur
    }
    
    return 0;
}

//ajoute une entité à la position x, y (relative au donjon) , celle-ci va s'attacher automatiquement à une salle si la position x,y est dans une salle
void ajouter_entite_donjon(entite_id mon_entite_id, a_donjon mon_donjon, int x, int y, int interaction, int forcage){
	
	//verifie si l'entité va se trouver dans une salle, si oui, i est l'indice dans le tableau de a_salle_donjon où ajouter l'entité
	int i = verifier_entite_donjon(mon_donjon, x, y);
	
	if(i!=-1){
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

	
//verifie si l'entité qu'on veut ajouter à la position x,y dans le donjon sera bien contenu dans une salle, si oui retourne l'indice i de la a_salle_donjon dans le tableau des  a_salles_donjon où l'entité va se retrouver 
int verifier_entite_donjon(a_donjon mon_donjon, int x, int y){
	for(int i =0;i<mon_donjon->nbre_elements_salles; i++){
		if((x>= mon_donjon->salles_donjon[i]->x && x <= mon_donjon->salles_donjon[i]->x + mon_donjon->salles_donjon[i]->salle->largeur) &&
			(y>= mon_donjon->salles_donjon[i]->y && y <= mon_donjon->salles_donjon[i]->y + mon_donjon->salles_donjon[i]->salle->longueur))
		 {
		 	printf("DANS UNE SALLE OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
			return i;
			}    
	}
	return -1;
}


// ajoute un couloir dans le tableau de couloir lié au donjon
int ajouter_tableau_couloirs(a_couloir_donjon un_couloir, a_donjon mon_donjon){
	mon_donjon->couloirs_donjon[mon_donjon->nbre_elements_couloirs++] = un_couloir;
	
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
    
    return 0;
}

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
