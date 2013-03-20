#ifndef GENERATION_H__
#define GENERATION_H__
#define TAI 8

void calcIndice(int*,int**,int*,int*,int,int);
void genGrille(int**);
void choixGrille(int**,int);
void choixMasque(int**,int);
void initgrille_jeu(int **,int **, int **);
int** creeTab();
void supprTab(int **tab);

#endif // GENERATION_H__
