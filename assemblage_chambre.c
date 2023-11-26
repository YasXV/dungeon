#include "fonctions_utiles.h"
#include "assemblage_chambre.h"
#include "entites.h"
#include "chambre.h"
#include <stdio.h>
#include <stdlib.h>


//ajouter une entité dans une salle, par défaut le forcage est à 0! c'est à dire que si il y a dèjà une entité en x,y , on ne l'écrase pas !
void ajouter_entite(entite_id mon_entite_id, a_salle ma_salle, int x, int y, int interaction, int forcage){
	
	// calcul de entite_presente, qui vérifie si il y a déjà une entité présente ou non à la position x,y
	int present = verifier_entite_presente(ma_salle, x, y);
	
	// calcul de verifier_possibilite_ajout, retourne 0 si l'ajout de l'entité est possible à cette postion dans la salle 	
	int possible = verifier_possibilite_ajout(mon_entite_id, ma_salle, x, y, interaction);

	//cas où il n'y a pas dèjà une entité en x,y
	if(present==-1){	
		if(possible==0){
			//création de l'entité
			a_entite nouvelle_entite = creer_entite(mon_entite_id, x, y, interaction);
			
			// ajout de cette entité dans le tableau d'entité lié à la salle
			ajouter_tableau_entite(nouvelle_entite, ma_salle);
			
			// ajout du symbole de l'entité dans l'enceinte de la salle
			ma_salle->enceinte[y][x]=nouvelle_entite->symbole;
			}
		}
	
	//cas où il y a dèjà une entité en x,y
	else {
		if(possible==0){
			if(forcage==1){
				fprintf(stderr, "Attention, vous avez écraser l'entité en position (%d,%d).\n", x,y);
				// création de l'entité
				a_entite nouvelle_entite = creer_entite(mon_entite_id, x, y, interaction);
				
				//placement de l'entité à l'endroit où était l'ancienne entité si écrasement
				ma_salle->entites_contenu[present]=nouvelle_entite;
				
				// ajout du symbole de l'entité dans l'enceinte de la salle
				ma_salle->enceinte[y][x]=nouvelle_entite->symbole;
				}

			else {
				fprintf(stderr, "Vous avez choisi de ne pas écraser l'entité.\n");
				}	
			}
		}
}

//vérifie si une entité est déjà présente à la position x,y dans la salle, retourne l'indice, dans le tableau d'entites lié à la salle, où est contenu l'entité à la position x,y 
int verifier_entite_presente(a_salle ma_salle, int x, int y){
	for(int i =0;i<ma_salle->nbre_elements; i++){
		if(ma_salle->entites_contenu[i]->x==x && ma_salle->entites_contenu[i]->y==y){
			return i;
			}    
	}
	return -1;
}

//vérification sur l'ajout d'une entité dans la salle (une porte doit être ajoutéee sur un mur obligatoirement, les autres entités doivent être ajoutées hors des murs)
int verifier_possibilite_ajout(entite_id mon_entite_id, a_salle ma_salle, int x, int y, int interaction){

	//cas d'ajout d'une porte
	if(mon_entite_id==PORTE){
		if(ma_salle->enceinte[y][x]!='#' && ma_salle->enceinte[y][x]!='F' & ma_salle->enceinte[y][x]!='O' ){
			fprintf(stderr, "Vous essayez d'ajouter une porte hors d'un mur. Aucune modification apportée.\n");
			return 1;
			}
		else{
			return 0;
			}
	}
	
	//cas d'ajout des autres entités
	else {
		if(x==0 || y==0 || x== ma_salle->longueur-1 || y==ma_salle->largeur-1){
			fprintf(stderr, "Vous essayez d'ajouter une entité, qui n'est pas une porte, dans un mur. Aucune modification apportée.\n");
			return 1;
			}
		else{
			return 0;
			}	
		}
}


