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

void genMasque(int **masque,int **solution){
    /// on initialise la fonction de generation de nombres aleatoires
    srand((unsigned)time(NULL));
    int nb_masque= TAI*TAI-2.5*TAI-6; /// on définit le nombre de cases affichées par le masque
    int **tab, /// tableau qui contient les coordonnées des points affichés, pour vérifier qu'on
    /// entre pas deux fois les mêmes coordonnées
    **grille_jeu = creeTab();
    int tab_ut=0, /// taille utile de tab
        i=0,j=0,
        x,y,
        fin=0,
        remplie=0;

    coords *c_prec, /// coordonnée précédente, pour les comparaisons
     *c;

    tab = (int**)malloc(sizeof(int*)*nb_masque);
    for(i=0;i<nb_masque;i++) /// on alloue de la mémoire à notre tableau
        tab[i]=(int*)malloc(2*sizeof(int));


    while(!remplie){ /// tant que rempliAuto n'est pas capable de résoudre la grille seul
        for(i=0;i<TAI;i++){ /// on met le masque et la grille à zéro
            for(j=0;j<TAI;j++){
                masque[i][j]=0;
                grille_jeu[i][j]=0;
            }
        }
        delList(c); /// on supprime une éventuelle ancienne liste chainée
        c = (coords*) malloc(sizeof(coords)); /// on recrée un élément de liste
        initElem(1,1,VIDE,NULL,c,NULL,NULL); /// initialisation
        tab_ut=0;
        i=0;
        while(i<nb_masque){ /// tant qu'on a pas le bon nombre de cases pour le masque
            x= rand()%TAI;
            y= rand()%TAI;
            fin=0;
            for(j=0;j<tab_ut && fin==0;j++){ /// on vérifie qu'on a pas déjà entré les coordonnées
                if(tab[j][0]==x && tab[j][1]==y){
                    fin=1;
                }
            }
            if(fin==0){ /// si ce sont des nouvelles coordonnées, on les entre
                masque[x][y]=2;
                tab[tab_ut][0]=x;
                tab[tab_ut][1]=y;
                tab_ut+=1;
                i+=1; /// et on incrémente le nombre de cases remplies de 1.
            }
        }
        /// on remplit grille_jeu avec les données collectées
        initgrille_jeu(grille_jeu,solution,masque);
        do{ /// on vérifie que rempliAuto est capable de finir la grille, sinon on recommence.
            c_prec=c;
            c = rempliAuto(grille_jeu,c);
            remplie = estRemplie(grille_jeu);
        }while(!remplie && c_prec!=c);
    }
    supprTab(grille_jeu); /// on rend la mémoire
    delList(c);
}

