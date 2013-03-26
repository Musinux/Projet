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
    //srand((unsigned)time(NULL));
    int **solution;//,alea;
    int **masque;
    coords *c;

    int **grille_jeu;
    int i,fin=0;
    /// on crée nos trois tableaux dynamiquement.
    solution = creeTab();
    grille_jeu = creeTab();
    masque = creeTab();

    /// on affiche les consignes et le menu
    affMenu(4,0);
    affMenu(3,0);
    affMenu(0,0);
    affMenu(1,3);

    /// on génère une grille et le masque qui lui correspond
    genGrille(solution);
    gotoxy(1,1);
    genMasque(masque,solution);
    /// on remplit la grille grille_jeu avec les données précédentes
    initgrille_jeu(grille_jeu,solution,masque);
    c = (coords*) malloc(sizeof(coords));
    initElem(0,0,VIDE,0,c,NULL,NULL);
    while(fin==0){
        gotoxy(1,3);
        affJoueur(grille_jeu, masque, c, NULL); /// on affiche la grille
        c = deplJoueur(grille_jeu, masque, c, solution); /// on affiche le curseur
        estValide(grille_jeu, c, NULL); /// on vérifie la validité des cases entrées
        c = addElem(c);
    }

    printf("\n");

    supprTab(solution);
    supprTab(masque);
    supprTab(grille_jeu);
    delList(c);
    return 0;
}
