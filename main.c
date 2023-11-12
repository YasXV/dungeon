// C File standard
//--------------------------------------------------------------------------------
//  File main.c
// Date: 12 Nov 2023
//--------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "couloir.h" 

//--------------------------------------------------------------------------------

#define l 1// n est la largeur des couloirs, ici ils seront définis à 1, mais c'est tout a fait possible d'avoir une largeur personalisée
int main(){

couloir *c = malloc(sizeof(couloir));
    if (c == NULL) {
        printf("échec de l'allocation de mémoire");
        return 1;
    }

init(c,l,"NNNNEEEENNNNNNWWWWWWNNNNNNW");

// # #
// # ####
// #    #
// #### ##
//    #   
//    ####
 
orientation(c->sequence);
affiche(c);
free(c);
return 0;
}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------