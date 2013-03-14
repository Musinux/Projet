#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAI 8

//#define DEBUG 8


void affJeu(int **tab)
{
    int i,j;
    printf("\n\n");
    for(i=0;i<TAI;i++)
    {
        printf("\n");
        for(j=0;j<TAI;j++)
        {
            printf("%d ",tab[i][j]);
        }
    }
}

void calcIndice(int *l,int **tab, int *i,int *m,int k,int type){

    // et si deux fois de suite on regénère la même ligne, on repart de la ligne précédente, et ainsi de suite
    int o,p;
    *m+=1;
    *i=(*i-*m>=0)?*i-*m:0;
    /*
    #ifdef DEBUG
    printf("FAIL %d | %d",*m,type);


    for(o=0;o<TAI;o++){
        if(l[o]>=0)
            printf(" %d ",l[o]);
        else
            printf("%d ",l[o]);
    }
    printf("\n");
    #endif
    */
    for(p=0;p<TAI;p++)
        l[p]=0;
    for(o=0;o<=*i;o++){
        for(p=0;p<TAI;p++)
            l[p]=tab[o][p]?l[p]+1:l[p]-1;
    }


    #ifdef DEBUG
    printf("---\n");
    #endif
    /*
    printf("%d %d %d %d %d %d %d %d | %d\n",tab[*i][0],tab[*i][1],tab[*i][2],tab[*i][3],tab[*i][4],tab[*i][5],tab[*i][6],tab[*i][7],k);
    for(o=0;o<TAI;o++){
        if(l[o]>=0)
            printf(" %d ",l[o]);
        else
            printf("%d ",l[o]);
    }
    printf("\n\n");
    #endif
    */
}


