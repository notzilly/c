#include "lista.h"
#include "pilha.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(){

    printf("CALCULADORA EM C v2 - Luis Henrique Medeiros\n");
    printf("A operacao deve ser digitada sem espacos. Use:\n");
    printf("+ -> soma;\n");
    printf("- -> subtracao;\n");
    printf("* -> multiplicacao;\n");
    printf("/ -> divisao;\n");
    printf("^ -> potenciacao;\n");
    printf("# -> radiciacao.\n");
    printf("Pode-se tambem utilizar parenteses \"(\" e \")\" para alterar\n");
    printf("a ordem de precedencia das operacoes;\n");
    printf("O programa funciona para numeros de ate duas casas decimais! Ex.: 21.5\n");
    printf("Nao esqueca de usar o sinal de igual no final da operacao, pois o pro-\n");
    printf("grama so le ate ele, o que tem adiante eh ignorado!\n");
    printf("Digite a operacao: ");

    char entrada[50];
    scanf("%s", entrada);
    printf("\nResultado da operacao = %.2lf\n", calcula(entrada));

    return 0;
}
