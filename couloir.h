#ifndef COULOIR_H
#define COULOIR_H

typedef struct my_couloir{

char *sequence;
int largeur;
}couloir;

void init(couloir *c, int largeur, const char *sequence);

void affiche(couloir *c);

void orientation(const char *sequence);

int count_north(const char *sequence);

int count_west(const char *sequence);

//void save(Couloir *c);


#endif 
