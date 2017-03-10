#include <stdbool.h>
#include <math.h>
#include "geom.h"

circulo movC(circulo c, ponto d)
{
	c.centro.x+=d.x;
	c.centro.y+=d.y; 
	return c;
}


bool colisaoCC(circulo c1, circulo c2) //"GIRO" será sempre o 2 circulo
{	
	//em menos de um mes essa pourra vamo chora caraio e n vamo roda em lab (quer dizer, depende da prova) Xd e se o benhur tiver de bom humor, ou seja, tamo rodado
	if(c1.raio + c2.raio >= distanciaCC(c1, c2)) {
		return true;}
	else return false;
}

float distanciaCC(circulo c1, circulo c2) {
	float dist;
	dist = pow((c2.centro.x - c1.centro.x), 2) + pow((c2.centro.y - c1.centro.y), 2);
	return sqrt(dist);
}
