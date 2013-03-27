#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "conio.h"
#include "coords.h"
#include "generation.h"
#include "affichage.h"
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
    coords ***errors;
    int grille_remplie=1,erreurs_grille=0;

    /// errors est un tableau de coords, qui contient chaque coordonnée à sa bonne position, avec son état
    errors = (coords***) malloc(TAI*sizeof(coords**));
    for(i=0;i<TAI;i++){ /// allocation
        errors[i] = (coords**) malloc(TAI*sizeof(coords*));
        for(j=0;j<TAI;j++){
            errors[i][j]=(coords*)(-1);
        }
    }
    if(c->x>=0 && c->x<TAI && c->y>=0 && c->y<TAI && c->etat!=VIDE)
        errors[c->x][c->y]=c; /// d'abord on met le curseur actuel au bon endroit

    while(c!=NULL && c->prec!=NULL){ /// puis on remplit le tableau jusqu'à ce qu'on ait atteint le dernier curseur
        c=c->prec; /// à chaque itération on se déplace au curseur précédent
        if(errors[c->x][c->y]==-1 && c->etat!=VIDE){
            errors[c->x][c->y]=c; /// on le place au bon endroit
        }/*
        else{
            c = removeElem(c); /// s'il y a doublon, on supprime le curseur le plus ancien
        }*/
    }


    gotoxy(1,3);
    for(i=0;i<TAI;i++)
    {
        for(j=0;j<TAI;j++)
        {
            if(errors[i][j]!=-1 && errors[i][j]->etat!=VIDE && masque[i][j]!=0){
                switch(errors[i][j]->etat){ /// couleurs en fonction des états
                case ZEROS:
                case UNS:
                    textcolor(LIGHTMAGENTA);
                    break;
                case LIGS:
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
                }
                if(errors[i][j]->estEnVerif>0){ /// si on est dans le cadre des véfications de grille,
                                /// on affiche un message explicatif à chaque coup
                    affVerifs(errors[i][j]->estEnVerif);
                    errors[i][j]->estEnVerif=0; /// puis on efface son état de vérification
                }

            }
            else if(masque[i][j]==0) /// si la case fait partie du masque
                textcolor(LIGHTGREEN);
            else /// tous les autres cas [ERREURS]
                textcolor(WHITE);

            /// on affiche la valeur de la grille si elle est affichable
            if(grille_jeu[i][j]!=2){
                printf("%d ",grille_jeu[i][j]);
            }
            else{
                textcolor(RED);
                printf(". ");
                grille_remplie=0; /// si on affiche un point, c'est que toute la grille n'est pas remplie
            }
            textcolor(WHITE);
        }
        printf("\n");
    }
    if(grille_remplie){ /// si la grille est remplie on vérifie qu'elle est correcte, si oui on affiche la fin.
        if(checkErreurs(grille_jeu,c,NULL)){
            gotoxy(1,15);
            textcolor(LIGHTCYAN);
            printf("vous avez trouve une solution VALIDE!");
            textcolor(WHITE);
        }
    }
}

void affVerifs(int val){
    int x,y;
    x=wherex();
    y=wherey();
    gotoxy(1,19);
    switch(val){
    case 1:
        printf("Il y a deux zeros devant.                              ");
        break;
    case 2:
        printf("Il y a deux uns devant.                                ");
        break;
    case 3:
        printf("Il y a deux zeros derriere.                            ");
        break;
    case 4:
        printf("Il y a deux uns derriere.                              ");
        break;
    case 5:
        printf("Il y a deux zeros alignes sur la meme colonne.         ");
        break;
    case 6:
        printf("Il y a deux uns alignes devant sur la meme colonne.    ");
        break;
    case 7:
        printf("Il y a deux zeros alignes sur la meme colonne .        ");
        break;
    case 8:
        printf("La case est entouree par deux zeros sur la ligne.      ");
        break;
    case 9:
        printf("La case est entouree par deux uns sur la ligne.        ");
        break;
    case 10:
        printf("La case est entouree par deux zeros sur la colonne.    ");
        break;
    case 11:
        printf("La case est entouree par deux uns sur la colonne.      ");
        break;
    case 12:
        printf("La ligne contient quatre zero, la case doit etre un 1. ");
        break;
    case 13:
        printf("La ligne contient quatre un, la case doit etre un 0.   ");
        break;
    case 14:
        printf("La colonne contient quatre un, la case doit etre zero. ");
        break;
    case 15:
        printf("La ligne contient quatre zero, la case doit etre un.   ");
        break;
    default:
        printf("devine.                                                ");
    }
    Sleep(900);
    gotoxy(x,y);
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
    case 4:
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
        printf("Codes couleurs:");
    }
}

coords *deplJoueur(int **grille_jeu,int **masque, coords* co, int **solution)
{
    static int aide_restante=3; /// l'utilisateur n'a le droit qu'à 3 indices
    coords *prev_co; /// coordonnée permettant de comparer l'ancienne et la nouvelle
    char c;
    int y=co->x+3, /// on convertit les coords du tableau en coords visuelles
        x=(co->y)*2+1;
    int erreurs=1; /// variable attestant d'une erreur
    gotoxy(x,y);
    c=getch();

    while(c!=' ' || masque[co->x][co->y]==0 || x==20) /// tant qu'on a pas rentré 'Espace' sur une case valide de la grille
    {
        if((c=='q' || c=='Q') && x>1){ /// vers la gauche
            if(x!=20) /// si on se déplace dans la grille
                x-=2;
            else{ /// si on se déplace du menu vers la grille
                y=co->x+3;
                x=(co->y)*2+1;
            }

        }
        else if(c=='d' || c=='D'){ /// vers la droite
            if(x<15) /// si on se déplace dans la grille
                x+=2;
            else{ /// si on se déplace vers le menu
                x=20;
                y=12;
            }
        }
        else if((c=='z'||c=='Z') && ((x!=20 && y>3)||(x==20 && y>12))){ /// vers le haut
            y-=1;
        }
        else if((c=='s'||c=='S') && ((x!=20 && y<10)||(x==20 && y<13))){ /// vers le bas
            y+=1;
        }
        if(x!=20 || y<10){ /// si on est dans la grille, on enregistre les coordonnées dans le coord.
            co->x=y-3;
            co->y=(x-1)/2;
        }
        gotoxy(x,y);
        fflush(stdin); /// on vide le buffer au cas où l'utilisateur aurait rentré plus d'une valeur
        c=getch();
        if(x==20 && y==12 && c==13 && aide_restante>0){ /// si l'utilisateur clique sur 'afficher un indice'

            gotoxy(20,12); /// on change le bouton en vert
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
        if(x==20 && y==13 && c==13){
            prev_co=(coords*)-1;
            affMenu(2,0);
            do{
                prev_co=co;
                co = rempliAuto(grille_jeu,co);
                gotoxy(1,20);
                affJoueur(grille_jeu,masque,co,NULL);
                erreurs = estRemplie(grille_jeu);
            }while(!erreurs && prev_co!=co);
            if(erreurs)
                affMenu(4,0);
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
        checkErreurs(grille_jeu,co,NULL);
    }
    else{
        grille_jeu[co->x][co->y]=2;
        co->etat=VIDE;
        checkErreurs(grille_jeu,co,NULL);
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
