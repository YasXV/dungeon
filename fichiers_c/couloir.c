// C File standard
//--------------------------------------------------------------------------------
//  File couloir.c
// Date: 12 Nov 2023
//--------------------------------------------------------------------------------

#include "couloir.h"
#include <stdio.h>
#include <stdlib.h>
#include "fonctions_utiles.h"
#include <string.h>

//--------------------------------------------------------------------------------

a_couloir creer_couloir(int largeur, const char *sequence){
	
	//allocation de la mémoire pour un couloir
	a_couloir c = malloc(sizeof(couloir));
	if (c == NULL) {
        printf("échec de l'allocation de mémoire d'un couloir");
        return NULL;
    	}
    
    //dimension
	c->largeur = largeur;
	
	//allocation de la mémoire pour la sequence
	c->sequence = malloc(strlen(sequence) + 1);
	strcpy(c->sequence,sequence);
	count_max_length(c);
	count_max_ligne(c);
	
	//Allouer de la mémoire pour les lignes
    c->tableau = (char**)malloc(c->hauteur * sizeof(char*));

    //Allouer de la mémoire pour les colonnes
    for (int i = 0; i < c->hauteur; i++) {
        c->tableau[i] = (char*)malloc(c->largeur * sizeof(char));
    }
    
	// attribution de l'identifiant 
	if (c != NULL){
        int nouveau_id = lire_int("couloirs/config.txt");
	   	c->id_couloir = ++nouveau_id;
	   	mettre_ajour_int("couloirs/config.txt", c->id_couloir);
	}
	create_tableau(c);
	return c;
}

//--------------------------------------------------------------------------------

void affiche_couloir(couloir *c){
    for (int i = 0; i < c->hauteur; i++) {
        for (int j = 0; j < c->ligne; j++) {
			if (c->tableau[i][j] == '-'){
				printf("  ");
			}
			else{
            	printf("%c ", c->tableau[i][j]);
			}
        }
        printf("\n");
    }
}

//--------------------------------------------------------------------------------

void create_tableau(couloir *c){
	for (int i = 0; i < c->hauteur; i++) {
        for (int j = 0; j < c->ligne; j++) {
            c->tableau[i][j] = '#';
        }
    }
	fill_couloir(c);
}

//--------------------------------------------------------------------------------

int count_occurence(char *direction,couloir *c){
	int occurence = 0;
	for (int i=0; (c->sequence)[i] != '\0'; i++){
		if((c->sequence)[i] == *direction){
			occurence++;
		}
	}
	return occurence;
}

//--------------------------------------------------------------------------------

void fill_couloir(couloir *c){
	int x = 0;
	int y = 0;
	int x_phy = 0;
	int y_phy = 0;
	start_placement(c,&x,&y);

	int longueurSequence = strlen(c->sequence);
	int first_y;
	int first_x;
	int final_x;
	int final_y;
    for (int i = 0; i < longueurSequence; i++) {

        char direction = c->sequence[i];

        if (direction == 'E') {
            y += 1;
        } else if (direction == 'W') {
            y -= 1;
        } else if (direction == 'S') {
            x += 1;
        } else if (direction == 'N') {
            x -= 1;
        }
		if (i == 0){
			first_x = x;
			first_y = y;
		}
		if (i == longueurSequence - 1){
			final_x = x;
			final_y = y;
		}
		
        // Assurez-vous que les nouvelles coordonnées sont valides
        if (x >= 0 && x < c->hauteur && y >= 0 && y < c->ligne) {
            c->tableau[x][y] = ' ';
        }
    }
	clean_tableau(c);
	
	if (first_x > 0){
		if(c->sequence[0] == 'S'){
			c->tableau[first_x - 1][first_y] = '-';
		}
		if(c->sequence[0] == 'N'){
			c->tableau[first_x + 1][first_y] = '-';
		}
	}
	if (first_y == 1){
		if (c->sequence[0] == 'E'){
			c->tableau[first_x][first_y - 1] = '-';
		}
	}
	if (final_y < c->ligne - 1){
		if (c->sequence[strlen(c->sequence) - 1] == 'E'){
			c->tableau[final_x][final_y + 1] = '-';
		}
		if (c->sequence[strlen(c->sequence) - 1] == 'N'){
			if (final_x > 0){
				c->tableau[final_x - 1][final_y] = '-';
			}
		}
	}
	if (c->sequence[strlen(c->sequence) - 1] == 'S'){
		if (final_x != c->hauteur - 1){
			c->tableau[final_x + 1][final_y] = '-';
		}
	}
}