// fonction qui ajoute une entite dans l'attribut tableau entites lié à une salle
int ajouter_tableau_entite(a_entite mon_entite, a_salle ma_salle){

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
        fprintf(stderr,"échec de l'allocation de mémoire d'une salle");
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
    	ajouter_entite(id,s,x,y,interaction,0);
    }
		
	// attribution de l'identifiant et mise à jour dans le fichier de configuration externe
	if (s != NULL) {
	int nouveau_id = lire_int("chambres/config.txt");
	   	s->id_salle = ++nouveau_id;
	   	mettre_ajour_int("chambres/config.txt", s->id_salle);
	}
   
	return s;
}

//interagis avec une entite à la position (x,y) dans une salle
void interagir_entite(a_salle ma_salle, int x, int y){
	
	//vérifie qu'il y a bien une entité avec laquelle interagir en x,y
	int i = verifier_entite_presente(ma_salle, x, y);

	//si il y a une entite avec la laquelle interagire en x,y
	if(i!=-1){
		//differenciation des differents types d'entites
		switch(ma_salle->entites_contenu[i]->id_entite){
			case MONSTRE:
				if(ma_salle->entites_contenu[i]->interaction==0){
					ma_salle->entites_contenu[i]->symbole ='w';
					ma_salle->entites_contenu[i]->interaction=1;
					ma_salle->enceinte[y][x]='w';
					}
				else{
					fprintf(stderr, "MONSTRE déjà mort.\n");
					}
				break;
			
			case BOSS:
				if(ma_salle->entites_contenu[i]->interaction==0){
					ma_salle->entites_contenu[i]->symbole ='W';
					ma_salle->entites_contenu[i]->interaction=1;
					ma_salle->enceinte[y][x]='W';
					}
				else{
					fprintf(stderr, "BOSS déjà mort.\n");
					}
				break;
			
			case COFFRE:
				if(ma_salle->entites_contenu[i]->interaction==0){
					ma_salle->entites_contenu[i]->symbole ='U';
					ma_salle->entites_contenu[i]->interaction=1;
					ma_salle->enceinte[y][x]='U';
					}
				else{
					fprintf(stderr, "COFFRE déjà ouvert.\n");
					}
				break;
			
			case ENTREE:
				fprintf(stderr, "Impossible d'interagir avec une ENTREE, pour l'instant :)\n");
				break;
				
			case SORTIE:
				if(ma_salle->entites_contenu[i]->interaction==0){
					ma_salle->entites_contenu[i]->symbole ='s';
					ma_salle->entites_contenu[i]->interaction=1;
					ma_salle->enceinte[y][x]='s';
					}
				else{
					fprintf(stderr, "SORTIE déjà ouverte.\n");
					}
				break;
				
			case AUTEL:
				if(ma_salle->entites_contenu[i]->interaction==0){
					ma_salle->entites_contenu[i]->symbole ='a';
					ma_salle->entites_contenu[i]->interaction=1;
					ma_salle->enceinte[y][x]='a';
					}
				else{
					fprintf(stderr, "AUTEL déjà utilisé.\n");
					}
				break;
				
			case PORTE:
				if(ma_salle->entites_contenu[i]->interaction==0){
					ma_salle->entites_contenu[i]->symbole ='O';
					ma_salle->entites_contenu[i]->interaction=1;
					ma_salle->enceinte[y][x]='O';
					}
				else{
					fprintf(stderr,"PORTE déjà ouverte.\n");
					}
				break;
				
			case PIEGE:
				if(ma_salle->entites_contenu[i]->interaction==0){
					ma_salle->entites_contenu[i]->symbole ='p';
					ma_salle->entites_contenu[i]->interaction=1;
					ma_salle->enceinte[y][x]='p';
					}
				else{
					fprintf(stderr,"PIEGE déjà activé.\n");
					}
				break;
				
			case MUR:
					fprintf(stderr, "Impossible d'interagir avec un MUR, pour l'instant :)\n");
				break;

			default:
				fprintf(stderr, "Type d'entité non reconnue. Veuillez réessayer.\n");
				break;
			}	
		}
		
		//si il n'y a pas d'entite avec laquelle interagir en (x,y)
		else {
			fprintf(stderr, "Pas d'entité avec laquelle interagir en position (%d,%d)\n",x,y);
			}
	}

