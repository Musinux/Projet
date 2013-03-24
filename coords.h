#ifndef COORDS_H_
#define COORDS_H_

typedef enum e_etat{  // ici les �tats donnent POURQUOI il y a une erreur, sauf dans le cas
    // de rempliAuto, l� �a indique POURQUOI c'est BON.
VIDE,
ZEROS, // trop de zeros sur la ligne/colonne
UNS, // trop de un sur la ligne/colonne
LIGS, // deux lignes identiques
COLS, // deux colonnes identiques
TROIS, // 3 z�ros/un sur la ligne/colonne
VALIDE, // correcspond aux regles du takuzu
CORRECT, // correspond � la solution donn�e
INCORRECT // faux.
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
