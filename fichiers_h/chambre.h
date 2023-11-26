#ifndef CHAMBRE_H
#define CHAMBRE_H
#include "entites.h"

typedef struct salle{

char **enceinte ;
int largeur;
int longueur;
int id_salle; // id_unique de la salle
entite** entites_contenu; // tableau d'entités qui contient toutes les a_entite contenu dans la salle
int nbre_elements;// nbre elements dans le tableau d'entites
int capacite_actuelle;// capacité actuelle du tableau d'entités
}salle;

typedef salle* a_salle;

a_salle creer_salle(int largeur, int longueur);

void remplir_mur_salle(a_salle salle);

void affiche_salle(salle *s);

int sauvegarder_salle(salle *s);

void affiche_entites_salle(a_salle ma_salle);




#endif



