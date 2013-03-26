#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "conio.h"
#include "coords.h"
#include "affichage.h"
#include "generation.h"
#define TAI 8
//#define DEBUG 8

int main()
{
    srand((unsigned)time(NULL));
    int **solution,alea;
    int **masque;
    coords *c;
    c = (coords*) malloc(sizeof(coords));
    int **grille_jeu;
    int i,fin=0;
    unsigned char test_char;

    initElem(NULL,NULL,NULL,NULL,c,NULL,NULL);
    //alea = rand()%4;
    solution = creeTab();
    grille_jeu = creeTab();

    masque = creeTab();

    gotoxy(20,2);
    printf("Bienvenue au Takuzu!");
    gotoxy(20,3);
    printf("1- Naviguez avec z,q,s,d");
    gotoxy(20,4);
    printf("2- Selectionnez la case a modifier avec 'Espace'");
    gotoxy(20,5);
    printf("3- Entrez votre choix: 0/1/Espace pour effacer une case");
    gotoxy(20,6);
    printf("\t 0 ou 1: entrer la valeur souhaitee");
    gotoxy(20,7);
    printf("\t'Espace': effacer une case");
    gotoxy(20,8);
    printf("4- Validez avec 'Entree'");
    gotoxy(55,11);
    printf("Codes couleur:");

    affMenu(3,0);
    affMenu(0,0);
    affMenu(1,3);


    genGrille(solution);
    genMasque(masque,solution);

    //choixGrille(solution,alea);

    //choixMasque(masque, alea);

    initgrille_jeu(grille_jeu,solution,masque);
    while(fin==0){
        gotoxy(1,3);
        affJoueur(grille_jeu, masque, c, NULL);
        c= deplJoueur(grille_jeu, masque, c, solution);
        c= estValide(grille_jeu, c, NULL);
    }

    printf("\n");

    supprTab(solution);
    supprTab(masque);
    supprTab(grille_jeu);
    delList(c);
    return 0;
}
