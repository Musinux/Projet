#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "conio.h"
#include "generation.h"
#include "affichage.h"
#define TAI 8
//#define DEBUG 8

void initCoords(coords*c,coords*prec,coords*suiv){
    c->x=0;
    c->y=0;
    c->etat=VIDE;
    c->prec=(prec!=NULL)?prec:NULL;
    c->suiv=(suiv!=NULL)?suiv:NULL;
}

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
    errors = creeTab();
    errors[c->x][c->y]=c->etat;
    while(prec->prec!=NULL){
        prec=prec->prec;
        errors[prec->x][prec->y]=prec->etat;
    }
    //affTab(errors, 18);
    //clrscr();
    for(i=0;i<TAI;i++)
    {
        for(j=0;j<TAI;j++)
        {
            if(errors[i][j]!=VIDE && masque[i][j]!=0){
                switch(errors[i][j]){
                    case CORRECT:
                        textcolor(LIGHTCYAN);
                        break;
                    case VALIDE:
                        textcolor(LIGHTMAGENTA);
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
                textcolor(YELLOW);
            if(grille_jeu[i][j]!=2){
                printf("%d ",grille_jeu[i][j]);
            }
            else{
                textcolor(RED);
                printf(". ");
            }
            textcolor(WHITE);
        }
        printf("\n");
    }
}

void deplJoueur(int **grille_jeu,int **masque, coords* co, int **solution)
{
    char c;
    int y=co->x+3,x=(co->y)*2+1;
    gotoxy(x,y);
    c=getch();
    while(c!=' ' || masque[co->x][co->y]==0)
    {
        if((c=='q' || c=='Q' ) && x>1){ // vers la gauche
            x-=2;
        }
        else if((c=='d' || c=='D') && x<15){ // vers la droite
            x+=2;
        }
        else if((c=='z'||c=='Z') && y>3){ // vers le haut
            y-=1;
        }
        else if((c=='s'||c=='S') && y<10){ //vers le bas
            y+=1;
        }
        co->x=y-3;
        co->y=(x-1)/2;
        gotoxy(x,y);
        c=getch();
    }
    c=0;
    while(c!='0' && c!='1' && c!=' '){
        c=0;
        gotoxy(1,3);
        affJoueur(grille_jeu, masque, co, NULL);
        gotoxy(x,y);
        c=getchar();

        if(c=='c'){

            checkErreurs(grille_jeu, co, solution);
            gotoxy(1,3);
            affJoueur(grille_jeu,masque,co,solution);
            Sleep(5000);
            checkErreurs(grille_jeu, co, NULL);
            gotoxy(1,3);
            affJoueur(grille_jeu,masque,co,NULL);
        }
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
}

