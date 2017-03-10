#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    float x;
    int y;
    srand(time(NULL));
    x = (rand()%500)/10.0;
    printf("%g\n", x);
    y = (rand()%2);
    printf("%d", y);
    return 0;
}
