#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "generation.h"
#include "affichage.h"
#define TAI 8

//#define DEBUG 8
void affJoueur(int **grille_jeu)
{
    int i,j;
    for(i=0;i<TAI;i++)
    {
        for(j=0;j<TAI;j++)
        {
            if(grille_jeu[i][j]!=2)
                printf("%d ",grille_jeu[i][j]);
            else
                printf("# ");
        }
        printf("\n");
    }
}

void deplJoueur(int **grille_jeu,int **masque)
{
    char c,y=3,x=1;
    gotoxy(x,y);
    c=getch();
    while(c!=' ' || masque[(x-1)/2][(y-3)/2]==0)
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

        gotoxy(x,y);
        c=getch();
        if(c==' ' && masque[(x-1)/2][(y-3)/2]==0){
            gotoxy(20,20);
            printf("Case inchangeable ");
            gotoxy(x,y);
        }
    }
    while(c!='0' && c!='1'){
        c=0;
        gotoxy(1,3);
        affJoueur(grille_jeu);
        gotoxy(x,y);
        c=getchar();
        gotoxy(20,20);
        printf("cool %c",c);

    }
    grille_jeu[(x-1)/2][(y-3)/2]=c-48;
}
