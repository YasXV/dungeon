#ifndef DONJON_H
#define DONJON_H
#include "chambre.h"
#include "entites.h"
#include "couloir.h"
#include "assemblage_chambre.h"

//structure representant une salle à l'intérieur d'un donjon(défini par un couloir, et ses positions x,y dans le donjon)
typedef struct s_salle_dans_donjon{
a_salle salle;
int x;
int y;
}salle_donjon;

typedef salle_donjon* a_salle_donjon; 

//structure representant un couloir à l'intérieur d'un donjon(défini par un couloir, et ses positions x,y dans le donjon)
typedef struct s_couloir_dans_donjon{
a_couloir couloir;
int x;
int y;
}couloir_donjon;

typedef couloir_donjon* a_couloir_donjon;

//structure donjon
typedef struct s_donjon{
int largeur;
int longueur;
int id_donjon;
char **enceinte ; // tableau qui contient le donjon entier 
entite ** entree_sortie; //tableau qui contient les a_entite entree et sortie du donjon
salle_donjon** salles_donjon; // tableau qui contient toutes les a_salle contenu dans le donjon
couloir_donjon** couloirs_donjon; // tableau qui contient tout les a_couloirs contenu dans le donjon
int nbre_elements_couloirs; // le nbre de couloirs contenu dans le tableau couloirs_donjon (utilie pour de la réallocation dynamique)
int nbre_elements_salles; // le nbre de couloirs contenu dans le tableau salles_donjon (utilie pour de la réallocation dynamique)
int capacite_couloirs; // la capacite actuelle du tableau couloirs_donjon (utilie pour de la réallocation dynamique)
int capacite_salles;//la capacite actuelle du tableau salles_donjon (utilie pour de la réallocation dynamique)

}donjon;

typedef donjon* a_donjon;

a_donjon creer_donjon(int largeur, int longueur);

void affiche_donjon(a_donjon mon_donjon);

void remplir_mur_donjon(a_donjon mon_donjon);

int sauvegarder_donjon(a_donjon mon_donjon);

//insere une a_salle dans un a_donjon a la position x,y! forcage est un int qui indique si on force l'écrasement des salles si il y en a dèjà une à la position x,y
void inserer_salle(a_donjon mon_donjon, a_salle une_salle, int x, int y, int forcage);






#endif
