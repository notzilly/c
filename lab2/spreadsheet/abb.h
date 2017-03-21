#ifndef _ARVORE_H_
#define _ARVORE_H_

typedef struct arv arv; //apagar typedef e struct \/

typedef enum{desconhecido, calculando, calculado} estado_t ;
struct arv{
    char *chave;
    char *formula;
    double valor;
    int altura;
    estado_t estado;
    arv *esq;
    arv *dir;
};

void destroi_no(arv *arvore);

void altera_estado(arv *arvore, int est);

void insere_formula(arv *arvore, char *formula); //insere no nó da árvore a formula

arv* rotEsq(arv *arvore); //rotacao a esquerda

arv* rotDir(arv *arvore); //rotacao a direita

int maxDepth(arv* arvore);

int fatorBal(arv* arvore); // retorna a dif de altura esq - dir dos filhos

//void printaERD(arv *arvore);  //printa arvore no esquema esquerda-raiz-direita

//void printaSTR(arv *arvore); //printa no esquema <no<esq><dir>>

int arv_altura(arv *arvore);   // retorna a altura da árvore (simplesmente retorna o valor do campo altura ou -1 se a for NULL)

void arv_calc_altura(arv *arvore);   // recalcula a altura da árvore (chamando a função anterior pra cada filho)

arv* arv_maior_valor(arv **arvore); //retorna o no de maior valor da arvore (mais a direita)

arv* arv_menor_valor(arv *arvore);

arv* arv_cria_no(char *chave, arv *esquerda, arv *direita);  //aloca espaço para um no e seta seus dois filhos para NULL

// busca um nó da árvore
  // recebe um ponteiro para a raiz de uma (sub-)árvore e uma chave
  // retorna um ponteiro para o nó da árvore que contém a chave passada,
  //   ou NULL caso não exista
  arv *arv_busca(arv *a, char *chave);

  // busca um nó da árvore
  // recebe um ponteiro para a raiz de uma (sub-)árvore e uma chave
  // retorna um ponteiro para o nó da árvore que contém a menor chave maior
  //   que a chave passada, ou NULL caso não exista (a chave passada é maior
  //   ou igual à maior chave na árvore, ou a árvore está vazia)
  // caso a chave passada seja NULL, retorna o nó com a menor chave na árvore
  //   ou NULL caso a árvore seja vazia
  // a chave passada não precisa existir na árvore
  arv *arv_busca_prox(arv *a, char *chave);

  // insere um nó na árvore
  // recebe um ponteiro para o ponteiro que aponta para a raiz da (sub-)árvore e uma chave
  // retorna um ponteiro para o nó da árvore que contém a chave passada
  // caso já exista um nó com essa chave, a árvore não deve ser alterada
  //   e deve ser retornado um ponteiro para esse nó;
  //   caso não exista, um novo nó deve ser alocado, inicializado e inserido
  //   na árvore. Os campos do novo nó não precisam ser inicializados (exceto
  //   a chave e os ponteiros para os filhos).
  // o ponteiro chave deve ser simplesmente copiado para o nó, não deve ser
  //   alocado espaço e copiada a string
  // a função recebe um ponteiro para a raiz da (sub-)árvore porque essa
  // raiz pode ser alterada.
  arv *arv_insere(arv **a, char *chave);

  // remove um nó da árvore
  // recebe um ponteiro para o ponteiro que aponta para a raiz da (sub-)árvore e uma chave
  // remove da árvore o nó com essa chave ou não faz nada caso não exista
  //   nó com essa chave na árvore
  // a função recebe um ponteiro para a raiz da (sub-)árvore porque essa
  // raiz pode ser alterada.
  void arv_remove(arv **a, char *chave);

#endif // _ARVORE_H_
