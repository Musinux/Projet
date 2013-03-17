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

void initCoords(coords*c){
    c->x=0;
    c->y=0;
    c->etat=VIDE;
}


int main()
{
    srand((unsigned)time(NULL));
    int **solution,alea;
    int **masque;
    coords c;
    int **grille_jeu;
    int i,j=1,fin=0;

    initCoords(&c);
    alea = rand()%4;
    solution = creeTab();
    grille_jeu = creeTab();

    masque = creeTab();

    gotoxy(20,5);
    printf("Bienvenue au Takuzu!");
    gotoxy(20,6);
    printf("1- Naviguez avec z,q,s,d");
    gotoxy(20,7);
    printf("2- Selectionnez la case a modifier avec 'Espace'");
    gotoxy(20,8);
    printf("3- Entrez votre choix 0/1/Espace pour effacer une case");
    gotoxy("4- ");

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
