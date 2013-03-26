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


int estRemplie(int **grille_jeu);
int** creeTab();

void estValide(int **,coords *,int**);
coords* rempliAuto(int **grille_jeu, coords *c);
int checkErreurs(int**, coords*,int**);

#endif // GENERATION_H__
