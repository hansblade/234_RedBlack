#include <stdio.h>
#include <stdlib.h>
#include "arvore234_redblack.h"

int main(){
    arvoreB *arvore234 = alocaArvoreB();
    noB *raiz;

    int valores[12] = {12, 50, 45, 32, 60, 22, 34, 11, 10, 40, 15, 38};

    for(int i = 0; i < 12; i++){
        insereChaveB(valores[i], arvore234);
        printf("arvore em ordem: ");
        percorreArvoreB(arvore234->raiz);
        printf("\n");
    }

    percorreArvoreBPreOrdem(arvore234->raiz);
    printf("\n");

    arvoreRB *arvoreRB;

    arvoreRB = converter234ParaRB(arvore234);

    percorreArvoreRBPreOrdem(arvoreRB, arvoreRB->sentinela->fDir);

    return 0;
}