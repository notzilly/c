#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

//implementacao da estrutura pilha, definida como Pilha no pilha .h
struct pilha{
    int nElem;
    int *vet;
};

//aloca a pilha e coloca 0 no numero de elementos
Pilha* pilha_cria(){
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if(p == NULL){
        printf("Falha ao criar pilha!\n");
        exit(1);
    }
    p->nElem = 0;
    return p;
}

//destroi pilha
void pilha_destroi(Pilha* p){
    free(p->vet);
    free(p);
}

//verifica se a pilha esta vazia (p->nElem == 0)
bool pilha_vazia(Pilha* p){
    if(p->nElem == 0){return true;}
    else{return false;}
}

//insere na primeira posicao disponivel
void pilha_push(Pilha* p, int dado){
    if(p->nElem == 0){  //aloca o vetor pra mais um elemento se a pilha estiver vazia
        p->vet = (int*) malloc(sizeof(int));
    }
    else{                        //realloca o vetor para caber mais um inteiro caso ela ja contenha algum elemento
        p->vet = (int*) realloc(p->vet, (p->nElem + 1) * sizeof(int));
    }
    p->vet[p->nElem] = dado;
    p->nElem++;
}

//remove e retorna o elemento do topo da pilha
int pilha_pop(Pilha* p){
    if(pilha_vazia(p)){
        printf("Nao foi possivel dar pop na pilha, pois ela esta vazia!!\n");
        exit(1);
    }
    else{            //decrementa o nElem e realloca o vetor para retirar o elemento do topo da pilha
        p->nElem--;
        int aux = p->vet[p->nElem];
        if(p->nElem != 0){
            p->vet = (int*) realloc(p->vet, (p->nElem) * sizeof(int));
        }
        else{
            p->vet = NULL;
        }
        return aux;
    }
}

//insere o dado na posicao pos da pilha p
void pilha_insere(Pilha* p, int pos, int dado){
    if(pos < 0){
        printf("Posicao invalida para insercao!\n");
        exit(1);
    }
    if(pos == p->nElem){  //se a posicao for a proxima do vetor, somente damos push
        pilha_push(p, dado);
        return;
    }
    if(pos < p->nElem){    //se a posicao ja estiver ocupada por 0 ou qualquer outro numero, substituimos seu valor pela int dado
        p->vet[pos] = dado;
        return;
    }
    else{            //inserimos um 0 no topo da pilha e chamamos a funcao de insercao novamente
        pilha_push(p, 0);
        pilha_insere(p, pos, dado);
    }
}

//remove e retorna o dado da posicao pos da pilha p
int pilha_remove(Pilha* p, int pos){
    if(pos < 0 || pos > p->nElem - 1){
        printf("Posicao invalida para remocao!\n");
        exit(1);
    }
    if(pilha_vazia(p)){
        printf("Pilha vazia! Nao eh possivel remover!\n");
        exit(1);
    }

    if(pos == p->nElem - 1){     //elemento esta na ultima posicao do vetor, entao so damos pop na pilha
        return pilha_pop(p);
    }
    else{
        int aux = p->vet[pos];                 //faz com que o elemento a ser removido fique na ultima posicao do vetor, possibilitando o pop, ja implementado
        p->vet[pos] = p->vet[pos + 1];
        p->vet[pos+ 1] = aux;
        pos++;
        pilha_remove(p, pos);
    }
}
