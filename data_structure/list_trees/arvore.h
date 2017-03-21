#ifndef _ARVORE_H_
#define _ARVORE_H_

typedef struct arv arv;

//cria e inicializa arvore com subarvores
arv* cria_no(int dado, arv* esquerda, arv* direita);

//printa arvore estilo E-R-D
void printaERD(arv* arvore);

#endif // _ARVORE_H_
