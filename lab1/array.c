#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//preenche com numeros aleatórios
void fill(int rnd[], int i) {
    int j;
    srand(time(NULL));
    for (j = 0; j < i; j++) {
        rnd[j] = rand()%100;
    }
}
//printa
void printa(int rnd[], int i) {
    int j;
    for(j = 0; j < i; j++){
        printf ("%d\n", rnd[j]);
    }
}
//troca 2 valores de posição
void troca_valores(int rnd[], int x, int y) {
    int aux = 0;
    aux = rnd[x];
    rnd[x] = rnd[y];
    rnd[y] = aux;
}
//informa o índice do menor elemento do vetor
int menor_indice(int rnd[], int x, int y) {
    int menor = x, i = 0;
    
    for (i = x; i < (x+y); i++) { 
        if (rnd[i] < rnd[menor]) { 
            menor = i;  
        } 
    }
    return menor;
}
//ordena
void ordena_trecho(int rnd[], int x, int y) { 
    int i = 0, menor = 0;
    
    for(i = 0; i < (x+y); i++) {
        menor = menor_indice(rnd, i+x, y-i+1); 
        troca_valores(rnd, i+x, menor);
    }
}
//main
int main() {
    int rnd[30], i = 0;
       
    fill(rnd, 30);
    printa(rnd, 30);
    ordena_trecho(rnd, 0, 29);
    printf("\n\n");
    printa(rnd, 30);
    
    system("PAUSE");
}
