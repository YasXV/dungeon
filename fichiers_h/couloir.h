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
int x_entree;//coordonnée x de l'entrée du couloir
int y_entree;//coordonnée y de l'entrée du couloir
int x_sortie;//coordonnée x de la sortie du couloir
int y_sortie;//coordonnée y de la sortie du couloir
}couloir;

typedef couloir* a_couloir;

//--------------------------------------------------------------------------------

a_couloir creer_couloir(int largeur, const char *sequence);

//--------------------------------------------------------------------------------

void affiche_couloir(couloir *c);

//--------------------------------------------------------------------------------

void remplacer_couloir(couloir *c);

//--------------------------------------------------------------------------------

void create_tableau(couloir *c);

//--------------------------------------------------------------------------------

void nettoyer_tableau(couloir *c);

//--------------------------------------------------------------------------------

void retirer_colonne(char **array, int colIndex, int ROWS, int COLS);

//--------------------------------------------------------------------------------

void retirer_ligne(char **array, int rowIndex/*indice de la ligne*/,int ROWS /*nombre de colonne*/);

//--------------------------------------------------------------------------------

int sauvegarder_couloir(couloir *c);

//--------------------------------------------------------------------------------

a_couloir recuperer_couloir(char *nom_fichier);

//--------------------------------------------------------------------------------
void trouver_debut_fin_couloir(couloir *c);

//--------------------------------------------------------------------------------
#endif 

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------
