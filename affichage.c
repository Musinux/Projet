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
    if(prec!=NULL)
        c->prec=prec;
    else
        c->prec=NULL;

    if(suiv!=NULL)
        c->suiv=suiv;
    else
        c->suiv=NULL;
}

void affJoueur(int **grille_jeu, int **masque, coords* c)
{
    int i,j;
    int **errors;
    errors = creeTab();
    errors[c->x][c->y]=c->etat;

    while(c->prec!=NULL){
        c=c->prec;
        switch(c->etat){
            case VALIDE:
                errors[c->x][c->y]=VALIDE;
                break;
            case CORRECT:
                errors[c->x][c->y]=CORRECT;
                break;
            case INCORRECT:
                errors[c->x][c->y]=INCORRECT;
                break;
            default:
                errors[c->x][c->y]=0;
        }
        //gotoxy(20,10);
        //printf("c:\nx=%d\ny=%d\netat=%d\nprec=%d\nsuiv=%d\nerrors[]=%d",c->x,c->y,c->etat,c->prec,c->suiv,errors[c->x][c->y]);
    }

    //clrscr();
    for(i=0;i<TAI;i++)
    {
        for(j=0;j<TAI;j++)
        {
            if(errors[i][j]!=0 && masque[i][j]!=0){
                if(errors[i][j]==CORRECT)
                    textcolor(LIGHTCYAN);
                else if(errors[i][j]==VALIDE)
                    textcolor(LIGHTMAGENTA);
                else if(errors[i][j]==INCORRECT)
                    textcolor(LIGHTRED);
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

void deplJoueur(int **grille_jeu,int **masque, coords* co)
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
        if(c==' ' && masque[co->x][co->y]==0){
            gotoxy(20,21);
            printf("Case inchangeable [%d][%d]",co->x,co->y);
            gotoxy(x,y);
        }
        gotoxy(20,22);
        printf("Case [%d][%d]=%d",co->x,co->y,masque[co->x][co->y]);
        gotoxy(x,y);
        c=getch();
    }
    c=0;
    while(c!='0' && c!='1' && c!=' '){
        c=0;
        gotoxy(1,3);
        affJoueur(grille_jeu, masque, co);
        gotoxy(x,y);
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
}

