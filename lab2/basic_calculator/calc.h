#ifndef _CALC_H_
#define _CALC_H_
#include "pilha.h"
//le entrada e retorna um double que podera ou nao ser empilhado
dado_t le_entrada(char *entrada, int indice);

//opera topo da pilha e reescreve o resultado la
dado_t opera_pilha(pilha *operandos, pilha *operadores);

//entrada de dados e calculos
dado_t calcula(char *entrada);

#endif // _CALC_H_
