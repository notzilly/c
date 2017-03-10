#include "tela.h"
#include "giro.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

cor azuli = {0, 0, 1};		    //Azul Interno
cor azule = { 0, 0.3, 0.9 };		//Azul Externo
cor amareloi = {1, 1, 0};		    //Amarelo Interno
cor amareloe = { 0.5, 0.6, 0 };	//Amarelo Externo
cor verdei = {0, 1, 0};		    //Verde Interno
cor verdee = {0, 0.3, 0};		    //Verde Externo
cor branco = {1, 1, 1};           //Branco
cor vermelho = { 1, 0, 0 };		//Vermelho

ponto placar = {2.3, 0.04}, dvida = {2.3, 0.11};
ponto endgame[4] = { {1.2, 0.7}, {1.2, 0.9}, {1.2, 1.1}, {1.2, 1.3}};
ponto ranking[12] = {{2.1, 1.5}, {2.1, 1.6}, {2.1, 1.7}, {2.1, 1.8}, {2.1, 1.9}, {2.1, 2.0}, {2.1, 2.1},
					{2.1, 2.2}, {2.1, 2.3}, {2.1, 2.4}, {2.1, 2.5}, {2.1, 2.6}};

jogo inicializa_jogo(void) //inicializa as variaveis de estrutura do jogo
{
  jogo j;
  j.g.cir_aux.centro.x = 1.5, j.g.cir_aux.centro.y = 2.0, j.g.cir_aux.raio = 0.5;

  j.g.cir_azuli.centro.x = 1.5, j.g.cir_azuli.centro.y = 2.0, j.g.cir_azuli.raio = 0.5;
  j.g.cir_azule.centro.x = 1.5, j.g.cir_azule.centro.y = 2.0, j.g.cir_azule.raio = 0.5;

  j.g.cir_amareloi.centro.x = 1.5, j.g.cir_amareloi.centro.y = 2.0, j.g.cir_amareloi.raio = 0.5;
  j.g.cir_amareloe.centro.x = 1.5, j.g.cir_amareloe.centro.y = 2.0, j.g.cir_amareloe.raio = 0.5;

  j.g.cir_verdei.centro.x = 1.5, j.g.cir_verdei.centro.y = 2.0, j.g.cir_verdei.raio = 0.5;
  j.g.cir_verdee.centro.x = 1.5, j.g.cir_verdee.centro.y = 2.0, j.g.cir_verdee.raio = 0.5;

  j.pont = 0;
  j.vida = 3;

  j.fim = false;
  srand(time(NULL));
  return j;
}

jogo trata_teclado(jogo j)
{
  int tec[4], i;
  if(tela_teclas_apertadas(tec) > 0)
  {
    for(i = 0; i < 4; i++)
    {
      switch(tec[i])
      {
        case 'r': j = inicializa_jogo(); break;
        case 'e': j.fim = true;
      }
    }
  }
  return j;
}

//tentamos resolver a parte dos arquivos, mas não conseguimos (infelizmente)
/*void printa_scores(void){
	FILE *Arq;
	char aux[1000], aux2[1000];
	char nome[4];
	int pont, i;
	Arq = fopen("ranking.txt", "r");

	if(Arq == NULL){
	}
	else {
		tela_cor(branco);
		tela_texto(ranking[0], "    Ranking:");

		while(fgets(aux, 1000, Arq) != NULL){

				tela_cor(branco);
				//sprintf(aux2, "%s\n", aux);
				tela_texto(ranking[1], aux);

		}
	}
	fclose(Arq);
}

void ranking(int pontuacao){
  FILE *Arq;
  char nome[5];
  char v_pont[10];
  char aux[10];
  Arq = fopen("ranking.txt", "a");

  if(Arq == NULL) {
  	//printar que deu erro ao abrir o arquivo
  }
  else if(Arq){
    fseek(Arq, 0, SEEK_END);
    if(ftell(Arq) == 0){
      	//Arquivo está vazio, printar na tela para o user escrever o nome
    	tela_cor(branco);
    	tela_texto(endgame[3], "    Digite suas iniciais:");
    	tela_atualiza();
    	fflush(stdin);
    	scanf("%s", nome);
    	fprintf(Arq, "%s ", nome);
      	fprintf(Arq, "%d", pontuacao);
    }
    else { //Arquivo NÂO está vazio
    	while(fgets(Arq, ) != NULL)
      }
  }
  fclose(Arq);
}*/

float rad_graus(ponto p, ponto g) {
	float x;
	x = atan((g.y-p.y)/(g.x-p.x)) * (180/3.14159265);
	if(p.y > g.y) {
		if(p.x > g.x) x = (90-x) + 90;
		else x *= (-1);
 	}
 	else {
 		if(p.x > g.x) x = (x*(-1)) + 180;
 		else x = (90-x) + 270;
 	}
	return x;
}

bool colisao_cor(pelota bola, float ang1, float ang2, int x) {
	if(bola.graus > ang1 && bola.graus < ang2 && bola.rand_cor == x)
	{
		return true;
	}
	else return false;
}

int retorna_cor(pelota bola, jogo j) {
  if(bola.graus < j.g.ang) {
    while(bola.graus < j.g.ang) j.g.ang -= 360;
  }
  else if(bola.graus > j.g.ang + 360) {
    while(bola.graus > j.g.ang + 360) j.g.ang += 360;
  }
  if(bola.graus > j.g.ang && bola.graus < j.g.ang + 120) return 0;
  else if(bola.graus > j.g.ang + 120 && bola.graus < j.g.ang + 240) return 1;
  else if(bola.graus > j.g.ang + 240 && bola.graus < j.g.ang + 360) return 2;
}

