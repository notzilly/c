#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool bissexto(int a)
{
    if(a % 400 == 0) return true;
    if(a % 100 == 0) return false;
    if(a % 4 == 0 ) return true;

    return false;
}

bool data_valida(int dia, int mes, int ano) {
    switch(mes)      {

        case 2:
            if(bissexto(ano))
            {
                if(dia > 0 && dia <= 29)
                {
                    return true;
                }
                else
                    return false;
            }
            else
            {
                if( dia > 0 && dia <= 28)
                {
                    return true;
                }
                else
                    return false;

            }
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            if(dia > 0 && dia <= 30)
                return true;
            else
                return false;
            break;

        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(dia > 0 && dia <= 31)
                return true;
            else
                return false;
            break;

        default:
            return false;
    }
}

int dia_do_ano(int dia, int mes, int ano){
    if(data_valida(dia, mes, ano))	{

    int num = dia;
    switch(mes){
        case 12: num+=30;    
        case 11: num+=31;
        case 10: num+=30;
        case 9: num+=31;
        case 8: num+=31;
        case 7: num+=30;
        case 6: num+=31;
        case 5: num+=30;
        case 4: num+=31;
        case 3: if (bissexto(ano)) num+=29;
             else num+=28;
        case 2: num+=31;
        } 
     return num;
     }
     return 0;
}

int entre_datas(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2)
{
	if(data_valida(dia1, mes1, ano1) && data_valida(dia2, mes2, ano2))
	{
		int difer = dia_do_ano(dia1, mes1, ano1) - dia_do_ano(dia2, mes2, ano2);	
		
		if(difer<0) return difer*(-1);
		else return difer;
	}
	return -1;
}

int main()
{
    int difer, dia1, mes1, ano1, dia2, mes2, ano2;

    printf("Digite um dia: ");
    scanf("%d", &dia1);

    printf("\nDigite o mes: ");
    scanf("%d", &mes1);

    printf("\nDigite o ano: ");
    scanf("%d", &ano1);
    
    printf("\nDigite um dia: ");
    scanf("%d", &dia2);

    printf("\nDigite o mes: ");
    scanf("%d", &mes2);

    printf("\nDigite o ano: ");
    scanf("%d", &ano2);

    difer = entre_datas(dia1, mes1, ano1, dia2, mes2, ano2);
    if(difer < 0) printf("\nAs datas informadas sao invalidas ou os anos sao diferentes\n");
    else printf("\nAs datas possuem %d dias de diferenca entre si\n", difer);

    system("PAUSE");
}


