#include "ins_rem_duplam_enc.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Lista* lista1 = inicia_lista();
    lista1 = insere_duplamente(lista1, 12);
    lista1 = insere_duplamente(lista1, 23);
    printa_circular(lista1);


    return 0;
}

