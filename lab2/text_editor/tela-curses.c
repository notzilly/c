#include "tela.h"
#include "texto.h"
#include <curses.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// devem estar na mesma ordem da definicao de cores do .h
int cores[] = {COLOR_BLACK, COLOR_WHITE, COLOR_BLUE, COLOR_RED, COLOR_GREEN};

//desenha toda a tela
void tela_desenha(texto* tx)
{
    //desenhav3
    int origLine = tx->cursorLin;

    vaipralinha(tx, tx->linhainitela);

    int i, j = 0;
    if(tx->linhainitela == 0 && num_linhas(tx->text) == 1){
        dado_t s = lista_corrente(tx->text);
        tela_lincol(0, 0);
        tela_cor(preto, branco);
        tela_texto(s);
    }
    else{
        for(i = tx->linhainitela; i < tela_numlin(); i++){
            dado_t s = lista_corrente(tx->text);
            tela_lincol(j, 0);
            tela_cor(preto, branco);
            tela_texto(s);
            avanca_linha(tx);
            j++;
            if(tx->text->corr->prox == NULL){
                dado_t s = lista_corrente(tx->text);
                tela_lincol(j, 0);
                tela_cor(preto, branco);
                tela_texto(s);
                j++;
                break;
            }
        }
    }

    vaipralinha(tx, origLine);
    tela_lincol(tx->cursorLin, tx->cursorCol);


    //desenha v2
    /*int origLine = tx->cursorLin;
    int iniDraw = 0;
    while(origLine > tela_numlin()){
        iniDraw++;
    }
    while(origLine <= tela_numlin()){
        iniDraw--;
    }

    int i;
    for(i = iniDraw; i < tela_numlin(); i++){
        if(tx->text->corr != NULL){
            if(iniDraw > 0){}
            dado_t s = lista_corrente(tx->text);
            tela_lincol(i, 0);
            tela_cor(preto, branco);
            tela_texto(s);
            avanca_linha(tx);
            lista_avanca(tx->text);
        }
        vaipralinha(tx, origLine);
        tela_lincol(tx->cursorCol, tx->cursorLin);
    }*/

    //desenha v1
    /*int i;
    elemento* aux = tx->text->prim;

    int numElemLista = tela_numlin();

    for(i = 0; i < numElemLista; i++)
    {
        if(aux != NULL)
        {
            tela_lincol(i, 0);
            tela_cor(preto, branco);
            char *s = malloc(strlen(aux->line) + 1);
            strcpy(s, aux->line);
            //s = lista_corrente(tx->text);
            tela_texto(s);
            aux = aux->prox;
        }
    }*/

    /*while(tx->cursorLin > tela_numlin() - 2){
        //avanca_lin
        lista_avanca(tx->text);
        tx->cursorLin--;
        tx->linhainitela++;
    }*/
}

void tela_inicia(void)
{
    initscr();
    noecho();  // os caracteres teclados nao aparecem na tela
    keypad(stdscr, true); // interpreta caracteres de controle

    start_color();
    cor f, l;
    for (f=preto; f<=verde; f++)
        for (l=preto; l<=verde; l++)
            if (f != preto || l != preto)
                // o "5" na linha abaixo é o número de cores
                init_pair(f*5+l, cores[l], cores[f]);
}

void tela_termina(void)
{
    endwin();
}

void tela_atualiza(void)
{
    refresh();
}

void tela_limpa(void)
{
    erase();
}

void tela_lincol(int l, int c)
{
    move(l, c);
}

void tela_texto(char *s)
{
    printw("%s", s);
}

int tela_numlin(void)
{
    return LINES;
}

int tela_numcol(void)
{
    return COLS;
}

void tela_cor(cor fundo, cor texto)
{
    // o "5" na linha abaixo é o número de cores
    attron(COLOR_PAIR(fundo*5+texto));
}

tecla tela_tecla(void)
{
    int c;

    c = getch();
    if (isprint(c)) return c;
    switch (c)
    {
    case KEY_LEFT:
        return voltacol;
    case KEY_RIGHT:
        return avancacol;
    case KEY_UP:
        return voltalin;
    case KEY_DOWN:
        return avancalin;
    case KEY_PPAGE:
        return voltapag;
    case KEY_NPAGE:
        return avancapag;
    case KEY_HOME:
        return col0;
    case KEY_END:
        return coln;
    case KEY_IC:
        return insere;
    case KEY_DC:
        return apaga;
    case KEY_BACKSPACE:
        return retorna;
    case KEY_ENTER:
        return enter;
    case '\n':
        return enter;
    case KEY_F(1):
        return termina;
    case KEY_F(5):
        return grava;
    case KEY_F(6):
        return le;
    //case ' ': return espaco;
    default:
        beep();
    }
    return 0;
}
