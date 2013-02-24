#include <stdio.h>
#include <stdlib.h>
#define TAILLE 8

void affJeu(int **tab){
    int i,j;
    for(i=0;i<TAILLE;i++)
    {
        printf("\n");
        for(j=0;j<TAILLE;j++)
        {
            if(tab[i][j]==0)
                printf("0 ");
            else
                printf("1 ");
        }
    }
}

void calcJeu(int **tab){
    srand((unsigned)time(NULL));
    int i,j,k;
    for(i=0;i<TAILLE;i++){
        for(j=0;j<TAILLE;j++){

            if(j>=2 && tab[i][j-1]==tab[i][j-2])
            {
                tab[i][j]= tab[i][j-1]?0:1;
            }
            else{
                tab[i][j]=rand()%2;
            }
            if(j==TAILLE-1)
            {
                k=tab[i][j]?k+1:k-1;
                if(k!=0)
                    tab[i][j] = (tab[i][j])?0:1;
            }
        }
    }
}

int main()
{
    int **tab;
    int i;
    tab =(int*) malloc(TAILLE*sizeof(int*));

    for(i=0;i<TAILLE;i++){
        tab[i] = malloc(TAILLE*sizeof(int));
    }

    calcJeu(tab);
    affJeu(tab);
    return 0;
}
