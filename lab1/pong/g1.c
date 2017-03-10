#include "geom.h"

// movimenta um circulo por um dado deslocamento
// o deslocamento é dado por um ponto, com seus campos //x// e //y// contendo o deslocamento na direÃ§Ã£o horizontal e vertical.
// retorna o cÃ­rculo deslocado.
circulo movC(circulo c, ponto d)
{
    c.centro.x += d.x;
    c.centro.y += d.y;
    return c;
}

// movimenta um retÃ¢ngulo por um dado deslocamento
// o deslocamento Ã© dado por um ponto, com seus campos //x// e //y// contendo o deslocamento na direÃ§Ã£o horizontal e vertical.
// retorna o retÃ¢ngulo deslocado.
retangulo movR(retangulo r, ponto d)
{
    r.cid.x += d.x;
    r.cid.y += d.y;

    r.cse.x += d.x;
    r.cse.y += d.y;

    return r;
}

// detecta colisao entre um cÃ­rculo e um retangulo
// retorna //true// caso o circulo e o retangulo recebidos estejam colidindo.

bool colisaoCR(circulo c, retangulo r)
{
    
    if( (c.centro.x + c.raio >= r.cse.x && r.cid.x >= c.centro.x - c.raio -0.1   ) &&
        (c.centro.y + c.raio +0.1>= r.cse.y && r.cid.y >= c.centro.y - c.raio)   ){
        
            return true;
    }
    else return false;   
}

bool colisaoRR(retangulo r1, retangulo r2/*raquete*/){
    

    //Retangulo Superior
    if(r1.cid.y < r2.cse.y){
        return false;
    }
    else{
        return true;
    }   

}
