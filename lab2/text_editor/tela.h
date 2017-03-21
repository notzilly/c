#ifndef _TELA_H_
#define _TELA_H_

#include <curses.h>
#include "texto.h"

// uma cor (nao tem muitas...)
typedef enum {
  preto,
  branco,
  azul,
  vermelho,
  verde
} cor;

// um caractere digitado
// (pode ser um caractere imprimível ou um dos de controle listados abaixo)
typedef enum {
  voltacol = 256,
  avancacol,
  voltalin,
  avancalin,
  voltapag,
  avancapag,
  col0,
  coln,
  insere,
  apaga,
  retorna,
  enter,
  termina,
  grava,
  le
} tecla;

//desenha as strings da lista tx->text na tela
void tela_desenha(texto* tx);

// inicializa a tela - deve ser chamado antes de outra função de tela
void tela_inicia(void);

// finaliza a tela - deve ser chamado quando nao for mais usar as funcoes de
//   tela, antes de terminar o programa
void tela_termina(void);

// atualiza a tela para refletir os ultimos comandos enviados para ela
// sem isso, o conteudo da tela nao é alterado
void tela_atualiza(void);

// apaga todo o conteúdo da tela (preenche toda a tela com espaços)
void tela_limpa(void);

// posiciona o cursor (o proximo texto sera escrito nessa posição)
void tela_lincol(int l, int c);

// retorna o numero de linhas da tela
int tela_numlin(void);

// retorna o numero de colunas da tela
int tela_numcol(void);

// escolhe a cor em que o texto será escrito
void tela_cor(cor fundo, cor texto);

// escreve a string s na posicao do cursor, com a última cor escolhida
void tela_texto(char *s);

// retorna a tecla apertada
// (espera até que alguma tecla seja apertada, se necessario)
tecla tela_tecla(void);


#endif // _TELA_H_
