#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef enum{desconhecido, calculando, calculado} estado_t ;

/*struct arv{
    char *chave;
    char *formula;
    double valor;
    estado_t estado;
    arv *esq;
    arv *dir;
};*/

arv* rotEsq(arv *arvore){ //rotacao a esquerda
    arv* aux1;
    arv* aux2;
    aux1 = arvore->dir;
    aux2 = aux1->esq;
    aux1->esq = arvore;
    arvore->dir = aux2;
    arvore = aux1;
    return arvore;
}

arv* rotDir(arv *arvore){ //rotacao a direita
    arv* aux1;
    arv* aux2;
    aux1 = arvore->esq;
    aux2 = aux1->dir;
    aux1->dir = arvore;
    arvore->esq = aux2;
    arvore = aux1;
    return arvore;
}

int maxDepth(arv* arvore){
   if (!arvore) return 0;
   else{
       int esqDepth = maxDepth(arvore->esq);
       int dirDepth = maxDepth(arvore->dir);

       /* use the larger one */
       if (esqDepth > dirDepth)
           return(esqDepth + 1);
       else return(dirDepth + 1);
   }
}

int fatorBal(arv* arvore){ // retorna a dif de altura esq - dir dos filhos
    int he, hd;

    if(arvore->esq != NULL) he = maxDepth(arvore->esq);     //he = arvore->esq->altura;
    else he = 0;
    if(arvore->dir != NULL) hd = maxDepth(arvore->dir);
    else hd = 0;
    return he - hd;
}

void printaERD(arv *arvore){
    arv* copy = arvore;
    if(copy == NULL) return;
    printaERD(copy->esq);
    printf("%s: ", copy->chave);
    printf("%d  ", copy->altura);
    printaERD(copy->dir);
}

void printaSTR(arv *arvore){ //printa no esquema (raiz, esq, dir)
    arv* copy = arvore;
    if(copy == NULL) return;
    if(copy->esq == NULL && copy->dir == NULL) {printf("%s", copy->chave); return;}
    printf("(");
    printf("%s", copy->chave);
    printf(", ");
    printaSTR(copy->esq);
    if(copy->esq == NULL) printf("/");
    printf(", ");
    printaSTR(copy->dir);
    if(copy->dir == NULL) printf("/");
    printf(")");
}

int arv_altura(arv *arvore){   // retorna a altura da árvore
    arv* copy = arvore;
    if (!copy) return -1; // altura de árvore vazia é -1
    else{
        int he = arv_altura(copy->esq);
        int hd = arv_altura(copy->dir);
        if (he < hd) return hd + 1;
        else return he + 1;
   }
}

void arv_calc_altura(arv *arvore){   // recalcula a altura da árvore (chamando a função anterior pra cada filho)
    arv* copy = arvore;
    if(!copy) return;
    arv_calc_altura(copy->esq);
    copy->altura = arv_altura(copy);
    arv_calc_altura(copy->dir);
}

arv* arv_maior_valor(arv **arvore){ //retorna o no de maior valor da arvore passada
    arv* aux = *arvore;
    if(!aux) return NULL;
    if(aux->dir != NULL){
       return arv_maior_valor(&(aux->dir));
    }
    else{
       if((*arvore)->esq != NULL)
          *arvore = (*arvore)->esq;
       else
          *arvore = NULL;
       return aux;
       }
}

arv* arv_menor_valor(arv *arvore){
    arv* aux = arvore;
    if(!aux) return NULL; //arvore vazia
    if(aux->esq != NULL){
        return arv_menor_valor(aux->esq);
    }
    else return aux;
}

arv* arv_cria_no(char *chave, arv* esquerda, arv* direita){
    arv* novo = malloc(sizeof(arv));
    if(novo){
        novo->esq = malloc(sizeof(arv));
        novo->dir = malloc(sizeof(arv));

        novo->chave = strdup(chave);
        novo->esq = esquerda;
        novo->dir = direita;
        return novo;
    }
    else{printf("Erro na alocacao de nos!!\n"); exit(EXIT_FAILURE);}
}

