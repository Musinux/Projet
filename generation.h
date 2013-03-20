#ifndef GENERATION_H__
#define GENERATION_H__
#include "affichage.h"
#define TAI 8
void calcIndice(int*,int**,int*,int*,int,int);
void genGrille(int**);
void genMasque(int **);
void choixGrille(int**,int);
void choixMasque(int**,int);
void initgrille_jeu(int **,int **, int **);
int** creeTab();
void supprTab(int **tab);
coords* estValide(int **,coords *);
void checkErreurs(int**, coords*);
#endif // GENERATION_H__
