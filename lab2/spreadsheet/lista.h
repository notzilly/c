#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdbool.h>

// os dados na lista são double
typedef double dado_t;

// um elemento é uma estrutura definida em lista.c
typedef struct elemento elemento;

// uma lista é um ponteiro para o primeiro elemento
typedef elemento *lista;

// Atenção: a maior parte das funções recebe um ponteiro para uma lista,
//   que por sua vez é um ponteiro para o primeiro elemento.
// Isso porque a lista precisa ser alterada caso o primeiro elemento
//   seja alterado.
// As funções que retornam dado_t devem imprimir uma mensagem de erro
//   brabo e abortar a execução caso a lista esteja vazia

// cria e retorna uma lista vazia
// (nesta implementação, uma lista vazia é NULL, não tem nada alocado)
lista lista_cria(void);

// destroi uma lista; altera a lista apontada por pl para ser vazia
void lista_destroi(lista *l);

// retorna true se a lista não contiver nenhum elemento
bool lista_vazia(lista *l);

// insere um dado no início da lista
void lista_insere_inicio(lista *l, dado_t d);

// insere um dado no final da lista
void lista_insere_fim(lista *l, dado_t d);

//imprime uma lista
void printa_lista(elemento* aux);

// retorna o dado no início da lista (não altera a lista)
dado_t lista_inicio(lista *l);

// retorna o dado no final da lista (não altera a lista)
dado_t lista_fim(lista *l);

// remove o elemento do início da lista e retorna o dado que ele continha
dado_t lista_remove_inicio(lista *l);

// remove o elemento do final da lista e retorna o dado que ele continha
dado_t lista_remove_fim(lista *l);

#endif // _LISTA_H_
