#ifndef ENTITES_H
#define ENTITES_H


//structure entite
typedef struct s_entite{
int interaction;
char symbole;
int x;
int y;
int id_entite; // un id qui permet de distinguer le type d'entité
}entite;

typedef entite* a_entite;


//enumeration des differents types d'entites 
typedef enum e_entite{
ENTREE=0,
SORTIE,
PORTE,
AUTEL,
PIEGE,
MUR,
COFFRE,
MONSTRE,
BOSS,
NB_ENTITE
}entite_id;


// fonction permettant de créer une entité, le type d'entité est déterminer par son id à l'intérieur de la structure
a_entite creer_entite(entite_id id, int x, int y,int interaction);

// retourne un char* décrivant le type de l'entite via l'id 
char* avoir_type_entite(a_entite mon_entite);

//affiche une entité avec ses propriétes
void affiche_entite(a_entite mon_entite);

#endif
