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
            if(tab[i][j]==0)
                printf("0 ");
            else
                printf("1 ");
        }
    }
}

void calcJeu(int **tab)
{
    srand((unsigned)time(NULL));
    int i,j,k;
    for(i=0;i<TAI;i++){
        for(j=0;j<TAI;j++){
            if(j==0)
                k=0;
            if(j>=2 && tab[i][j-1]==tab[i][j-2])
            {
                tab[i][j]= tab[i][j-1]?0:1;
            }
            else{
                tab[i][j]=rand()%2;
            }
            k=tab[i][j]?k+1:k-1;
            if(j==TAI-1)
            {
                if(k!=0){
                    tab[i][j] = tab[i][j]?0:1;
                    k=tab[i][j]?k+1:k-1;
                }
                if((tab[i][j-1]==tab[i][j-2] && tab[i][j]==tab[i][j-1]) || k!=0)
                    printf("%d %d %d %d %d %d %d %d - %d\n\n",tab[i][0],tab[i][1],tab[i][2],tab[i][3],tab[i][4],tab[i][5],tab[i][6],tab[i][7],k);
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

int main()
{
    int **tab;
    int i;
    tab =(int*) malloc(TAI*sizeof(int*));

    for(i=0;i<TAI;i++){
        tab[i] = malloc(TAI*sizeof(int));
    }

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
