#include <stdio.h>
#include <stdlib.h>
#include "../fichiers_h/fonctions_utiles.h"


//lire dans le fichier config l'entier contenu dans le fichier
int lire_int(char* fichier_config){
	FILE* fichier;
	
	//ouverture du fichier 
	fichier = fopen(fichier_config,"r");
	
	//erreur d'ouverture fichier
	if (fichier == NULL) {
        fprintf(stderr,"Impossible d'ouvrir le fichier %s pour la lecture.\n",
			 fichier_config);
			 return 0;
    	}
    else{
    	int entier;
		fscanf(fichier,"%d\n",&entier);    
    	return entier;
    	}
    fclose(fichier);
}

//mettre à jours dans le fichier config l'entier contenu dans le fichier
void mettre_ajour_int(char* fichier_config,int entier){
	FILE* fichier;
	
	//ouverture du fichier 
	fichier = fopen(fichier_config,"w+");
	
	//erreur d'ouverture fichier
	if (fichier == NULL) {
        fprintf(stderr,"Impossible d'ouvrir le fichier %s pour l'écriture.\n",
			 fichier_config);
    	}

    else{
		fprintf(fichier,"%d\n", entier);    
    }
    fclose(fichier);
}

