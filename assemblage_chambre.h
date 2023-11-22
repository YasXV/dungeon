#ifndef ASSEMBLAGE_CHAMBRE_H
#define ASSEMBLAGE_CHAMBRE_H
#include "entites.h"
#include "chambre.h"


//fonction qui ajoute une entité (type déterminé avec l'id) dans la salle ma_salle aux positions x,y
void ajout_entite(entite_id mon_entite_id, a_salle ma_salle, int x, int y, int interaction);


//ajoute une entite dans un tableau d'entites
int ajout_tableau_entite(a_entite mon_entite, a_salle ma_salle);

//récupération d'une chambre depuis un fichier existant, et stockage dans un a_salle
a_salle recup_salle(char* nom_fichier);













#endif
