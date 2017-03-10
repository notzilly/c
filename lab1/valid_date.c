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


bool valida_data(int dia, int mes, int ano)
{
    switch(mes)
    {

        // DIAS : 1 - 31,
        // CASO FEVEREIRO: TESTAR SE É BISSEXTO;


        // Fevereiro, pode ser bissexto. 28 ou 29 dias.
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

int main()
{
    int dia, mes, ano;

    printf("Digite um dia: ");
    scanf("%d", &dia);

    printf("\nDigite o mes: ");
    scanf("%d", &mes);

    printf("\nDigite o ano: ");
    scanf("%d", &ano);

    if(valida_data(dia, mes, ano))
    {
        printf("\nData e valida!\n");
    }
    else
    {
        printf("\nData eh invalida!\n");
    }

    system("PAUSE");
}


