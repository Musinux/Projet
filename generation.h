#ifndef GENERATION_H__
#define GENERATION_H__
#include "coords.h"
#include "affichage.h"
#define TAI 8
void calcIndice(int*,int**,int*,int*,int,int);
void genGrille(int**);
void genMasque(int **,int **);
void choixGrille(int**,int);
void choixMasque(int**,int);
void initgrille_jeu(int **,int **, int **);
void supprTab(int **tab);

int checkErreurs(int**, coords*,int**);
int estRemplie(int **grille_jeu);
int** creeTab();

coords* estValide(int **,coords *,int**);
coords* rempliAuto(int **grille_jeu, coords *c);

#endif // GENERATION_H__