void genGrille(int **tab)
{
    srand((unsigned)time(NULL));
    #ifdef DEBUG
    printf("\n\n");
    char debug_ligne[30]="",cpt_debug=0;
    #endif

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
                #ifdef DEBUG
                cpt_debug=0;
                #endif
            }
            // dans le cas où en ligne et en colonne on a deux chiffres identiques qui se succèdent
            if((j>=2 && tab[i][j-1]==tab[i][j-2]) && (i>=2 && tab[i-1][j]==tab[i-2][j])){
                // si ce sont les mêmes chiffres, la nouvelle case aura l'inverse
                if(tab[i][j-1]==tab[i-1][j]){
                    tab[i][j]= tab[i-1][j]?0:1;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]='.';
                    cpt_debug+=1;
                    #endif
                }
                else{ // sinon, on recommence la génération de la ligne, vu que c'est un cas impossible à gérer
                    calcIndice(l,tab,&i,&m,k,0);
                    break;
                }
            }
            else if(j>=2 && tab[i][j-1]==tab[i][j-2]){ // si juste la ligne a deux chiffres identiques
                if(((l[j]==1 || k==2) && tab[i][j-1]==0) || ((l[j]==-1 || k==-2) && tab[i][j-1]==1)){
                    calcIndice(l,tab,&i,&m,k,5);
                    break;
                }
                else{
                    tab[i][j]= tab[i][j-1]?0:1;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]=',';
                    cpt_debug+=1;
                    #endif
                }
            }
            else if(i>=2 && tab[i-1][j]==tab[i-2][j]){ // si juste la colonne a deux chiffres identiques
                if(((l[j]==2 || k==1) && tab[i-1][j]==0) || ((l[j]==-2 || k==-1) && tab[i-1][j]==1)){
                    calcIndice(l,tab,&i,&m,k,6);
                    break;
                }
                else{
                    tab[i][j]= tab[i-1][j]?0:1;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]='?';
                    cpt_debug+=1;
                    #endif
                }
            }
            else if((k==2 && l[j]==-2)||(k==-2 && l[j]==2))  { // si on se retrouve avec des valeurs inverses pour k et l[]
                // pas d'autre solution que de regénérer la ligne, avec les mêmes conditions que pour précédement
                calcIndice(l,tab,&i,&m,k,1);
                break;
            }
            else if(k==2 || l[j]==2) { // cas où on a trop de 1
                if((k==2 && (j!=TAI-1 || l[j]==2)) || (l[j]==2 && (i!=TAI-1 || k==2))){ // si on a un k ou l[] == 2 et qu'on est pas dans une situation inextricable
                    tab[i][j]=0;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]=';';
                    cpt_debug+=1;
                    #endif
                }
                else{
                    // lorsqu'on est arrivé à la dernière ligne ou dernière colonne
                    // il n'y a forcément qu'une solution possible pour cette ligne.
                    // si k ou l[] == 2 dans cette situation, la seule solution est de regénérer la grille
                    calcIndice(l,tab,&i,&m,k,2);
                    break;
                }
            }
            else if(k==-2 || l[j]==-2) { // cas où on a trop de 0
                if((k==-2 && (j!=TAI-1 || l[j]==-2)) || (l[j]==-2 && (i!=TAI-1 || k==-2))){
                    tab[i][j]=1;
                    #ifdef DEBUG
                    debug_ligne[cpt_debug]=':';
                    cpt_debug+=1;
                    #endif
                }
                else{
                    calcIndice(l,tab,&i,&m,k,3);
                    break;
                }
            }
            else if(j==TAI-1 || i==TAI-1) { // si on est à une fin de ligne ou de colonne
                if((j==TAI-1 && i==TAI-1) && ((k==1 && l[j]==-1) || (k==-1 && l[j]==1))){ // si on est à la toute fin et qu'il faut un 1 pour la ligne et
                    // un 0 pour la colonne, on est coincé, on regénère la ligne.
                    calcIndice(l,tab,&i,&m,k,4);
                    break;
                }
                else if(j==TAI-1){ // si on n'est qu'à la fin d'une ligne
                    if(k==-1){ // s'il faut un 1
                        tab[i][j]=1;
                        #ifdef DEBUG
                        debug_ligne[cpt_debug]='/';
                        cpt_debug+=1;
                        #endif
                    }
                    else if(k==1){ // s'il faut un 0
                        tab[i][j]=0;
                        #ifdef DEBUG
                        debug_ligne[cpt_debug]='!';
                        cpt_debug+=1;
                        #endif
                    }
                }
                else if(i==TAI-1){ // si on n'est qu'à la fin d'une colonne
                    if(l[j]==-1){ // s'il faut un 1
                        tab[i][j]=1;
                        #ifdef DEBUG
                        debug_ligne[cpt_debug]='*';
                        cpt_debug+=1;
                        #endif
                    }
                    else if(l[j]==1){ // s'il faut un 0
                        tab[i][j]=0;
                        #ifdef DEBUG
                        debug_ligne[cpt_debug]='`';
                        cpt_debug+=1;
                        #endif
                    }
                }
            }
            else{  // si aucune des conditions précédentes n'est rencontrées, on génère un nombre aléatoire
                tab[i][j]=rand()%2;
                #ifdef DEBUG
                debug_ligne[cpt_debug]='&';
                cpt_debug+=1;
                #endif
            }
            k=tab[i][j]?k+1:k-1; // on calcule le compteur de 0|1 par ligne
            l[j]=tab[i][j]?l[j]+1:l[j]-1; // on calcule le compteur de 0|1 par colonne
            #ifdef DEBUG
            debug_ligne[cpt_debug]=tab[i][j]+48;
            cpt_debug+=1;
            debug_ligne[cpt_debug]=' ';
            cpt_debug+=1;
            #endif
            if(j==TAI-1) // si on est à la fin de la ligne
            {
                #ifdef DEBUG
                printf("%s",debug_ligne);
                printf("| %d\n",k);
                #endif
                int cpt_simili=0;
                for(n=0;n<i;n++) // on teste toutes les lignes à chaque fois
                {
                    cpt_simili=0;
                    for(o=0;o<TAI;o++) // lignes
                    {
                        if(i>0  && tab[i][o] == tab[n][o]){
                            cpt_simili+=1;
                        }
                    }
                    if(cpt_simili==8){
                        calcIndice(l,tab,&i,&m,k,7);
                        n=i+1;
                    }
                }
                if(n=i+1)
                    break;


                #ifdef DEBUG


                int o;
                for(o=0;o<TAI;o++){
                    if(l[o]>=0)
                        printf(" %d ",l[o]);
                    else
                        printf("%d ",l[o]);
                }
                printf("\n");

                printf("%d %d %d %d %d %d %d %d | %d\n",tab[i][0],tab[i][1],tab[i][2],tab[i][3],tab[i][4],tab[i][5],tab[i][6],tab[i][7],k);
                #endif
                if(i==TAI-1){
                    // n,o,p
                    cpt_simili=0;
                    for(n=0;n<j;n++) // on teste toutes les lignes à chaque fois
                    {
                        for(o=0;o<TAI;o++) // lignes
                        {
                            if(i>0  && tab[o][j] == tab[o][n]){
                                cpt_simili+=1;
                            }
                        }
                        if(cpt_simili==8){
                            calcIndice(l,tab,&i,&m,k,8);
                            n=j+1;
                        }
                    }
                    if(n=j+1)
                        break;
                    #ifdef DEBUG
                    printf("_ _ _ _ _ _ _ _\n");
                    printf("%d %d %d %d %d %d %d %d \n\n",l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7]);
                    #endif
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
        fgetc(fgrille);

    for(i=0;i<TAI;i++){
        for(j=0;j<TAI;j++)
        {
            if(j==0&&i!=0)
                fgetc(fgrille);
            grille[i][j] = (int)fgetc(fgrille)-48;
        }
    }
    fclose(fgrille);
}

