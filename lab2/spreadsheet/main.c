#include "abb.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("PLANILHA DE CALCULO EM C v2 - Luis Henrique Medeiros\n");
    printf("A operacao deve ser digitada sem espacos. Use:\n");
    printf("+ -> soma;\n");
    printf("- -> subtracao;\n");
    printf("* -> multiplicacao;\n");
    printf("/ -> divisao;\n");
    printf("^ -> potenciacao;\n");
    printf("# -> radiciacao.\n");
    printf("Pode-se tambem utilizar parenteses \"(\" e \")\" para alterar\n");
    printf("a ordem de precedencia das operacoes;\n");
    printf("O programa funciona para numeros de ate duas casas decimais! Ex.: 21.75\n");
    printf("Nao esqueca de usar o sinal de igual no final da operacao, pois o pro-\n");
    printf("grama so le ate ele, o que tem adiante eh ignorado!\n");
    printf("Se quiser digitar uma formula, use a seguinte sintaxe: a+b=\n");
    printf("Se quiser digitar direto o valor da celula, sem formulas, digite somente o numero\n");
    printf("Digite a operacao: ");


    char entrada[50];
    scanf("%s", entrada);

    arv* var = cria_arv_variaveis(entrada);
    //printaERD(var); printf("\n");
    //printaSTR(var);
    printf("\nResultado da operacao = %.2lf\n", calc_calcula(entrada, var));


    return 0;
}
