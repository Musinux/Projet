#include <stdio.h>
#include <stdlib.h>
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

            if(j>=2 && tab[i][j-1]==tab[i][j-2])
            {
                tab[i][j]= tab[i][j-1]?0:1;
            }
            else{
                tab[i][j]=rand()%2;
            }
            if(j==TAI-1)
            {
                k=tab[i][j]?k+1:k-1;
                if(k!=0)
                    tab[i][j] = (tab[i][j])?0:1;
            }
        }
    }
}

int grille()
{
    srand((unsigned)time(NULL));// choix de la grille aléatoirement

    int choix;
    int i;
    int **grid1;
    int **grid2;
    int **grid3;
    int **grid4;

    choix = (rand()%3) +1;

    if (choix==1)
    {
        grid1 =(int*) malloc(TAI * (sizeof(int*)));

        for(i=0;i<TAI;i++)
        {
            grid1[i]= malloc(TAI * (sizeof(int)));
        }
        grid1[0][0]=grid1[0][2]=grid1[0][3]=grid1[0][5]=grid1[1][0]=grid1[1][2]=grid1[1][4]=grid1[1][7]=grid1[2][1]=grid1[2][3]=grid1[2][4]=grid1[2][6]=grid1[3][1]=grid1[3][3]=grid1[3][5]=grid1[3][6]=grid1[4][0]=grid1[4][2]=grid1[4][5]=grid1[4][7]=grid1[5][1]=grid1[5][4]=grid1[5][6]=grid1[5][7]=grid1[6][2]=grid1[6][3]=grid1[6][5]=grid1[6][6]=grid1[7][0]=grid1[7][1]=grid1[7][4]=grid1[7][7]=1;
        grid1[0][1]=grid1[0][4]=grid1[0][6]=grid1[0][7]=grid1[1][1]=grid1[1][3]=grid1[1][5]=grid1[1][6]=grid1[2][0]=grid1[2][2]=grid1[2][5]=grid1[2][7]=grid1[3][0]=grid1[3][2]=grid1[3][4]=grid1[3][7]=grid1[4][1]=grid1[4][3]=grid1[4][4]=grid1[4][6]=grid1[5][0]=grid1[5][2]=grid1[5][3]=grid1[5][5]=grid1[6][0]=grid1[6][1]=grid1[6][4]=grid1[6][7]=grid1[7][2]=grid1[7][3]=grid1[7][5]=grid1[7][6]=0;
        return grid1;
    }
    else if (choix==2)
    {
        grid2 =(int*) malloc(TAI * (sizeof(int*)));

        for(i=0;i<TAI;i++)
        {
            grid2[i]= malloc(TAI * (sizeof(int)));
        }
        grid2[0][0]=grid2[0][1]=grid2[0][3]=grid2[0][5]=grid2[1][1]=grid2[1][2]=grid2[1][4]=grid2[1][6]=grid2[2][0]=grid2[2][2]=grid2[2][5]=grid2[2][7]=grid2[3][0]=grid2[3][3]=grid2[3][4]=grid2[3][7]=grid2[4][1]=grid2[4][3]=grid2[4][4]=grid2[4][6]=grid2[5][1]=grid2[5][2]=grid2[5][5]=grid2[5][6]=grid2[6][0]=grid2[6][3]=grid2[6][5]=grid2[6][7]=grid2[7][2]=grid2[7][4]=grid2[7][6]=grid2[7][7]=0;
        grid2[0][2]=grid2[0][4]=grid2[0][6]=grid2[0][7]=grid2[1][0]=grid2[1][3]=grid2[1][5]=grid2[1][7]=grid2[2][1]=grid2[2][3]=grid2[2][4]=grid2[2][6]=grid2[3][1]=grid2[3][2]=grid2[3][5]=grid2[3][6]=grid2[4][0]=grid2[4][2]=grid2[4][5]=grid2[4][7]=grid2[5][0]=grid2[5][3]=grid2[5][4]=grid2[5][7]=grid2[6][1]=grid2[6][2]=grid2[6][4]=grid2[6][6]=grid2[7][0]=grid2[7][1]=grid2[7][3]=grid2[7][5]=1;
        return grid2;
    }
    else if (choix==3)
    {
        grid3 =(int*) malloc(TAI * (sizeof(int*)));

        for(i=0;i<TAI;i++)
        {
            grid3[i]= malloc(TAI * (sizeof(int)));
        }
        //grid1[0][0]=grid1[0][2]=grid1[0][3]=grid1[0][5]=grid1[1][0]=grid1[1][2]=grid1[1][4]=grid1[1][7]=grid1[2][1]=grid1[2][3]=grid1[2][4]=grid1[2][6]=grid1[3][1]=grid1[3][3]=grid1[3][5]=grid1[3][6]=grid1[4][0]=grid1[4][2]=grid1[4][5]=grid1[4][7]=grid1[5][1]=grid1[5][4]=grid1[5][6]=grid1[5][7]=grid1[6][2]=grid1[6][3]=grid1[6][5]=grid1[6][6]=grid1[7][0]=grid1[7][1]=grid1[7][4]=grid1[7][7]=1;
        //grid1[0][1]=grid1[0][4]=grid1[0][6]=grid1[0][7]=grid1[1][1]=grid1[1][3]=grid1[1][5]=grid1[1][6]=grid1[2][0]=grid1[2][2]=grid1[2][5]=grid1[2][7]=grid1[3][0]=grid1[3][2]=grid1[3][4]=grid1[3][7]=grid1[4][1]=grid1[4][3]=grid1[4][4]=grid1[4][6]=grid1[5][0]=grid1[5][2]=grid1[5][3]=grid1[5][5]=grid1[6][0]=grid1[6][1]=grid1[6][4]=grid1[6][7]=grid1[7][2]=grid1[7][3]=grid1[7][5]=grid1[7][6]=0;
        return grid1;
    }
    else
    {
        grid4 =(int*) malloc(TAI * (sizeof(int*)));

        for(i=0;i<TAI;i++)
        {
            grid4[i]= malloc(TAI * (sizeof(int)));
        }
        //grid1[0][0]=grid1[0][2]=grid1[0][3]=grid1[0][5]=grid1[1][0]=grid1[1][2]=grid1[1][4]=grid1[1][7]=grid1[2][1]=grid1[2][3]=grid1[2][4]=grid1[2][6]=grid1[3][1]=grid1[3][3]=grid1[3][5]=grid1[3][6]=grid1[4][0]=grid1[4][2]=grid1[4][5]=grid1[4][7]=grid1[5][1]=grid1[5][4]=grid1[5][6]=grid1[5][7]=grid1[6][2]=grid1[6][3]=grid1[6][5]=grid1[6][6]=grid1[7][0]=grid1[7][1]=grid1[7][4]=grid1[7][7]=1;
        //grid1[0][1]=grid1[0][4]=grid1[0][6]=grid1[0][7]=grid1[1][1]=grid1[1][3]=grid1[1][5]=grid1[1][6]=grid1[2][0]=grid1[2][2]=grid1[2][5]=grid1[2][7]=grid1[3][0]=grid1[3][2]=grid1[3][4]=grid1[3][7]=grid1[4][1]=grid1[4][3]=grid1[4][4]=grid1[4][6]=grid1[5][0]=grid1[5][2]=grid1[5][3]=grid1[5][5]=grid1[6][0]=grid1[6][1]=grid1[6][4]=grid1[6][7]=grid1[7][2]=grid1[7][3]=grid1[7][5]=grid1[7][6]=0;
        return grid1;
    }

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

    printf("\n\n");
    affJeu(grille());

    printf("\n\n\n %");
    return 0;
}
