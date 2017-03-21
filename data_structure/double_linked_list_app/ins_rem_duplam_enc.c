#include "ins_rem_duplam_enc.h"
#include <stdio.h>
#include <stdlib.h>

struct lista{
    int dado;
    Lista* prox;
    Lista* ant;
};

Lista* inicia_lista(){
    Lista *l = NULL;
    return l;
}

Lista* insere_duplamente(Lista* l, int d){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->dado = d;
    novo->prox = l;
    novo->ant = NULL;

    if(l != NULL){
        l->ant = novo;
    }
    return novo;
}

void printa_circular(Lista* l){
    Lista* aux = l;

    if(aux->prox != l){
        while(aux->prox != l){
            printf("Dado = %d\n", aux->dado);
            aux = aux->prox;
        }
    }
    else{
        printf("Dado = %d\n", aux->dado);
    }
}
