#include "matdin.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Matriz* cria_mat(int m, int n){
    int i;
    Matriz* mat = (Matriz*) malloc(sizeof(Matriz));
    mat->lin = m;
    mat->col = n;
    mat->v = (float**) malloc(m * sizeof(float*));

    for(i = 0; i < m; i++){
        mat->v[i] = (float*) malloc(n * sizeof(float));
    }
    return mat;
}

Matriz* cria_trans(Matriz* mat){
    int i, j;
    Matriz* mat2 = (Matriz*) malloc(sizeof(Matriz));
    mat2->lin = mat->col;
    mat2->col = mat->lin;
    mat2->v = (float**) malloc(mat2->lin * sizeof(float*));

    for(i = 0; i < mat2->lin; i++){
        mat2->v[i] = (float*) malloc(mat2->col * sizeof(float));
    }

    for(i = 0; i < mat2->lin; i++){
        for(j = 0; j < mat2->col; j++){
            mat2->v[i][j] = mat->v[j][i];
        }
    }
    return mat2;
}

void libera(Matriz* mat){
    int i;
    for(i = 0; i < mat->lin; i++){
        free(mat->v[i]);
    }
    free(mat);
}

float acessa(Matriz* mat, int i, int j){
    return mat->v[i][j];
}

void atribui(Matriz* mat, int i, int j, float val){
    mat->v[i][j] = val;
}

void imprime(Matriz* mat){
    int i, j;
    for(i = 0; i < mat->lin; i++){
        for(j = 0; j < mat->col; j++){
            printf("%.2f   ", mat->v[i][j]);
        }
        printf("\n");
    }
}

void preenche(Matriz* mat){
    srand(time(NULL));
    int r, m, n;

    for(m = 0; m < mat->lin; m++){
        for(n = 0; n < mat->col; n++){
            atribui(mat, m, n, r = rand()%300);
        }
    }
}
