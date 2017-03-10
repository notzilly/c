#ifndef _GIRO_H
#define _GIRO_H

#include <stdbool.h>
#include "geom.h"
#include "tela.h"

typedef struct {
	circulo cir_azule, cir_amareloe, cir_verdee, cir_azuli, cir_amareloi, cir_verdei, cir_aux;
	float ang;
} giro;

typedef struct {
	circulo posicao;
	int rand_cor;
	bool real;
	ponto veloc;
	float graus;
} pelota;

typedef struct {
	giro g;
	pelota bola[5];
	int pont, vida;
	bool fim; //Finaliza o game
} jogo;

//void ranking(int pontuacao);
jogo aumenta_saude (jogo j, int cor, float s); 
jogo diminui_saude (jogo j, int cor, float s); 
bool colisao_cor (pelota bola, float ang1, float ang2, int x);
jogo inicializa_jogo();
float rad_graus(ponto p, ponto g);
jogo trata_teclado(jogo j);
void desenha_giro(giro g);
void desenha_jogo(jogo j);
jogo mov_bolas(jogo j);
jogo spawna_bola(jogo j);
int retorna_cor(pelota bola, jogo j);
void end_game();
//void printa_scores();

#endif // _GIRO_H
