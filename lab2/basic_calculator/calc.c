#include "calc.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

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
dado_t calcula(char *entrada){
    pilha operadores = pilha_cria();
    pilha operandos = pilha_cria();
    pilha_insere(&operadores, '%');
    pilha_insere(&operandos, '%');

    int imax = strlen(entrada);
    int i;

    if(le_entrada(entrada, imax - 1) != '='){
        printf("\nDigitacao incorreta: faltou o sinal de igual: \"=\"!\n");
        exit(1);
    }

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

        else if(isalpha(aux) == 0){   //numeros = operandos
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
