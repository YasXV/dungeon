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
#include "donjon.h"


//--------------------------------------------------------------------------------
//initialisation des id
#define l 1// n est la largeur des couloirs, ici ils seront définis à 1, mais c'est tout a fait possible d'avoir une largeur personalisée
int main(){
    a_couloir c1 = creer_couloir(1,"SSSSEEEE");
    sauvegarder_couloir(c1);
    a_couloir c2 = recuperer_couloir("couloirs/couloir1.txt");
    affiche_couloir(c2);
return 0;
}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------
