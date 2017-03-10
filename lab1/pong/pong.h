#ifndef _PONG_H
#define _PONG_H

#include <stdbool.h>
#include "geom.h"
#include "tela.h"

typedef struct {
	circulo cir;
	ponto velo;
	cor cor;
} bola;

typedef struct {
	retangulo ret;
	ponto velo;
	cor cor;
} raquete;

typedef struct {
	bola pelota;
	raquete raq[2];
	retangulo retSup;
	retangulo retInf;
	retangulo retEsquerdo;
	retangulo retDireito;
	int placar[2];
	bool fim; //Finaliza o game
} jogo;

jogo inicializa_jogo();
jogo mov_bola(jogo j);
jogo mov_raquete(jogo j, int raq);
jogo mov_raquetes(jogo j);
jogo trata_teclado(jogo j);
void desenha_jogo(jogo j);

#endif // _PONG_H
