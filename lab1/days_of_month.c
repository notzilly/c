#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool bissexto (int a) {
	if (a%400 == 0) return true;
	if (a%100 == 100) return false;
	if (a%4 == 0) return true;
	
	return false;
}

int numero_dias(int mes, int ano){

int d;
    switch (mes){
       //função do ano bissexto
       case 2: 
               if(bissexto(ano)){
                                 d = 29;
                                 }
               else {
                    d = 28;
                    }
               break;
       //meses com 30 dias
       case 4:
       case 6:
       case 9:
       case 11:
               d = 30;
               break;
       //meses com 31 dias
       case 1:
       case 3:
       case 5:
       case 7:
       case 8:
       case 10:
       case 12:
               d = 31;
               break;
       //qualquer input que não é de 1 a 12 retorna -1
       default:
               d = -1; 
      
      }
      return d;
}



int main () {
	int mes, ano, d;
	
	printf("Digite um mes: ");
	scanf("%d", &mes);
	
	printf("Digite um ano: ");
	scanf("%d", &ano);
	
	d = numero_dias(mes, ano);
	printf("Este mes tem %d dias\n", d);
	
	system("PAUSE");
}	


