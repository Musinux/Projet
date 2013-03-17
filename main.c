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

void initTabU(int **tabU,int **tab, int **mask){
    int i,j;
    for(i=0;i<TAI;i++){
        for(j=0;j<TAI;j++){
            if(mask[i][j]==0)
                tabU[i][j]=tab[i][j];
            else
                tabU[i][j]=2;
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
    int **tabU;
    int i,j=1;
    alea = rand()%4;
    tab = creeTab();
    tabU = creeTab();

    masque = creeTab();

    //printf("%d",alea);

    choixGrille(tab,alea);

    mask(masque, alea);

    initTabU(tabU,tab,masque);


    printf("\n\n");
    affJoueur(tabU);


    deplJoueur(tabU, masque);

    printf("\n");

    supprTab(tab);
    supprTab(masque);
    supprTab(tabU);
    return 0;
}
