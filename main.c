#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arvore234_redblack.h"

void menuRB(arvoreRB *aRB);
void menu234(arvoreB *a234);

int main()
{

    noB *raiz;

    FILE *arq;
    char nomeArq[50];
    int valor;

    // Leitura do arquivo de entrada
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArq);

    arq = fopen(nomeArq, "r");
    if (!arq)
    {
        printf("Arquivo não encontrado\n");
        return 1;
    }

    arvoreB *arv234 = alocaArvoreB();
    while (fscanf(arq, "%d", &valor) != EOF)
    {
        insereChaveB(valor, arv234);
    }

    fclose(arq);

    printf("\n-------------------------------------------");
    printf("\n          Árvore 2-3-4\n");
    printf("-------------------------------------------\n");

    percorreArvoreBPreOrdem(arv234->raiz);

    menu234(arv234);

    return 0;
}

void menu234(arvoreB *a234)
{
    int op = 0, num;

    while (op != 5)
    {
        printf("\n-------------------------------------------");
        printf("\n      Árvores Balanceadas 234: Menu\n");
        printf("-------------------------------------------\n");
        printf("1. Inserir novo elemento na árvore 2-3-4\n");
        printf("2. Remover elemento da árvore 2-3-4\n");
        printf("3. Imprimir árvore 2-3-4\n");
        printf("4. Converter em uma árvore rubro-negra\n");
        printf("5. Sair\n");
        printf("\nDigite a opção desejada: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\nDigite o valor a ser inserido: ");
            scanf("%d", &num);
            insereChaveB(num, a234);
            printf("\n\n");
            percorreArvoreBPreOrdem(a234->raiz);
            printf("\n\n");
            break;

            // case 2:
            //     printf("\nDigite o valor a ser removido: ");
            //     scanf("%d", &num);
            //     removeChaveB(a234, num);
            //     printf("\n-------------------------------------------");
            //     percorreArvoreBPreOrdem(a234->raiz);
            //     printf("\n-------------------------------------------");
            //     break;

        case 3:
            printf("\nImprimindo árvore 2-3-4\n\n");
            percorreArvoreBPreOrdem(a234->raiz);
            printf("\n\n");
            break;

        case 4:
            arvoreRB *aRB = converter234ParaRB(a234);

            if (!converter234ParaRB)
            {
                printf("\nErro ao converter a árvore 2-3-4 para árvore rubro-negra\n");
                break;
            }

            printf("\nÁrvore 2-3-4 convertida em árvore rubro-negra\n\n");
            percorreArvoreRBPreOrdem(aRB, aRB->sentinela->fDir);
            printf("\n\n");

            menuRB(aRB);
            op = 5;
            break;

        case 5:
            printf("Adeus!\n");
            break;

        default:
            printf("Opção inválida\n");
            break;
        }
    }
}

void menuRB(arvoreRB *aRB)
{
    int op = 0, num;

    while (op != 4)
    {
        printf("\n-------------------------------------------");
        printf("\n      Árvores Balanceadas RB: Menu\n");
        printf("-------------------------------------------\n");
        printf("1. Inserir novo elemento na árvore rubro-negra\n");
        printf("2. Remover elemento da árvore rubro-negra\n");
        printf("3. Imprimir árvore rubro-negra\n");
        printf("4. Sair\n");
        printf("\nDigite a opção desejada: ");
        scanf("%d", &op);

        switch (op)
        {
            // case 1:
            //     printf("\nDigite o valor a ser inserido: ");
            //     scanf("%d", &num);
            //     insereChaveRB(aRB, num);
            //     printf("\n\n");
            //     percorreArvoreRBPreOrdem(aRB, aRB->sentinela->fDir);
            //     printf("\n\n");
            //     break;
            //
            // case 2:
            //     printf("Digite o valor a ser removido: ");
            //     scanf("%d", &num);
            //     removeChaveRB(aRB, num);
            //     printf("\n\n");
            //     percorreArvoreRBPreOrdem(aRB, aRB->sentinela->fDir);
            //     printf("\n\n");
            //     break;

        case 3:
            printf("\nImprimindo árvore RB\n\n");
            percorreArvoreRBPreOrdem(aRB, aRB->sentinela->fDir);
            printf("\n");
            break;

        case 4:
            printf("Adeus!\n");
            break;

        default:
            printf("Opção inválida\n");
            break;
        }
    }
}