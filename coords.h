#ifndef COORDS_H_
#define COORDS_H_

typedef enum e_etat{
VIDE,
ZEROS,
UNS,
LIGS,
COLS,
TROIS,
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

void initElem(int x,int y, int etat, coords*c,coords*prec,coords*suiv);
coords* removeElem(coords*);
coords* addElem(coords *c);
void delList(coords *);
#endif // COORDS_H_