jogo aumenta_saude(jogo j, int cor, float s){
	switch(cor){
		case 0: //amarelo
			if(j.g.cir_amareloi.raio + s <= 0.5) j.g.cir_amareloi.raio += s;
			else j.g.cir_amareloi.raio = 0.5;
			break;
		case 1: //azul
			if(j.g.cir_azuli.raio + s <= 0.5) j.g.cir_azuli.raio += s;
			else j.g.cir_azuli.raio = 0.5;
			break;
		case 2: //verde
			if(j.g.cir_verdei.raio + s <= 0.5) j.g.cir_verdei.raio += s;
			else j.g.cir_verdei.raio = 0.5;
			break;
	}
	return j;
}

jogo diminui_saude(jogo j, int cor, float s){
	switch(cor){
		case 0: //amarelo
			if(j.g.cir_amareloi.raio - s >= 0) j.g.cir_amareloi.raio -= s;
			else {j.g.cir_amareloi.raio = 0.5; j.vida -= 1;}
			break;
		case 1: //azul
			if(j.g.cir_azuli.raio - s >= 0) j.g.cir_azuli.raio -= s;
			else {j.g.cir_azuli.raio = 0.5; j.vida -= 1;}
			break;
		case 2: //verde
			if(j.g.cir_verdei.raio - s >= 0) j.g.cir_verdei.raio -= s;
			else {j.g.cir_verdei.raio = 0.5; j.vida -= 1;}
			break;
	}
	return j;
}

jogo mov_bolas(jogo j)
{
  int i;
  for(i = 0; i < 5; i++)
  {
  	if(j.bola[i].real)
  	{
    	j.bola[i].posicao = movC(j.bola[i].posicao, j.bola[i].veloc);
    	if(colisaoCC(j.bola[i].posicao, j.g.cir_aux))
    	{
    		if(j.bola[i].graus < j.g.ang) {
    			while(j.bola[i].graus < j.g.ang) j.g.ang -= 360;
    		}
    		else if(j.bola[i].graus > j.g.ang + 360) {
    			while(j.bola[i].graus > j.g.ang + 360) j.g.ang += 360;
    		}

    		if((colisao_cor(j.bola[i], j.g.ang, j.g.ang+120, 0)) || (colisao_cor(j.bola[i], j.g.ang+120, j.g.ang+240, 1)) ||
    		(colisao_cor(j.bola[i], j.g.ang+240, j.g.ang+360, 2))) {  //amarelo azul e verde
          j.pont = j.pont + 50;
    			j = aumenta_saude(j, j.bola[i].rand_cor, 0.01);
    		}
    		else {
          j = diminui_saude(j, retorna_cor(j.bola[i], j), 0.125);
          if(j.pont - 70 <= 0) j.pont = 0;
          else j.pont = j.pont - 70;
        }
    		j.bola[i].real = false;
    	}
	}
  }
  return j;
}

jogo spawna_bola(jogo j) {
  int rand_y = 0, i;

  for(i = 0;i < 5;i++) {
  	if(rand()%1000 + 1 > 996){
  		if(!j.bola[i].real) {
  			j.bola[i].posicao.centro.x = (rand()%30)/10.0;

  			rand_y = rand()%2;
  			if(rand_y == 0) {j.bola[i].posicao.centro.y = -0.08;}
  			else {j.bola[i].posicao.centro.y = 4.08;}

  			j.bola[i].posicao.raio = 0.08;

  			j.bola[i].rand_cor = rand()%3;

  			j.bola[i].veloc.x = (j.g.cir_aux.centro.x - j.bola[i].posicao.centro.x) / 80;
  			j.bola[i].veloc.y = (j.g.cir_aux.centro.y - j.bola[i].posicao.centro.y) / 80;

  			j.bola[i].real = true;
  			j.bola[i].graus = rad_graus(j.g.cir_aux.centro, j.bola[i].posicao.centro);
  		}
  		break;
  	}
  }
  return j;
}

void desenha_giro(giro g) {             //OK
	tela_cor(branco);
	tela_arco(g.cir_aux, 0, 360);

   	tela_cor(amareloe);
   	tela_arco(g.cir_amareloe, g.ang, g.ang+120);

   	tela_cor(amareloi);
   	tela_arco(g.cir_amareloi, g.ang, g.ang+120);

    tela_cor(azule);
    tela_arco(g.cir_azule, g.ang+120, g.ang+240);

    tela_cor(azuli);
    tela_arco(g.cir_azuli, g.ang+120, g.ang+240);

    tela_cor(verdee);
    tela_arco(g.cir_verdee, g.ang+240, g.ang+360);

    tela_cor(verdei);
    tela_arco(g.cir_verdei, g.ang+240, g.ang+360);
}

void desenha_jogo(jogo j)
{
  tela_limpa();
  desenha_giro(j.g); //desenha o giro

  char plac[60];
  char vida[10];

  int i;
  for(i = 0;i < 5;i++) { //desenha as bolas
  	if(j.bola[i].real) {

  		if(j.bola[i].rand_cor == 0) {tela_cor(amareloi);}
  		else if(j.bola[i].rand_cor == 1) {tela_cor(azuli);}
  		else if(j.bola[i].rand_cor == 2) {tela_cor(verdei);}

  		tela_circulo(j.bola[i].posicao);
  	}
  }
  tela_cor(branco);
  sprintf(plac, "Pontua%c%co: %02d", 231, 227, j.pont);
  tela_texto(placar, plac);
  sprintf(vida, "Vidas: %d", j.vida);
  tela_texto(dvida, vida);
}
void end_game() {
  tela_cor(branco);
  tela_texto(endgame[0], "       FIM DE JOGO");
  tela_texto(endgame[1], "Aperte R para jogar de novo");
  tela_texto(endgame[2], "     Ou E para sair");
  return;
}
