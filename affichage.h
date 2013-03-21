#ifndef AFFICHAGE_H__
#define AFFICHAGE_H__

typedef enum e_etat{
VIDE,
VALIDE,
CORRECT,
INCORRECT
}e_etat;

typedef struct coords{
    int x;
    int y;
    e_etat etat;
    struct coords* prec;
    struct coords* suiv;
}coords;


void deplJoueur(int**,int**,coords*,int**);
void affJoueur(int**,int**,coords*,int**);
void affTab(int**);
void initCoords(coords*c,coords*prec,coords*suiv);

#endif // AFFICHAGE_H__
