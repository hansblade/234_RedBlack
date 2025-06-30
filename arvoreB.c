#include "arvoreB.h"
#include <stdlib.h>
#include <stdio.h>

struct no{
    int *vetChaves;
    noB **vetFilhos;
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
    noB *pai = NULL;
    int i = 0, pos = 0;;

    //Encontrar a folha correta
    //completar com o loop
    while(aux->folha == 0){
        i = 0;
        while(i < aux->ocupacao && valor > aux->vetChaves[i]){
            i++;
        }
        pai = aux;
        pos = i;
        aux = aux->vetFilhos[i];

    }

    //Inserir na folha
    if(aux->ocupacao < arv->ordem - 1){
        //Inserir
        i = aux->ocupacao - 1;
        while(i >= 0 && valor < aux->vetChaves[i]){
            aux->vetChaves[i] = aux->vetChaves[i-1];
            i--;
        }
        aux->vetChaves[i] = valor;
        aux->ocupacao++;
    }else{
        //Split
        split(pai, pos, arv);
        insereChave(valor, arv);
    }
}

void *split(noB *pai, int posicaoFilho, arvoreB *arv){
    int m = arv->ordem;
    int t = m/2;
    noB *noCheio = pai->vetFilhos[posicaoFilho];

    noB *novoNo = alocaNo(m);
    novoNo->folha = noCheio->folha;
    novoNo->ocupacao = t-1;

    for(int i = 1; i <= t-1; i++){
        novoNo->vetChaves[i] = noCheio->vetChaves[i+t];
    }

    if(noCheio->folha = 0){
        for(int i = 1; i <= t; i++){
            novoNo->vetFilhos[i] = noCheio->vetFilhos[i + t];
        }
    }

    noCheio->ocupacao = t-1;

    for(int i = pai->ocupacao+1; i >= posicaoFilho+1; i--){
        pai->vetFilhos[i+1] = pai->vetChaves[i];
    }

    pai->vetChaves[posicaoFilho] = noCheio->vetChaves[t];

    pai->ocupacao = pai->ocupacao+1;
}