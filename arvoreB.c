#include "arvoreB.h"
#include <stdlib.h>
#include <stdio.h>

#define M 4

struct no{
    int *vetChaves;
    noB *vetFilhos[M];
    noB *noPai;
    int ocupacao;
    int folha;
};

arvoreB *alocaArvore(){
    arvoreB *novaArvore = (arvoreB*) malloc(sizeof(arvoreB));
    if(!novaArvore){
        return NULL;
    }

    noB *noRaiz = alocaNo();

    noRaiz->folha = 1;

    novaArvore->ordem = M;
    novaArvore->raiz = noRaiz;

    return novaArvore;
}

noB *alocaNo(){
    noB *novoNo = (noB*) malloc(sizeof(noB));
    if(!novoNo){
        return NULL;
    }

    int *vetChaves = (int*) malloc((M-1) * sizeof(int));
    
    novoNo->vetChaves = vetChaves;
    for(int i=0; i < M; i++){
        novoNo->vetFilhos[i] = NULL;
    }
    novoNo->noPai = NULL;
    novoNo->ocupacao = 0;
    novoNo->folha = 0;

    return novoNo;
}

// void insereChave(int valor, arvoreB *arv){
//     //DECLARAÇÃO DE VARIÁVEIS
//     noB *aux = arv->raiz;
//     noB *pai = NULL;
//     int i = 0, pos = 0;;

//     //Encontrar a folha correta
//     //completar com o loop
//     while(aux->folha == 0){
//         i = 0;
//         while(i < aux->ocupacao && valor > aux->vetChaves[i]){
//             i++;
//         }
//         pai = aux;
//         pos = i;
//         aux = &aux->vetFilhos[i];

//     }

//     //Inserir na folha
//     if(aux->ocupacao < arv->ordem - 1){
//         //Inserir
//         i = aux->ocupacao - 1;
//         while(i >= 0 && valor < aux->vetChaves[i]){
//             aux->vetChaves[i] = aux->vetChaves[i-1];
//             i--;
//         }
//         aux->vetChaves[i] = valor;
//         aux->ocupacao++;
//         printf("ok");
//     }else{
//         //Split
//         split(pai, pos, arv);
//         insereChave(valor, arv);
//     }
// }

void percorreArvore(noB *no){
    if(no != NULL){
        int i;
        for (i = 0; i < no->ocupacao; i++){
            percorreArvore(no->vetFilhos[i]);
            printf("%d ", no->vetChaves[i]);
        }
        percorreArvore(no->vetFilhos[i]);
    }
}

void percorreArvorePreOrdem(noB *no){
    if(no != NULL){
        printf("[");
        for (int i = 0; i < no->ocupacao; i++){
            printf("%d ", no->vetChaves[i]);
        }
        printf("] ");
        for(int i = 0; i <= no->ocupacao; i++){
            percorreArvorePreOrdem(no->vetFilhos[i]);
        }
    }
}


void insereChave(int chave, arvoreB *arv){
    noB *aux = arv->raiz;

    if(aux->ocupacao == M - 1){
        noB *novaRaiz = alocaNo();
        novaRaiz->folha = 0;
        novaRaiz->vetFilhos[0] = aux;
        split(novaRaiz, 0);
        arv->raiz = novaRaiz;
        aux->noPai = novaRaiz;
    }
    insereNaoCheio(arv->raiz, chave);
}


void insereNaoCheio(noB *no, int chave){
    int i = no->ocupacao - 1;

    if(no->folha == 1){//Caso o nó seja folha
        //Encontra a posição correta no nó
        while(i >= 0 && no->vetChaves[i] > chave){
            no->vetChaves[i+1] = no->vetChaves[i];
            i--;
        }

        //Insere o valor na posição correta
        no->vetChaves[i+1] = chave;
        printf("%d inserido\n", chave);
        //Atualiza a ocupação do nó
        no->ocupacao++;

    }else{//Caso o nó não seja folha
        //Encontra o nó filho correto para a chave
        while(i >= 0 && no->vetChaves[i] > chave){
            i--;
        }
        i++;

        if(no->vetFilhos[i]->ocupacao == M - 1){
            //Se o nó filho estiver cheio, aciona o split
            split(no, i);

            //Encontra o filho correto para posicionar o elemento
            if(no->vetChaves[i] < chave){
                i++;
            }
        }

        //Insere o filho no próximo nó recursivamente
        //até encontrar o nó correto
        insereNaoCheio(no->vetFilhos[i], chave);

    }
}

void split(noB *pai, int posicaoFilho){
    int t = M/2;
    noB *noCheio = pai->vetFilhos[posicaoFilho];

    noB *novoNo = alocaNo();
    novoNo->folha = noCheio->folha;
    novoNo->ocupacao = t-1;

    for(int i = 0; i < t-1; i++){
        novoNo->vetChaves[i] = noCheio->vetChaves[i+t];
    }

    if(noCheio->folha == 0){
        for(int i = 0; i < t; i++){
            novoNo->vetFilhos[i] = noCheio->vetFilhos[i + t];
            if(novoNo->vetFilhos[i]) novoNo->vetFilhos[i]->noPai = novoNo;
        }
    }

    noCheio->ocupacao = t-1;

    for(int i = pai->ocupacao; i > posicaoFilho; i--){
        pai->vetFilhos[i+1] = pai->vetFilhos[i];
    }

    pai->vetFilhos[posicaoFilho+1] = novoNo;

    for(int i = pai->ocupacao; i >= posicaoFilho; i--){
        pai->vetChaves[i+1] = pai->vetChaves[i];
    }

    pai->vetChaves[posicaoFilho] = noCheio->vetChaves[t - 1];

    pai->ocupacao++;
    printf("split!\n");

}

