#include "lista2.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//retorna o numero de elementos da lista = numero de linhas do texto
int num_linhas(lista2 *l){
    if(lista_vazia(l)){return 0;}
    else{
        int numLinha = 0;
        elemento* aux = l->prim;
        while(aux->prox != NULL){
            numLinha++;
            aux = aux->prox;
        }
        return numLinha + 1;
    }
}

// cria e retorna uma lista vazia
// (deve alocar memória para o descritor da lista, inicializá-lo
//  e retornar um ponteiro para isso)
lista2 *lista_cria(void){     ///ok
    lista2* l = (lista2*) malloc(sizeof(lista2));
    if(l != NULL){
        l->prim = NULL;
        l->ult = NULL;
        l->corr = NULL;
    }
    return l;
}

// destroi uma lista
// libera a memória alocada por cada elemento da lista e pelo descritor (lista2)
void lista_destroi(lista2 *l){    ///ok
    if(lista_vazia(l)) return;
    else if(l->prim != NULL && l->ult != NULL && l->corr != NULL && l->prim == l->ult && l->prim == l->corr){   //verifica se os 3 ponteiro são não nulos e iguais
        free(l->prim);
    }
    else if(l->prim != NULL && l->ult != NULL && l->corr != NULL && l->prim != l->ult){    //verifica se os 3 ponteiros são não nulos e diferentes
        l->corr = l->prim;
        elemento *seguinte = l->corr->prox;

        while(seguinte->prox != NULL){
            free(l->corr);
            l->corr = seguinte;
            seguinte = seguinte->prox;
        }
        free(l->corr);
        free(seguinte);
    }
    else{
        printf("Erro ao destruir lista!");
        exit(1);
    }
    free(l);
    return;
}

// retorna true se a lista não contiver nenhum elemento
bool lista_vazia(lista2 *l){   ///ok
    if(l->prim == NULL && l->ult == NULL && l->corr == NULL) return true;
    else{return false;}
}

// testa a integridade da lista
// retorna true se a lista tiver OK, retorna false caso encontre algum problema
// deve verificar pelo menos se os dois encadeamentos estão corretos e se o
//   elemento corrente pertence a lista
//se o ant prox é o prox do ant até o final
bool lista_verifica(lista2 *l){  ///ok
    if(lista_vazia(l)){
        return true;
    }
    else if(l->prim != NULL && l->ult != NULL && l->prim == l->ult && l->prim == l->corr){   //se a lista tiver so um elemento
        if(l->prim->prox == NULL && l->prim->ant == NULL){
            return true;
        }
        else{return false;}
    }
    else if(l->prim != NULL && l->ult != NULL && l->prim != l->ult && l->corr != NULL){
        elemento* vai = l->prim;
        elemento* volta = l->ult;
        int countVai = 0, countVolta = 0;
        while(vai->prox != l->ult){
            vai = vai->prox;
            countVai++;
        }
        while(volta->ant != l->prim){
            volta = volta->ant;
            countVolta++;
        }
        if(countVai != countVolta){return false;}
        else{return true;}
    }
    else{return false;}
}


// insere um dado na lista, após o elemento corrente
// o elemento corrente passa a ser o novo elemento inserido
// caso a lista esteja vazia, insere o primeiro elemento da lista
void lista_insere_apos(lista2 *l, dado_t d){  ///ok
    elemento* novo = malloc(sizeof(elemento));
    novo->line = d;
    if(lista_vazia(l)){ //primeiro elemento e lista vazia
        novo->ant = NULL;
        novo->prox = NULL;

        l->prim = novo;
        l->ult = novo;
        l->corr = novo;
        return;
    }
    else if(l->corr->prox == NULL && l->corr != NULL && l->corr == l->ult && l->prim != NULL && l->ult != NULL){       //corr == ult / no final
        novo->ant = l->ult;
        novo->prox = NULL;

        l->ult->prox = novo;
        l->ult = novo;
        l->corr = novo;
        return;
    }
    else if(l->corr != NULL && l->prim != l->ult && l->prim != NULL && l->ult != NULL && l->corr != l->ult){ // corr != ult
        novo->ant = l->corr;
        novo->prox = l->corr->prox;

        l->corr->prox->ant = novo;
        l->corr->prox = novo;
        l->corr = novo;
        return;
    }
    else{
        printf("Erro na insercao \"depois\"!");
        exit(1);
    }
}