//--------------------------------------------------------------------------------

void start_placement(couloir *c, int *x, int *y){
	int nb_est = count_occurence("E",c);
	int nb_west = count_occurence("W",c);
	int nb_sud = count_occurence("S",c);
	int nb_nord = count_occurence("N",c);
	
	//calcul de la position de départ
	if ((nb_est == 0) && (nb_west != 0)){
		if (c->sequence[0] == 'W'){
			*y = c->ligne ;
		}
		else{
			*y = (c->ligne) - 2;
		}

	}
	else if ((nb_est != 0) && (nb_west == 0)){
		if (c->sequence[0] == 'E'){
			if (nb_est == strlen(c->sequence)){
			*y = -1;
			}
			else{
				*y= 0;
			}
		}
		else{
			*y = 1;
		}
	}
	else{
		if ((nb_est != 0 ) && (nb_west != 0)){
			if (nb_est > nb_west){
				*y = 1;
			}
			else{
				*y = c->ligne - 2;
			}
		}
		else{
			*y = 1;
		}
	}
	//----------------------------------------
	if ((nb_nord == 0)&&(nb_sud != 0)){
		if (c->sequence[0] == 'S'){
			*x = 0;
		}
		else{
			*x = -1;
		}
	}
	else if ((nb_nord != 0)&&(nb_sud == 0)){
		if (c->sequence[0] == 'N'){
			*x = c->hauteur;
		}
		else{
			*x = c->hauteur - 2;
		}
	}
	else{
		if ((nb_nord != 0 ) && (nb_sud != 0)){
			if (nb_nord > nb_sud){
				int occurence_nord = 0;
				int occurence_sud = 0;
				for(int i = 0; i < strlen(c->sequence); i++){
					if (c->sequence[i] == 'S'){
						occurence_sud += 1;
					}
					else{
						break;
					}
				}
				for(int j = 0; j < strlen(c->sequence); j++){
					if (c->sequence[j] == 'N'){
						occurence_nord += 1;
					}
					else{
						if(occurence_nord == 0){
							continue;
						}
						else{
							break;
						}
					}
				}
				if (occurence_nord > occurence_sud){
					*x = occurence_nord - occurence_sud + 1;
				}
				else if(occurence_nord == occurence_sud){
					*x = nb_nord - nb_sud;
				}
				
			}
			else if (nb_nord == nb_sud){
				*x = 1;
			}
			else{
				if (c->sequence[0] == 'S'){
					int occurence_nord = 0;
					int occurence_sud = 0;
					for(int i = 0; i < strlen(c->sequence); i++){
						if (c->sequence[i] == 'S'){
							occurence_sud += 1;
						}
						else{
							break;
						}
					}
					for(int j = 0; j < strlen(c->sequence); j++){
						if (c->sequence[j] == 'N'){
							occurence_nord += 1;
						}
						else{
							if(occurence_nord == 0){
								continue;
							}
							else{
								break;
							}
						}
					}
					if (occurence_nord > occurence_sud){
						*x = occurence_nord - occurence_sud + 1;
					}
					else if(occurence_nord == occurence_sud){
						*x = 1;
					}
					else{
						*x = occurence_nord - occurence_sud;
					}
				}
				else if(c->sequence[0] == 'N'){
					int occurence_nord = 0;
					int occurence_sud = 0;
					for(int i = 0; i < strlen(c->sequence); i++){
						if (c->sequence[i] == 'N'){
							occurence_nord += 1;
						}
						else{
							break;
						}
					}
					for(int j = 0; j < strlen(c->sequence); j++){
						if (c->sequence[j] == 'S'){
							occurence_sud += 1;
						}
						else{
							if(occurence_sud == 0){
								continue;
							}
							else{
								break;
							}
						}
					}
					if (occurence_sud > occurence_nord){
						*x = c->hauteur - 1 - (occurence_sud - occurence_nord);
					}
					else{
						*x = 0;
					}
					
				}
				else{
					*x = 0;
				}
			}
		}
		else{
			*x = 1;
		}
	}
}

