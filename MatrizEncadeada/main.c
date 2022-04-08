#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include <locale.h>
int menu();
int main(){
        setlocale(LC_ALL, "Portuguese");
        int linha,coluna,valor;
        int l,c;
        printf("\nBem Vindos a nossa Matriz\n");
        printf("\nDigite o tamanho que você quer que para a Matriz em linha/coluna\n");
        scanf("%d%d",&l,&c);
        Matriz *m=cria_matriz(l,c);
        int op;
        do{
            op=menu();
        switch(op){
        case 1:
            printf("\nSua matriz tem dimensão : \nLinha: %d\nColuna: %d\n",l,c);
            printf("\nDigite a linha e coluna e o valor que deseja inserir considerando linha inicial 0 e coluna inicial 0: \n");
            scanf("%d%d%d",&linha,&coluna,&valor);
            insere_cordenada(m,linha,coluna,valor);
            break;
        case 2:
            for(int i=0;i<l;i++){
                for(int j=0;j<c;j++){
                    insere_cordenada(m,i,j, rand() % 99);
                }
            }
            break;
        case 3:
            printf("\nSua matriz tem dimensão : \nLinha: %d\nColuna: %d\n",l,c);
            printf("\nDigite a linha e coluna e o valor que deseja remover considerando linha inicial 0 e coluna inicial 0: \n");
            scanf("%d%d",&linha,&coluna);
            remove_cordenada(m,linha,coluna);
            break;
        case 4:
            imprime_alocados(m);
            break;
        case 5:
            imprime_completo(m);
            break;
        case 6:
            printf("\nSua matriz tem dimensão : \nLinha: %d\nColuna: %d\n",l,c);
            printf("\nDigite a linha e coluna e o valor que deseja somar considerando linha inicial 0 e coluna inicial 0: \n");
            scanf("%d%d%d",&linha,&coluna,&valor);
            soma_em_cordenada(m,linha,coluna,valor);
            break;
        case 7:
            printf("\nSua matriz tem dimensão : \nLinha: %d\nColuna: %d\n",l,c);
            printf("\nDigite a linha e o valor que deseja somar considerando linha inicial 0: \n");
            scanf("%d%d",&linha,&valor);
            somalinha(m,linha,valor);
            break;
        case 8:
            printf("\nSua matriz tem dimensão : \nLinha: %d\nColuna: %d\n",l,c);
            printf("\nDigite a coluna e o valor que deseja somar considerando coluna inicial 0: \n");
            scanf("%d%d",&coluna,&valor);
            somacoluna(m,coluna,valor);
            break;
        case 9:
            printf("\nSua matriz tem dimensão : \nLinha: %d\nColuna: %d\n",l,c);
            printf("\nDigite a linha e coluna e o valor que deseja saber considerando linha inicial 0 e coluna inicial 0: \n");
            scanf("%d%d",&linha,&coluna);
            consultaposi(m,linha,coluna);
            break;
        case 10:
            printf("\nDigite o valor que deseja encontrar na matriz: \n");
            scanf("%d",&valor);
            buscar_valor(m,valor);
            break;
        case 11:
            printf("\nSua matriz tem dimensão : \nLinha: %d\nColuna: %d\n",l,c);
            printf("\nDigite a linha e coluna que deseja saber os 4 vizinhos considerando linha inicial 0 e coluna inicial 0: \n");
            scanf("%d%d",&linha,&coluna);
            imprimir_vizinhos(m,linha,coluna);
            break;
        case 12:
            libera_matriz(m);
            break;
        }
        }while(op!=13);
        return 0;
}
int menu(){
    printf("\n1-Insere na Cordenada\n");
    printf("2-Insere Aleatórios\n");
    printf("3-Remove na Cordenada\n");
    printf("4-Imprime só os alocados\n");
    printf("5-Imprime a Matriz\n");
    printf("6-Soma valor em cordenada\n");
    printf("7-Soma valor na linha toda\n");
    printf("8-Soma valor na coluna toda\n");
    printf("9-Consulta cordenada\n");
    printf("10-Consulta valor\n");
    printf("11-Imprimir Vizinhos\n");
    printf("12-Libera a Matriz\n");
    printf("13-Sair\n");
    int op;
    scanf("%d",&op);
    return op;
}

