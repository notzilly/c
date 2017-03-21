#ifndef _DUPLAM_ENC_H_
#define _DUPLAM_ENC_H_

//definicao da estrutura lista
typedef struct lista Lista;

//inicializa a lista duplamente encadeada
Lista* inicia_lista();

//insere no inicio de uma lista duplamente encadeada circular
Lista* insere_duplamente(Lista* l, int d);

//printa lista circular duplamente encadeada
void printa_circular(Lista* l);

#endif // _DUPLAM_ENC_H_
