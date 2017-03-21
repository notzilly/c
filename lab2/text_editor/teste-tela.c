#include "tela.h"
#include <ctype.h>

int main()
{
  int i=0;
  int l=5;
  int c=20;
  int t=0;
  bool fim=false;
  char s[20];
  tela_inicia();

  while(!fim) {
    tela_limpa();
    tela_lincol(l, c);
    tela_cor(vermelho, branco);
    if (isprint(t)) {
      sprintf(s, "[%d %c]", i++, t);
    } else {
      sprintf(s, "[%d %d]", i++, t);
    }
    tela_texto(s);
    tela_cor(verde, azul);
    tela_lincol(15, 40);
    tela_texto("[ ]");
    tela_lincol(15, 41);
    tela_atualiza();
    switch(t=tela_tecla()) {
      case voltalin: l--; break;
      case voltacol: c--; break;
      case avancalin: l++; break;
      case avancacol: c++; break;
      case apaga: fim = true; break;
    }
    if (l==15 && c==40) fim = true;
  }

  tela_termina();
  return 0;
}
