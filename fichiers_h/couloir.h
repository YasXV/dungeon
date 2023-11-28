// C File standard
//--------------------------------------------------------------------------------
//  File couloir.h
// Date: 12 Nov 2023
//--------------------------------------------------------------------------------

#ifndef COULOIR_H
#define COULOIR_H
//--------------------------------------------------------------------------------

typedef struct my_couloir{
int hauteur; //nombre de lignes
char *sequence;//sequence des déplacements dans le couloir
int largeur; //largeur des couloirs
int ligne; //taille de la ligne
char **tableau;//tableau qui contient le couloir
int id_couloir;//id unique d'un couloir
}couloir;

typedef couloir* a_couloir;

//--------------------------------------------------------------------------------

a_couloir creer_couloir(int largeur, const char *sequence);

//--------------------------------------------------------------------------------

void affiche_couloir(couloir *c);

//--------------------------------------------------------------------------------

void fill_couloir(couloir *c);

//--------------------------------------------------------------------------------

int count_occurence(char *direction,couloir *c);

//--------------------------------------------------------------------------------

void count_max_length(couloir *c);

//--------------------------------------------------------------------------------

void count_max_ligne(couloir *c);

//--------------------------------------------------------------------------------

void create_tableau(couloir *c);

//--------------------------------------------------------------------------------

void start_placement(couloir *c,int *x,int *y);

//--------------------------------------------------------------------------------

void clean_tableau(couloir *c);

//--------------------------------------------------------------------------------

int sauvegarder_couloir(couloir *c);

//--------------------------------------------------------------------------------

a_couloir recuperer_couloir(char *nom_fichier);

//--------------------------------------------------------------------------------

void calcul_position_physique(couloir *c, int *x, int *y, int *x_physique, int *y_physique);

//--------------------------------------------------------------------------------
#endif 

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------
