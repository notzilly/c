#ifndef _CADEIA_H_
#define _CADEIA_H_

// API para manusear cadeias de caracteres alocadas dinamicamente
// a ser usada sugestivamente na disciplina lab2, 1o sem 2015
// ver descrição em http://www.inf.ufsm.br/~benhur/l22015a

#include <stdbool.h>

// todas as strings são alocadas dinamicamente, e realocadas conforme a 
//   necessidade, para que a quantidade de memoria alocada seja igual a
//   consumida pela string.
// caso a operacao altere o tamanho da string, deve ser alocada memoria para
//   conter a nova versao da string, e a memoria anterior deve ser liberada;
//   para que seja possível alterar as strings originais, a API recebe
//   ponteiros para as strings (ou ponteiros para ponteiros para char).
// uma string vazia pode ser representada por um ponteiro que aponta para 
//   uma região de memória que tem só o caractere '\0' ou por um 
//   ponteiro com o valor NULL.
// o ponteiro recebido pelas funções não pode ser NULL, mas podem apontar para
//   um ponteiro que é NULL, que representa uma string vazia.
// em geral manter a memória alocada com o mesmo tamanho da memória
//   consumida isso não é uma boa ideia para dados muito dinamicos, por 
//   resultar em excesso de operações de alocação / realocação.
// uma ideia melhor seria ter um TAD para strings, com uma struct mantendo
//   mais informação sobre cada string e sobre a memória usada para armazená-la

// substitui um caractere em uma dada posição da string
// adiciona espaços no final da string antes dessa posição, caso necessário.
void cad_subst(char **s, int p, char c);

// insere um caractere em uma dada posição da string
// adiciona espaços no final da string antes dessa posição, caso necessário.
void cad_ins(char **s, int p, char c);

// remove o caractere em uma dada posição da string
// não faz nada se a posição estiver fora da string
void cad_rem(char **s, int p);

// quebra a string s na posição p
// s passa a conter os primeiros p caracteres e s2 os caracteres a partir daí
// a string s2 recebida não deve ser válida (a função não deve manipular o
//   valor original de s2, nem considerar que a memória para onde ela 
//   eventualmente aponta deva ser liberada)
// não altera s e inicializa s2 com uma string vazia caso p esteja além
//   do final de s
void cad_quebra(char **s, int p, char **s2);

// concatena a string s2 no final de s
// nao altera s2 (em parte dos usos, isso implica que s2 terá que ser liberada
//   por quem chama)
void cad_gruda(char **s, char **s2);

// ajusta a string s para que tenha pelo menos o tamanho dado, adicionando
//   espaços no final se necessário
void cad_ajusta(char **s, int tam);

#endif // _CADEIA_H_
