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

	c->hauteur = strlen(c->sequence) * 2 + 1;
	c->ligne = strlen(c->sequence) * 2 + 1;

	//Allouer de la mémoire pour les lignes
    c->tableau = (char**)malloc(c->hauteur * sizeof(char*));

    //Allouer de la mémoire pour les colonnes
    for (int i = 0; i < c->hauteur; i++) {
        c->tableau[i] = (char*)malloc(c->ligne * sizeof(char));
    }
    
	// attribution de l'identifiant 
	if (c != NULL){
        int nouveau_id = lire_int("couloirs/config.txt");
	   	c->id_couloir = ++nouveau_id;
	   	mettre_ajour_int("couloirs/config.txt", c->id_couloir);
	}
	
	create_tableau(c);
	remplacer_couloir(c);
	nettoyer_tableau(c);
	trouver_debut_fin_couloir(c);
	return c;
}

//--------------------------------------------------------------------------------

void affiche_couloir(couloir *c){
	for (int i = 0; i < c->hauteur; ++i) {
		for (int j = 0; j < c->ligne; ++j) {
			if (c->tableau[i][j] == '#') {
				printf("# ");
			}
			else if(c->tableau[i][j] == 'L'){
				printf("  ");
			}
			else if(c->tableau[i][j] == 'E'){
				printf("  ");
			}
			else if(c->tableau[i][j] == 'S'){
				printf("  ");
			}
			else {
				printf("  ");
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
}

//--------------------------------------------------------------------------------

void remplacer_couloir(couloir *c){
	int row = c->hauteur / 2; // Ligne initiale
	int col = c->ligne / 2; // Colonne initiale

	c->x_entree = row;
	c->y_entree = col;
	c->tableau[row][col] = 'E'; // Point de départ

	for (int i = 0; i<=strlen(c->sequence) - 1; ++i) {
		switch (c->sequence[i]) {
			case 'N':
				row--;
				break;
			case 'E':
				col++;
				break;
			case 'S':
				row++;
				break;
			case 'W':
				col--;
				break;
			default:
				printf("Caractère de direction non valide.\n");
				return;
		}
		if (row >= 0 && row < c->hauteur && col >= 0 && col < c->ligne) {
			if (i==strlen(c->sequence) - 1){
				c->tableau[row][col] = 'S'; // Remplissage du couloir
			}
			else{
				c->tableau[row][col] = 'L'; // Remplissage du couloir
			}
		} else {
			printf("Déplacement en dehors des limites du tableau.\n");
			return;
		}
	}

	c->x_sortie = row;
	c->y_sortie = col;	
}

//--------------------------------------------------------------------------------

void nettoyer_tableau(couloir *c) {
    for (int i = 0; i < c->hauteur; i++) {
        for (int j = 0; j < c->ligne; j++) {
            if (c->tableau[i][j] == '#') {
                if ((i == 0 || (c->tableau[i-1][j] != 'L' && c->tableau[i-1][j] != 'E' && c->tableau[i-1][j] != 'S')) &&
                    (i == c->hauteur-1 || (c->tableau[i+1][j] != 'L' && c->tableau[i+1][j] != 'E' && c-> tableau[i+1][j] != 'S')) &&
                    (j == 0 || (c->tableau[i][j-1] != 'L' && c->tableau[i][j-1] != 'E' && c->tableau[i][j-1] != 'S')) &&
                    (j == c->ligne-1 || (c->tableau[i][j+1] != 'L' && c->tableau[i][j+1] != 'E' && c->tableau[i][j+1] != 'S')) &&
                    (i == 0 || j == 0 || (c->tableau[i-1][j-1] != 'L' && c->tableau[i-1][j-1] != 'E' && c->tableau[i-1][j-1] != 'S')) &&
                    (i == 0 || j == c->ligne-1 || (c->tableau[i-1][j+1] != 'L' && c->tableau[i-1][j+1] != 'E' &&c->tableau[i-1][j+1] != 'S')) &&
                    (i == c->hauteur-1 || j == 0 || (c->tableau[i+1][j-1] != 'L' && c->tableau[i+1][j-1] != 'E' && c->tableau[i+1][j-1] != 'S')) &&
                    (i == c->hauteur-1 || j == c->ligne-1 || (c->tableau[i+1][j+1] != 'L' && c->tableau[i+1][j+1] != 'E' && c->tableau[i+1][j+1] != 'S'))) {
                    // Remplacer par '-'
                    c->tableau[i][j] = '-';
                }
            }
        }
    }
	//dernier nettoyage avant la suppression de ligne et de colonne
	if (c->sequence[0] == 'E'){
		c->tableau[c->hauteur / 2][c->ligne / 2 - 1] = '-';
		c->tableau[c->hauteur / 2 - 1][c->ligne / 2 - 1] = '-';
		c->tableau[c->hauteur / 2 + 1][c->ligne / 2 - 1] = '-';
	}
	else if (c->sequence[0] == 'W'){
		c->tableau[c->hauteur / 2][c->ligne / 2 + 1] = '-';
		c->tableau[c->hauteur / 2 - 1][c->ligne / 2 + 1] = '-';
		c->tableau[c->hauteur / 2 + 1][c->ligne / 2 + 1] = '-';
	}
	else if (c->sequence[0] == 'N'){
		c->tableau[c->hauteur / 2 + 1][c->ligne / 2] = '-';
		c->tableau[c->hauteur / 2 + 1][c->ligne / 2 - 1] = '-';
		c->tableau[c->hauteur / 2 + 1][c->ligne / 2 + 1] = '-';
	}
	else if (c->sequence[0] == 'S'){
		c->tableau[c->hauteur / 2 - 1][c->ligne / 2] = '-';
		c->tableau[c->hauteur / 2 - 1][c->ligne / 2 - 1] = '-';
		c->tableau[c->hauteur / 2 - 1][c->ligne / 2 + 1] = '-';
	}
	int length = strlen(c->sequence);
	if (c->sequence[length - 1] == 'E'){
		c->tableau[c->x_sortie][c->y_sortie + 1] = '-';
		c->tableau[c->x_sortie - 1][c->y_sortie + 1] = '-';
		c->tableau[c->x_sortie + 1][c->y_sortie + 1] = '-';
	}
	else if (c->sequence[length - 1] == 'W'){
		c->tableau[c->x_sortie][c->y_sortie - 1] = '-';
		c->tableau[c->x_sortie - 1][c->y_sortie - 1] = '-';
		c->tableau[c->x_sortie + 1][c->y_sortie - 1] = '-';
	}
	else if (c->sequence[length - 1] == 'N'){
		c->tableau[c->x_sortie - 1][c->y_sortie] = '-';
		c->tableau[c->x_sortie - 1][c->y_sortie - 1] = '-';
		c->tableau[c->x_sortie - 1][c->y_sortie + 1] = '-';
	}
	else if (c->sequence[length - 1] == 'S'){
		c->tableau[c->x_sortie + 1][c->y_sortie] = '-';
		c->tableau[c->x_sortie + 1][c->y_sortie - 1] = '-';
		c->tableau[c->x_sortie + 1][c->y_sortie + 1] = '-';
	}

	//suppression des lignes et colonnes inutiles : 
	int nb_element = 0;
	int old_hauteur = c->hauteur;
	int position_depart_trouvee = 0;
	for (int i = 0; i < c->hauteur; ++i) {
		for (int j = 0; j < c->ligne; ++j) {
			if (c->tableau[i][j] == '-') {
				nb_element++;
			}
		}
		if (nb_element == c->ligne) {
			retirer_ligne(c->tableau, i, c->hauteur);
			c->hauteur -= 1;
			if (i < c->hauteur / 2){
				c->x_entree -= 1;
			}
			i -= 1;
		}
		nb_element = 0;
	}
	if (c->x_entree < 0){
		c->x_entree = 0;
	}
	
	nb_element = 0;
	int old_ligne = c->ligne;

	for (int i = 0; i < c->ligne; ++i) {
		for (int j = 0; j < c->hauteur; ++j) {
			if (c->tableau[j][i] == '-') {
				nb_element++;
			}
		}
		
		if (nb_element == c->hauteur) {
			retirer_colonne(c->tableau, i, c->hauteur, c->ligne);
			c->ligne -= 1;
			i -= 1;
		}
		
		nb_element = 0;
	}
}

//------------------------------------------------------------------

void retirer_ligne(char **array, int rowIndex/*indice de la ligne*/,int ROWS /*nombre de colonne*/){
	if (rowIndex < 0 || rowIndex >= ROWS) {
		printf("Indice de ligne invalide.\n");
		return;
	}

	free(array[rowIndex]); // Libère la mémoire de la ligne à supprimer

	// Déplace les pointeurs vers les lignes suivantes vers le haut pour remplir l'espace de la ligne à supprimer
	for (int i = rowIndex; i < ROWS - 1; ++i) {
		array[i] = array[i + 1];
	}

	// Déplace le dernier pointeur vers NULL pour marquer la fin du tableau
	array[ROWS - 1] = NULL;

}

//------------------------------------------------------------------

void retirer_colonne(char **array, int colIndex, int ROWS, int COLS){
    if (colIndex < 0 || colIndex >= COLS) {
        printf("Indice de colonne invalide.\n");
        return;
    }

    // Libère la mémoire pour chaque élément de la colonne à supprimer
    for (int i = 0; i < ROWS; ++i) {
        for (int j = colIndex; j < COLS - 1; ++j) {
            array[i][j] = array[i][j + 1];
        }
        // Réalloue la mémoire pour chaque ligne afin de retirer la colonne
        array[i] = realloc(array[i], (COLS - 1) * sizeof(char));
        if (array[i] == NULL) {
            printf("Erreur de reallocation de mémoire.\n");
            // Gérer l'erreur ici (sortie, nettoyage, etc.)
            return;
        }
    }
}


//------------------------------------------------------------------
void trouver_debut_fin_couloir(couloir *c){
    // Recherche de la nouvelle position de départ (x_entree, y_entree)
    for (int i = 0; i < c->hauteur; ++i) {
        for (int j = 0; j < c->ligne; ++j) {
            if (c->tableau[i][j] == 'E') {
                c->x_entree = i;
                c->y_entree = j;
                break;
            }
        }
    }

    // Recherche de la nouvelle position de sortie (x_sortie, y_sortie)
    for (int i = 0; i < c->hauteur; ++i) {
        for (int j = 0; j < c->ligne; ++j) {
            if (c->tableau[i][j] == 'S') {
                c->x_sortie = i;
                c->y_sortie = j;
                return; // Sortir dès que la sortie est trouvée
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
	
	//ouverture du fichier 
	fichier = fopen(nom_fichier, "r");
	
	//erreur d'ouverture 
	if (fichier == NULL) {
		fprintf(stderr, "Impossible d'ouvrir le fichier %s pour la lecture.\n", nom_fichier);
		return NULL;
	}
	
	//lecture des dimensions en largeur et longueur des couloirs
	fscanf(fichier, "%d\n%d\n", &hauteur, &largeur);
	
	char *sequence = malloc(50 * sizeof(char));// Définissez une taille suffisante pour stocker la séquence

    // Lecture de la séquence du fichier
    if (fscanf(fichier, "%s", sequence) == 1) {
        printf("Séquence lue : %s\n", sequence);
    } else {
        printf("Impossible de lire la séquence.\n");
    }
	//fermeture du fichier
	fclose(fichier);

	//création du couloir
	a_couloir c = creer_couloir(1, sequence);
	printf("couloir créé\n");
	//libération de la mémoire
	free(sequence);
	
	return c;
}

//--------------------------------------------------------------------------------
// end file
//--------------------------------------------------------------------------------
