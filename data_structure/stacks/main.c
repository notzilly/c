#include "pilha.h"
#include <stdio.h>

int main(){
    Pilha* p1 = pilha_cria();

    printf("***Remocao e insercao em pilha implementada como vetor dinamicamente alocado***\n");
    printf("by Luis Henrique Medeiros\n");
    printf("OBS.: A pilha \"p1\" ja foi previamente alocada, pronta para realizar as operacoes a seguir.\n");
    printf("\nDigite:\n");
    printf("\"p\" para push seguido do valor;\n");
    printf("\"q\" para pop;\n");
    printf("\"i\" para insercao seguido da posicao e depois do valor;\n");
    printf("\"r\" para remocao seguido da posicao a ser removida (se existir);\n");
    printf("\"x\" para desalocar pilha e sair do programa;\n\n");

    char s;
    int aux = 0, aux2 = 0;
    printf("Digite a operacao: ");
    scanf(" %c", &s);

    while(s != 'x'){
        switch(s){
            case 'p':
                        printf("Digite o valor: ");
                        scanf("%d", &aux);
                        pilha_push(p1, aux);
                        break;
            case 'q':
                        printf("Pop = %d\n", pilha_pop(p1));
                        break;
            case 'i':
                        printf("Digite a posicao de insercao: ");
                        scanf("%d", &aux);
                        printf("Digite o valor: ");
                        scanf("%d", &aux2);
                        pilha_insere(p1, aux, aux2);
                        break;
            case 'r':
                        printf("Digite a posicao de remocao: ");
                        scanf("%d", &aux);
                        printf("Pop = %d\n", pilha_remove(p1, aux));
                        break;
            default:
                        printf("Comando nao existente!!!");
                        break;
        }
        printf("Digite a proxima operacao: ");
        scanf(" %c", &s);
    }
    pilha_destroi(p1);

    return 0;
}
