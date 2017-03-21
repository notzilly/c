#include "arvore.h"
#include <stdio.h>

int main(){
    arv* a = cria_no(2, cria_no(4, NULL, NULL), NULL);
    //arv* b = cria_no(1, a, NULL);
    //arv* c = cria_no(3, NULL, NULL);
    //arv* d = cria_no(12, b, c);
    printaERD(a);
    return 0;
}
