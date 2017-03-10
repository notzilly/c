#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main () {
	int a, b;
	bool c;
	a = 7;
	b = 30;
	c = a!=b;
	
	if (c == true){
		printf("%d nao e igual a %d\n", a, b);
	}
	else {
		printf("E igual");
	}
	system("PAUSE");
}	

