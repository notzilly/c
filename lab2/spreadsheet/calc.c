#include "calc.h"
#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//verifica se a string é um double
bool so_numeros(char *entrada){
    int imax = strlen(entrada);
    int i;
    for(i = 0; i < imax; i++){
        if(isdigit(entrada[i])== 0){
            return false;
        }
    }
    return true;
}

//cria a arvore de variaveis
arv* cria_arv_variaveis(char *entrada){

    arv* var = NULL;

    char* chave;
    int i;
    int imax = strlen(entrada);
    for(i = 0; i < imax; i++){
        chave = retorna_char(entrada, i);
        if(chave != '\0'){
            arv* aux = arv_insere(&var, chave);

            //printf("ERD: "); printaERD(var); //prints
            //printf("\nSTR: "); printaSTR(var); printf("\n");  //prints

            printf("Digite a formula que deseja colocar no nó \"%s\": ", chave);
            char formula[50];
            scanf("%s", formula);

            insere_formula(aux, formula);

            altera_estado(aux, 0);

            //printf("ERD: "); printaERD(var); //prints
            //printf("\nSTR: "); printaSTR(var); printf("\n");  //prints
        }
    }
    return var;
}

//retorna o char se existir um char na entrada
char* retorna_char(char *entrada, int indice){
    char *ret = malloc(2);
    if(isalpha(entrada[indice])){
        ret[0] = entrada[indice];
        ret[1] = '\0';
        return ret;
    }
    else return '\0';
}

dado_t le_entrada(char *entrada, int indice){
    char cpy;
    if(isdigit(entrada[indice])) cpy = entrada[indice] - '0';
    else cpy = entrada[indice];
    return cpy;
}

dado_t opera_pilha(pilha *operandos, pilha *operadores){
    dado_t aux1, aux2;
    if(pilha_topo(operadores) == '+'){
        aux1 = pilha_remove(operandos);
        aux2 = pilha_remove(operandos);
        pilha_remove(operadores);
        return aux1 + aux2;
    }
    else if(pilha_topo(operadores) == '-'){
        aux1 = pilha_remove(operandos);
        aux2 = pilha_remove(operandos);
        pilha_remove(operadores);
        return aux2 - aux1;
    }
    else if(pilha_topo(operadores) == '*'){
        aux1 = pilha_remove(operandos);
        aux2 = pilha_remove(operandos);
        pilha_remove(operadores);
        return aux1 * aux2;
    }
    else if(pilha_topo(operadores) == '/'){
        aux1 = pilha_remove(operandos);
        aux2 = pilha_remove(operandos);
        pilha_remove(operadores);
        return aux2 / aux1;
    }
    else if(pilha_topo(operadores) == '^'){
        aux1 = pilha_remove(operandos);
        aux2 = pilha_remove(operandos);
        pilha_remove(operadores);
        return pow(aux2, aux1);
    }
    else if(pilha_topo(operadores) == '#'){
        aux1 = pilha_remove(operandos);
        pilha_remove(operadores);
        return sqrt(aux1);
    }
    else{
        printf("Erro nos operadores!\n");
        exit(1);
    }
}

