#ifndef _GEOM_H
#define _GEOM_H
#include <stdbool.h>
#include <math.h>

// um ponto
typedef struct {
    float x;
    float y;
} ponto;

// um retangulo (cantos sup esq e inf dir)
typedef struct {
    ponto cse;
    ponto cid;
} retangulo;

// um circulo
typedef struct {
    ponto centro;
    float raio;
} circulo;


// movimenta um círculo por um dado deslocamento
// o deslocamento é dado por um ponto, com seus campos //x// e //y// contendo o deslocamento na direção horizontal e vertical.
// retorna o círculo deslocado.
circulo movC(circulo c, ponto d);
  
// movimenta um retângulo por um dado deslocamento
// o deslocamento é dado por um ponto, com seus campos //x// e //y// contendo o deslocamento na direção horizontal e vertical.
// retorna o retângulo deslocado.
retangulo movR(retangulo r, ponto d);
  
// detecta colisão entre um círculo e um retângulo
// retorna //true// caso o círculo e o retângulo recebidos estejam colidindo.
bool colisaoCR(circulo c, retangulo r);

// detecta colisão entre dois retângulos
// retorna //true// caso os retângulos tenham interseção não nula
bool colisaoRR(retangulo r1, retangulo r2);


#endif				// _GEOM_H
