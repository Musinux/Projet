#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "conio.h"
#include "coords.h"
#include "generation.h"
#include "affichage.h"
#define TAI 8
//#define DEBUG 8


void affTab(int **tab,int dist){
    int i,j;

    for(i=0;i<TAI;i++){
        gotoxy(20+dist,3+i);
        for(j=0;j<TAI;j++){
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
    gotoxy(1,3);
}

void affJoueur(int **grille_jeu, int **masque, coords* c, int **solution)
{
    int i,j;
    coords *prec=c;
    int **errors;
    int grille_remplie=1;
    errors = creeTab();
    errors[c->x][c->y]=c->etat;
    while(prec->prec!=NULL){
        prec=prec->prec;
        errors[prec->x][prec->y]=prec->etat;
    }
    //affTab(errors, 18);
    //clrscr();
    gotoxy(1,3);
    for(i=0;i<TAI;i++)
    {
        for(j=0;j<TAI;j++)
        {
            if(errors[i][j]!=VIDE && masque[i][j]!=0){
                switch(errors[i][j]){
                case UNS:
                    textcolor(LIGHTMAGENTA);
                    break;
                case ZEROS:
                    textcolor(LIGHTMAGENTA);
                    break;
                case LIGS:
                    textcolor(DARKGRAY);
                    break;
                case COLS:
                    textcolor(DARKGRAY);
                    break;
                case TROIS:
                    textcolor(YELLOW);
                    break;
                case CORRECT:
                    textcolor(LIGHTBLUE);
                    break;
                case VALIDE:
                    textcolor(LIGHTCYAN);
                    break;
                case INCORRECT:
                    textcolor(LIGHTRED);
                    break;
                default:
                    textcolor(WHITE);
                }
            }
            else if(masque[i][j]==0)
                textcolor(LIGHTGREEN);
            else
                textcolor(WHITE);
            if(grille_jeu[i][j]!=2){
                printf("%d ",grille_jeu[i][j]);
            }
            else{
                textcolor(RED);
                printf(". ");
                grille_remplie=0;
            }
            textcolor(WHITE);
        }
        printf("\n");
    }
    if(grille_remplie){
        if(checkErreurs(grille_jeu,c,NULL)){
            gotoxy(1,15);
            textcolor(LIGHTCYAN);
            printf("vous avez trouve une solution VALIDE!");
            textcolor(WHITE);
        }
    }
}

void affMenu(int mode,int etat){

    switch(mode){
    case 0: // mode standard
        gotoxy(20,11);
        printf("Menu:");
        gotoxy(20,13);
        textbackground(LIGHTRED);
        printf(" ");
        textbackground(BLACK);
        textcolor(LIGHTGREEN);
        printf(" remplir la grille automatiquement");
        textcolor(WHITE);
        break;
    case 1:
        gotoxy(20,12);
        if(etat!=0){
            textbackground(LIGHTRED);
            printf(" ");
            textbackground(BLACK);
            textcolor(LIGHTGREEN);
            printf(" afficher un indice(encore %d)",etat);
        }
        else{
            textbackground(LIGHTGRAY);
            printf(" ");
            textbackground(BLACK);
            textcolor(LIGHTGRAY);
            printf(" afficher un indice           ");
        }
        break;
    case 2:
        gotoxy(20,12);
        gotoxy(55,12);
        textcolor(LIGHTCYAN);
        printf("Coup valide");
        gotoxy(55,13);
        textcolor(LIGHTBLUE);
        printf("Coup correct");
        gotoxy(55,14);
        textcolor(LIGHTRED);
        printf("Coup invalide");
        gotoxy(55,15);
        textcolor(LIGHTGREEN);
        printf("case predefinie");
        gotoxy(55,16);
        textcolor(LIGHTMAGENTA);
        printf("complement de 1 ou de 0");
        gotoxy(55,17);
        textcolor(DARKGRAY);
        printf("ligne ou colonne identiques\n");
        gotoxy(55,18);
        textcolor(YELLOW);
        printf("suite de deux 0 ou 1\n");
        break;
    case 3:
        gotoxy(55,12);
        textcolor(LIGHTCYAN);
        printf("Coup valide");
        gotoxy(55,13);
        textcolor(LIGHTBLUE);
        printf("Coup correct");
        gotoxy(55,14);
        textcolor(LIGHTRED);
        printf("Coup invalide");
        gotoxy(55,15);
        textcolor(LIGHTGREEN);
        printf("case predefinie");
        gotoxy(55,16);
        textcolor(LIGHTMAGENTA);
        printf("trop de 1 ou de 0");
        gotoxy(55,17);
        textcolor(DARKGRAY);
        printf("lig. ou col. identiques");
        gotoxy(55,18);
        textcolor(YELLOW);
        printf("plus de deux 0 ou 1 a cote");
        break;
    }
}

coords *deplJoueur(int **grille_jeu,int **masque, coords* co, int **solution)
{
    static int aide_restante=3;
    coords *prev_co;
    char c;
    int y=co->x+3,x=(co->y)*2+1;
    gotoxy(x,y);
    c=getch();

    while(c!=' ' || masque[co->x][co->y]==0 || x==20)
    {
        if((c=='q' || c=='Q') && x>1){ // vers la gauche
            if(x!=20)
                x-=2;
            else{
                y=co->x+3;
                x=(co->y)*2+1;
            }

        }
        else if(c=='d' || c=='D'){ // vers la droite
            if(x<15)
                x+=2;
            else{
                x=20;
                y=12;
            }
        }
        else if((c=='z'||c=='Z') && ((x!=20 && y>3)||(x==20 && y>12))){ // vers le haut
            y-=1;
        }
        else if((c=='s'||c=='S') && ((x!=20 && y<10)||(x==20 && y<13))){ //vers le bas
            y+=1;
        }
        if(x!=20 || y<10){
            co->x=y-3;
            co->y=(x-1)/2;
        }
        gotoxy(x,y);
        fflush(stdin);
        c=getch();
        if(x==20 && y==12 && c==13 && aide_restante>0){

            gotoxy(20,12);
            textbackground(LIGHTGREEN);
            printf(" ");
            textbackground(BLACK);

            checkErreurs(grille_jeu, co, solution);
            gotoxy(1,3);
            affJoueur(grille_jeu,masque,co,solution);
            Sleep(5000);
            checkErreurs(grille_jeu, co, NULL);
            gotoxy(1,3);
            affJoueur(grille_jeu,masque,co,NULL);
            aide_restante-=1;
            affMenu(1,aide_restante);

        }
        if(x==20 && y==13 && c==13){ // modifier le menu ici
            prev_co=-1;
            affMenu(3,0);
            do{
                prev_co=co;
                co = rempliAuto(grille_jeu,co);
                affJoueur(grille_jeu,masque,co,NULL);
            }while(checkErreurs(grille_jeu,co,NULL) && prev_co!=co);
            affMenu(32,0);
        }
    }
    c=0;
    while(c!='0' && c!='1' && c!=' '){
        c=0;
        gotoxy(1,3);
        checkErreurs(grille_jeu,co,NULL);
        affJoueur(grille_jeu, masque, co, NULL);
        gotoxy(x,y);
        fflush(stdin);
        c=getchar();
    }
    if(c!=' '){
        grille_jeu[co->x][co->y]=c-48;
        co->etat=INCORRECT;
    }
    else{
        grille_jeu[co->x][co->y]=2;
        co->etat=VIDE;
    }
    checkErreurs(grille_jeu, co, NULL);

    if(checkErreurs(grille_jeu, co, NULL)==1)
    {
        affMenu(3,0);
    }
    return co;
}

void affgrile(int **grid)
{
    int i,j;
    printf("\n");
    for(i=0;i<TAI;i++){
        for(j=0;j<TAI;j++){
            if(grid[i][j]==0 || grid[i][j]==1)
                printf("%d ",grid[i][j]);
            else
                printf(". ");
        }
        printf("\n");
    }
}
