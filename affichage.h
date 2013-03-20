#ifndef AFFICHAGE_H__
#define AFFICHAGE_H__

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
    struct coords* prec;
    struct coords* suiv;
}coords;


void deplJoueur(int**,int**,coords*);
void affJoueur(int**,int**,coords*);
void initCoords(coords*c,coords*prec,coords*suiv);

#endif // AFFICHAGE_H__