//--------------------------------------------------------------------------------

void count_max_length(couloir *c){
	int max_length=0;
	int length_sud = count_occurence("S",c);
	int length_nord = count_occurence("N",c);

	int gain = 1;
	if ((length_sud != strlen(c->sequence)) && (length_nord != strlen(c->sequence))){
		if ((length_sud == 0)||(length_nord == 0)){
			if ((c->sequence[strlen(c->sequence)-1] == 'S') && (c->sequence[0] == 'S')){
				gain = 0;
			}
			else if ((c->sequence[strlen(c->sequence)-1] == 'S') || (c->sequence[0] == 'S')){
				gain = 2;
			}
			else if ((c->sequence[strlen(c->sequence) - 1] == 'N') && (c->sequence[0] == 'N')){
				gain = 0;
			}
			else{
				if ((c->sequence[strlen(c->sequence) - 1] == 'N')||(c->sequence[0] == 'N')){
					gain = 1;
				}
				else{
					gain = 3;
				}
			}
		}
		else{
			if (length_sud == length_nord){
				if ((c->sequence[strlen(c->sequence) - 1] == 'E') || (c->sequence[strlen(c->sequence) - 1] == 'W')){
					gain = 3;
				}
				else{
					if((c->sequence[strlen(c->sequence) - 1] == 'N') && (c->sequence[0] == 'S')){
						gain = 3;
					}
					else{
						gain = 2;
					}
				}
			}
			else if (length_sud > length_nord){
				if (c->sequence[0]=='S'){
					gain = 2;
				}
				else{
					gain = 2;
				}
			}
			else if (length_sud < length_nord){
				if ((c->sequence[strlen(c->sequence) - 1] == 'E') || (c->sequence[strlen(c->sequence) - 1] == 'W')){
					gain = 3;
				}
				else if ((c->sequence[strlen(c->sequence) - 1] == 'S') || (c->sequence[0] == 'N')){
					gain = 2;
				}
				//else if (c->sequence[strlen(c->sequence) - 1] == 'N'){
				//	gain = 3;
				//}
				else{
					gain = 1;
				}
			}
		}
	}
	else{
		gain = 0;
	}


	//--------------------------------------------------------------------------------
	if (length_sud > length_nord){
		max_length = length_sud + gain;
	}
	else{
		max_length = length_nord + gain;
	}
	if ((length_sud == 0) && (length_nord == 0)){
		max_length = 3;
	}
	c->hauteur = max_length;
}

//--------------------------------------------------------------------------------

void count_max_ligne(couloir *c){
	int max_ligne=0;
	int ligne_est = count_occurence("E",c);
	int ligne_west = count_occurence("W",c);

	int gain = 1;
	if ((ligne_est != strlen(c->sequence)) && (ligne_west != strlen(c->sequence))){
		if ((ligne_est == 0)||(ligne_west == 0)){
			if ((c->sequence[strlen(c->sequence) - 1] == 'E') || (c->sequence[strlen(c->sequence) - 1] == 'W')){
				gain = 3;
			}
			else{
				if (ligne_est == 0){
					gain = 1;
				}
				else{
					gain = 3;
				}
			}
		}
		else{
			gain = 3;
		}
	}
	else{
		gain = 0;
	}


	if (ligne_est > ligne_west){
		max_ligne = ligne_est + gain;
	}
	else{
		max_ligne = ligne_west + gain;
	}
	if ((ligne_est == 0) && (ligne_west == 0)){
		max_ligne = 3;
	}
	c->ligne = max_ligne;
}

//--------------------------------------------------------------------------------