arv* arv_busca(arv *a, char *chave){   //retorna o nó com a chave caso encontrar, senao retorna NULL
    arv* aux = a;
    if(aux == NULL) return NULL;
    int cmp = strcmp(chave, aux->chave);

    if(cmp == 0){  //chave = copy->chave
        return aux;
    }
    else if(cmp > 0){
        return arv_busca(aux->dir, chave);
    }
    else if(cmp < 0){
        return arv_busca(aux->esq, chave);
    }
}

arv *arv_busca_prox(arv *a, char *chave){
    static arv* dad = NULL;

    if(!a) return NULL;
    if(chave == NULL) return arv_menor_valor(a);

    arv* aux = a;
    if(aux == NULL) return NULL;
    int cmp = strcmp(chave, aux->chave);

    if(cmp == 0){  //chave = copy->chave
        if(aux->dir != NULL) return arv_menor_valor(aux->dir);
        else return dad;
    }
    else if(cmp > 0){
        return arv_busca_prox(aux->dir, chave);
    }
    else if(cmp < 0){
        dad = a;
        return arv_busca_prox(aux->esq, chave);
    }
}

arv* arv_insere(arv **a, char *chave){
    arv* aux = *a;
    if(!aux){
        aux = arv_cria_no(chave, NULL, NULL);
        if(*a == NULL) *a = aux;
    }
    int cmp = strcmp(chave, aux->chave);
    if(cmp < 0){
        arv_insere(&(aux->esq), chave);
    }
    else if(cmp > 0){
        arv_insere(&(aux->dir), chave);
    }
    else if(cmp == 0){
        return NULL;
    }
    arv_calc_altura(aux);
    int fat = fatorBal(aux);
    if(fat > 1){
        if(aux->esq){
            if(fatorBal(aux->esq) == -1) aux->esq = rotEsq(aux->esq);
            *a = rotDir(aux);
        }
    }
    else if(fat < -1){
        if(aux->dir){
            if(fatorBal(aux->dir) == +1) aux->dir =  rotDir(aux->dir);
            *a = rotEsq(aux);
        }
    }
}

void arv_remove(arv **a, char *chave){ //remove o nó. se nao existir nao faz nada
    arv* aux = *a;
    if(!aux) return;  //arvore vazia ou nao achou a chave

    int cmp = strcmp(chave, aux->chave);
    if(cmp < 0){
        arv_remove(&(aux->esq), chave);
    }
    else if(cmp > 0){
        arv_remove(&(aux->dir), chave);
    }
    else if(cmp == 0){
        if(aux->esq == NULL && aux->dir == NULL){   //folha
            free(*a);
            *a = NULL;
            return;
        }
        else if(aux->esq != NULL && aux->dir == NULL){  //só tem o filho esquerdo
            (*a) = (*a)->esq;
            aux->esq = NULL;
            free(aux);
            aux = NULL;
            return;
        }
        else if(aux->esq == NULL && aux->dir != NULL){  //só tem o filho direito
            (*a) = (*a)->dir;
            aux->dir = NULL;
            free(aux);
            aux = NULL;
            return;
        }
        else if(aux->esq != NULL && aux->dir != NULL){  //tem os dois filhos
            aux = arv_maior_valor(&(*a)->esq);
            if(aux == (*a)->esq){
                aux->dir = (*a)->dir;
            }
            else{
                aux->esq = (*a)->esq;
                aux->dir = (*a)->dir;
            }
            (*a)->esq = (*a)->dir = NULL;
            free(*a);
            *a = aux;
            aux = NULL;
            arv_calc_altura(*a);
            return;
        }
    }
    arv_calc_altura(aux);
    int fat = fatorBal(aux);
    if(fat > 1){
        if(aux->esq){
            if(fatorBal(aux->esq) == -1) aux->esq = rotEsq(aux->esq);
            *a = rotDir(aux);
        }
    }
    else if(fat < -1){
        if(aux->dir){
            if(fatorBal(aux->dir) == +1) aux->dir = rotDir(aux->dir);
            *a = rotEsq(aux);
        }
    }
}
