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
    arv* copy = arvore;
    if(copy == NULL) return;
    printaERD(copy->esq);
    printf("%d\n", copy->d);
    printaERD(copy->dir);
}

void feq(arv* a){
    return altura(a->esq) - altura(a->dir);
}

//usando feq para rotar
if(feq(a) == 2){
    if(feq(a->esq) == -1){
        rotD(a->esq);
    }
    rotE(a);
}

void rotE(arv* a){
    arv* b = a->esq;
    arv* c = b->esq;
    arv* d = b->dir;
    arv* e = a->dir;

    troca_valores(a, b);

    a->esq = c;
    a->dir = b;
    b->esq = d;
    b->dir = e;
}
