#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "conio.h"
#include "coords.h"
#include "affichage.h"
#include "generation.h"
//#define DEBUG



int** creeTab(){
    int **tab,i,j;
    tab =(int**) malloc(TAI*sizeof(int*));

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

void genMasque(int **masque){
    srand((unsigned)time(NULL));
    int nb_masque= TAI*TAI-2.5*TAI-10;
    int **tab;
    int tab_ut=0,i=0,j=0,x,y,fin=0;
    tab = (int**)malloc(sizeof(int*)*nb_masque);
    for(i=0;i<nb_masque;i++)
        tab[i]=(int*)malloc(2*sizeof(int));
    i=0;
    while(i<nb_masque){
        x= rand()%TAI;
        y= rand()%TAI;
        fin=0;
        for(j=0;j<tab_ut&& fin==0;j++){
            if(tab[j][0]==x && tab[j][1]==y){
                fin=1;
            }
        }
        if(fin==0){
            masque[x][y]=2;
            tab[tab_ut][0]=x;
            tab[tab_ut][1]=y;
            tab_ut+=1;
            i+=1;
        }
    }
}

void calcIndice(int *l,int **solution, int *i,int *m,int k,int type){

    // si deux fois de suite on regénère la même ligne, on repart de la ligne précédente, et ainsi de suite
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
    #ifdef DEBUG
    printf("\n\n");
    char debug_ligne[30]="",cpt_debug=0;
    #endif

    int i,j,k,l[TAI]={0},m=0,n,o,p,cpt_simili;
    int erreur=0;

    // i et j sont des compteurs.
    // k est une variable qui prend +1 lorsqu'on ajoute un 1 à une ligne, et -1 lorsqu'on ajoute un 0.
    // le but étant d'avoir un k==0 à la fin de la ligne

    // l[] est un tableau comprenant les valeurs pour chaque colonne.
    // même concept que pour le k.
    // après plusieurs essais, si |k| ou |l[]| > 2, il y aura forcément une erreur par la suite.


    for(i=0;i<TAI;i++){ // i descend
        erreur=0;
        for(j=0;j<TAI && !erreur;j++){ // j va vers la droite

            if(j==0){ // au début on met le compteur à 0
                k=0;
                #ifdef DEBUG
                cpt_debug=0;
                #endif
            }
            // dans le cas où en ligne et en colonne on a deux chiffres identiques qui se succèdent
            if((j>=2 && solution[i][j-1]==solution[i][j-2]) && (i>=2 && solution[i-1][j]==solution[i-2][j])){
                // si ce sont les mêmes chiffres, la nouvelle case aura l'inverse
                if(solution[i][j-1]==solution[i-1][j]){
                    solution[i][j]= solution[i-1][j]?0:1;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]='.';
                    cpt_debug+=1;
                    #endif
                }
                else{ // sinon, on recommence la génération de la ligne, vu que c'est un cas impossible à gérer
                    calcIndice(l,solution,&i,&m,k,0);
                    erreur=1;
                }
            }
            else if(j>=2 && solution[i][j-1]==solution[i][j-2]){ // si juste la ligne a deux chiffres identiques
                if(((l[j]==1 || k==2) && solution[i][j-1]==0) || ((l[j]==-1 || k==-2) && solution[i][j-1]==1)){
                    calcIndice(l,solution,&i,&m,k,5);
                    erreur=1;
                }
                else{
                    solution[i][j]= solution[i][j-1]?0:1;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]=',';
                    cpt_debug+=1;
                    #endif
                }
            }
            else if(i>=2 && solution[i-1][j]==solution[i-2][j]){ // si juste la colonne a deux chiffres identiques
                if(((l[j]==2 || k==1) && solution[i-1][j]==0) || ((l[j]==-2 || k==-1) && solution[i-1][j]==1)){
                    calcIndice(l,solution,&i,&m,k,6);
                    erreur=1;
                }
                else{
                    solution[i][j]= solution[i-1][j]?0:1;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]='?';
                    cpt_debug+=1;
                    #endif
                }
            }
            else if((k==2 && l[j]==-2)||(k==-2 && l[j]==2)) { // si on se retrouve avec des valeurs inverses pour k et l[]
                // pas d'autre solution que de regénérer la ligne, avec les mêmes conditions que pour précédement
                calcIndice(l,solution,&i,&m,k,1);
                erreur=1;
            }
            else if(k==2 || l[j]==2) { // cas où on a trop de 1
                if((k==2 && (j!=TAI-1 || l[j]==2)) || (l[j]==2 && (i!=TAI-1 || k==2))){ // si on a un k ou l[] == 2 et qu'on est pas dans une situation inextricable
                    solution[i][j]=0;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]=';';
                    cpt_debug+=1;
                    #endif
                }
                else{
                    // lorsqu'on est arrivé à la dernière ligne ou dernière colonne
                    // il n'y a forcément qu'une solution possible pour cette ligne.
                    // si k ou l[] == 2 dans cette situation, la seule solution est de regénérer la grille
                    calcIndice(l,solution,&i,&m,k,2);
                    erreur=1;
                }
            }
            else if(k==-2 || l[j]==-2) { // cas où on a trop de 0
                if((k==-2 && (j!=TAI-1 || l[j]==-2)) || (l[j]==-2 && (i!=TAI-1 || k==-2))){
                    solution[i][j]=1;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]=':';
                    cpt_debug+=1;
                    #endif
                }
                else{
                    calcIndice(l,solution,&i,&m,k,3);
                    erreur=1;
                }
            }
            else if(j==TAI-1 || i==TAI-1) { // si on est à une fin de ligne ou de colonne
                if((j==TAI-1 && i==TAI-1) && ((k==1 && l[j]==-1) || (k==-1 && l[j]==1))){ // si on est à la toute fin et qu'il faut un 1 pour la ligne et
                    // un 0 pour la colonne, on est coincé, on regénère la ligne.
                    calcIndice(l,solution,&i,&m,k,4);
                    erreur=1;
                }
                else if(j==TAI-1){ // si on n'est qu'à la fin d'une ligne
                    if(k==-1){ // s'il faut un 1
                        solution[i][j]=1;
                        #ifdef DEBUG
                        debug_ligne[cpt_debug]='/';
                        cpt_debug+=1;
                        #endif
                    }
                    else if(k==1){ // s'il faut un 0
                        solution[i][j]=0;
                        #ifdef DEBUG
                        debug_ligne[cpt_debug]='!';
                        cpt_debug+=1;
                        #endif
                    }
                }
                else if(i==TAI-1){ // si on n'est qu'à la fin d'une colonne
                    if(l[j]==-1){ // s'il faut un 1
                        solution[i][j]=1;
                        #ifdef DEBUG
                        debug_ligne[cpt_debug]='*';
                        cpt_debug+=1;
                        #endif
                    }
                    else if(l[j]==1){ // s'il faut un 0
                        solution[i][j]=0;
                        #ifdef DEBUG
                        debug_ligne[cpt_debug]='`';
                        cpt_debug+=1;
                        #endif
                    }
                }
            }
            else{ // si aucune des conditions précédentes n'est rencontrées, on génère un nombre aléatoire
                solution[i][j]=rand()%2;
                #ifdef DEBUG
                debug_ligne[cpt_debug]='^';
                cpt_debug+=1;
                #endif
            }
            #ifdef DEBUG
            if(erreur)
                textcolor(LIGHTRED);
            else
                textcolor(LIGHTGREEN);
            printf("%d",erreur);
            textcolor(LIGHTGREEN);
            #endif
            if(!erreur){
                k=solution[i][j]?k+1:k-1; // on calcule le compteur de 0|1 par ligne
                l[j]=solution[i][j]?l[j]+1:l[j]-1; // on calcule le compteur de 0|1 par colonne
                #ifdef DEBUG
                debug_ligne[cpt_debug]=solution[i][j]+48;
                cpt_debug+=1;
                debug_ligne[cpt_debug]=' ';
                cpt_debug+=1;
                #endif

                if(j==TAI-1) // si on est à la fin de la ligne
                {
                    #ifdef DEBUG
                    gotoxy(1,3+i);
                    printf("%s",debug_ligne);
                    printf("| %d         \n",k);
                    #endif
                    for(n=0;n<i && !erreur;n++) // on teste toutes les lignes à chaque fois
                    {
                        cpt_simili=0;
                        for(o=0;o<TAI;o++) // lignes
                        {
                            if(i>0 && solution[i][o] == solution[n][o]){
                                cpt_simili+=1;
                            }
                        }
                        if(cpt_simili==8){
                            calcIndice(l,solution,&i,&m,k,7);
                            erreur=1;
                        }
                    }
                }
                if((i==TAI-1) && !erreur){
                    // n,o,p
                    for(n=0;n<j && !erreur;n++) // on teste toutes les lignes à chaque fois
                    {
                        cpt_simili=0;
                        for(o=0;o<TAI ;o++) // lignes
                        {
                            if(j>0 && solution[o][j] == solution[o][n]){
                                cpt_simili+=1;
                            }
                        }
                        if(cpt_simili==8){
                            calcIndice(l,solution,&i,&m,k,8);
                            erreur=1;
                        }
                    }
                }

                if(!erreur && (j==TAI-1) && m!=0){
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


coords* estValide(int **grille_jeu,coords *c,int **solution){
    /**
    VIDE,
    ZEROS,
    UNS,
    LIGS,
    COLS,
    TROIS,
    VALIDE,
    CORRECT,
    INCORRECT
    **/
    int i=0,j=0,cpt0=0,cpt1=0;
    int somme1=0,somme2=0,
        fin_cpt_cmp_lignes=0,fin_cpt_cmp_cols=0,
        cpt_lignes_stop=0,cpt_cols_stop=0,
        pow=1;

    if(solution!=NULL){
        if(grille_jeu[c->x][c->y]==solution[c->x][c->y])
            c->etat=CORRECT;
        else
            c->etat=INCORRECT;
    }


    else if(c->etat!=VIDE){
        cpt_lignes_stop=0;
        for(i=0;i<TAI && cpt1<TAI;i++){
            if(grille_jeu[c->x][i]!=2){
                if(grille_jeu[c->x][i])
                    cpt1+=1;
                else
                    cpt0+=1;
                if(i>0 && i<TAI-1 && grille_jeu[c->x][i-1]==grille_jeu[c->x][i] && grille_jeu[c->x][i+1]==grille_jeu[c->x][i])
                    cpt1=TAI;


                somme1+=grille_jeu[c->x][i]*pow;
                pow *=10;
            }
            else{
                cpt_lignes_stop=1;
            }
        }


        pow=1;
        fin_cpt_cmp_lignes=0;
        for(i=0;i<TAI && !fin_cpt_cmp_lignes && !cpt_lignes_stop;i++){

            if(i != c->x){
                somme2=0;
                pow=1;
                for(j=0;j<TAI;j++){
                    somme2+=grille_jeu[i][j]*pow;
                    pow*=10;
                }
                if(somme2==somme1){
                    fin_cpt_cmp_lignes=1;
                }
            }
        }


        if(fin_cpt_cmp_lignes && !cpt_lignes_stop)
            c->etat=LIGS;
        else if(cpt1==TAI)
                c->etat=TROIS;
        else if(cpt0>(TAI/2))
            c->etat=ZEROS;
        else if(cpt1>(TAI/2))
            c->etat=UNS;
        else{
            cpt0=cpt1=0;
            pow=1;
            somme2=somme1=0;
            cpt_cols_stop=0;
            fin_cpt_cmp_cols=0;
            for(i=0;i<TAI && cpt1<TAI;i++){
                if(grille_jeu[i][c->y]!=2){
                    if(grille_jeu[i][c->y])
                        cpt1+=1;
                    else
                        cpt0+=1;
                    if(i>0 && i<TAI-1 && grille_jeu[i-1][c->y]==grille_jeu[i][c->y] && grille_jeu[i+1][c->y]==grille_jeu[i][c->y])
                        cpt1=TAI;
                    somme1+=grille_jeu[c->x][i]*pow;
                    pow *=10;
                }
                else{
                    cpt_cols_stop=1;
                }
            }

            pow=1;
            for(i=0;i<TAI && !fin_cpt_cmp_cols && !cpt_cols_stop;i++){
                if(i != c->x){
                    somme2=0;
                    pow=1;
                    for(j=0;j<TAI;j++){
                        somme2+=grille_jeu[i][j]*pow;
                        pow*=10;
                    }
                    if(somme2==somme1){
                        fin_cpt_cmp_cols=1;
                    }
                }
            }

            if(fin_cpt_cmp_cols && !cpt_cols_stop)
                c->etat=COLS;
            else if(cpt1==TAI)
                c->etat=TROIS;
            else if(cpt0>(TAI/2))
                c->etat=ZEROS;
            else if(cpt1>(TAI/2))
                c->etat=UNS;
            else{
                //gotoxy(20,18);
                //printf("coup correct, cpt=%d,%d",cpt0,cpt1);
                c->etat=VALIDE;
            }
        }
        return addElem(c);
    }
    return c;
}



int checkErreurs(int **grille_jeu,coords *c, int **solution)
{
    int tout_valide=1;
    gotoxy(20,10);
    while(c!=NULL && c->prec!=NULL){
        c=c->prec;
        estValide(grille_jeu, c, solution);
        if(c->etat==VIDE){
            c = removeElem(c);
        }
        else if(c->etat!=VALIDE && c->etat!=CORRECT)
            tout_valide=0;
    }
    return tout_valide;
}

coords* rempliAuto(int **grille_jeu, coords *c)
{
    int i,j;
    int k,l,n;
    int n1=0, n0=0;
    int nl1=0, nl0=0;
    int l1,l2;
    int ligne_compl,ligne_pas_compl;
    int solve=0;
    int x=0, y=0;
    gotoxy(1,20);
    do
    {
        solve=0;
        for(i=0;i<TAI;i++){
            for(j=0;j<TAI;j++){
                //c->x=i;
                //c->y=j;
                n1=0;
                n0=0;
                nl1=0;
                nl0=0;
                n=0;
                if(grille_jeu[i][j]==2){

                    if(j>=0 && j<TAI-2 && solve==0){ /**lorsque l'on a deux 0 ou deux 1 a la suite devant**/
                        if(grille_jeu[i][j+1]==0 && grille_jeu[i][j+2]==0){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=1;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("Il y a deux zéros devant.                               ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                        else if(grille_jeu[i][j+1]==1 && grille_jeu[i][j+2]==1 && solve==0){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=0;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("Il y a deux uns devant.                                   ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                    }
                    if(j>1 && solve==0){ /**lorsque l'on a deux 0 ou deux 1 a la suite derriere**/
                        if(grille_jeu[i][j-2]==0 && grille_jeu[i][j-1]==0 ){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=1;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("Il y a deux zeros derriere.                           ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                        else if(grille_jeu[i][j-2]==1 && grille_jeu[i][j-1]==1){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=0;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("Il y a deux uns derriere.                                  ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                    }
                    if(i>=0 && i<TAI-2 && solve==0){ /**alignés sur la même colonne**/
                        if(grille_jeu[i+1][j]==0 && grille_jeu[i+2][j]==0){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=1;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("Il y a deux zeros alignes sur la meme colonne.       ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                        else if(grille_jeu[i+1][j]==1 && grille_jeu[i+2][j]==1){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=0;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("Il y a deux uns alignes devant sur la meme colonne.   ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                    }
                    if(i>1 && solve==0){ /**Si deux zéros ou deux uns se suivent **/
                        if(grille_jeu[i-2][j]==0 && grille_jeu[i-1][j]==0){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=1;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("Il y a deux zeros alignes sur la meme colonne .         ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                        else if(grille_jeu[i-2][j]==1 && grille_jeu[i-1][j]==1){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=0;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("Il y a deux uns alignes sur la meme colonne.          ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                    }
                    if(j>0 && j<TAI && solve==0){ /**Sur la ligne, la case est entouré par deux zéros ou deux uns **/
                        if(grille_jeu[i][j-1]==0 && grille_jeu[i][j+1]==0){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=1;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("La case est entouree par deux zeros sur la ligne.        ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                        else if(grille_jeu[i][j-1]==1 && grille_jeu[i][j+1]==1){
                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=0;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("La case est entoures par deux uns sur la ligne.           ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                    }
                    if(i>0 && i<TAI-1 && solve==0){/** sur la colonne, la case est entouré par deux zéros ou deux uns **/
                        if(grille_jeu[i-1][j]==0 && grille_jeu[i+1][j]==0){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=1;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("La case est entoures par deux zeros sur la colonne.        ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                        else if(grille_jeu[i-1][j]==1 && grille_jeu[i+1][j]==1){

                            initElem(i,j,TROIS,c,c->prec,c->suiv);
                            c = addElem(c);
                            grille_jeu[i][j]=0;
                            solve=1;
                            gotoxy(1,19);
                            textcolor(GREEN);
                            printf("La case est entoures par deux uns sur la colonne.              ");
                            //affgrile(grille_jeu);
                            Sleep(500);
                            textcolor(WHITE);
                        }
                    }
                    /** Calcul du nombre de 1 et de 0 par lignes **/
                    for(k=0;k<TAI;k++){
                        if(grille_jeu[k][j]==0)
                            n0+=1;
                        else if(grille_jeu[k][j]==1)
                            n1+=1;
                    }
                    if(grille_jeu[i][j]==2 && n0==4 && solve==0){/** Si il y a 3 uns sur la même ligne **/

                        initElem(i,j,ZEROS,c,c->prec,c->suiv);
                        c = addElem(c);
                        grille_jeu[i][j]=1;
                        solve=1;
                        gotoxy(1,19);
                        textcolor(GREEN);
                        printf("La ligne contient quatre zero, la case doit etre un 1.             ");
                        //affgrile(grille_jeu);
                        Sleep(500);
                        textcolor(WHITE);
                    }
                    else if(grille_jeu[i][j]==2 && n1==4 && solve==0){/** Si il y a 3 zéros sur la même ligne **/
                        initElem(i,j,UNS,c,c->prec,c->suiv);
                        c = addElem(c);
                        grille_jeu[i][j]=0;
                        solve=1;
                        gotoxy(1,19);
                        textcolor(GREEN);
                        printf("La ligne contient quatre un, la case doit etre un 0.             ");
                        //affgrile(grille_jeu);
                        Sleep(500);
                        textcolor(WHITE);
                    }

                    /** Calcul du nombre de 1 et de 0 par colonnes **/
                    for(l=0;l<TAI;l++){
                        if(grille_jeu[i][l]==0)
                            nl0+=1;
                        else if(grille_jeu[i][l]==1)
                            nl1+=1;
                    }
                    if(grille_jeu[i][j]==2 && nl1==4 && solve==0){/** Si il y a 3 zéros sur la même colonne **/

                        initElem(i,j,UNS,c,c->prec,c->suiv);
                        c = addElem(c);
                        grille_jeu[i][j]=0;
                        solve=1;
                        gotoxy(1,19);
                        textcolor(GREEN);
                        printf("La colonne contient quatre un, la case doit etre zero.             ");
                        //affgrile(grille_jeu);
                        Sleep(500);
                        textcolor(WHITE);
                    }
                    else if(grille_jeu[i][j]==2 && nl0==4 && solve==0){/** Si il y a 3 uns sur la même colonne **/

                        initElem(i,j,ZEROS,c,c->prec,c->suiv);
                        c = addElem(c);
                        grille_jeu[i][j]=1;
                        solve=1;
                        gotoxy(1,19);
                        textcolor(GREEN);
                        printf("La ligne contient quatre zero, la case doit etre un.                  ");
                        //affgrile(grille_jeu);
                        Sleep(500);
                        textcolor(WHITE);
                    }
                }
            }


        }
        x++;
        y++;
    }while(grille_jeu[x][y]==2);
    return c;
}

