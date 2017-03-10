#include <stdio.h>
#include <stdlib.h>

int main(void){
    float c;
    float f;
    
    scanf("%f", &c);
    f = (c * 9 / 5) + 32;
    printf("Temperatura em graus Fahrenheit = %4.2f\n", f);
    system("PAUSE");
    return 0;
}
