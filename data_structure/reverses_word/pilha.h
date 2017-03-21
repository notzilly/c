#ifndef _PILHA_H_
#define _PILHA_H_
#include <stdlib.h>
#include <stdio.h>

typedef struct pilha Pilha;

Pilha* pilha_cria();

Pilha* pilha_empilha(Pilha* p, char emp);

#endif //_PILHA_H_
