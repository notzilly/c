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

        // Meses com 30 dias: 4, 6, 9, 11.
        case 4:
        case 6:
        case 9:
        case 11:
            if(dia > 0 && dia <= 30)
                return true;
            else
                return false;
            break;

        // Meses com 31 dias: 1, 3, 5, 7, 8, 10, 12

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

int main()
{
    int num, dia, mes, ano;

    printf("Digite um dia: ");
    scanf("%d", &dia);

    printf("\nDigite o mes: ");
    scanf("%d", &mes);

    printf("\nDigite o ano: ");
    scanf("%d", &ano);

    printf("\nA data informada corresponde ao %d -esimo dia do ano\n", dia_do_ano(dia, mes, ano));  

    system("PAUSE");
}


