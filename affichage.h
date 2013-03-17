#ifndef AFFICHAGE_H__
#define AFFICACHE_H__

typedef enum e_etat{
VALIDE,
CORRECT,
INCORRECT,
VIDE
}e_etat;

typedef struct coords{
    int x;
    int y;
    e_etat etat;
}coords;



void deplJoueur(int**,int**,coords*);
void affJoueur(int**,int**,coords*);

#endif // AFFICHAGE_H__