// insere um dado na lista, antes do elemento corrente
// o elemento corrente passa a ser o novo elemento inserido
// caso a lista esteja vazia, insere o primeiro elemento da lista
void lista_insere_antes(lista2 *l, dado_t d){   ///OK
    elemento* novo = malloc(sizeof(elemento));
    novo->line = d;
    if(lista_vazia(l)){ //primeiro elemento
        novo->ant = NULL;
        novo->prox = NULL;

        l->prim = novo;
        l->ult = novo;
        l->corr = novo;
        return;
    }
    else if(l->corr->ant == NULL && l->corr != NULL && l->corr == l->prim && l->prim != NULL && l->ult != NULL){        //corr == prim / no inicio
        novo->ant = NULL;
        novo->prox = l->prim;

        l->prim->ant = novo;
        l->prim = novo;
        l->corr = novo;
        return;
    }
    else if(l->corr != NULL && l->prim != l->ult && l->prim != NULL && l->ult != NULL && l->corr != l->prim){  //corr != prim
        novo->ant = l->corr->ant;
        novo->prox = l->corr;

        l->corr->ant->prox = novo;
        l->corr->ant = novo;
        l->corr = novo;
        return;
    }
    else{
        printf("Erro na insercao \"antes\"!");
        exit(1);
    }
}

// remove o elemento corrente da lista
// retorna o dado contido no elemento removido
// nao faz nada se a lista estiver vazia (e nesse caso retorna NULL)
// o elemento corrente passa a ser o elemento que estava apos o removido,
// ou o anterior, caso tenha sido removido o último, ou NULL, caso a lista
// tenha ficado vazia.
dado_t lista_remove(lista2 *l){  ///ok
    if(lista_vazia(l)){return NULL;}    //lista vazia
    else if(l->corr != NULL && l->corr == l->prim && l->corr == l->ult){    //se houver so um elemento
        dado_t aux = l->corr->line;
        free(l->corr);
        l->corr = NULL;
        l->prim = NULL;
        l->ult = NULL;
        return aux;
    }
    else if(l->corr != NULL && l->corr == l->ult && l->prim != NULL){    //corr eh o ultimo elemento
        dado_t aux = l->corr->line;
        elemento* back = l->corr->ant;
        free(l->corr);
        back->prox = NULL;
        l->corr = back;
        l->ult = back;
        return aux;
    }
    else if(l->corr != NULL && l->corr != l->ult && l->corr == l->prim){ //se o corr for o primeiro
        dado_t aux = l->corr->line;
        elemento* front = l->corr->prox;
        free(l->corr);
        l->prim = front;
        l->corr = front;
        front->ant = NULL;
        return aux;
    }
    else if(l->corr != NULL && l->corr != l->ult && l->corr != l->prim){  //no meio da lista
        dado_t aux = l->corr->line;
        elemento* front = l->corr->prox;
        elemento* back = l->corr->ant;
        free(l->corr);
        back->prox = front;
        front->ant = back;
        return aux;
    }
    else{
        printf("Falha na remocao do elemento corrente!!");
        exit(1);
    }
}


// retorna o dado contido no elemento corrente da lista
// caso a lista esteja vazia, retorna NULL
dado_t lista_corrente(lista2 *l){  ///ok
    if(lista_vazia(l)){return NULL;}
    else{
        return l->corr->line;
    }
}

// substitui o dado contido no elemento corrente da lista
// retorna o dado anterior contido nesse elemento
// retorna NULL (e nao faz nada com o dado recebido) caso a lista esteja vazia
dado_t lista_substitui(lista2 *l, dado_t d){ ///ok
    if(lista_vazia(l)){return NULL;}
    else{
        dado_t aux = l->corr->line;
        l->corr->line = d;
        return aux;
    }
}


// posiciona o elemento corrente no inicio (primeiro elemento) da lista
// nao faz nada se a lista estiver vazia
void lista_inicio(lista2 *l){ ///ok
    if(lista_vazia(l)){return;}
    else{
        l->corr = l->prim;
        return;
    }
}

// posiciona o elemento corrente no final (último elemento) da lista
// nao faz nada se a lista estiver vazia
void lista_fim(lista2 *l){ ///ok
    if(lista_vazia(l)){return;}
    else{
        l->corr = l->ult;
        return;
    }
}

// avança o elemento corrente para o elemento seguinte e retorna true
// retorna false e não avança caso a lista esteja vazia ou o elemento
//   corrente seja o último.
bool lista_avanca(lista2 *l){ ///ok
    if(lista_vazia(l) || l->corr->prox == NULL){return false;}
    else{
        l->corr = l->corr->prox;
        return true;
    }
}

// recua o elemento corrente para o elemento anterior e retorna true
// retorna false e não recua caso a lista esteja vazia ou o elemento
//   corrente seja o primeiro.
bool lista_recua(lista2 *l){ ///ok
    if(lista_vazia(l) || l->corr->ant == NULL){return false;}
    else{
        l->corr = l->corr->ant;
        return true;
    }
}

