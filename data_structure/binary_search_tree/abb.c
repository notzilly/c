#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef enum{desconhecido, calculando, calculado} estado_t ;

/*struct arv{
    char *chave;
    char *formula;
    double valor;
    estado_t estado;
    arv *esq;
    arv *dir;
};*/

void printaERD(arv *arvore){
    arv* copy = arvore;
    if(copy == NULL) return;
    printaERD(copy->esq);
    printf("%s ", copy->chave);
    printaERD(copy->dir);
}

void printaSTR(arv *arvore){ //printa no esquema (no, esq, dir)
    arv* copy = arvore;
    if(copy == NULL) return;
    if(copy->esq == NULL && copy->dir == NULL) {printf("%s", copy->chave); return;}
    printf("(");
    printf("%s", copy->chave);
    printf(", ");
    printaSTR(copy->esq);
    if(copy->esq == NULL) printf("/");
    printf(", ");
    printaSTR(copy->dir);
    if(copy->dir == NULL) printf("/");
    printf(")");
}

arv* arv_cria_no(char *chave, arv* esquerda, arv* direita){
    arv* novo = malloc(sizeof(arv));
    if(novo){
        novo->esq = malloc(sizeof(arv));
        novo->dir = malloc(sizeof(arv));

        novo->chave = strdup(chave);
        novo->esq = esquerda;
        novo->dir = direita;
        return novo;
    }
    else{printf("Erro na alocacao de nos!!\n"); exit(EXIT_FAILURE);}
}

arv* arv_busca(arv *a, char *chave){   //retorna o nó com a chave caso encontrar, senao retorna NULL
    arv* aux = a;
    if(aux == NULL) return NULL;
    int cmp = strcmp(chave, aux->chave);

    if(cmp == 0){  //chave = copy->chave
        return aux;
    }
    else if(cmp > 0){
        return arv_busca(aux->dir, chave);
        //arv_insere(&(aux->dir), chave);
    }
    else if(cmp < 0){
        return arv_busca(aux->esq, chave);
        //arv_insere(&(aux->esq), chave);
    }
}

arv *arv_busca_prox(arv *a, char *chave){

}

arv* arv_insere(arv **a, char *chave){  //retorna o nó se inserido ou aquele que ja existe com a mesma chave
    arv* aux = *a;
    if(!aux){
        aux = arv_cria_no(chave, NULL, NULL);
        if(*a == NULL){*a = aux;}
    }
    int cmp = strcmp(chave, aux->chave);
    if(cmp < 0){
        arv_insere(&(aux->esq), chave);
    }
    else if(cmp > 0){
        arv_insere(&(aux->dir), chave);
    }
    else if(cmp == 0){
        return NULL;
    }
}

void arv_remove(arv **a, char *chave){ //remove o nó. se nao existir nao faz nada

}
