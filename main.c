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

void initgrille_jeu(int **grille_jeu,int **tab, int **masque){
    int i,j;
    for(i=0;i<TAI;i++){
        for(j=0;j<TAI;j++){
            if(masque[i][j]==0)
                grille_jeu[i][j]=tab[i][j];
            else
                grille_jeu[i][j]=2;
        }
    }
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
    int **tab,alea;
    int **masque;
    int **grille_jeu;
    int i,j=1;
    alea = rand()%4;
    tab = creeTab();
    grille_jeu = creeTab();

    masque = creeTab();

    //printf("%d",alea);

    choixGrille(tab,alea);

    choixMasque(masque, alea);

    initgrille_jeu(grille_jeu,tab,masque);


    printf("\n\n");
    affJoueur(grille_jeu);


    deplJoueur(grille_jeu, masque);

    printf("\n");

    supprTab(tab);
    supprTab(masque);
    supprTab(grille_jeu);
    return 0;
}
