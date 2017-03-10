#include <stdbool.h>
#include <stdio.h>
#include <unistd.h> 
#include "pong.h"
#include "geom.h"
#include "tela.h"

#define VBX -0.05
#define VBY 0.07

static cor roxo =      {255, 0.0, 255};
static cor branco =    {1.0, 1.0, 1.0};
static cor preto =     {0.0, 0.0, 0.0};
static cor verde =     {0.0, 1.0, 0.0};
static cor azul =      {0.0, 0.3, 0.9};
static cor amarelo =   {0.7, 0.7, 0.0};
static cor vermelho =  {1.0, 0.0, 0.0};

static ponto placar[2] = { {1.0, 0.08}, {3, 0.08} }, _dis = {0.7, 2.9};

jogo inicializa_jogo(void) 
{
  jogo j;
  j.pelota.cir.centro.x = 2.0, j.pelota.cir.centro.y = 1.5;
  j.pelota.velo.x = VBX, j.pelota.velo.y = VBY;
  j.pelota.cir.raio = 0.08;
  j.pelota.cor = branco;

  j.raq[0].ret.cse.x = 0.25, j.raq[0].ret.cse.y = 1.0;
  j.raq[0].ret.cid.x = 0.35, j.raq[0].ret.cid.y = 2.0;
  j.raq[0].velo.x = 0.0, j.raq[0].velo.y = 0.0;
  j.raq[0].cor = roxo;

  j.raq[1].ret.cse.x = 3.65, j.raq[1].ret.cse.y = 1.0;
  j.raq[1].ret.cid.x = 3.75, j.raq[1].ret.cid.y = 2.0;
  j.raq[1].velo.x = 0.0, j.raq[1].velo.y = 0.0;
  j.raq[1].cor = roxo;

  j.retSup.cse.x = 0.00, j.retSup.cse.y = 0.0;
  j.retSup.cid.x = 4.00, j.retSup.cid.y = 0.2;

  j.retInf.cse.x = 0.00, j.retInf.cse.y = 2.8;
  j.retInf.cid.x = 4.00, j.retInf.cid.y = 3.0;

  j.retEsquerdo.cse.x = 0.00, j.retEsquerdo.cse.y = 0.2;
  j.retEsquerdo.cid.x = 0.10, j.retEsquerdo.cid.y = 2.9;

  j.retDireito.cse.x = 3.90, j.retDireito.cse.y = 0.2;
  j.retDireito.cid.x = 4.00, j.retDireito.cid.y = 2.9;

  j.placar[0] = 0, j.placar[1] = 0;

  j.fim = false;
  return j;
}

jogo saque_jogo(jogo j, int raque) 
{
  j.pelota.cir.centro.x = 2.0, j.pelota.cir.centro.y = 1.5;

  if(raque == 0)
  {
    j.pelota.velo.x = VBX, j.pelota.velo.y = VBY;
  }
  else
  {
    j.pelota.velo.x = -VBX, j.pelota.velo.y = -VBY;
  }

  j.raq[0].ret.cse.x = 0.25, j.raq[0].ret.cse.y = 1.0;
  j.raq[0].ret.cid.x = 0.35, j.raq[0].ret.cid.y = 2.0;
  j.raq[0].velo.x = 0.0, j.raq[0].velo.y = 0.0;
  j.raq[1].ret.cse.x = 3.65, j.raq[1].ret.cse.y = 1.0;
  j.raq[1].ret.cid.x = 3.75, j.raq[1].ret.cid.y = 2.0;
  j.raq[1].velo.x = 0.0, j.raq[1].velo.y = 0.0;

  return j;
}

jogo mov_bola(jogo j)
{
  j.pelota.cir = movC(j.pelota.cir, j.pelota.velo);
  int i;

  for(i = 0; i < 2; i++)
  {
    //Bola e Raquete
    if(colisaoCR(j.pelota.cir, j.raq[i].ret)) 
    {

      if(i == 0)
        j.pelota.velo.x -= 0.015;
      else
        j.pelota.velo.x += 0.015;



      j.pelota.velo.x *= (-1) ;
    }
  }

  if(colisaoCR(j.pelota.cir, j.retSup) || colisaoCR(j.pelota.cir, j.retInf)) 
  { // Bola ~> Top e Bottom
    j.pelota.velo.y *= (-1);
  }

  if(colisaoCR(j.pelota.cir, j.retEsquerdo)) // Bola ~> Left
  {
    j.placar[1]++;
    j = saque_jogo(j, 1);
  }
  else if(colisaoCR(j.pelota.cir, j.retDireito)) // Bola ~> Right
  {
    j.placar[0]++;
    j = saque_jogo(j, 0);
  }
  return j;
}


jogo mov_raquete(jogo j, int raq)
{
  j.raq[raq].ret = movR(j.raq[raq].ret, j.raq[raq].velo);

  if(colisaoRR(j.retSup, j.raq[raq].ret)) //-- COLISAO SUPERIOR --//
  {    
    j.raq[raq].velo.y = 0.0;
    j.raq[raq].ret.cse.y = j.retSup.cid.y;
    j.raq[raq].ret.cid.y = j.retSup.cid.y+1;
  }
  if(colisaoRR(j.raq[raq].ret, j.retInf)) //-- COLISAO INFERIOR --//
  {
    j.raq[raq].velo.y = 0.0;
    j.raq[raq].ret.cse.y = j.retInf.cse.y-1;
    j.raq[raq].ret.cid.y = j.retInf.cse.y;
  }

  return j;
}

// movimenta as raquetes
jogo mov_raquetes(jogo j)
{
  j = mov_raquete(j, 0);
  j = mov_raquete(j, 1);
  return j;
}

jogo trata_teclado(jogo j)
{
  int tec[4], i;
  if(tela_teclas_apertadas(tec) > 0)
  {
    if(tec[0] == 'b') {j.fim = true;}
    for(i = 0; i < 4; i++)
    {
      switch(tec[i])
      {
        case 'a': j.raq[0].velo.y = 0.0; break;
        case 'k': j.raq[1].velo.y = 0.0; break;
        case 'q': j.raq[0].velo.y -= 0.035; break;
        case 'o': j.raq[1].velo.y -= 0.035; break;
        case 'z': j.raq[0].velo.y += 0.035; break;
        case 'm': j.raq[1].velo.y += 0.035; break;
        case 'v': j = inicializa_jogo(); break;
      }
    }
  }
  return j;
}


void desenha_jogo(jogo j)
{
  char temp[32];

  tela_limpa();

  tela_cor(vermelho);
  tela_retangulo(j.retEsquerdo);
  tela_retangulo(j.retDireito);
  
  tela_cor(azul);
  tela_retangulo(j.retSup);
  tela_retangulo(j.retInf);

  tela_cor(j.raq[0].cor);
  tela_retangulo(j.raq[0].ret);

  tela_cor(j.raq[1].cor);
  tela_retangulo(j.raq[1].ret);

  tela_cor(branco);
  tela_circulo(j.pelota.cir);

  tela_cor(branco);
  sprintf(temp, "%02d", j.placar[0]);
  tela_texto(placar[0], temp);
  sprintf(temp, "%02d", j.placar[1]);
  tela_texto(placar[1], temp);

  tela_texto(_dis, "Controle Jogador 1: (Q,A,Z)   \"B\" P/ SAIR!   Controle Jogador 2 (O,K,M)");
}