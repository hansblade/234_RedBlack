#include "arvoreB.h"
#include <stdlib.h>
#include <stdio.h>

struct no{
    int *vetChaves;
    noB *vetFilhos;
    noB *noPai;
    int ocupacao;
    int folha;
};

struct arv{
    noB *raiz;
    int ordem;
};

arvoreB *alocaArvore(int m){
    arvoreB *novaArvore = (arvoreB*) malloc(sizeof(arvoreB));
    if(!novaArvore){
        return NULL;
    }

    noB *noRaiz = alocaNo(m);

    noRaiz->folha = 1;

    novaArvore->ordem = m;
    novaArvore->raiz = noRaiz;

    return novaArvore;
}

noB *alocaNo(int m){
    noB *novoNo = (noB*) malloc(sizeof(noB));
    if(!novoNo){
        return NULL;
    }

    int *vetChaves = (int*) malloc((m-1) * sizeof(int));
    noB *vetFilhos = (noB*) malloc(m * sizeof(noB));
    
    novoNo->vetChaves = vetChaves;
    novoNo->vetFilhos = vetFilhos;
    novoNo->noPai = NULL;
    novoNo->ocupacao = 0;
    novoNo->folha = 0;

    return novoNo;
}

void insereChave(int valor, arvoreB *arv){
    //DECLARAÇÃO DE VARIÁVEIS
    noB *aux = arv->raiz;
    int i = 0;

    //Encontrar a folha correta
    //completar com o loop
    while(aux->folha == 0){
        while(valor > aux->vetChaves[i]){
            i++;
        }
        if(valor > aux->vetChaves[i])
           i++;
        aux = &aux->vetFilhos[i];

        i = 0;
    }

    //Inserir na folha
    if(aux->ocupacao < arv->ordem - 1){
        //Inserir
        i = aux->ocupacao;
        while(valor < aux->vetChaves[i]){
            aux->vetChaves[i] = aux->vetChaves[i-1];
        }
        aux->vetChaves[i] = valor;
    }else{
        //Split
        //Completar com o algoritmo do cormen
    }
}

noB *split(noB *noCheio, arvoreB *arv){
    int m = arv->ordem;
    int t = m/2;
    noB *pai = noCheio->noPai;

    noB *novoNo = alocaNo(m);
    novoNo->folha = noCheio->folha;
    novoNo->ocupacao = t-1;

    for(int i = 0; i < t-1; i++){
        novoNo->vetChaves[i] = noCheio->vetChaves[i+t];
    }

    if(noCheio->folha = 0){
        for(int i = 0; i < t; i++){
            novoNo->vetFilhos[i] = noCheio->vetFilhos[i + t];
        }
    }

    noCheio->ocupacao = t-1;



}

// 2t - 1 = 4
// 2t = 5
// t = 2,5

// 2t - 1 = 3
// 2t = 4
// t = 2