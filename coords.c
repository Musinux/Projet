#include <stdio.h>
#include <stdlib.h>
#include "coords.h"

void initElem(int x,int y, int etat, coords*c,coords*prec,coords*suiv){

    c->x=(x!=NULL)?x:NULL;
    c->y=(y!=NULL)?y:NULL;
    c->etat=(etat!=NULL)?etat:VIDE;
    c->prec=(prec!=NULL)?prec:NULL;
    c->suiv=(suiv!=NULL)?suiv:NULL;
}

coords* removeElem(coords *c){
    coords *suiv = c->suiv;
    coords *prec = c->prec;
    suiv->prec = c->prec;
    prec->suiv = c->suiv;
    if(suiv!=NULL)
        c=suiv;
    else if(prec!=NULL)
        c=prec;
    return c;
}

coords* addElem(coords *c){
    coords *newCoord;
    newCoord = (coords*) malloc(sizeof(coords));
    initElem(c->x,c->y,VIDE,newCoord,c,c->suiv);
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
