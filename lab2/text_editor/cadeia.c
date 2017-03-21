#include "cadeia.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// substitui um caractere em uma dada posição da string
// adiciona espaços no final da string antes dessa posição, caso necessário.
void cad_subst(char **s, int p, char c){  ///100%
    char *aux = *s;

    if(p < strlen(aux) && p > -1){     //se o caracter a ser substituido nao adiciona nada a string
        aux[p] = c;
        *s = aux;
        return;
    }
    else if(p == strlen(aux)){  //se o caracter esta no '\0' da string
        aux = realloc(aux, p + 2);
        aux[p] = c;
        aux[p + 1] = '\0';
        *s = aux;
        return;
    }
    else if(p > strlen(aux)){   //se o caracter deveria estar alem da string
        int newLen = p + 2;
        int origSize = strlen(aux);
        aux = realloc(aux, newLen);

        int i;
        for(i = origSize; i < p; i++){
            aux[i] = ' ';
        }
        aux[p] = c;
        aux[p + 1] = '\0';
        *s = aux;
        return;
    }
    else{return;}
}

// insere um caractere em uma dada posição da string
// adiciona espaços no final da string antes dessa posição, caso necessário.
void cad_ins(char **s, int p, char c){   ///100%
    char *aux = *s;

    if(p < strlen(aux) && p > -1){ //se o caracter deveria estar no meio da string
        int bZero = strlen(aux) + 2;
        aux = realloc(aux, bZero);

        int i;
        aux[bZero - 1] = '\0';
        for(i = bZero - 1; i > p; i--){
            aux[i] = aux[i - 1];
        }
        aux[p] = c;
        //printf("\n\n\n\n\ncad_ins: strlen = %d, realloc = %d\n", strlen(aux), bZero);
        *s = aux;
       // printf("\nfinal = %p", *s);
        return;
    }
    else if(p == strlen(aux)){  //se o caracter esta no '\0' da string
        aux = realloc(aux, p + 2);
        //printf("\naux = %p", aux);

        aux[p] = c;
        aux[p + 1] = '\0';
       // printf("\n\n\n\n\ncad_ins: strlen = %d, realloc = %d\n", strlen(aux), p + 2);
        *s = aux;
        //printf("\nfinal = %p", *s);
        return;
    }
    else if(p > strlen(aux)){   //se o caracter deveria estar alem da string
        int newLen = p + 1;    //numero novo de caracteres mais o '\0'
        aux = realloc(aux, newLen);
        //printf("\naux = %p", aux);

        int i;
        for(i = strlen(aux); i < p; i++){
            aux[i] = ' ';
        }
        aux[p] = c;
        aux[p + 1] = '\0';
        //printf("\n\n\n\n\ncad_ins: strlen = %d, realloc = %d\n", strlen(aux), newLen);
        *s = aux;
        //printf("\nfinal = %p", *s);
        return;
    }
    else{return;}
}

// remove o caractere em uma dada posição da string
// não faz nada se a posição estiver fora da string
void cad_rem(char **s, int p){   ///100%
    char *aux = *s;

    //if(p == 0 && strlen(aux) == 0){    }
    /*else*/ if(p == strlen(aux) - 1){     //ultima pos da string
        int newLen = strlen(aux);
        aux[p] = '\0';
        aux = realloc(aux, newLen);
        *s = aux;
        return;
    }
    else if(p < strlen(aux) - 1 && p > -1){
        int newLen = strlen(aux);
        int i;
        aux = realloc(aux, newLen);
        for(i = p; i < newLen; i++){
            aux[i] = aux[i + 1];
        }
        aux[i] = '\0';
        *s = aux;
        return;
    }
    else{return;}
}

// quebra a string s na posição p
// s passa a conter os primeiros p caracteres e s2 os caracteres a partir daí
// a string s2 recebida não deve ser válida (a função não deve manipular o
//   valor original de s2, nem considerar que a memória para onde ela
//   eventualmente aponta deva ser liberada)
// não altera s e inicializa s2 com uma string vazia caso p esteja além
//   do final de s
void cad_quebra(char **s, int p, char **s2){   ///ok
    char *aux = *s;
    char *aux2 = *s2;

    if(p < strlen(aux) && p > -1){
        int oldSizes1 = strlen(aux);
        int newSizes2 = oldSizes1 - p;
        aux2 = malloc(newSizes2 + 1);

        int i, j = 0;
        for(i = p; i < oldSizes1; i++){
            aux2[j] = aux[i];
            j++;
        }
        aux2[j] = aux[i];
        aux2[j + 1] = '\0';

        aux = realloc(aux, p + 1);
        aux[p] = '\0';

        *s = aux;  //alterado
        *s2 = aux2;
        return;
    }
    else{
        aux2 = malloc(strlen("") + 1);
        strcpy(aux, "");
        *s2 = aux2;
        return;
    }
}

// concatena a string s2 no final de s
// nao altera s2 (em parte dos usos, isso implica que s2 terá que ser liberada
//   por quem chama)
void cad_gruda(char **s, char **s2){ ///100%
    char *aux = *s;
    char *aux2 = *s2;

    int sizes = strlen(aux);
    int sizes2 = strlen(aux2) + 1;  //ja com o +1 do '\0'
    aux = realloc(aux, sizes + sizes2);

    int i, j = 0;
    for(i = sizes; i < sizes + sizes2; i++){
        aux[i] = aux2[j];
        j++;
    }
    aux[i] = '\0';  //antes tava i + 1
    *s = aux;
    return;
}

// ajusta a string s para que tenha pelo menos o tamanho dado, adicionando
//   espaços no final se necessário
void cad_ajusta(char **s, int tam){  ///100%
    char *aux = *s;
    int strsize = strlen(aux);
    if(tam > strsize){
        aux = realloc(aux, tam + 1);
        int i;
        for(i = strsize; i < tam; i++){
            aux[i] = ' ';
        }
        aux[tam] = '\0';
        *s = aux;
        return;
    }
    else{return;}
}
