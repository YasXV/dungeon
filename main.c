// C File standard
//--------------------------------------------------------------------------------
//  File main.c
// Date: 12 Nov 2023
//--------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fichiers_h/fonctions_utiles.h"
#include "fichiers_h/couloir.h" 
#include "fichiers_h/chambre.h"
#include "fichiers_h/entites.h"
#include "fichiers_h/assemblage_chambre.h"
#include "fichiers_h/donjon.h"


//--------------------------------------------------------------------------------
//initialisation des id
#define l 1// n est la largeur des couloirs, ici ils seront définis à 1, mais c'est tout a fait possible d'avoir une largeur personalisée
int main(){
a_donjon d1 = creer_donjon(67,90);
affiche_donjon(d1);
sauvegarder_donjon(d1);
/*a_salle s1 = creer_salle(31,15);
ajouter_entite(COFFRE, s1,3,5, 0,1);
ajouter_entite(AUTEL, s1, 8,3, 1,1);
//ajout_entite(PORTE,s1,0,4,0);
ajouter_entite(MONSTRE,s1,0,4,1,0);
affiche_salle(s1);
affiche_entites_salle(s1);
interagir_entite(s1, 3,8);
interagir_entite(s1, 3,5);
interagir_entite(s1, 8,3);
ajouter_entite(PIEGE,s1,3,5,0,1);
ajouter_entite(PORTE,s1,5,0,1,0);
ajouter_entite(PORTE,s1,5,0,0,1);
affiche_salle(s1);
affiche_entites_salle(s1);
sauvegarder_salle(s1);
printf("VERIFICATION\n");
a_salle s2 = recup_salle("chambres/salle1.txt");
affiche_salle(s2);
sauvegarder_salle(s2);
a_couloir c1 = creer_couloir(2, "SSSSSSWWWWWWWW");
affiche_couloir(c1);
sauvegarder_couloir(c1);
/*ajout_entite(BOSS,s1,0,4,0);
affiche_salle(s1);
printf("verif :\n");
ajout_entite(PORTE,s1,0,4,1);
ajout_entite(PORTE,s1,13,17,1);
affiche_salle(s1);
affiche_entites_salle(s1);
/*sauvegarder_salle(s1);
affiche_entites_salle(s1);
printf("vérification\n");
a_salle s3 = recup_salle("chambres/salle1.txt");
affiche_salle(s3);
affiche_entites_salle(s3);
ajout_entite(BOSS,s3,7,20,0);
ajout_entite(PIEGE,s3,4,15,0);
ajout_entite(MONSTRE,s3,6,12,1);
affiche_entites_salle(s3);
affiche_salle(s3);
sauvegarder_salle(s3);*/
/*
a_salle s2 = creer_salle(43,16);
affiche_salle(s2);
sauvegarder_salle(s2);

a_couloir c1 = creer_couloir(2,"SSSSSEEEESSS");
affiche_couloir(c1);
sauvegarder_couloir(c1);

a_couloir c2 = creer_couloir(2,"NNNNNNNWWWWW");
affiche_couloir(c2);
sauvegarder_couloir(c2);

a_salle s3 = recup_salle("chambres/salle1.txt");
//printf("%d\n%d\n",s3->largeur,s3->longueur);
affiche_salle(s3);
sauvegarder_salle(s3);
printf("%d\n",s3->id_salle);
//free(c1);
//free(s2);
free(s3);
free(s1);*/
/*a_entite m1 = creer_entite(MONSTRE,5,8,1);
a_entite b1 = creer_entite(BOSS,10,6,0);
printf("%c\t(%d,%d)\n",m1->symbole,m1->x,m1->y);
printf("%c\t(%d,%d)\n",b1->symbole,b1->x,b1->y);
printf("%d\n", MONSTRE);
printf("%s\n",avoir_type_entite(m1));
printf("%s\n",avoir_type_entite(b1));*/
return 0;
}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------