void clean_tableau(couloir *c) {
    for (int i = 0; i < c->hauteur; i++) {
        for (int j = 0; j < c->ligne; j++) {
            if (c->tableau[i][j] == '#') {
                // Vérifier si la case est entourée d'espaces
                if ((i == 0 || c->tableau[i-1][j] != ' ') &&
                    (i == c->hauteur-1 || c->tableau[i+1][j] != ' ') &&
                    (j == 0 || c->tableau[i][j-1] != ' ') &&
                    (j == c->ligne-1 || c->tableau[i][j+1] != ' ') &&
					(i == 0 || j == 0 || c->tableau[i-1][j-1] != ' ') &&
                    (i == 0 || j == c->ligne-1 || c->tableau[i-1][j+1] != ' ') &&
                    (i == c->hauteur-1 || j == 0 || c->tableau[i+1][j-1] != ' ') &&
                    (i == c->hauteur-1 || j == c->ligne-1 || c->tableau[i+1][j+1] != ' ')){
                    // Remplacer par '-'
                    c->tableau[i][j] = '-';
                }
            }
        }
    }
	if (c->sequence[0] == 'N'){
		for(int i = 1; i < c->hauteur - 1; i++){
			if(c->tableau[c->hauteur - i][1] == '#'){
				c->tableau[c->hauteur - i][1] = '-';
			}
		}
	}
	if (c->sequence[strlen(c->sequence) - 1] == 'S'){
		for(int i = 1; i < c->hauteur - 1; i++){
			if((c->tableau[c->hauteur - i][c->ligne - 2] == '#') && (c->tableau[c->hauteur - i][c->ligne - 3] == '#')&& (c->tableau[c->hauteur - i][c->ligne - 1] == '#')){
				c->tableau[c->hauteur - i][c->ligne - 2] = '-';
				c->tableau[c->hauteur - i][c->ligne - 3] = '-';
				c->tableau[c->hauteur - i][c->ligne - 1] = '-';
			}
		}
		
	}
}

//--------------------------------------------------------------------------------

int sauvegarder_couloir(couloir *c) {
    FILE *fichier;
    
    //création du nom du fichier en utilisant l'id du couloir
	char nom_fichier[50];
	sprintf(nom_fichier,"couloirs/couloir%d.txt",c->id_couloir);
	
	//ouverture du fichier 
	fichier = fopen(nom_fichier,"w+");
	
	//erreur d'ouverture 
    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s pour l'écriture.\n", nom_fichier);
        return 1;
    }
    
    //écriture des dimensions en largeur et longueur des couloirs
	fprintf(fichier, "%d\n%d\n", c->hauteur, c->ligne);

	//écriture du couloir 
	fprintf(fichier, "%s\n", c->sequence);
	
	//fermeture du fichier
    fclose(fichier);
	printf("Le fichier %s a été sauvegardé.\n", nom_fichier);
	return 0;
}

//--------------------------------------------------------------------------------

a_couloir recuperer_couloir(char* nom_fichier) {
	FILE *fichier;
	int hauteur;
	int largeur;
	char *sequence;
	
	//ouverture du fichier 
	fichier = fopen(nom_fichier, "r");
	
	//erreur d'ouverture 
	if (fichier == NULL) {
		fprintf(stderr, "Impossible d'ouvrir le fichier %s pour la lecture.\n", nom_fichier);
		return NULL;
	}
	
	//lecture des dimensions en largeur et longueur des couloirs
	fscanf(fichier, "%d\n%d\n", &hauteur, &largeur);
	
	//lecture du couloir 
	fscanf(fichier, "%s\n", sequence);
	
	//fermeture du fichier
	fclose(fichier);
	
	//création du couloir
	a_couloir c = creer_couloir(1, sequence);
	
	//libération de la mémoire
	free(sequence);
	
	return c;
}

//--------------------------------------------------------------------------------

