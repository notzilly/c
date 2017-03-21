#ifndef _MATDIN_H_
#define _MATDIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct matriz{
    int lin, col;
    float** v;
}Matriz;

//Cria uma matriz com m linhas n colunas
Matriz* cria_mat(int m, int n);

//Funcao que libera a memoria
void libera(Matriz* mat);

//Funcao que retorna o valor de um elemento da matriz
float acessa(Matriz* mat, int i, int j);

//Funcao que atribui os valores para a matriz
void atribui(Matriz* mat, int i, int j, float val);

//preenche a matriz com numeros aleatorios usando a void atribui
void preenche(Matriz* mat);

//Funcao que imprime a matriz
void imprime(Matriz* mat);

//Recebe uma matriz pronta e retorna uma transposta a recebida
Matriz* cria_trans(Matriz* mat);

#endif //_MATDIN_H
