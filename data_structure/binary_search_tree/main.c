#include "abb.h"
#include <stdio.h>

int main(){
    arv* a = NULL;

    arv_insere(&a, "d");
    arv_insere(&a, "b");
    arv_insere(&a, "g");
    arv_insere(&a, "a");
    arv_insere(&a, "f");
    arv_insere(&a, "c");
    arv_insere(&a, "e");
    printf("ERD: ");
    printaERD(a);
    printf("\n\n");
    printf("STR: ");
    printaSTR(a);
    printf("\n");
    arv* aux = arv_busca(a, "e");
    if(aux == NULL) printf("wer!");
    else printf("Busca = %s", aux->chave);

    return 0;
}
