#include "lista2.h"
#include "tela.h"
#include "texto.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// adiciona o conteúdo do arquivo chamado nome após a posicao corrente
// da lista l. A posição corrente passa a ser a que contém a última linha lida.
// retorna true se ok, false se nao.
// l deve ser uma lista inicializada.
// linhas com mais de 1234 caracteres no arquivo de entrada serao quebradas
//   (como esse bug poderia ser corrigido?)
bool adic_arq(lista2 *l, char *nome){
    FILE *f;

    f = fopen(nome, "rt");
    if (f == NULL) return false;

    char s[1235];

    while (fgets(s, 1235, f) != NULL) {
        int n = strlen(s);
        // remove o \n do final da linha
        if (s[n] == '\n') s[n] = '\0';
        // strdup aloca memoria e copia a sring
        lista_insere_apos(l, strdup(s));
    }
    fclose(f);
    return true;
}

bool cria_arq(lista2 *l, char *nome){
    FILE *f;

    f = fopen(nome, "w");
    if (f == NULL) return false;

    char *s = strdup("");

    while(l->corr != NULL){
        strcpy(s, lista_corrente(l));
        fprintf(f, "%s\n", s);
        if(!lista_avanca(l)){break;}
    }
    fclose(f);
    return true;
}

int main(){
    int t=0;
    bool fim = false;

    tela_inicia();

    texto* tx1 = texto_cria();
    lista2* lista1 = lista_cria();
    tx1->text = lista1;
    tx1->cursorCol = 0;
    tx1->cursorLin = 0;
    tx1->linhainitela = 0;
    tx1->colunainitela = 0;
    tx1->insertion = true;

    lista_insere_apos(tx1->text, strdup(""));

    while(!fim) {
        char *read = strdup("");
        char text1[100];
        char text2[100];

        tela_limpa();
        tela_desenha(tx1);
        tela_lincol(tx1->cursorLin, tx1->cursorCol);   //desenho do cursor

        tela_atualiza();
        switch(t=tela_tecla()) {
            case voltalin: recua_linha(tx1); break;    //^
            case voltacol: recua_cursor(tx1);  break;   // <
            case avancalin: avanca_linha(tx1); break;  // \/
            case avancacol: avanca_cursor(tx1); break;  // >
            case voltapag: recua_pagina(tx1); break;  //pageup
            case avancapag: avanca_pagina(tx1); break;  //pagedown
            case col0: recua_inilinha(tx1); break;  //home
            case coln: avanca_finallinha(tx1); break; //end
            case enter: quebra_linha(tx1); break; //enter
            case 32: if(tx1->insertion) {insere_caracter(tx1, t); break;}  //espaço
                            else if(!tx1->insertion) {substitui_caracter(tx1, t); break;}
            case insere: muda_modo(tx1); break;   //insert
            case retorna: remove_caracter_ant(tx1); break; //backspace
            case apaga: remove_caracter_corr(tx1); break; //delete
            case termina: fim = true; break;   //f1
            case le: tela_lincol(22, 30);   //f6
                        tela_cor(azul, branco);
                        sprintf(text1, "%s", "Digite o nome do arquivo que deseja abrir: ");
                        tela_texto(text1);
                        tela_atualiza();
                        scanf("%s", read);
                        if(!adic_arq(tx1->text, read)){exit(1);}
                        else{tela_limpa(); avanca_pagina(tx1); break;}
            case grava: tela_lincol(22, 30);      //f5
                        tela_cor(azul, branco);
                        sprintf(text2, "%s", "Para salvar, digite o nome do novo arquivo: ");
                        tela_texto(text2);
                        tela_atualiza();
                        scanf("%s", read);
                        tx1->cursorCol = 0;
                        lista_inicio(tx1->text);
                        if(!cria_arq(tx1->text, read)){exit(1);}
                        else{tela_limpa(); avanca_pagina(tx1); break;}
            default: if((isalnum(t) || ispunct(t)) && tx1->insertion) {insere_caracter(tx1, t); break;}   //caracteres, numeros e simbolos de pontuacao
                            else if((isalnum(t) || ispunct(t)) && !tx1->insertion) {substitui_caracter(tx1, t); break;}
        }
    }
    lista_destroi(tx1->text);
    tela_termina();
    return 0;
}
