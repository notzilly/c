#ifndef _PILHA_H_
#define _PILHA_H_

#include "lista.h"

// uma pilha é uma lista
typedef lista pilha;

// cria e retorna uma pilha vazia
pilha pilha_cria(void);

// destroi uma pilha; altera a pilha apontada por p para ser vazia
void pilha_destroi(pilha *p);

// retorna true se a pilha não contiver nenhum elemento
bool pilha_vazia(pilha *p);

// insere um dado no topo da pilha
void pilha_insere(pilha *p, dado_t d);

// remove o elemento do topo da pilha e retorna o dado que ele continha
dado_t pilha_remove(pilha *p);

// retorna o dado no topo da pilha (não altera a pilha)
dado_t pilha_topo(pilha *p);

#endif // _PILHA_H_
