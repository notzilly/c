#include "abb.h"
#include <stdio.h>
#include <string.h>

int main(){
    arv* a = NULL;

    /*
    arv *r = minha_arv();
    char *c = NULL;
    arv* a;
    while ((arv_busca_prox(r, c) != NULL){
        c = a->chave;
        printf("%s\n", c);
    }*/

    //rotaçoes do benhur
    /*
reequilibrio(a)
    feq(a)
        +2: feq(a->esq)
                -1: rotesq(a->esq)
            rotdir(a)
        -2: feq(a->dir)
                +1: rotdir(a->dir)
            rotesq(a)
    */

    arv_insere(&a, "e");
    arv_insere(&a, "b");
    arv_insere(&a, "a");
    arv_insere(&a, "d");
    arv_insere(&a, "c");
    arv_insere(&a, "f");
    arv_insere(&a, "h");
    arv_insere(&a, "g");
    //arv_insere(&a, "k");
    //arv_insere(&a, "l");
    printf("ERD: "); printaERD(a);
    printf("\nSTR: "); printaSTR(a); printf("\n");


    ///teste busca
    /*arv* aux = arv_busca(a, "a");
    if(aux == NULL) printf("Busca n achou\n");
    else printf("Busca = %s\n", aux->chave);*/

    ///teste busca prox
    /*arv* aux2 = arv_busca_prox(a, "g");
    if(aux2 == NULL) printf("Busca prox n achou\n");
    else printf("Busca prox = %s\n", aux2->chave);*/

    char* remChar = strdup("a");
    printf("Tentando remover o \'%s\'...\n", remChar);
    arv_remove(&a, remChar);
    printf("ERD: "); printaERD(a);
    printf("\nSTR: ");printaSTR(a); printf("\n");

    return 0;
}