//entrada de dados e calculos
dado_t calcula(char *entrada, arv *variaveis){
    int imax = strlen(entrada);
    int i;

    //fazer função que verifica isso \/  \/  \/
    /*char *ch;
    for(i = 0; i < imax; i++){
        ch = retorna_char(entrada, i);
        if(ch != '\0') break;
        else{
            dado_t res = strtod(entrada, NULL);
            return res;
        }
    }*/

    if(le_entrada(entrada, imax - 1) != '='){
        printf("\nDigitacao incorreta: faltou o sinal de igual: \"=\"!\n");
        exit(1);
    }

    pilha operadores = pilha_cria();
    pilha operandos = pilha_cria();
    pilha_insere(&operadores, '%');
    pilha_insere(&operandos, '%');

    for(i = 0; i < imax; i++){
        dado_t aux = le_entrada(entrada, i);

        if(aux == '+'){
            bool p = true;
            while(p){   ///o 'if' opera
                if(pilha_topo(&operadores) == '+' || pilha_topo(&operadores) == '-' || pilha_topo(&operadores) == '*' || pilha_topo(&operadores) == '/' || pilha_topo(&operadores) == '^' || pilha_topo(&operadores) == '#'){
                    dado_t result = opera_pilha(&operandos, &operadores);
                    pilha_insere(&operandos, result);
                }
                else{     /*serve pra ( e sem operador*/   ///empilha
                    p = false;
                    pilha_insere(&operadores, aux);
                }
            }
            continue;
        }

        else if(aux == '-'){
            bool p = true;
            while(p){   ///o 'if' opera
                if(pilha_topo(&operadores) == '+' || pilha_topo(&operadores) == '-' || pilha_topo(&operadores) == '*' || pilha_topo(&operadores) == '/' || pilha_topo(&operadores) == '^' || pilha_topo(&operadores) == '#'){
                    dado_t result = opera_pilha(&operandos, &operadores);
                    pilha_insere(&operandos, result);
                }
                else{     /*serve pra ( e sem operador*/   ///empilha
                    p = false;
                    pilha_insere(&operadores, aux);
                }
            }
            continue;
        }

        else if(aux == '*'){
            bool p = true;
            while(p){   ///o 'if' opera
                if(pilha_topo(&operadores) == '*' || pilha_topo(&operadores) == '/' || pilha_topo(&operadores) == '^' || pilha_topo(&operadores) == '#'){
                    dado_t result = opera_pilha(&operandos, &operadores);
                    pilha_insere(&operandos, result);
                }
                else{     ///empilha
                    p = false;
                    pilha_insere(&operadores, aux);
                }
            }
            continue;
        }

        else if(aux == '/'){
            bool p = true;
            while(p){   ///o 'if' opera
                if(pilha_topo(&operadores) == '*' || pilha_topo(&operadores) == '/' || pilha_topo(&operadores) == '^' || pilha_topo(&operadores) == '#'){
                    dado_t result = opera_pilha(&operandos, &operadores);
                    pilha_insere(&operandos, result);
                }
                else{     ///empilha
                    p = false;
                    pilha_insere(&operadores, aux);
                }
            }
            continue;
        }

        else if(aux == '='){
            dado_t result = 0;
            while(pilha_topo(&operadores) == '+' || pilha_topo(&operadores) == '*' || pilha_topo(&operadores) == '-' || pilha_topo(&operadores) == '/' || pilha_topo(&operadores) == '^' || pilha_topo(&operadores) == '#'){
                result = opera_pilha(&operandos, &operadores);
                pilha_insere(&operandos, result);
            }
            if(pilha_topo(&operadores) == '('){
                printf("\nErro no uso dos parenteses!\n");
                exit(1);
            }
            break;
        }

        else if(aux == '^'){   //potencia
            pilha_insere(&operadores, aux);
            continue;
        }

        else if(aux == '#'){    //radiciacao
            pilha_insere(&operadores, aux);
            continue;
        }

        else if(aux == '('){
            pilha_insere(&operadores, aux);
            continue;
        }

        else if(aux == ')'){
            if(pilha_topo(&operadores) == '('){
                pilha_remove(&operadores);
            }
            else{
                int lambuja = 0;
                dado_t result = 0;
                while(pilha_topo(&operadores) != '('){
                    result = opera_pilha(&operandos, &operadores);
                    pilha_insere(&operandos, result);
                    lambuja++;
                    if(lambuja > 1000){
                        printf("\nErro nos parenteses!\n");
                        exit(1);
                    }
                }
                pilha_remove(&operadores);
            }
            continue;
        }

        char *text = retorna_char(entrada, i);
        if(text != '\0'){
            arv *no = arv_busca(variaveis, text);
            //if(no == NULL){printf("\nErro brabo!\n"); exit(2);}
            aux = arv_valor(no, variaveis);
            pilha_insere(&operandos, aux);
            continue;
        }

        else if(isdigit(aux) == 0){   //numeros = operandos
            dado_t prox = le_entrada(entrada, i + 1);
            while(prox != '+' && prox != '-' && prox != '=' && prox != '.' && prox != '*' && prox != '/' && prox != '(' && prox != ')' && prox != '^' && prox != '#'){
                aux *= 10;
                aux += prox;
                i++;
                prox = le_entrada(entrada, i + 1);
            }
            if(prox == '.'){
                i++;
                prox = le_entrada(entrada, i + 1);
                aux = aux + (prox / 10);
                i++;
                dado_t prox1 = le_entrada(entrada, i + 1);
                if(prox1 != '+' && prox1 != '-' && prox1 != '=' && prox1 != '.' && prox1 != '*' && prox1 != '/' && prox1 != '(' && prox1 != ')' && prox1 != '^' && prox1 != '#'){
                    aux = aux + (prox / 100);
                    i++;
                }
            }
            pilha_insere(&operandos, aux);
            continue;
        }

        else{
            printf("\nOperacao digitada incorretamente!");
            exit(1);
        }
    }
    dado_t res = pilha_remove(&operandos);
    pilha_destroi(&operadores);
    pilha_destroi(&operandos);
    return res;
}

// calcula o valor da expressão expr, usando a árvore variaveis para buscar
// valores de variáveis existentes na expressão.
dado_t calc_calcula(char *expr, arv *variaveis){
    return calcula(expr, variaveis);
}

// retorna o valor do nó no.
// caso necessário, calcula a fórmula do nó, usando a árvore de variáveis.
dado_t arv_valor(arv *no, arv *variaveis){
    dado_t res;
    if(no){
        if(no->estado == 0){  //desconhecido
            altera_estado(no, 1); //calculando
            if(so_numeros(no->formula)){
                no->valor = atof(no->formula);
            }
            else{
                int i;
                int imax = strlen(no->formula);
                char *chave;
                for(i = 0; i < imax; i++){
                    chave = retorna_char(no->formula, i);
                    if(chave != '\0'){
                        arv* aux = arv_insere(&variaveis, chave);

                        printf("Digite a formula que deseja colocar no nó \"%s\": ", chave);
                        char formula[50];
                        scanf("%s", formula);

                        insere_formula(aux, formula);
                        altera_estado(aux, 0);
                    }
                }
                no->valor = calcula(no->formula, variaveis);
            }
            altera_estado(no, 2); //calculado
            res = no->valor;

            return res;
        }
    }
}
