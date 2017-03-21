#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

struct arv{
    int d;
    arv* esq;
    arv* dir;
};

arv* cria_no(int dado, arv* esquerda, arv* direita){
    arv* novo = malloc(sizeof(arv));
    if(novo){
        novo->esq = malloc(sizeof(arv));
        novo->dir = malloc(sizeof(arv));

        novo->d = dado;
        novo->esq = esquerda;
        novo->dir = direita;
        return novo;
    }
    else{printf("Erro na alocacao de nos!!\n"); exit(EXIT_FAILURE);}
}

void printaERD(arv* arvore){
    if(arvore != NULL){
        if(arvore->esq == NULL) return;
        printaERD(arvore->esq);
        printf("%d\n", arvore->d);

        if(arvore->dir == NULL) return;
        printaERD(arvore->dir);
        printf("%d\n", arvore->d);
    }
}
