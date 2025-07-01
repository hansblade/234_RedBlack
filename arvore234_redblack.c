#include "arvore234_redblack.h"
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

arvoreB *alocaArvoreB(){
    // Aloca uma árvore B
    arvoreB *novaArvore = (arvoreB*) malloc(sizeof(arvoreB));
    if(!novaArvore){
        return NULL;
    }

    // Aloca um nó para a raiz
    noB *noRaiz = alocaNoB();

    // Define a raiz como folha
    noRaiz->folha = 1;

    // Define a ordem da árvore como 4
    novaArvore->ordem = M;

    //Conecta a raiz criada à árvore
    novaArvore->raiz = noRaiz;

    return novaArvore;
}

noB *alocaNoB(){
    // Aloca um novo nó
    noB *novoNo = (noB*) malloc(sizeof(noB));
    if(!novoNo){
        return NULL;
    }

    //Aloca o vetor de chaves do nó
    int *vetChaves = (int*) malloc((M-1) * sizeof(int));
    
    //Faz as definições do novo nó
    novoNo->vetChaves = vetChaves;
    for(int i=0; i < M; i++){
        novoNo->vetFilhos[i] = NULL;
    }
    novoNo->noPai = NULL;
    novoNo->ocupacao = 0;
    novoNo->folha = 0;

    return novoNo;
}

void percorreArvoreB(noB *no){
    if(no != NULL){
        int i;
        for (i = 0; i < no->ocupacao; i++){
            //Percorre a sub-árvore de cada um dos filhos
            percorreArvoreB(no->vetFilhos[i]);

            //Imprime o valor da chave no vetor
            printf("%d ", no->vetChaves[i]);
        }
        //Percorre a última sub-árvore do nó
        percorreArvoreB(no->vetFilhos[i]);
    }
}

void percorreArvoreBPreOrdem(noB *no){
    if(no != NULL){
        printf("[");
        //Imprime cada um dos valores do nó
        for (int i = 0; i < no->ocupacao; i++){
            printf("%d ", no->vetChaves[i]);
        }
        printf("] ");
        //Imprime cada uma das sub-árvores
        for(int i = 0; i <= no->ocupacao; i++){
            percorreArvoreBPreOrdem(no->vetFilhos[i]);
        }
    }
}

void insereChaveB(int chave, arvoreB *arv){
    noB *aux = arv->raiz;

    if(aux->ocupacao == M - 1){
        //Faz o split da raiz caso ela esteja cheia
        //É criada uma nova raiz para isso
        noB *novaRaiz = alocaNoB();
        novaRaiz->folha = 0;
        novaRaiz->vetFilhos[0] = aux;
        split(novaRaiz, 0);
        arv->raiz = novaRaiz;
        aux->noPai = novaRaiz;
    }
    //Insere o valor caso a raiz não esteja cheia
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
        //Atualiza a ocupação do nó
        no->ocupacao++;
        printf("%d inserido -- ocupacao: %d\n", chave, no->ocupacao);

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
    //Definição do grau mínimo (t) e do nó cheio
    int t = M/2;
    noB *noCheio = pai->vetFilhos[posicaoFilho];

    //Cria um novo nó para o split
    noB *novoNo = alocaNoB();
    novoNo->folha = noCheio->folha;
    novoNo->ocupacao = t-1;

    //Passa a segunda metade do vetor para o novo nó
    for(int i = 0; i < t-1; i++){
        novoNo->vetChaves[i] = noCheio->vetChaves[i+t];
    }

    //Passa os filhos do nó para o novo nó, caso não seja folha
    if(noCheio->folha == 0){
        for(int i = 0; i < t; i++){
            novoNo->vetFilhos[i] = noCheio->vetFilhos[i + t];
            if(novoNo->vetFilhos[i]) novoNo->vetFilhos[i]->noPai = novoNo;
        }
    }

    //Define a ocupação do nó cheio após o split
    noCheio->ocupacao = t-1;

    //Encontra a posição do novo nó no nó pai
    for(int i = pai->ocupacao; i > posicaoFilho; i--){
        pai->vetFilhos[i+1] = pai->vetFilhos[i];
    }

    //Faz a conexão do pai com o novo nó
    pai->vetFilhos[posicaoFilho+1] = novoNo;

    //Encontra a posição da nova chave no nó pai
    for(int i = pai->ocupacao; i >= posicaoFilho; i--){
        pai->vetChaves[i+1] = pai->vetChaves[i];
    }

    //Passa o valor mediano do nó cheio para o pai
    pai->vetChaves[posicaoFilho] = noCheio->vetChaves[t - 1];

    //Ajusta a ocupação do pai
    pai->ocupacao++;
    printf("split!\n");

}

