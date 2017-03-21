#include "pilha.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

typedef enum {
  mais,
  menos,
  vezes,
  dividido,
  na,
  raiz,
  abre,
  fecha,
  fimp,
  fime
} oper_t;

char opers[] = "+-*/^#()$&";

oper_t opdotok(char *tok)
{
  char *s;
  if (*tok == '\0') return fime;
  s = strchr(opers, *tok);
  if (s == NULL) return fime;
  return s - opers;
}

typedef enum {
  E, D, O, R, F
} operacao_t;

operacao_t operacao(oper_t o1, oper_t o2)
{
  operacao_t operacoes[10][9] =
    { //    + - * / ^ # ( ) $
    /*+*/ { O,O,O,O,O,O,E,R,E },
    /*-*/ { O,O,O,O,O,O,E,R,E },
    /***/ { E,E,O,O,O,O,E,R,E },
    /*/*/ { E,E,O,O,O,O,E,R,E },
    /*^*/ { E,E,E,E,E,O,E,R,E },
    /*#*/ { E,E,E,E,E,E,E,R,E },
    /*(*/ { E,E,E,E,E,E,E,R,E },
    /*)*/ { O,O,O,O,O,O,D,R,R },
    /*$*/ { R,R,R,R,R,R,R,R,R },
    /*&*/ { O,O,O,O,O,O,R,R,F },
    };
  return operacoes[o1][o2];
}

bool operador(char *tok)
{
  if (*tok == '\0') return true;
  return strchr(opers, *tok) != NULL;
}

bool operando(char *tok)
{
  if (*tok == '\0') return false;
  return strchr(opers, *tok) == NULL;
}

void letok(char *expr, int *pos, char *tok)
{
  while (expr[*pos] && isspace(expr[*pos])) {
    (*pos)++;
  }
  if (expr[*pos] == '\0') {
    ;
  } else if (operador(expr + *pos)) {
    *tok++ = expr[(*pos)++];
  } else {
    while (expr[*pos] && !isspace(expr[*pos]) && !operador(expr + *pos)) {
      *tok++ = expr[(*pos)++];
    }
  }
  *tok = '\0';
}

void opera(pilha *ppoper, pilha *ppopen)
{
  oper_t oper;
  double x1, x2;
  oper = pilha_remove(ppoper);
  switch(oper) {
    case mais:
      x2 = pilha_remove(ppopen);
      x1 = pilha_remove(ppopen);
      pilha_insere(ppopen, x1 + x2);
      break;
    case menos:
      x2 = pilha_remove(ppopen);
      x1 = pilha_remove(ppopen);
      pilha_insere(ppopen, x1 - x2);
      break;
    case vezes:
      x2 = pilha_remove(ppopen);
      x1 = pilha_remove(ppopen);
      pilha_insere(ppopen, x1 * x2);
      break;
    case dividido:
      x2 = pilha_remove(ppopen);
      x1 = pilha_remove(ppopen);
      pilha_insere(ppopen, x1 / x2);
      break;
    case na:
      x2 = pilha_remove(ppopen);
      x1 = pilha_remove(ppopen);
      pilha_insere(ppopen, pow(x1, x2));
      break;
    case raiz:
      x1 = pilha_remove(ppopen);
      pilha_insere(ppopen, pow(x1, 0.5));
      break;
    default:
      break;
  }
}

double valor(char *tok)
{
  return atof(tok);
}

double calc(char *expr)
{
  pilha poper, popen;
  double result;
  char tok[50];
  int postok = 0;
  bool fim = false;
  bool deve_ler = true;
  oper_t oper;

  poper = pilha_cria();
  popen = pilha_cria();

  pilha_insere(&poper, fimp);

  while (!fim) {
    if (deve_ler) {
      letok(expr, &postok, tok);
    }
    if (operando(tok)) {
      pilha_insere(&popen, valor(tok));
    } else {
      deve_ler = true;
      oper = opdotok(tok);
      switch(operacao(oper, pilha_topo(&poper))) {
        case E: pilha_insere(&poper, oper);
                break;
        case D: pilha_remove(&poper);
                break;
        case O: opera(&poper, &popen);
                deve_ler = false;
                break;
        case R: //
                break;
        case F: fim = true;
                break;
      }
    }
  }

  result = pilha_remove(&popen);

  pilha_destroi(&poper);
  pilha_destroi(&popen);

  return result;
}

main()
{
  printf("%f\n", calc("#2^(1+1)"));
}
