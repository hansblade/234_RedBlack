#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

int main(){
    arvoreB *arvore234 = alocaArvore();
    noB *raiz;

    int valores[12] = {12, 50, 45, 32, 60, 22, 34, 11, 10, 40, 15, 38};

    for(int i = 0; i < 12; i++){
        insereChave(valores[i], arvore234);
        printf("arvore em ordem: ");
        percorreArvore(arvore234->raiz);
        printf("\n");
    }

    percorreArvorePreOrdem(arvore234->raiz);

    return 0;
}