arvoreRB *converter234ParaRB(arvoreB *arv){
    //Inicia a conversão a partir da raiz
    noRB *novaRaiz = converterNo234(arv->raiz);

    //Pinta a raiz de preto
    if(novaRaiz != NULL){
        novaRaiz->cor = 'P';
    }

    //Aloca uma nova árvore e adiciona a raiz a ela
    arvoreRB *novaArvoreRB = alocaArvoreRB();
    novaArvoreRB->sentinela->fDir = novaRaiz;

    return novaArvoreRB;
}

noRB *converterNo234(noB *noOriginal){
    if(noOriginal == NULL) return NULL;

    //Declaração de variáveis
    noRB *noPai;
    noRB *noEsq;
    noRB *noDir;

    switch(noOriginal->ocupacao){
        case 1://Nó com 1 de ocupação e 2 filhos
            //cria um nó preto único
            noPai = alocaNoRB(noOriginal->vetChaves[0], 'P');

            //Chama a função recursivamente para os filhos
            noPai->fEsq = converterNo234(noOriginal->vetFilhos[0]);
            noPai->fDir = converterNo234(noOriginal->vetFilhos[1]);
            
            return noPai;
            break;
        case 2://Nó com 2 de ocupação e 3 filhos
            //cria uma raiz preta com um filho vermelho à esquerda
            noPai = alocaNoRB(noOriginal->vetChaves[1], 'P');
            noEsq = alocaNoRB(noOriginal->vetChaves[0], 'V');

            //Chama a função recursivamente para os filhos
            //e faz a conexão com o filho à esquerda
            noEsq->fEsq = converterNo234(noOriginal->vetFilhos[0]);
            noEsq->fDir = converterNo234(noOriginal->vetFilhos[1]);
            noPai->fEsq = noEsq;
            noPai->fDir = converterNo234(noOriginal->vetFilhos[2]);

            return noPai;
            break;
        case 3://Nó com 3 de ocupação e 4 filhos
            //cria uma raiz preta com dois filhos vermelhos
            noPai = alocaNoRB(noOriginal->vetChaves[1], 'P');
            noEsq = alocaNoRB(noOriginal->vetChaves[0], 'V');
            noDir = alocaNoRB(noOriginal->vetChaves[2], 'V');

            //Chama a função recursivamente para os filhos
            noEsq->fEsq = converterNo234(noOriginal->vetFilhos[0]);
            noEsq->fDir = converterNo234(noOriginal->vetFilhos[1]);
            noDir->fEsq = converterNo234(noOriginal->vetFilhos[2]);
            noDir->fDir = converterNo234(noOriginal->vetFilhos[3]);

            //Faz as conexões com os filhos da esquerda e da direita
            noPai->fEsq = noEsq;
            noPai->fDir = noDir;

            return noPai;
            break;
    }
}

arvoreRB *alocaArvoreRB(){
    //Aloca nova árvore RB
    arvoreRB* novaArvore = (arvoreRB*) malloc(sizeof(arvoreRB));

    //Define os valores iniciais da árvore
    noRB* sentinela = alocaNoRB(-1000, 'P');
    novaArvore->sentinela = sentinela;
    novaArvore->alturaPreto = 0;

    return novaArvore;
}

noRB *alocaNoRB(int chave, char cor){
    //Aloca novo nó RB
    noRB* novoNo= (noRB*) malloc(sizeof(noRB));

    //Define os valores iniciais do nó
    novoNo->chave=chave;
    novoNo->cor=cor;
    novoNo->fEsq=NULL;
    novoNo->fDir=NULL;
    novoNo->pai=NULL;
    novoNo->alturaPreto=0;

    return novoNo;
}

void percorreArvoreRBPreOrdem(arvoreRB *arv, noRB *aux){
    if(!aux)
        return;
    //Imprime a raiz
    printf("%d -- %c -- %d\n", aux->chave, aux->cor, aux->alturaPreto);
    //Percorre sub-árvore da esquerda
    percorreArvoreRBPreOrdem(arv, aux->fEsq);
    //Percorre sub-árvore da direita
    percorreArvoreRBPreOrdem(arv, aux->fDir);
}