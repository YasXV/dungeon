#ifndef ASSEMBLAGE_CHAMBRE_H
#define ASSEMBLAGE_CHAMBRE_H
#include "entites.h"
#include "chambre.h"




//fonction qui ajoute une entité (type déterminé avec l'id) dans la salle ma_salle aux positions x,y, nous avons un paramétre forcage (0 ou 1) qui détermine si on l'utilisateur veut forcer l'ajout
//d'une entité dans le cas d'une entité déjà présente à la position x, y
void ajouter_entite(entite_id mon_entite_id, a_salle ma_salle, int x, int y, int interaction, int forcage);


//ajoute une entite dans un tableau d'entites
int ajouter_tableau_entite(a_entite mon_entite, a_salle ma_salle);

//récupération d'une chambre depuis un fichier existant, et stockage dans un a_salle
a_salle recup_salle(char* nom_fichier);

//vérification sur l'ajour d'une entité dans la salle (une porte doit être ajoutéee sur un mur obligatoirement, les autres entités doivent être ajoutées hors des murs)
int verifier_possibilite_ajout(entite_id mon_entite_id, a_salle ma_salle, int x, int y, int interaction);

//vérifie si une entité est déjà présente à la position x,y dans la salle
int verifier_entite_presente(a_salle ma_salle, int x, int y);

//interagis avec une entite à la position (x,y) dans une salle, exemple : ouvre une porte, tue un boss, utilise un autel
void interagir_entite(a_salle ma_salle, int x, int y);













#endif
