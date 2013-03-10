#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAI 8

void affJeu(int **tab)
{
    int i,j;
    for(i=0;i<TAI;i++)
    {
        printf("\n");
        for(j=0;j<TAI;j++)
        {
            printf("%d ",tab[i][j]);
        }
    }
}

void calcJeu(int **tab)
{
    srand((unsigned)time(NULL));
    printf("\n\n");
    int i,j,k,l[TAI]={0},m=0,n;
    for(i=0;i<TAI;i++){

        for(j=0;j<TAI;j++){
            if(j==0)
                k=0;
            if((j>=2 && tab[i][j-1]==tab[i][j-2]) && (i>=2 && tab[i-1][j]==tab[i-2][j])){
                if(tab[i][j-1]==tab[i-1][j]){
                    tab[i][j]= tab[i][j-1]?0:1;
                }
                else{
                    m+=1;
                    i-=m;
                    printf("FAIL %d\n",m);
                    for(n=0;n<m;n++)
                        l[j-n]=0;
                    break;
                }
            }
            else if(j>=2 && tab[i][j-1]==tab[i][j-2]){
                tab[i][j]= tab[i][j-1]?0:1;
            }
            else if(i>=2 && tab[i-1][j]==tab[i-2][j]){
                tab[i][j]= tab[i-1][j]?0:1;
            }
            else if((k==2 && l[j]==-2)||(k==-2 && l[j]==2))  {
                m+=1;
                i-=m;
                printf("FAIL. %d\n",m);
                for(n=0;n<m;n++)
                    l[j-n]=0;
                break;
            }
            else if(k==2 || l[j]==2) {
                if((k==2 && (j!=TAI-1 || l[j]==2)) || (l[j]==2 && (i!=TAI-1 || k==2)))
                    tab[i][j]=0;
                else{
                    m+=1;
                    i-=m;
                    printf("FAIL; %d\n",m);
                    for(n=0;n<m;n++)
                        l[j-n]=0;
                    break;
                }
            }
            else if(k==-2 || l[j]==-2) {
                if((k==-2 && (j!=TAI-1 || l[j]==-2)) || (l[j]==-2 && (i!=TAI-1 || k==-2)))
                    tab[i][j]=1;
                else{
                    m+=1;
                    i-=m;
                    printf("FAIL_ %d\n",m);
                    for(n=0;n<m;n++)
                        l[j-n]=0;
                    break;
                }
            }
            else if(j==TAI-1 || i==TAI-1) {
                if((j==TAI-1 && i==TAI-1) && ((k==1 && l[j]==-1) || (k==-1 && l[j]==1))){
                    m+=1;
                    i-=m;
                    printf("FAIL, %d\n",m);
                    for(n=0;n<m;n++)
                        l[j-n]=0;
                    break;
                }
                else if(j==TAI-1){
                    if(k==-1)
                        tab[i][j]=1;
                    else if(k==1)
                        tab[i][j]=0;
                }
                else if(i==TAI-1){
                    if(l[j]==-1)
                        tab[i][j]=1;
                    else if(l[j]==1)
                        tab[i][j]=0;
                }
            }
            else{
                tab[i][j]=rand()%2;
            }
            k=tab[i][j]?k+1:k-1;
            l[j]=tab[i][j]?l[j]+1:l[j]-1;
            if(j==TAI-1)
            {
                m=0;
                if(k==-2){
                    tab[i][j] = 1;
                    k+=2;
                    l[j]+=2;
                }
                else if(k==2){
                    tab[i][j] = 0;
                    k-=2;
                    l[j]+=2;
                }
                printf("%d %d %d %d %d %d %d %d | %d\n",tab[i][0],tab[i][1],tab[i][2],tab[i][3],tab[i][4],tab[i][5],tab[i][6],tab[i][7],k);
                if(i==TAI-1){
                    printf("_ _ _ _ _ _ _ _\n");
                    printf("%d %d %d %d %d %d %d %d \n\n",l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7]);
                }
            }
        }

    }
}

void grille(int **grille){
    srand((unsigned)time(NULL));
    int i,j,alea;
    FILE *fgrille= fopen("grilles.txt","r");
    alea = rand()%4;
    switch(alea)
    {
        case 1:
            for(i=0;i<73;i++)
                fgetc(fgrille);
            break;
        case 2:
            for(i=0;i<146;i++)
                fgetc(fgrille);
            break;
        case 3:
            for(i=0;i<219;i++)
                fgetc(fgrille);
            break;
    }
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

int main()
{
    int **tab;
    int i;
    tab = creeTab();

    calcJeu(tab);
    affJeu(tab);

    //printf("\n\n");
    //grille(tab);
    //affJeu(tab);

    printf("\n\n\n %");
    for(i=0;i<TAI;i++){
        free(tab[i]);
    }
    free(tab);
    return 0;
}
