#include "pong.h"
#include "tela.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main(){
   
  jogo j = inicializa_jogo();
  tela_inicializa();

   while(!j.fim){
    
    //Testa Placar
    if(j.placar[0] >= 11 || j.placar[1] >= 11){
      //j.fim = true;
      j.placar[0] = 0; j.placar[1] = 0;
    }

    j = trata_teclado(j);
    j = mov_raquetes(j);
    j = mov_bola(j);
    desenha_jogo(j);
    tela_atualiza();
    usleep(30000);
  }
  tela_finaliza();
  return 0; 
}