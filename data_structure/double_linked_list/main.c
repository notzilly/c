#include <stdio.h>
#include <stdlib.h>

typedef struct lista Lista;

struct lista{
    int dado;
    Lista* prox;
    Lista* ant;
};

Lista* inicia_lista(){
    Lista* l = NULL;
    return l;
}

Lista* insere_duplamente(Lista* l, int d){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->dado = d;
    novo->prox = l;
    novo->ant = NULL;

    if(l != NULL){
        l->ant = novo;
    }
    return novo;
}

Lista* busca(Lista* l, int d){
    Lista* p = l;
    for(p = l; p != NULL; p = p->prox){
        if(p->dado == d){
            return p;
        }
    }
    return NULL;
}

///retira o elemento do ponteiro atual
Lista* remove_elemento(Lista* l, int d){
    Lista* p = busca(l, d);
    Lista* prec = p->ant;
    Lista* suc = p->prox;

    if(p == NULL){
        return l; //nao achou
    }
    if(p == l){
        l = suc;  //primeiro
    }
    else{
        prec->prox = p->prox;
    }
    if(suc != NULL){
        suc->ant = p->ant;
        free(p);
    }
    return l;

    /*
    prec->prox = p->prox;   //testar com suc
    suc->ant = p->ant;    //testar com prec
    */
}

void printa_circular_inversa(Lista* l){
    Lista* p = l;
    if(p){
        while(p->prox != l){
            p = p->prox;
        }
        do{
            printf("%d", p->dado);
            p = p->ant;
        }while(p->ant != l);
    }
    return;
}

void printa_lista(Lista* l){
    Lista* p = l;
    if(p){
        while(p != NULL){
            printf("%d\n", p->dado);
            p = p->prox;
        }
    }
}

int main(){
    Lista* lista1 = inicia_lista();
    int i;
    for(i = 10; i < 81; i += 10){
        lista1 = insere_duplamente(lista1, i);
    }
    printa_lista(lista1);

    return 0;
}
