#ifndef CHAMBRE_H
#define CHAMBRE_H

typedef struct salle{

char **enceinte ;
int largeur;
int longueur;
int id_salle;
}salle;

void init_salle(salle *s, int largeur, int longueur);

void affiche_salle(salle *s);

void sauvegarder_salle(salle *s);




#endif



