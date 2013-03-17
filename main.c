#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "conio.h"
#include "affichage.h"
#include "generation.h"
#define TAI 8
//#define DEBUG 8


int** creeTab(){
    int **tab,i;
    tab =(int*) malloc(TAI*sizeof(int*));

    for(i=0;i<TAI;i++){
        tab[i] = malloc(TAI*sizeof(int));
    }
    return tab;
}

void supprTab(int **tab){
    int i;
    for(i=0;i<TAI;i++){
        free(tab[i]);
    }
    free(tab);
}



int main()
{
    srand((unsigned)time(NULL));
    int **solution,alea;
    int **masque;
    coords c;
    int **grille_jeu;
    int i,j=1,fin=0;

    c.x=0;
    c.y=0;
    c.etat=VALIDE;

    alea = rand()%4;
    solution = creeTab();
    grille_jeu = creeTab();

    masque = creeTab();

    //printf("%d",alea);

    choixGrille(solution,alea);

    choixMasque(masque, alea);

    initgrille_jeu(grille_jeu,solution,masque);
    while(fin==0){
        //clrscr();
        gotoxy(1,3);
        affJoueur(grille_jeu, masque, &c);
        deplJoueur(grille_jeu, masque, &c);
        estValide(grille_jeu, &c);
    }

    printf("\n");

    supprTab(solution);
    supprTab(masque);
    supprTab(grille_jeu);
    return 0;
}
