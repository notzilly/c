#ifndef _LISTA2_H_
#define _LISTA2_H_

// API de uma lista duplamente encadeada de strings
// a ser usada na disciplina lab2, 1o sem 2015
// ver descrição em http://www.inf.ufsm.br/~benhur/l22015a

// 3/5/15: faltava um argumento em lista_substitui

#include <stdbool.h>

// os dados na lista são char *
// a lista não toca nos dados, simplesmente os armazena e os disponibiliza
// a responsabilidade pela alocação e manutenção desses dados está alhures
typedef char * dado_t;

// um elemento é uma estrutura a ser definida em lista2.c
typedef struct elemento elemento;

// uma lista é uma estrutura a ser definida em lista2.c
typedef struct lista2 lista2;

struct elemento{    //um elemento = 1 linha do texto alocada dinamicamente no dado_t string
    dado_t line;
    elemento* ant;
    elemento* prox;
};

struct lista2{         //se lista estiver vazia, os tres ponteiros devem ser NULL
    elemento* prim;
    elemento* ult;
    elemento* corr;
};

//retorna o numero de elementos da lista = numero de linhas do texto
int num_linhas(lista2 *l);

// cria e retorna uma lista vazia
// (deve alocar memória para o descritor da lista, inicializá-lo
//  e retornar um ponteiro para isso)
lista2 *lista_cria(void);

// destroi uma lista
// libera a memória alocada por cada elemento da lista e pelo descritor
void lista_destroi(lista2 *l);

// retorna true se a lista não contiver nenhum elemento
bool lista_vazia(lista2 *l);

// testa a integridade da lista
// retorna true se a lista tiver OK, retorna false caso encontre algum problema
// deve verificar pelo menos se os dois encadeamentos estão corretos e se o
//   elemento corrente pertence a lista
bool lista_verifica(lista2 *l);


// insere um dado na lista, após o elemento corrente
// o elemento corrente passa a ser o novo elemento inserido
// caso a lista esteja vazia, insere o primeiro elemento da lista
void lista_insere_apos(lista2 *l, dado_t d);

// insere um dado na lista, antes do elemento corrente
// o elemento corrente passa a ser o novo elemento inserido
// caso a lista esteja vazia, insere o primeiro elemento da lista
void lista_insere_antes(lista2 *l, dado_t d);

// remove o elemento corrente da lista
// retorna o dado contido no elemento removido
// nao faz nada se a lista estiver vazia (e nesse caso retorna NULL)
// o elemento corrente passa a ser o elemento que estava apos o removido,
// ou o anterior, caso tenha sido removido o último, ou NULL, caso a lista
// tenha ficado vazia.
dado_t lista_remove(lista2 *l);


// retorna o dado contido no elemento corrente da lista
// caso a lista esteja vazia, retorna NULL
dado_t lista_corrente(lista2 *l);

// substitui o dado contido no elemento corrente da lista
// retorna o dado anterior contido nesse elemento
// retorna NULL (e nao faz nada com o dado recebido) caso a lista esteja vazia
dado_t lista_substitui(lista2 *l, dado_t d);


// posiciona o elemento corrente no inicio (primeiro elemento) da lista
// nao faz nada se a lista estiver vazia
void lista_inicio(lista2 *l);

// posiciona o elemento corrente no final (último elemento) da lista
// nao faz nada se a lista estiver vazia
void lista_fim(lista2 *l);

// avança o elemento corrente para o elemento seguinte e retorna true
// retorna false e não avança caso a lista esteja vazia ou o elemento
//   corrente seja o último.
bool lista_avanca(lista2 *l);

// recua o elemento corrente para o elemento anterior e retorna true
// retorna false e não recua caso a lista esteja vazia ou o elemento
//   corrente seja o primeiro.
bool lista_recua(lista2 *l);

#endif // _LISTA2_H_
