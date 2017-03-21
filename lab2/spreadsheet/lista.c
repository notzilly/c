#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

struct elemento{
    dado_t dado;
    elemento* prox;
};

lista lista_cria(){
    lista l = NULL;
	return l;
}

void lista_destroi(lista *l){
    if(lista_vazia(l)){
        *l = NULL;
        return;
    }
    else{
        elemento* atual = *l;
        elemento* next;
        if(atual->prox != NULL){
            next = atual->prox;
        }
        free(atual);


        while(atual->prox != NULL){
            atual = next;
            if(next->prox){
                next = next->prox;
            }
            free(atual);
        }
        return;
    }
}

bool lista_vazia(lista *l){
    if(!l) {
        return true;
    }
    else{
        return false;
    }
}

void lista_insere_inicio(lista *l, dado_t d){
    elemento* novo_elem;
    elemento* prim_elem = *l;
    novo_elem = malloc(sizeof(lista));
    if(novo_elem == NULL){ printf("Erro de alocacao!"); exit(1); }

    novo_elem->dado = d;
    novo_elem->prox = prim_elem;
    *l = novo_elem;
}

void lista_insere_fim(lista *l, dado_t d){
    if(lista_vazia(l)){
        exit(1);
    }
    elemento* novo_elem;
    elemento* acha_ultimo = *l;

    novo_elem = malloc(sizeof(lista));
    if(novo_elem == NULL){ printf("Erro de alocacao!"); exit(1); }

    while(acha_ultimo->prox != NULL){
        acha_ultimo = acha_ultimo->prox;
    }
    novo_elem->dado = d;
    novo_elem->prox = NULL;
    acha_ultimo->prox = novo_elem;
}

void printa_lista(elemento* aux){
	while(aux){
		printf("Valor: %.2f\n", aux->dado);
		aux = aux->prox;
	}
	printf("\n");
}

dado_t lista_inicio(lista *l){
    if(lista_vazia(l)){
        printf("Lista vazia! Nao ha como retornar o primeiro elemento!\n");
        exit(1);
    }
    else{
        elemento *aux = *l;
        if(aux){
            return aux->dado;
        }
    }
}

dado_t lista_fim(lista *l){
    if(lista_vazia(l)){
        printf("Lista vazia! Nao ha como retornar o ultimo elemento!\n");
        exit(1);
    }
    else{
        elemento *aux = *l;
        if(aux){
            while(aux->prox != NULL){
                aux = aux->prox;
            }
            return aux->dado;
        }
    }
}

dado_t lista_remove_inicio(lista *l){
    if(lista_vazia(l)){
        printf("Lista vazia! Nao ha como retornar e remover o primeiro elemento!\n");
        exit(1);
    }
    else{
        elemento *aux = *l;
        if(aux){
            if(aux->prox != NULL){
                dado_t removido = aux->dado;
                *l = aux->prox;
                return removido;
            }
            else{ /*if(aux->prox == NULL)*/
                dado_t removido = aux->dado;
                *l = NULL; //usar funcao destroi!!!!!!!
                return removido;
            }
        }
    }
}

dado_t lista_remove_fim(lista *l){
    if(lista_vazia(l)){
        printf("Lista vazia! Nao ha como retornar e remover o ultimo elemento!\n");
        exit(1);
    }
    else{
        elemento *aux = *l;

        if(aux){
            if(aux->prox == NULL){
                dado_t removido = aux->dado;
                *l = NULL;   //usar funcao destroi!!!!!!!
                return removido;
            }

            else{
                while(aux->prox != NULL){
                    aux = aux->prox;
                }
                elemento *ant = *l;
                while(ant->prox != aux){
                    ant = ant->prox;
                }
                dado_t removido = aux->dado;
                ant->prox = NULL;   //usar funcao destroi!!!!!!!
                return removido;
            }
        }
    }
}

