#include <stdio.h>
#include <stdlib.h>
    
float quadrado (float x) {
          return x*x;
}    
float cubo (float x) {
          return x*x*x;
}

void calcula (void){
        float x, y, z;
        printf("Digite um numero: ");
        scanf("%f", &x);
        y = quadrado(x);
        z = cubo(x);
        printf("Numero digitado: %.2f, ao quadrado: %.2f, ao cubo: %.2f\n", x, y, z); 
}  

void cabecalho(void){
     printf("Calculo de quadrado e cubo por Luis Henrique Medeiros:\n");
}

int main (void) {
    cabecalho();
    calcula ();
    calcula ();
    calcula ();
    system("PAUSE");
}
   
    
