#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool bissexto (int a) {
	if (a%400 == 0) return true;
	if (a%100 == 100) return false;
	if (a%4 == 0) return true;
	
	return false;
}

int main () {
	int ano;
	printf("Digite um ano: ");
	scanf("%d", &ano);
	
	if (bissexto(ano)) {
		printf("%d e bissexto\n", ano);
		}
	else {
		printf("%d nao e bissexto\n", ano);
	}
	system("PAUSE");
}	