int** creeTab(){
    int **tab,i;
    tab =(int*) malloc(TAI*sizeof(int*));

    for(i=0;i<TAI;i++){
        tab[i] = malloc(TAI*sizeof(int));
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

int verifGrille(int **tab){
    int i,j,cpt=0,k,l[TAI]={0},cpt_simili_col[TAI]={0},cpt_simili_lig=0;
/*
    for(i=0;i<TAI;i++){
        cpt_simili_lig=0;
        for(j=0;j<TAI;j++){
            if((j!=0) && (tab[i][j]!=tab[i][j-1])){
                cpt_simili_lig+=1;
            }
            if(i!=0){
                if(tab[i][j]==tab[i-1][j])
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
            cpt = tab[i][j]?cpt+1:cpt-1;
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
                if((j>=2 && tab[i][j-1]==tab[i][j-2]) && (i>=2 && tab[i-1][j]==tab[i-2][j])){
                    // si ce sont les mêmes chiffres, la nouvelle case aura l'inverse
                    if(tab[i][j-1]!=tab[i-1][j]){
                        return -90;
                    }
                }
                else if(j>=2 && tab[i][j-1]==tab[i][j-2]){ // si juste la colonne a deux chiffres identiques
                    if((k==1 && tab[i][j-1]==0) || (k==-1 && tab[i][j-1]==1) || (tab[i][j]==tab[i][j-1])){

                        return -80;
                    }
                }
                else if(i>=2 && tab[i-1][j]==tab[i-2][j]){ // si juste la ligne a deux chiffres identiques
                    if((l[j]==1 && tab[i-1][j]==0) || (l[j]==-1 && tab[i-1][j]==1) || (tab[i][j]==tab[i-1][j])){
                        return -70;
                    }
                }
                else if((k==2 && l[j]==-2)||(k==-2 && l[j]==2))  { // si on se retrouve avec des valeurs inverses pour k et l[]
                    return -60;
                }
                else if(k==2 || l[j]==2) { // cas où on a trop de 1
                    if(((k==2 && (j!=TAI-1 || l[j]==2)) || (l[j]==2 && (i!=TAI-1 || k==2))) && tab[i][j]!=0){ // si on a un k ou l[] == 2 et qu'on est pas dans une situation inextricable
                        return -50;
                    }
                }
                else if(k==-2 || l[j]==-2) { // cas où on a trop de 0
                    if(((k==-2 && (j!=TAI-1 || l[j]==-2)) || (l[j]==-2 && (i!=TAI-1 || k==-2))) && tab[i][j]!=1){
                        printf("\n\ni:%d   \nj:%d   \ntab[%d][%d]:%d   \ntab[%d][%d]:%d  \ntab[%d][%d]:%d  \nk:%d  \nl[%d]:%d",i,j,i,j,tab[i][j],i,j-1,tab[i][j-1],i,j-2,tab[i][j-2],k,j,l[j]);
                        return -40;
                    }
                }
                else if(j==TAI-1 || i==TAI-1) { // si on est à une fin de ligne ou de colonne
                    if(((j==i && i==TAI-1) && ((k==1 && l[j]==-1) || (k==-1 && l[j]==1))) || (j==TAI-1 && ((k==-1 && tab[i][j]==0)|| (k==1 && tab[i][j]==1))) || (i==TAI-1 && ((l[j]==-1 && tab[i][j]==0)|| (l[j]==1 && tab[i][j]==1))) ){ // si on est à la toute fin et qu'il faut un 1 pour la ligne et
                        return -30;
                    }
                }
                k=tab[i][j]?k+1:k-1; // on calcule le compteur de 0|1 par ligne
                l[j]=tab[i][j]?l[j]+1:l[j]-1; // on calcule le compteur de 0|1 par colonne
            }
        }
    }
    return 1;
}

int main()

{
    srand((unsigned)time(NULL));
    int **tab,alea;
    int i,j=1;
    alea = rand()%4;
    tab = creeTab();
    //genGrille(tab);
    choixGrille(tab,alea);
    affJeu(tab);
    printf("\n\n%d",verifGrille(tab));

    printf("\n");

    supprTab(tab);

    return 0;
}
