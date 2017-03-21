#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

// cria e retorna uma pilha vazia
pilha pilha_cria(void){
    pilha p = lista_cria();
    return p;
}

// destroi uma pilha; altera a pilha apontada por p para ser vazia
void pilha_destroi(pilha *p){
    lista_destroi(p);
    return;
}

// retorna true se a pilha não contiver nenhum elemento
bool pilha_vazia(pilha *p){
    return lista_vazia(p);
}

// insere um dado no topo da pilha
void pilha_insere(pilha *p, dado_t d){
    lista_insere_inicio(p, d);
    return;
}

// remove o elemento do topo da pilha e retorna o dado que ele continha
dado_t pilha_remove(pilha *p){
    return lista_remove_inicio(p);
}

// retorna o dado no topo da pilha (não altera a pilha)
dado_t pilha_topo(pilha *p){
    return lista_inicio(p);
}
