#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "conio.h"
#include "affichage.h"
#include "generation.h"

int** creeTab(){
    int **tab,i,j;
    tab =(int*) malloc(TAI*sizeof(int*));

    for(i=0;i<TAI;i++){
        tab[i] = malloc(TAI*sizeof(int));
        for(j=0;j<TAI;j++){
            tab[i][j]=0;
        }
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

void calcIndice(int *l,int **solution, int *i,int *m,int k,int type){

    // et si deux fois de suite on regénère la même ligne, on repart de la ligne précédente, et ainsi de suite
    int o,p;
    *m+=1;
    *i=(*i-*m>=0)?*i-*m:0;
    for(p=0;p<TAI;p++)
        l[p]=0;
    for(o=0;o<=*i;o++){
        for(p=0;p<TAI;p++)
            l[p]=solution[o][p]?l[p]+1:l[p]-1;
    }
}


void genGrille(int **solution)
{
    srand((unsigned)time(NULL));

    int i,j,k,l[TAI]={0},m=0,n,o,p,cpt_simili;

    // i et j sont des compteurs.
    // k est une variable qui prend +1 lorsqu'on ajoute un 1 à une ligne, et -1 lorsqu'on ajoute un 0.
    // le but étant d'avoir un k==0 à la fin de la ligne

    // l[] est un tableau comprenant les valeurs pour chaque colonne.
    // même concept que pour le k.
    // après plusieurs essais, si |k| ou |l[]| > 2, il y aura forcément une erreur par la suite.


    for(i=0;i<TAI;i++){ // i descend
        for(j=0;j<TAI;j++){ // j va vers la droite

            if(j==0){ // au début on met le compteur à 0
                k=0;
            }
            // dans le cas où en ligne et en colonne on a deux chiffres identiques qui se succèdent
            if((j>=2 && solution[i][j-1]==solution[i][j-2]) && (i>=2 && solution[i-1][j]==solution[i-2][j])){
                // si ce sont les mêmes chiffres, la nouvelle case aura l'inverse
                if(solution[i][j-1]==solution[i-1][j]){
                    solution[i][j]= solution[i-1][j]?0:1;
                }
                else{ // sinon, on recommence la génération de la ligne, vu que c'est un cas impossible à gérer
                    calcIndice(l,solution,&i,&m,k,0);
                    break;
                }
            }
            else if(j>=2 && solution[i][j-1]==solution[i][j-2]){ // si juste la ligne a deux chiffres identiques
                if(((l[j]==1 || k==2) && solution[i][j-1]==0) || ((l[j]==-1 || k==-2) && solution[i][j-1]==1)){
                    calcIndice(l,solution,&i,&m,k,5);
                    break;
                }
                else{
                    solution[i][j]= solution[i][j-1]?0:1;
                }
            }
            else if(i>=2 && solution[i-1][j]==solution[i-2][j]){ // si juste la colonne a deux chiffres identiques
                if(((l[j]==2 || k==1) && solution[i-1][j]==0) || ((l[j]==-2 || k==-1) && solution[i-1][j]==1)){
                    calcIndice(l,solution,&i,&m,k,6);
                    break;
                }
                else{
                    solution[i][j]= solution[i-1][j]?0:1;
                }
            }
            else if((k==2 && l[j]==-2)||(k==-2 && l[j]==2))  { // si on se retrouve avec des valeurs inverses pour k et l[]
                // pas d'autre solution que de regénérer la ligne, avec les mêmes conditions que pour précédement
                calcIndice(l,solution,&i,&m,k,1);
                break;
            }
            else if(k==2 || l[j]==2) { // cas où on a trop de 1
                if((k==2 && (j!=TAI-1 || l[j]==2)) || (l[j]==2 && (i!=TAI-1 || k==2))){ // si on a un k ou l[] == 2 et qu'on est pas dans une situation inextricable
                    solution[i][j]=0;
                }
                else{
                    // lorsqu'on est arrivé à la dernière ligne ou dernière colonne
                    // il n'y a forcément qu'une solution possible pour cette ligne.
                    // si k ou l[] == 2 dans cette situation, la seule solution est de regénérer la grille
                    calcIndice(l,solution,&i,&m,k,2);
                    break;
                }
            }
            else if(k==-2 || l[j]==-2) { // cas où on a trop de 0
                if((k==-2 && (j!=TAI-1 || l[j]==-2)) || (l[j]==-2 && (i!=TAI-1 || k==-2))){
                    solution[i][j]=1;
                }
                else{
                    calcIndice(l,solution,&i,&m,k,3);
                    break;
                }
            }
            else if(j==TAI-1 || i==TAI-1) { // si on est à une fin de ligne ou de colonne
                if((j==TAI-1 && i==TAI-1) && ((k==1 && l[j]==-1) || (k==-1 && l[j]==1))){ // si on est à la toute fin et qu'il faut un 1 pour la ligne et
                    // un 0 pour la colonne, on est coincé, on regénère la ligne.
                    calcIndice(l,solution,&i,&m,k,4);
                    break;
                }
                else if(j==TAI-1){ // si on n'est qu'à la fin d'une ligne
                    if(k==-1){ // s'il faut un 1
                        solution[i][j]=1;
                    }
                    else if(k==1){ // s'il faut un 0
                        solution[i][j]=0;
                    }
                }
                else if(i==TAI-1){ // si on n'est qu'à la fin d'une colonne
                    if(l[j]==-1){ // s'il faut un 1
                        solution[i][j]=1;
                    }
                    else if(l[j]==1){ // s'il faut un 0
                        solution[i][j]=0;
                    }
                }
            }
            else{  // si aucune des conditions précédentes n'est rencontrées, on génère un nombre aléatoire
                solution[i][j]=rand()%2;
            }
            k=solution[i][j]?k+1:k-1; // on calcule le compteur de 0|1 par ligne
            l[j]=solution[i][j]?l[j]+1:l[j]-1; // on calcule le compteur de 0|1 par colonne
            if(j==TAI-1) // si on est à la fin de la ligne
            {
                int cpt_simili=0;
                for(n=0;n<i;n++) // on teste toutes les lignes à chaque fois
                {
                    cpt_simili=0;
                    for(o=0;o<TAI;o++) // lignes
                    {
                        if(i>0  && solution[i][o] == solution[n][o]){
                            cpt_simili+=1;
                        }
                    }
                    if(cpt_simili==8){
                        calcIndice(l,solution,&i,&m,k,7);
                        n=i+1;
                    }
                }
                if(n=i+1)
                    break;
                if(i==TAI-1){
                    // n,o,p
                    cpt_simili=0;
                    for(n=0;n<j;n++) // on teste toutes les lignes à chaque fois
                    {
                        for(o=0;o<TAI;o++) // lignes
                        {
                            if(i>0  && solution[o][j] == solution[o][n]){
                                cpt_simili+=1;
                            }
                        }
                        if(cpt_simili==8){
                            calcIndice(l,solution,&i,&m,k,8);
                            n=j+1;
                        }
                    }
                    if(n=j+1)
                        break;
                    m=0;
                }
                else{
                    m=0;
                }

            }
        }

    }
}

void choixGrille(int **grille,int alea){
    int i,j;
    FILE *fgrille= fopen("grilles.txt","r");



    // on se déplace jusqu'à la bonne grille
    for(i=0;i<73*alea;i++)
    {
        fgetc(fgrille);
    }

    for(i=0;i<TAI;i++)
    {
        for(j=0;j<TAI;j++)
        {
            if(j==0&&i!=0)
                fgetc(fgrille);
            grille[i][j] = (int)fgetc(fgrille)-48;
        }
    }
    fclose(fgrille);
}

void initgrille_jeu(int **grille_jeu,int **solution, int **masque){
    int i,j;
    for(i=0;i<TAI;i++){
        for(j=0;j<TAI;j++){
            if(masque[i][j]==0)
                grille_jeu[i][j]=solution[i][j];
            else
                grille_jeu[i][j]=2;
        }
    }
}

int verifGrille(int **solution){
    int i,j,cpt=0,k,l[TAI]={0},cpt_simili_col[TAI]={0},cpt_simili_lig=0;
/*
    for(i=0;i<TAI;i++){
        cpt_simili_lig=0;
        for(j=0;j<TAI;j++){
            if((j!=0) && (solution[i][j]!=solution[i][j-1])){
                cpt_simili_lig+=1;
            }
            if(i!=0){
                if(solution[i][j]==solution[i-1][j])
                    cpt_simili_col[j]+=1;
                if(cpt_simili_col[j]==8){
                    return -300;
                }
            }
        }
        if(cpt_simili_lig==8)
            return -200;
    }
*/

    for(i=0;i<TAI;i++) {
        for(j=0;j<TAI;j++) {
            cpt = solution[i][j]?cpt+1:cpt-1;
        }
    }
    if(cpt!=0)
        return -100;
    else{
        for(i=0;i<TAI;i++) {
            for(j=0;j<TAI;j++) {
                if(j==0) // au début on met le compteur à 0
                    k=0;

                // dans le cas où en ligne et en colonne on a deux chiffres identiques qui se succèdent
                if((j>=2 && solution[i][j-1]==solution[i][j-2]) && (i>=2 && solution[i-1][j]==solution[i-2][j])){
                    // si ce sont les mêmes chiffres, la nouvelle case aura l'inverse
                    if(solution[i][j-1]!=solution[i-1][j]){
                        return -90;
                    }
                }
                else if(j>=2 && solution[i][j-1]==solution[i][j-2]){ // si juste la colonne a deux chiffres identiques
                    if((k==1 && solution[i][j-1]==0) || (k==-1 && solution[i][j-1]==1) || (solution[i][j]==solution[i][j-1])){

                        return -80;
                    }
                }
                else if(i>=2 && solution[i-1][j]==solution[i-2][j]){ // si juste la ligne a deux chiffres identiques
                    if((l[j]==1 && solution[i-1][j]==0) || (l[j]==-1 && solution[i-1][j]==1) || (solution[i][j]==solution[i-1][j])){
                        return -70;
                    }
                }
                else if((k==2 && l[j]==-2)||(k==-2 && l[j]==2))  { // si on se retrouve avec des valeurs inverses pour k et l[]
                    return -60;
                }
                else if(k==2 || l[j]==2) { // cas où on a trop de 1
                    if(((k==2 && (j!=TAI-1 || l[j]==2)) || (l[j]==2 && (i!=TAI-1 || k==2))) && solution[i][j]!=0){ // si on a un k ou l[] == 2 et qu'on est pas dans une situation inextricable
                        return -50;
                    }
                }
                else if(k==-2 || l[j]==-2) { // cas où on a trop de 0
                    if(((k==-2 && (j!=TAI-1 || l[j]==-2)) || (l[j]==-2 && (i!=TAI-1 || k==-2))) && solution[i][j]!=1){
                        printf("\n\ni:%d   \nj:%d   \nsolution[%d][%d]:%d   \nsolution[%d][%d]:%d  \nsolution[%d][%d]:%d  \nk:%d  \nl[%d]:%d",i,j,i,j,solution[i][j],i,j-1,solution[i][j-1],i,j-2,solution[i][j-2],k,j,l[j]);
                        return -40;
                    }
                }
                else if(j==TAI-1 || i==TAI-1) { // si on est à une fin de ligne ou de colonne
                    if(((j==i && i==TAI-1) && ((k==1 && l[j]==-1) || (k==-1 && l[j]==1))) || (j==TAI-1 && ((k==-1 && solution[i][j]==0)|| (k==1 && solution[i][j]==1))) || (i==TAI-1 && ((l[j]==-1 && solution[i][j]==0)|| (l[j]==1 && solution[i][j]==1))) ){ // si on est à la toute fin et qu'il faut un 1 pour la ligne et
                        return -30;
                    }
                }
                k=solution[i][j]?k+1:k-1; // on calcule le compteur de 0|1 par ligne
                l[j]=solution[i][j]?l[j]+1:l[j]-1; // on calcule le compteur de 0|1 par colonne
            }
        }
    }
    return 1;
}

void choixMasque(int **masque, int alea)
{
    int i,j;
    FILE *fmasque= fopen("masque.txt","r");

    // on se déplace jusqu'à la bonne grille
    for(i=0;i<73*alea;i++)
        fgetc(fmasque);

    for(i=0;i<TAI;i++){
        for(j=0;j<TAI;j++)
        {
            if(j==0&&i!=0)
                fgetc(fmasque);
            masque[i][j] = (int)fgetc(fmasque)-48;
        }
    }
    fclose(fmasque);
}


void estValide(int **grille_jeu,coords *c){
    int i,cpt0=0,cpt1=0;
    if(c->etat!=VIDE){
        for(i=0;i<TAI;i++){
            if(grille_jeu[c->x][i]!=2){
                if(i>0 && i<TAI-1 && grille_jeu[c->x][i-1]==grille_jeu[c->x][i] && grille_jeu[c->x][i+1]==grille_jeu[c->x][i])
                        cpt1=TAI;
                if(grille_jeu[c->x][i])
                    cpt1+=1;
                else
                    cpt0+=1;
            }
        }
        if(cpt0>(TAI/2) || cpt1>(TAI/2)){
            gotoxy(20,18);
            printf("coup incorrect, cpt=%d,%d",cpt0,cpt1);
            c->etat=INCORRECT;
        }
        else{
            cpt0=cpt1=0;
            for(i=0;i<TAI;i++){
                if(grille_jeu[i][c->y]!=2){
                    if(i>0 && i<TAI-1 && grille_jeu[i-1][c->y]==grille_jeu[i][c->y] && grille_jeu[i+1][c->y]==grille_jeu[i][c->y])
                        cpt1=TAI;
                    else if(grille_jeu[i][c->y])
                        cpt1+=1;
                    else
                        cpt0+=1;
                }
            }
            if(cpt0>(TAI/2) || cpt1>(TAI/2)){
                gotoxy(20,18);
                printf("coup incorrect, cpt=%d,%d",cpt0,cpt1);
                c->etat=INCORRECT;
            }
            else{
                gotoxy(20,18);
                printf("coup correct, cpt=%d,%d",cpt0,cpt1);
                c->etat=CORRECT;
            }
        }
    }

}
