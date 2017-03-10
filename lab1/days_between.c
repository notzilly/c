#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//diz se o ano é bissexto ou não
bool bissexto(int ano) {
    if(ano%400 == 0) return true;
    if(ano%100 == 0) return false;
    if(ano%4 == 0) return true;
    return false;
}

//calcula quantos dias cada mes do ano tem
int n_dias_mes(int mes, int ano) {
    if(mes > 0 && mes < 13) {
        if(mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
        if(mes == 2) {
            if(bissexto(ano)) return 29;
            return 28;
        }        
        return 31;
    }
    return -1;
}

bool data_valida(int dia, int mes, int ano) {
    if(dia > 0 && dia <= n_dias_mes(mes, ano)) return true;
    return false;
}

int dia_do_ano(int dia, int mes, int ano) {
    if(data_valida(dia, mes, ano)) {
        int num = dia;
        switch(mes) {
            case 12: num += 30;
            case 11: num += 31;
            case 10: num += 30;
            case 9: num += 31;
            case 8: num += 31;
            case 7: num += 30;
            case 6: num += 31;
            case 5: num += 30;
            case 4: num += 31;
            case 3: if(bissexto(ano)) num += 29;
            else num += 28;
            case 2: num += 31;
        }
        return num;
    }
    return 0;
}

int n_dias_ano(int ano) {
    if(bissexto(ano)) return 366;
    else return 365;
}

int entre_datas(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2) {
    if(data_valida(dia1, mes1, ano1) && data_valida(dia2, mes2, ano2)) {
        int num1 = dia_do_ano(dia1, mes1, ano1), num2 = dia_do_ano(dia2, mes2, ano2);

        if(ano1 == ano2) { 
            if(num1 > num2) return num1 - num2; 
            else return num2 - num1;
        }
        if(ano1 > ano2) {
            int aux;
            aux = dia1; dia1 = dia2; dia2 = aux;
            aux = mes1; mes1 = mes2; mes2 = aux;
            aux = ano1; ano1 = ano2; ano2 = aux;
            aux = num1; num1 = num2; num2 = aux;
        }
        int num = n_dias_ano(ano1) - num1, ano = ano1 + 1;
        
        while(ano < ano2) {
            num = num + n_dias_ano(ano); 
            ano = ano + 1;
        }
        return num + dia_do_ano(dia2, mes2, ano2);
    }
    return -1;
}


int dias_ate_data(int dia, int mes, int ano) {
    int a = 1970, m = 1, d = ((time(0) - 10800) / 86400) + 1;

    while(d > n_dias_ano(a)) {
        d = d - n_dias_ano(a); 
        a = a + 1;
    }
    while(d > n_dias_mes(m, a)) {
        d = d - n_dias_mes(m, a);
        m = m + 1;
    }
    return entre_datas(dia, mes, ano, d, m, a);
}

int main() {
    int dia, mes, ano, dias_entre;
    printf("Informe uma data DD/MM/AAAA: ");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    dias_entre = dias_ate_data(dia, mes, ano);

    if(dias_entre == -1) printf("Data invalida!\n");
    else printf("Ha %d dias entre a data digitada e o dia de hoje\n", dias_entre);

    system("PAUSE");
}
