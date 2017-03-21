#ifndef _CALC_H_
#define _CALC_H_
#include "pilha.h"
#include "abb.h"

//verifica se a string é um double com ate 2 casas decimais
bool so_numeros(char *entrada);

//cria a arvore de variaveis
arv* cria_arv_variaveis(char *entrada);

//retorna se existir um char naquela posição da entrada
char* retorna_char(char *entrada, int indice);

//le entrada e retorna um double que podera ou nao ser empilhado
dado_t le_entrada(char *entrada, int indice);

//opera topo da pilha e reescreve o resultado la
dado_t opera_pilha(pilha *operandos, pilha *operadores);

//entrada de dados e calculos
dado_t calcula(char *entrada, arv *variaveis);

// calcula o valor da expressão expr, usando a árvore variaveis para buscar
// valores de variáveis existentes na expressão.
dado_t calc_calcula(char *expr, arv *variaveis);

// retorna o valor do nó no.
// caso necessário, calcula a fórmula do nó, usando a árvore de variáveis.
dado_t arv_valor(arv *no, arv *variaveis);


#endif // _CALC_H_
