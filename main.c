#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "conio.h"
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

    initCoords(c,NULL,NULL);
    alea = rand()%4;
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
    printf("\t 0 ou 1: entrer la valeur souhaitée");
    gotoxy(20,7);
    printf("\t'Espace': effacer une case");
    gotoxy(20,8);
    printf("\t'c' : afficher l'aide au joueur");
    gotoxy(20,9);
    printf("4- Validez avec 'Entree'");
    gotoxy(20,11);
    printf("Codes couleur:");
    gotoxy(20,12);
    textcolor(LIGHTCYAN);
    printf("\tCoup correct");
    gotoxy(20,13);
    textcolor(LIGHTMAGENTA);
    printf("\tCoup correspondant a la solution");
    gotoxy(20,14);
    textcolor(LIGHTRED);
    printf("\tCoup incorrect/Faux lorsque 'c' est entre");
    gotoxy(20,15);
    textcolor(LIGHTGREEN);
    printf("\tcase predefinie");
    textcolor(WHITE);


    genGrille(solution);
    genMasque(masque);
    //printf("\n\n%d",verifGrille(solution));
    //choixGrille(solution,alea);

    //choixMasque(masque, alea);

    initgrille_jeu(grille_jeu,solution,masque);
    while(fin==0){
        //clrscr();
        gotoxy(1,3);
        affJoueur(grille_jeu, masque, c, NULL);
        deplJoueur(grille_jeu, masque, c, solution);
        c= estValide(grille_jeu, c, NULL);
    }

    printf("\n");

    supprTab(solution);
    supprTab(masque);
    supprTab(grille_jeu);
    return 0;
}
