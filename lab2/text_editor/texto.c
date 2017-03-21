#include "texto.h"
#include "lista2.h"
#include "tela.h"
#include "cadeia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//cria texto  100%
texto* texto_cria(void){
    texto* tx = malloc(sizeof(texto));
    return tx;
}

//recua uma coluna, se possivel  100%
void recua_cursor(texto *tx){
    if(tx->cursorCol > 0){tx->cursorCol--;}
    else{return;}
}

//avanca uma coluna, se possivel   100%
void avanca_cursor(texto *tx){
    if(tx->cursorCol < tela_numcol()){tx->cursorCol++;}
    else{avanca_iniproxlinha(tx);}
}

//volta uma linha, se possivel e mantem-se na mesma coluna 100%
void recua_linha(texto *tx){
    if(lista_recua(tx->text) && tx->cursorLin > 0){tx->cursorLin--;}
    return;
}

//avanca uma linha, se possivel e mantem-se na mesma coluna 100%
void avanca_linha(texto *tx){
    if(lista_avanca(tx->text)){tx->cursorLin++;}
    return;
}

//recua ate a primeira linha do texto, mantendo a coluna 100%
void recua_pagina(texto *tx){
    lista_inicio(tx->text);
    tx->cursorLin = 0;
    return;
}

//avanca ate a ultima linha do texto, mantendo a coluna 100%
void avanca_pagina(texto *tx){
    lista_fim(tx->text);
    tx->cursorLin = num_linhas(tx->text) - 1;
    return;
}

//recua o cursor para o inicio da linha 100%
void recua_inilinha(texto *tx){
    tx->cursorCol = 0;
}

//avanca pro final da linha  100%
void avanca_finallinha(texto *tx){
    dado_t copy = lista_corrente(tx->text);
    tx->cursorCol = strlen(copy);
}

//avanca o cursor para o inicio da prox linha 100%
void avanca_iniproxlinha(texto *tx){
    if(lista_avanca(tx->text)){
        tx->cursorCol = 0;
        tx->cursorLin++;
    }
    else{
        dado_t s = malloc(strlen("") + 1);
        strcpy(s, "");
        lista_insere_apos(tx->text, s);
        tx->cursorCol = 0;
        tx->cursorLin++;
    }
}

//quebra a linha 100%
void quebra_linha(texto *tx){
    dado_t copy = lista_corrente(tx->text);
    int strSize = strlen(copy);

    if(tx->cursorCol >= strSize){
        dado_t s = malloc(strlen("") + 1);
        strcpy(s, "");
        lista_insere_apos(tx->text, s);
        tx->cursorCol = 0;
        tx->cursorLin++;
    }
    else{
        dado_t s;
        int p = tx->cursorCol;
        if(p == 0){
            s = malloc(strlen("") + 1);
            strcpy(s, "");
            lista_insere_antes(tx->text, s);

            lista_avanca(tx->text);
            tx->cursorCol = 0;
            tx->cursorLin++;
        }
        else{
            dado_t newOne;
            cad_quebra(&copy, p, &newOne);
            lista_insere_apos(tx->text, newOne);
            tx->cursorCol = 0;
            tx->cursorLin++;
        }
    }
}

//altera modo de escrita 100%
void muda_modo(texto *tx){
    if(tx->insertion){
        tx->insertion = false;
        return;
    }
   else if(!tx->insertion){
        tx->insertion = true;
        return;
    }
}

//insere na posicao atual do cursor 100%
void insere_caracter(texto *tx, char tecla){
    dado_t copy = lista_corrente(tx->text);
    cad_ins(&copy, tx->cursorCol, tecla);
    lista_substitui(tx->text, copy);
    tx->cursorCol++;
}

//substitui caracter da posicao atual do cursor 100%
void substitui_caracter(texto *tx, char tecla){
    dado_t copy = lista_corrente(tx->text);
    cad_subst(&copy, tx->cursorCol, tecla);
    lista_substitui(tx->text, copy);
    tx->cursorCol++;
}

//remove o caracter da posicao atual do cursor 100%
void remove_caracter_corr(texto *tx){
    dado_t copy = lista_corrente(tx->text);
    int p = strlen(copy);

    if(tx->cursorCol > p - 1 && tx->text->corr->prox != NULL){  //gruda
        lista_avanca(tx->text);
        dado_t s2 = lista_remove(tx->text);

        if(tx->text->corr != tx->text->ult){lista_recua(tx->text);}

        int differ = tx->cursorCol - p;
        if(differ > 0){
            cad_ajusta(&copy, p + differ);
            lista_substitui(tx->text, copy);
        }
        cad_gruda(&copy, &s2);
        lista_substitui(tx->text, copy);
    }
    else if(tx->cursorCol <= p - 1 && tx->cursorCol > -1){
        cad_rem(&copy, tx->cursorCol);
        lista_substitui(tx->text, copy);
    }
    else{return;}
}

//remove o caracter anterior ao cursor 100%
void remove_caracter_ant(texto *tx){
    if(tx->cursorCol == 0 && tx->cursorLin == 0){return;}
    else{
        dado_t copy = lista_corrente(tx->text);
        int p = strlen(copy);

        if(tx->cursorCol > p && tx->text->corr->prox != NULL){
            recua_cursor(tx);
            return;
        }
        else if(tx->cursorCol <= p && tx->cursorCol > 0){
            cad_rem(&copy, tx->cursorCol - 1);
            recua_cursor(tx);
            return;
        }
        else if(tx->cursorCol == 0 && tx->text->corr->ant != NULL){
            lista_recua(tx->text);
            dado_t copy2 = lista_corrente(tx->text);
            int p2 = strlen(copy2);
            cad_gruda(&copy2, &copy);
            lista_substitui(tx->text, copy2);
            tx->cursorLin--;
            tx->cursorCol = p2;

            if(lista_avanca(tx->text)){
                lista_remove(tx->text);
                if(tx->text->corr->prox != NULL)
                lista_recua(tx->text);
            }
            return;
        }
    }
}

//vai pra linha l
void vaipralinha(texto *tx, int l){
    while(tx->cursorLin > l){recua_linha(tx);}
    while(tx->cursorLin < l){avanca_linha(tx);}
    return;
}

