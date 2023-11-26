#include "entites.h"
#include <stdio.h>
#include <stdlib.h>


//une seule fonction qui peut crée n'importe qu'elle type d'entité, en fonction du entite_id donné, x et y sont les postions relatifs à la chambre! interaction est un int qui vaut 1 ou 0 
// 1 veut dire que nous avon dékà interagis avec cette entité (exemple coffre ouvert, monstre mort, porte ouverte) 0 nous n'avons pas interagis ! 
a_entite creer_entite(entite_id id, int x, int y, int interaction){

//creation d'une novelle entite 
	a_entite nouvelle_entite = malloc(sizeof(entite));
	if (nouvelle_entite == NULL) {
		printf("échec de l'allocation de mémoire d'une entite");
		return NULL;
	}
	nouvelle_entite->interaction = interaction;
	nouvelle_entite->x = x;
	nouvelle_entite->y = y;
	nouvelle_entite->id_entite = id;
	
	//differenciation des differents types d'entites
	switch(id){
		case MONSTRE:
			if(interaction==0){
				nouvelle_entite->symbole ='M';
			}
			else{
				nouvelle_entite->symbole ='w';
				}
			break;
		
		case BOSS:
			if(interaction ==0){
				nouvelle_entite->symbole ='B';
			}
			else{
				nouvelle_entite->symbole ='W';
				}
			break;
		
		case COFFRE:
			if(interaction==0){
				nouvelle_entite->symbole ='C';
			}
			else{
				nouvelle_entite->symbole ='U';
				}
			break;
		
		case ENTREE:
			nouvelle_entite->symbole ='E';
			break;
			
		case SORTIE:
			if(interaction==0){//une sortie peut être fermée, exemple : on doit ouvrir la porte en récupérant une clé sur un boss d'une certaine chambre)
				nouvelle_entite->symbole ='S';
			}
			else{
				nouvelle_entite->symbole ='s';
				}
			break;
			break;
			
		case AUTEL:
			if(interaction==0){
				nouvelle_entite->symbole ='A';
			}
			else{
				nouvelle_entite->symbole ='a';
				}
			break;
			
		case PORTE:
			if(interaction==0){
				nouvelle_entite->symbole ='F';
			}
			else{
				nouvelle_entite->symbole ='O';
				}
			break;
			
		case PIEGE:
			if(interaction==0){
				nouvelle_entite->symbole ='P';
			}
			else{
				nouvelle_entite->symbole ='p';
				}
			break;
			
		case MUR:
			nouvelle_entite->symbole ='#';
			break;

		default:
			printf("Type d'entité non reconnue. Veuillez réessayer.\n");
			return NULL;
	}
	return nouvelle_entite;
}

// retourne un char* indiquant le type d'entité 
char* avoir_type_entite(a_entite mon_entite){
	//tableau permettant de retrouver textuellement le type d'entité
	char* entite_nom[NB_ENTITE]={"ENTREE", "SORTIE", "PORTE", "AUTEL","PIEGE","MUR","COFFRE","MONSTRE","BOSS"};
	char* nom = entite_nom[mon_entite->id_entite];
	return nom;
}

//affiche une entité avec ses propriétes
void affiche_entite(a_entite mon_entite){
	printf("type : %s | interaction : %d | position: (%d,%d)\n",
		avoir_type_entite(mon_entite), mon_entite->interaction, 
		mon_entite->x, mon_entite->y
		);	
}			
			