int estRemplie(int **grille_jeu){
    int i,j,oui=1;
    for(i=0;i<TAI && oui;i++){
        for(j=0;j<TAI && oui;j++){
            if(grille_jeu[i][j]==2)
                oui=0;
        }
    }
    return oui;
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

    int i,j,k=0,l[TAI]={0},m=0,n,o,cpt_simili, err_fin_tableau=0;
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
            if(err_fin_tableau && i==TAI-1){
                m=3;
                calcIndice(l,solution,&i,&m,k,9);
                erreur=1;
                err_fin_tableau=0;
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
                            err_fin_tableau=1;
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


void estValide(int **grille_jeu,coords *c,int **solution){
    int i=0,j=0,cpt0=0,cpt1=0;
    int somme1=0,somme2=0, /// pour comparer les lignes et les colonnes
        fin_cpt_cmp_lignes=0,fin_cpt_cmp_cols=0, /// booléains de fin de boucles
        cpt_lignes_stop=0,cpt_cols_stop=0, /// booleains de fin de boucles
        pow=1; //// variable "puissance de 10"

    if(solution!=NULL){ /// si on a décidé de vérifier la correspondance avec la solution
        if(grille_jeu[c->x][c->y]==solution[c->x][c->y])
            c->etat=CORRECT;
        else
            c->etat=INCORRECT;
    }
    else if(c->etat!=VIDE){ /// cas général
        cpt_lignes_stop=0;
        for(i=0;i<TAI && cpt1<TAI;i++){ /// on vérifie qu'il n'y a pas trop de 0 ou de 1 dans une ligne
            if(grille_jeu[c->x][i]!=2){
                if(grille_jeu[c->x][i])
                    cpt1+=1;
                else
                    cpt0+=1;
                if(i>0 && i<TAI-1 && grille_jeu[c->x][i-1]==grille_jeu[c->x][i] && grille_jeu[c->x][i+1]==grille_jeu[c->x][i])
                    cpt1=TAI; /// s'il y a 3 1 ou 0 successifs


                somme1+=grille_jeu[c->x][i]*pow; /// on calcule la somme binaire de la ligne c->x
                pow *=10;
            }
            else{
                cpt_lignes_stop=1; /// s'il y a une case qui n'est pas remplie dans la ligne, on le signake
            }
        }


        pow=1; // on réinitialise
        fin_cpt_cmp_lignes=0;
        for(i=0;i<TAI && !fin_cpt_cmp_lignes && !cpt_lignes_stop;i++){

            if(i != c->x){ /// si on n'est pas à la ligne corespondant à somme1
                somme2=0;
                pow=1;
                for(j=0;j<TAI;j++){
                    somme2+=grille_jeu[i][j]*pow;
                    pow*=10;
                }
                if(somme2==somme1){
                    fin_cpt_cmp_lignes=1; /// si les lignes sont identiques, on le signale
                }
            }
        }


        if(fin_cpt_cmp_lignes && !cpt_lignes_stop) /// indication des problèmes rencontrés, pour les afficher plus tard
            c->etat=LIGS;
        else if(cpt1==TAI)
                c->etat=TROIS;
        else if(cpt0>(TAI/2))
            c->etat=ZEROS;
        else if(cpt1>(TAI/2))
            c->etat=UNS;
        else{

            /// même chose que précédement, pour les colonnes.
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
            else
                c->etat=VALIDE;
        }
    }
}


int checkErreurs(int **grille_jeu,coords *c, int **solution){
    int tout_valide=1;
    if(c!=NULL)
        estValide(grille_jeu, c, solution); /// on véfifie l'etat du point
    while(c!=NULL && c->prec!=NULL){ /// tant qu'on a pas atteint le dernier element
        c=c->prec; /// on passe au suivant.

            estValide(grille_jeu, c, solution); /// on véfifie l'etat du point

        if(c->etat==VIDE){ /// s'il est vide on le supprime
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
    int k,l;
    int n1, n0;
    int nl1, nl0;
    int solve;
    int x=0, y=0;

    solve=0;
    for(i=0;i<TAI;i++){
        for(j=0;j<TAI;j++){
            n1=0;
            n0=0;
            nl1=0;
            nl0=0;
            if(grille_jeu[i][j]==2){
                if(i>7 || j>7)
                    printf("grille_jeu[%d][%d]\n",i,j);
                if(j>=0 && j<TAI-2 && solve==0){ /**lorsque l'on a deux 0 ou deux 1 a la suite devant**/
                    if(grille_jeu[i][j+1]==0 && grille_jeu[i][j+2]==0){
                        initElem(i,j,TROIS,1,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=1;

                    }
                    else if(grille_jeu[i][j+1]==1 && grille_jeu[i][j+2]==1 && solve==0){
                        initElem(i,j,TROIS,2,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=0;
                    }
                }
                if(j>1 && solve==0){ /**lorsque l'on a deux 0 ou deux 1 a la suite derriere**/
                    if(grille_jeu[i][j-2]==0 && grille_jeu[i][j-1]==0 ){
                        initElem(i,j,TROIS,3,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=1;

                    }
                    else if(grille_jeu[i][j-2]==1 && grille_jeu[i][j-1]==1){
                        initElem(i,j,TROIS,4,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=0;
                    }
                }
                if(i>=0 && i<TAI-2 && solve==0){ /**alignés sur la même colonne**/
                    if(grille_jeu[i+1][j]==0 && grille_jeu[i+2][j]==0){
                        initElem(i,j,TROIS,5,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=1;

                    }
                    else if(grille_jeu[i+1][j]==1 && grille_jeu[i+2][j]==1){
                        initElem(i,j,TROIS,6,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=0;

                    }
                }
                if(i>1 && solve==0){ /**Si deux zéros ou deux uns se suivent **/
                    if(grille_jeu[i-2][j]==0 && grille_jeu[i-1][j]==0){
                        initElem(i,j,TROIS,7,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=1;

                    }
                    else if(grille_jeu[i-2][j]==1 && grille_jeu[i-1][j]==1){
                        initElem(i,j,TROIS,6,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=0;
                    }
                }
                if(j>0 && j<TAI-1 && solve==0){ /**Sur la ligne, la case est entouré par deux zéros ou deux uns **/
                    if(grille_jeu[i][j-1]==0 && grille_jeu[i][j+1]==0){
                        initElem(i,j,TROIS,8,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=1;

                    }
                    else if(grille_jeu[i][j-1]==1 && grille_jeu[i][j+1]==1){
                        initElem(i,j,TROIS,9,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=0;
                    }
                }
                if(i!=0 && (i<(TAI-1)) && (solve==0)) {/** sur la colonne, la case est entouré par deux zéros ou deux uns **/
                    if(grille_jeu[i-1][j]==0 && grille_jeu[i+1][j]==0){
                        initElem(i,j,TROIS,10,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=1;

                    }
                    else if(grille_jeu[i-1][j]==1 && grille_jeu[i+1][j]==1){
                        initElem(i,j,TROIS,11,c,c->prec,c->suiv);
                        solve=1;
                        c = addElem(c);
                        grille_jeu[i][j]=0;

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
                    initElem(i,j,TROIS,12,c,c->prec,c->suiv);
                    solve=1;
                    c = addElem(c);
                    grille_jeu[i][j]=1;

                }
                else if(grille_jeu[i][j]==2 && n1==4 && solve==0){/** Si il y a 3 zéros sur la même ligne **/
                    initElem(i,j,UNS,13,c,c->prec,c->suiv);
                    solve=1;
                    c = addElem(c);
                    grille_jeu[i][j]=0;
                }

                /** Calcul du nombre de 1 et de 0 par colonnes **/
                for(l=0;l<TAI;l++){
                    if(grille_jeu[i][l]==0)
                        nl0+=1;
                    else if(grille_jeu[i][l]==1)
                        nl1+=1;
                }
                if(grille_jeu[i][j]==2 && nl1==4 && solve==0){/** Si il y a 3 zéros sur la même colonne **/
                    initElem(i,j,UNS,14,c,c->prec,c->suiv);
                    solve=1;
                    c = addElem(c);
                    grille_jeu[i][j]=0;

                }
                else if(grille_jeu[i][j]==2 && nl0==4 && solve==0){/** Si il y a 3 uns sur la même colonne **/
                    initElem(i,j,TROIS,15,c,c->prec,c->suiv);
                    solve=1;
                    c = addElem(c);
                    grille_jeu[i][j]=1;
                }
            }
        }
    }
    return c;
}

