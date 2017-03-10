#ifndef _TELA_H
#define _TELA_H

#include "geom.h"
#include <stdbool.h>

// tamanho da tela
#define TELA_LARG 4
#define TELA_ALT  3


// uma cor, com seus 3 componentes, entre 0 e 1
typedef struct {
    float r;                    // vermelho
    float g;                    // verde
    float b;                    // azul
} cor;

// dados sobre o rato
typedef struct {
    ponto posicao;		// posi��o atual do rato
    bool botao[5];		// estado atual dos bot�es do rato
    int mudou;			// n�mero do bot�o que mudou de estado (ou -1)
} rato;

// Inicializa o sistema da tela
//   deve ser chamado uma vez no inicio do programa, 
//   antes de qualquer outra funcao deste arquivo
void tela_inicializa(void);

// Finaliza o sistema da tela
//   deve ser chamado uma vez, logo antes do termino do programa
void tela_finaliza(void);


// Atualiza tela.
// Deve ser chamada para que o conte�do da tela reflita as ultimas alteracoes.
void tela_atualiza(void);

// limpa a tela toda com a cor de fundo
void tela_limpa(void);

// muda a cor atual
void tela_cor(cor c);

// muda a cor de fundo
void tela_cor_fundo(cor c);

// desenha uma linha da ponto p1 ate p2, na cor atual
void tela_linha(ponto p1, ponto p2);

// preenche um retangulo com a cor atual
void tela_retangulo(retangulo ret);

// desenha um circulo na cor atual
void tela_circulo(circulo circ);

/* escreve o texto s a partir da posicao pos da tela */
void tela_texto(ponto pos, char s[]);

/* descobre o estado do rato */
rato tela_rato(void);

/* descobre o estado do teclado */
// v � preenchido com o c�digo de at� 4 teclas que est�o apertadas
// retorna quantas dessas teclas foram apertadas desde a �ltima chamada
// a esta funcao. Essas teclas est�o no in�cio do vetor.
int tela_teclas_apertadas(int v[4]);

#endif				// _TELA_H
