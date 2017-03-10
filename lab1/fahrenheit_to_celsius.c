#include <stdio.h>
#include <stdlib.h>

int main(void){
    float c;
    float f;
    
    scanf("%f", &f);
    c = (f - 32) / 1.8;
    printf("Temperatura em graus Celsius = %4.2f\n", c);
    system("PAUSE");
    return 0;
}
