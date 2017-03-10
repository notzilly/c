#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calcula_delta (double a, double b, double c){
    double d, e, x1, x2;

    d = (b*b) - (4*a*c);
    e = sqrt(d);

    x1 = ((-b) + e) / (2*a);
    x2 = ((-b) - e) / (2*a);

    if(d > 0)
        printf("A equacao tem 2 raizes reais e distintas de valor %.2lf e %.2lf\n", x1, x2);
    if(d == 0)
        printf("A equacao tem 2 raizes reais e iguais a: %.2lf e %.2lf\n", x1, x2);
    if(d < 0)
        printf("A equacao nao possui raizes reais\n");
    }

int main (){
    double a, b, c;

    printf("Escreva valores para a, b e c, sendo que y = a*x*x + b*x + c:\n");
    scanf("%lf %lf %lf", &a, &b, &c);
    
    if(a != 0)
    calcula_delta(a, b, c);
    else printf("Nao e uma equacao do segundo grau\n");   

    system("PAUSE");
    }
