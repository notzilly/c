#ifndef _TEXTO_H_
#define _TEXTO_H_
#include "lista2.h"

typedef struct texto texto;

//tralhas que o texto tem
struct texto{
    lista2* text;
    int cursorLin;
    int cursorCol;
    int linhainitela;
    int colunainitela;
    bool insertion;   //true = modo de insercao / false = modo de substituicao
};

//cria texto
texto* texto_cria(void);

//recua uma coluna, se possivel
void recua_cursor(texto *tx);

//avanca uma coluna, se possivel
void avanca_cursor(texto *tx);

//volta uma linha, se possivel e mantem-se na mesma coluna
void recua_linha(texto *tx);

//avanca uma linha, se possivel e mantem-se na mesma coluna
void avanca_linha(texto *tx);

//recua ate a primeira linha do texto, mantendo a coluna
void recua_pagina(texto *tx);

//avanca ate a ultima linha do texto, mantendo a coluna
void avanca_pagina(texto *tx);

//recua o cursor para o inicio da linha
void recua_inilinha(texto *tx);

//avanca pro final da linha
void avanca_finallinha(texto *tx);

//avanca o cursor para o inicio da prox linha
void avanca_iniproxlinha(texto *tx);

//quebra a linha
void quebra_linha(texto *tx);

//altera modo de escrita
void muda_modo(texto *tx);

//insere na posicao atual do cursor
void insere_caracter(texto *tx, char tecla);

//substitui caracter da posicao atual do cursor
void substitui_caracter(texto *tx, char tecla);

//remove o caracter da posicao atual do cursor
void remove_caracter_corr(texto *tx);

//remove o caracter anterior ao cursor
void remove_caracter_ant(texto *tx);

//vai pra linha l
void vaipralinha(texto *tx, int l);

#endif // _TEXTO_H_
