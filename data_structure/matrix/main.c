#include "matdin.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int m, n;
    printf("Informe o numero de linhas e colunas da matriz: ");
    scanf("%d %d", &m, &n);
    if(m <= 0 || n <= 0 || (m == 1 && n == 1)){
        printf("Meca suas matrizes!");
        exit(1);
    }

    Matriz* deep;
    deep = cria_mat(m, n);
    preenche(deep);

    Matriz* deep_t = cria_trans(deep);

    imprime(deep);
    printf("\n\n");
    imprime(deep_t);

    printf("\n%.2f", acessa(deep, 0, 0));
    printf("\n%.2f", acessa(deep_t, 0, 1));

    libera(deep);
    libera(deep_t);
    return 0;
}


