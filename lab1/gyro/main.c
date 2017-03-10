#include "giro.h"
#include "tela.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#define CONS 1.6666666666666666

int main(){
   
  jogo j = inicializa_jogo();
  tela_inicializa();

   while(!j.fim){
    tela_limpa();

    if(j.vida == 0){
      j = trata_teclado(j);
      desenha_jogo(j);
      end_game(j);
      //printa_scores();
      tela_atualiza();
      //ranking(j.pont);
    }

    else {
    j.g.ang = tela_rato().posicao.x / CONS;
    
    j = spawna_bola(j);
    j = mov_bolas(j);
    desenha_jogo(j);
    }
    tela_atualiza();
    usleep(30000);
  }
  tela_finaliza();
  return 0; 
}