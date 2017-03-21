#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

struct pilha{
    char c;
    Pilha* prox;
};

Pilha* pilha_cria(){
    return NULL;
}

Pilha* pilha_empilha(Pilha* p, char emp){
    Pilha* novo = (Pilha) malloc(sizeof(Pilha));

}
