#ifndef _PILHA_H_
#define _PILHA_H_
#include <stdbool.h>

//definicao da estrutura pilha
typedef struct pilha Pilha;

//cria pilha
Pilha* pilha_cria();

//destroi pilha
void pilha_destroi(Pilha* p);

//pilha vazia
bool pilha_vazia(Pilha* p);

//push - insere um elemento na pilha
void pilha_push(Pilha* p, int dado);

//pop - remove e retorna o elemento no topo da lista, se possível
int pilha_pop(Pilha* p);

//insere o dado na posicao pos da pilha p
void pilha_insere(Pilha* p, int pos, int dado);

//remove e retorna o dado da posicao pos da pilha p
int pilha_remove(Pilha* p, int pos);

#endif // _PILHA_H_
