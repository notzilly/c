#include "vdc.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int num;
  char *nome;
  double saldo;
} conta;

struct vdc {
  conta *contas;
  int n_contas;
};

char *le_int(char *s, int *p)
{
  if (s == NULL) return s;

  char num[20];
  int i = 0;

  while (*s == ' ' || *s == '\t') s++;
  while (isdigit(*s)) {
    if (i >= 19) return NULL;
    num[i++] = *s++;
  }
  if (i == 0) return NULL;
  num[i] = '\0';
  *p = atoi(num);
  return s;
}

char *le_virgula(char *s)
{
  if (s == NULL) return s;

  while (*s == ' ' || *s == '\t') s++;
  if (*s != ',') return NULL;
  return s+1;
}

char *le_fim(char *s)
{
  if (s == NULL) return s;

  while (*s == ' ' || *s == '\t') s++;
  if (*s != '\n' && *s != '\0') return NULL;
  return s;
}

char *le_str(char *s, char *d)
{
  if (s == NULL) return s;

  while (*s == ' ' || *s == '\t') s++;
  while (*s != '\0' && *s != ',' && *s != '\n') {
    // BUG: nao tem limite no tamanho da string
    *d++ = *s++;
  }
  *d = '\0';

  return s;  
}

char *le_double(char *s, double *p)
{
  if (s == NULL) return s;

  char num[20];
  int i = 0;

  while (*s == ' ' || *s == '\t') s++;
  while (isdigit(*s) || *s == '.') {
    if (i >= 19) return NULL;
    num[i++] = *s++;
  }
  if (i == 0) return NULL;
  num[i] = '\0';
  *p = atof(num);
  return s;
}

bool le_conta(FILE *a, int *cta, char *nom, double *saldo)
{
  char linha[500];

  if (fgets(linha, 500, a) == NULL) return false;
  // BUG: deveria suportar linhas de qquer tamanho
  if (strlen(linha) > 498) return false;

  char *s = linha;
  s = le_int(s, cta);
  s = le_virgula(s);
  s = le_str(s, nom);
  s = le_virgula(s);
  s = le_double(s, saldo);
  s = le_fim(s);

  return s != NULL;
}

vdc *vdc_cria(char *arquivo)
{
  vdc *v;

  v = vdc_cria_vazio();
  if (v == NULL) return v;

  FILE *a;

  a = fopen(arquivo, "r");
  if (a == NULL) {
    vdc_destroi(v);
    return NULL;
  }

  while (true) {
    int num;
    char nome[300];
    double saldo;
    if (!le_conta(a, &num, nome, &saldo)) break;
    if (!vdc_insere(v, num, nome, saldo)) break;
  }
  fclose(a);

  return v;
}

vdc *vdc_cria_vazio(void)
{
  vdc *v;
  v = malloc(sizeof(vdc));
  if (v != NULL) {
    v->contas = NULL;
    v->n_contas = 0;
  }
  return v;
}

void vdc_destroi(vdc *v)
{
  if (v == NULL) return;
  if (v->contas != NULL) {
    int i;
    // libera o espaco de cada nome
    for (i=0; i<v->n_contas; i++) {
      free(v->contas[i].nome);
    }
    // libera o espaco do vetor
    free(v->contas);
  }
  // libera o espaco do vdc
  free(v);
}

bool vdc_busca_conta(vdc *v, int ct, int *indice)
{
  if (v == NULL) return false;

  int i;
  bool achei = false;
  for (i = 0; i < v->n_contas; i++) {
    if (v->contas[i].num == ct) {
      achei = true;
      break;
    }
  }
  *indice = i;
  return achei;
}

bool vdc_insere(vdc *v, int cta, char *nome, double saldo)
{
  int pos;
  if (v == NULL) return false;
  if (vdc_busca_conta(v, cta, &pos)) return false;

  // realoca (ou aloca) o vetor
  conta *contas;
  if (v->contas == NULL) contas = malloc(sizeof(conta));
  else contas = realloc(v->contas, (v->n_contas+1) * sizeof(conta));
  if (contas == NULL) return false;

  // copia os dados para o final do vetor
  char *nom;
  nom = malloc(strlen(nome)+1);
  if (nom == NULL) return false;
  strcpy(nom, nome);
  contas[pos].num = cta;
  contas[pos].nome = nom;
  contas[pos].saldo = saldo;

  // atualiza o vdc
  v->contas = contas;
  v->n_contas++;

  return true;
}

bool vdc_remove(vdc *v, int conta)
{
  if (v == NULL) return false;

  int pos;
  if (!vdc_busca_conta(v, conta, &pos)) return false;

  free(v->contas[pos].nome);

  // transfere a ultima conta para o local liberado, se precisar
  if (pos < v->n_contas - 1) {
    v->contas[pos] = v->contas[v->n_contas - 1];
  }

  // corrige o vetor (realoca ou libera a memoria)
  v->n_contas--;
  if (v->n_contas == 0) {
    free(v->contas);
    v->contas = NULL;
  } else {
    v->contas = realloc(v->contas, v->n_contas * sizeof(conta));
  }

  return true;
}

bool vdc_altera_saldo(vdc *v, int conta, double valor)
{
  if (v == NULL) return false;

  int pos;
  if (!vdc_busca_conta(v, conta, &pos)) return false;

  v->contas[pos].saldo += valor;

  return true;
}


bool vdc_grava(vdc *v, char *arquivo)
{
  if (v == NULL) return false;

  FILE *a;
  a = fopen(arquivo, "w");
  if (a == NULL) return false;

  int pos;
  for (pos = 0; pos < v->n_contas; pos++) {
    conta *c = &(v->contas[pos]);
    if (fprintf(a, "%d,%s,%.2f\n", c->num, c->nome, c->saldo) < 0) {
      fclose(a);
      return false;
    }
  }
  fclose(a);
  return true;
}
