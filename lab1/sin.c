#include <stdio.h>
#include <stdlib.h>

float grau_rad(float x) {
      return x * 3.1415 / 180;
}

int fatorial(int x) {
    int resultado = 1, fat = x;
    
    while (fat > 1) {
          resultado = resultado * fat;
          fat = fat - 1;      
    }
    return resultado;
}

float potencia(float base, int exp) {
	if(exp == 0) return 1;
	if(exp == 1) return base;
	return base * potencia(base, exp - 1);
}

float seno(float x) {
    float t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    t1 = x;
    t2 = potencia(x, 3) / fatorial(3);
    t3 = potencia(x, 5) / fatorial(5);
    t4 = potencia(x, 7) / fatorial(7);
    t5 = potencia(x, 9) / fatorial(9);
    t6 = potencia(x, 11) / fatorial(11);
    t7 = potencia(x, 13) / fatorial(13);
    t8 = potencia(x, 15) / fatorial(15);
    t9 = potencia(x, 17) / fatorial(17);
    t10 = potencia(x, 19) / fatorial(19);
            
    return t1 - t2 + t3 - t4 + t5 - t6 + t7 - t8 + t9 - t10;
}

int main () {
	int angulo, v;
	
	float rad, v_seno;
	printf("Digite um angulo, em graus, para o calculo de seno: ");
	scanf("%d", &angulo);
	
	rad = grau_rad(angulo);
	v_seno = seno(rad);
	printf("%d, %.4f, %.4f\n", angulo, rad, v_seno);
	system("PAUSE");
}	
