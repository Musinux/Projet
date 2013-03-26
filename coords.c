#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "coords.h"

void initElem(int x,int y, int etat, int estEnVerif, coords*c,coords*prec,coords*suiv){

    c->x=(x!=0)?x:0;
    c->y=(y!=0)?y:0;
    c->etat=(etat!=NULL)?etat:VIDE;
    c->prec=(prec!=NULL)?prec:NULL;
    c->suiv=(suiv!=NULL)?suiv:NULL;
    c->estEnVerif=(estEnVerif!=0)?estEnVerif:0;
}

coords* removeElem(coords *c){
    coords *suiv = c->suiv;
    coords *prec = c->prec;
    if(suiv!=NULL || prec!=NULL){
        if(suiv!=NULL)
            suiv->prec = prec;
        if(prec!=NULL)
            prec->suiv = suiv;
        free(c);
        if(suiv!=NULL)
            c=suiv;
        else if(prec!=NULL)
            c=prec;
    }
    return c;
}

coords* addElem(coords *c){
    coords *newCoord;
    newCoord = (coords*) malloc(sizeof(coords));
    initElem(c->x,c->y,VIDE,0,newCoord,c,c->suiv);
    c->suiv=newCoord;
    return newCoord;
}

void delList(coords *c){
    while(c->suiv!=NULL){
        c=c->suiv;
    }
    while(c->prec!=NULL){
        c=c->prec;
        free(c->suiv);
    }
    free(c);
}
