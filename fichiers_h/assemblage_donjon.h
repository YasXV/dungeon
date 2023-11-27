#ifndef ASSEMBLAGE_DONJON_H
#define ASSEMBLAGE_DONJON_H
#include "donjon.h"
#include "chambre.h"


//ajoute une salle dans mon donjon à la position x, y, forcage est un entier qui si il est égal à 0, autorise l'écrasement d'une salle par une autre!
void ajouter_salle(a_donjon mon_donjon, a_salle une_salle, int x, int y, int forcage);

//ajoute une entité à la position x, y (relative au donjon) , celle-ci va s'attacher automatiquement à une salle si la position x,y est dans une salle
void ajouter_entite_donjon(entite_id mon_entite_id, a_donjon mon_donjon, int x, int y, int interaction, int forcage);

//vérifie si l'ajout de la salle ne se superpose pas avec une autre salle déjà présente dans le donjon en position x,y 
int verifier_salle_presente(a_donjon mon_donjon, a_salle une_salle, int x, int y);

// ajoute une salle dans le tableau de salle lié au donjon
int ajouter_tableau_salles(a_salle_donjon une_salle, a_donjon mon_donjon);

//ajoute un couloir dans le tableau de couloir lié au donjon
int ajouter_tableau_couloirs(a_couloir_donjon un_couloir, a_donjon mon_donjon);

//verifie si l'entité qu'on veut ajouter à la position x,y dans le donjon sera bien contenu dans une salle, si oui retourne l'indice i de la a_salle_donjon dans le tableau des  a_salles_donjon où l'entité va se retrouver 
int verifier_entite_donjon(a_donjon mon_donjon, int x, int y);

//récupération d'un dnjon depuis un fichier dans un a_donjon
a_donjon recup_donjon(char* nom_fichier);


#endif
