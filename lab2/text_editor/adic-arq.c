#include "lista2.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// adiciona o conteúdo do arquivo chamado nome após a posicao corrente 
// da lista l. A posição corrente passa a ser a que contém a última linha lida.
// retorna true se ok, false se nao.
// l deve ser uma lista inicializada.
// linhas com mais de 1234 caracteres no arquivo de entrada serao quebradas
//   (como esse bug poderia ser corrigido?)
bool adic_arq(lista2 *l, char *nome)
{
  FILE *f;

  f = fopen(nome, "rt");
  if (f == NULL) return false;

  char s[1235];

  while (fgets(s, 1235, f) != NULL) {
    int n = strlen(s);
    // remove o \n do final da linha
    if (s[n] == '\n') s[n] = '\0';
    // strdup aloca memoria e copia a sring
    lista_insere_apos(l, strdup(s));
  }

  fclose(f);
  return true;
}