void calcul_position_physique(couloir *c, int *x, int *y, int *x_physique, int *y_physique){
	*x_physique = *x;
	*y_physique = *y;
	//calcul des occurence de chaque direction
	int nb_deplacement_nord = count_occurence("N",c);
	int nb_deplacement_sud = count_occurence("S",c);
	int nb_deplacement_est = count_occurence("E",c);
	int nb_deplacement_west = count_occurence("W",c);

	//calcul de la position physique
	//hauteur
	if (nb_deplacement_nord == 0){
		if (c->sequence[0] == 'S'){
		*x_physique = *x;
		}
		else{
		*x_physique += 1;
		}
	}
	else if (nb_deplacement_sud == 0){
		if (c->sequence[0] == 'N'){
		*x_physique = *x + c->hauteur - 1;
		}
		else{
		*x_physique += c->hauteur - 2;
		}
	}
	else {
		if (nb_deplacement_nord > nb_deplacement_sud){
			if(c->sequence[0] != 'N'){
				*x_physique += (nb_deplacement_nord - nb_deplacement_sud);
			}
			else{
				*x_physique = *x + c->hauteur - 2;
			}
		}
		else if (nb_deplacement_nord < nb_deplacement_sud){
		*x_physique += (nb_deplacement_sud - nb_deplacement_nord - 1);
		}
		else{
			if (c->sequence[0] == 'N'){
				*x_physique = *x + c->hauteur - 2;
			}
			else if (c->sequence[0] == 'S'){
				*x_physique += 1;
			}
		}
	}
	//largeur
	if(nb_deplacement_est == 0){
		if (c->sequence[0] == 'W'){
			*y_physique = *x + c->ligne - 1;
		}
		else{
			*y_physique += c->ligne - 2;
		}
	}
	else if (nb_deplacement_west == 0){
		if (c->sequence[0] == 'E'){
			*y_physique = *x;
		}
		else{
			*y_physique += 1;
		}
	}
	else{
		if (nb_deplacement_est > nb_deplacement_west){
			*y_physique += (nb_deplacement_est - nb_deplacement_west);
		}
		else if (nb_deplacement_est < nb_deplacement_west){
			*y_physique += (nb_deplacement_west - nb_deplacement_est);
		}
	}
}

//--------------------------------------------------------------------------------

void calcul_position_sortie(couloir *c, int *x, int *y, int *x_physique, int *y_physique){
	*x_physique = *x;
	*y_physique = *y;

	//Ecriture de la séquence Miroir
	char *sequence_miroir = malloc(strlen(c->sequence) + 1);
	if (sequence_miroir == NULL) {
        printf("Allocation de mémoire échouée.\n");
        return;
    }
	strcpy(sequence_miroir,c->sequence);
	for (int i = 0; i < strlen(sequence_miroir); i++){
		if (sequence_miroir[i] == 'N'){
			sequence_miroir[i] = 'S';
		}
		else if (sequence_miroir[i] == 'S'){
			sequence_miroir[i] = 'N';
		}
		else if (sequence_miroir[i] == 'E'){
			sequence_miroir[i] = 'W';
		}
		else if (sequence_miroir[i] == 'W'){
			sequence_miroir[i] = 'E';
		}
	}
	size_t length = strlen(sequence_miroir);
	char* reversed = (char*)malloc((length + 1) * sizeof(char)); 
    if (reversed == NULL) {
        printf("Allocation de mémoire échouée.\n");
        return;
    }
	for (size_t i = 0; i < length; i++) {
        reversed[i] = sequence_miroir[length - 1 - i]; // Inverse les caractères
    }
    reversed[length] = '\0';
	couloir *c_miroir = creer_couloir(1,reversed);
	calcul_position_physique(c_miroir,x,y,x_physique,y_physique);
	
	
	//calcul des cas particulier
	if(c->sequence[strlen(c->sequence) - 1] != 'N'){
		int last_occurence = 0;
		for (int i = 0; i < strlen(c->sequence); i++){
			if (c->sequence[i] == 'N'){
				last_occurence = 1;
			}
			else if (c->sequence[i] == 'S'){
				last_occurence = 0;
			}
		}
		//on a finit sur un S
		if (last_occurence == 0){
			int occurence = 0;
			for(int j = strlen(c->sequence) - 1; j > 0; j--){
				if (c->sequence[j] == 'S'){
					occurence += 1;
				}
				else{
					if (occurence != 0){
						break;
					}

				}
			}
			int nb_depl_nord = count_occurence("N",c);
			int nb_depl_west = count_occurence("W",c);
			if(c->sequence[strlen(c->sequence) - 1] == 'S'){
				*x_physique -= occurence + 1;
			}
			else{
				if (nb_depl_nord == 0){
					*x_physique += 1;
					if (nb_depl_west == 0){
						*y_physique = *y + c->ligne - 1;
					}
				}
				else{
					*x_physique += occurence - 1;
				}
			}
		
		}//on est sur du Nord
		else{
			*x_physique += 1;
			//*x_physique += c->hauteur - 2;
		}
	}


}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------
