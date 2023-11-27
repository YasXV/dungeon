// C File standard
//--------------------------------------------------------------------------------
//  File main.c
// Date: 12 Nov 2023
//--------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fonctions_utiles.h"
#include "couloir.h" 
#include "chambre.h"
#include "entites.h"
#include "assemblage_chambre.h"
#include "assemblage_donjon.h"
#include "donjon.h"
#include "ihm.h"


//--------------------------------------------------------------------------------
//initialisation des id
#define l 1// n est la largeur des couloirs, ici ils seront définis à 1, mais c'est tout a fait possible d'avoir une largeur personalisée
int main(){

a_donjon d1 = creer_donjon(78,59);
affiche_donjon(d1);
a_salle s1 = creer_salle(22,17);
a_salle s2 = creer_salle(14,9);
ajouter_entite(MONSTRE,s1, 8,6,0,1);
ajouter_entite(AUTEL,s1,10,13,1,1);
ajouter_entite(MONSTRE,s1,12,15,0,1);
ajouter_salle(d1, s1, 4,8,0);
//ajouter_entite_donjon(COFFRE, d1, 19, 30, 1, 1);
affiche_salle(d1->salles_donjon[0]->salle);
ajouter_entite_donjon(COFFRE,d1,16,20,1,0);
ajouter_entite_donjon(BOSS,d1,7,12,0,0);
ajouter_entite_donjon(PIEGE,d1,5,25,1,1);
affiche_salles_donjon(d1);
affiche_donjon(d1);
sauvegarder_donjon(d1);
a_donjon d2 = recup_donjon("donjons/donjon14.txt");
affiche_donjon(d2);
return 0;
}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------
