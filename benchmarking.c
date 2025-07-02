#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore234_redblack.h"

int *geraDados(int tam)
{
    // aloca um vetor dinamicamente
    int *vet = (int *)malloc(sizeof(int) * tam);
    if (!vet)
    {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    // seta uma semente aleatória toda vez que a função é chamada
    srand(time(NULL));

    for (int i = 0; i < tam; i++)
    {
        vet[i] = rand() % 100001;
    }

    // for (int i = 0; i < tam; i++)
    // {
    //     printf("%d ", vet[i]);
    // }

    return vet;
}

int main()
{
    int tams[4] = {100, 1000, 10000, 100000};
    int *dados[4];
    for (int i = 0; i < 4; i++)
    {
        dados[i] = geraDados(tams[i]);

        arvoreB *arv234 = alocaArvoreB();

        for (int j = 0; j < tams[i]; j++)
        {
            insereChaveB(dados[i][j], arv234);
        }

        printf("\n ---- Comportamento da arvore 2-3-4 com %d elementos ----\n", tams[i]);
        printf("Numero de blocos ocupados: %d\n", arv234->blocosOcupados);
        printf("Numero de splits: %d\n", arv234->splits);
        printf("Altura da árvore: %d\n", alturaArvoreB(arv234));
        // printf("Número de merges: %d\n", merges);
        // printf("Número de rotações: %d\n", rotacao);

        free(dados[i]);
    }

    return 0;
}