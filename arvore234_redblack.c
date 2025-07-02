#include "arvore234_redblack.h"
#include <stdlib.h>
#include <stdio.h>

#define M 4

struct no
{
    int *vetChaves;
    noB *vetFilhos[M];
    noB *noPai;
    int ocupacao;
    int folha;
};

// ------------------------- Operações árvore B ------------------------- //

arvoreB *alocaArvoreB()
{
    // Aloca uma árvore B
    arvoreB *novaArvore = (arvoreB *)malloc(sizeof(arvoreB));
    if (!novaArvore)
    {
        return NULL;
    }

    // Aloca um nó para a raiz
    noB *noRaiz = alocaNoB();

    // Define a raiz como folha
    noRaiz->folha = 1;

    // Define a ordem da árvore como 4
    novaArvore->ordem = M;

    // Conecta a raiz criada à árvore
    novaArvore->raiz = noRaiz;

    return novaArvore;
}

noB *alocaNoB()
{
    // Aloca um novo nó
    noB *novoNo = (noB *)malloc(sizeof(noB));
    if (!novoNo)
    {
        return NULL;
    }

    // Aloca o vetor de chaves do nó
    int *vetChaves = (int *)malloc((M - 1) * sizeof(int));

    // Faz as definições do novo nó
    novoNo->vetChaves = vetChaves;
    for (int i = 0; i < M; i++)
    {
        novoNo->vetFilhos[i] = NULL;
    }
    novoNo->noPai = NULL;
    novoNo->ocupacao = 0;
    novoNo->folha = 0;

    return novoNo;
}

void percorreArvoreB(noB *no)
{
    if (no != NULL)
    {
        int i;
        for (i = 0; i < no->ocupacao; i++)
        {
            // Percorre a sub-árvore de cada um dos filhos
            percorreArvoreB(no->vetFilhos[i]);

            // Imprime o valor da chave no vetor
            printf("%d ", no->vetChaves[i]);
        }
        // Percorre a última sub-árvore do nó
        percorreArvoreB(no->vetFilhos[i]);
    }
}

void percorreArvoreBPreOrdem(noB *no)
{
    if (no != NULL)
    {
        printf("[");
        // Imprime cada um dos valores do nó
        for (int i = 0; i < no->ocupacao; i++)
        {
            printf("%d ", no->vetChaves[i]);
        }
        printf("] ");
        // Imprime cada uma das sub-árvores
        for (int i = 0; i <= no->ocupacao; i++)
        {
            percorreArvoreBPreOrdem(no->vetFilhos[i]);
        }
    }
}

void insereChaveB(int chave, arvoreB *arv)
{
    noB *aux = arv->raiz;

    if (aux->ocupacao == M - 1)
    {
        // Faz o split da raiz caso ela esteja cheia
        // É criada uma nova raiz para isso
        noB *novaRaiz = alocaNoB();
        novaRaiz->folha = 0;
        novaRaiz->vetFilhos[0] = aux;
        split(novaRaiz, 0);
        arv->raiz = novaRaiz;
        aux->noPai = novaRaiz;
    }
    // Insere o valor caso a raiz não esteja cheia
    insereNaoCheio(arv->raiz, chave);
}

void insereNaoCheio(noB *no, int chave)
{
    int i = no->ocupacao - 1;

    if (no->folha == 1)
    { // Caso o nó seja folha
        // Encontra a posição correta no nó
        while (i >= 0 && no->vetChaves[i] > chave)
        {
            no->vetChaves[i + 1] = no->vetChaves[i];
            i--;
        }

        // Insere o valor na posição correta
        no->vetChaves[i + 1] = chave;
        // Atualiza a ocupação do nó
        no->ocupacao++;
        printf("%d inserido -- ocupacao: %d\n", chave, no->ocupacao);
    }
    else
    { // Caso o nó não seja folha
        // Encontra o nó filho correto para a chave
        while (i >= 0 && no->vetChaves[i] > chave)
        {
            i--;
        }
        i++;

        if (no->vetFilhos[i]->ocupacao == M - 1)
        {
            // Se o nó filho estiver cheio, aciona o split
            split(no, i);

            // Encontra o filho correto para posicionar o elemento
            if (no->vetChaves[i] < chave)
            {
                i++;
            }
        }

        // Insere o filho no próximo nó recursivamente
        // até encontrar o nó correto
        insereNaoCheio(no->vetFilhos[i], chave);
    }
}

void split(noB *pai, int posicaoFilho)
{
    // Definição do grau mínimo (t) e do nó cheio
    int t = M / 2;
    noB *noCheio = pai->vetFilhos[posicaoFilho];

    // Cria um novo nó para o split
    noB *novoNo = alocaNoB();
    novoNo->folha = noCheio->folha;
    novoNo->ocupacao = t - 1;

    // Passa a segunda metade do vetor para o novo nó
    for (int i = 0; i < t - 1; i++)
    {
        novoNo->vetChaves[i] = noCheio->vetChaves[i + t];
    }

    // Passa os filhos do nó para o novo nó, caso não seja folha
    if (noCheio->folha == 0)
    {
        for (int i = 0; i < t; i++)
        {
            novoNo->vetFilhos[i] = noCheio->vetFilhos[i + t];
            if (novoNo->vetFilhos[i])
                novoNo->vetFilhos[i]->noPai = novoNo;
        }
    }

    // Define a ocupação do nó cheio após o split
    noCheio->ocupacao = t - 1;

    // Encontra a posição do novo nó no nó pai
    for (int i = pai->ocupacao; i > posicaoFilho; i--)
    {
        pai->vetFilhos[i + 1] = pai->vetFilhos[i];
    }

    // Faz a conexão do pai com o novo nó
    pai->vetFilhos[posicaoFilho + 1] = novoNo;

    // Encontra a posição da nova chave no nó pai
    for (int i = pai->ocupacao; i >= posicaoFilho; i--)
    {
        pai->vetChaves[i + 1] = pai->vetChaves[i];
    }

    // Passa o valor mediano do nó cheio para o pai
    pai->vetChaves[posicaoFilho] = noCheio->vetChaves[t - 1];

    // Ajusta a ocupação do pai
    pai->ocupacao++;
    printf("split!\n");
}

// ------------------------- Operações de conversão ------------------------- //

arvoreRB *converter234ParaRB(arvoreB *arv)
{
    // Inicia a conversão a partir da raiz
    noRB *novaRaiz = converterNo234(arv->raiz);

    // Pinta a raiz de preto
    if (novaRaiz != NULL)
    {
        novaRaiz->cor = 'P';
    }

    // Aloca uma nova árvore e adiciona a raiz a ela
    arvoreRB *novaArvoreRB = alocaArvoreRB();
    novaArvoreRB->sentinela->fDir = novaRaiz;
    novaRaiz->pai = novaArvoreRB->sentinela;

    return novaArvoreRB;
}

noRB *converterNo234(noB *noOriginal)
{
    if (noOriginal == NULL)
        return NULL;

    // Declaração de variáveis
    noRB *noPai;
    noRB *noEsq;
    noRB *noDir;

    switch (noOriginal->ocupacao)
    {
    case 1: // Nó com 1 de ocupação e 2 filhos
        // cria um nó preto único
        noPai = alocaNoRB(noOriginal->vetChaves[0], 'P');

        // Chama a função recursivamente para os filhos
        noPai->fEsq = converterNo234(noOriginal->vetFilhos[0]);
        if (noPai->fEsq)
            noPai->fEsq->pai = noPai;

        noPai->fDir = converterNo234(noOriginal->vetFilhos[1]);
        if (noPai->fDir)
            noPai->fDir->pai = noPai;

        return noPai;
        break;
    case 2: // Nó com 2 de ocupação e 3 filhos
        // cria uma raiz preta com um filho vermelho à esquerda
        noPai = alocaNoRB(noOriginal->vetChaves[1], 'P');
        noEsq = alocaNoRB(noOriginal->vetChaves[0], 'V');

        // Chama a função recursivamente para os filhos
        // e faz a conexão com o filho à esquerda
        noEsq->fEsq = converterNo234(noOriginal->vetFilhos[0]);
        if (noEsq->fEsq)
            noEsq->fEsq->pai = noEsq;

        noEsq->fDir = converterNo234(noOriginal->vetFilhos[1]);
        if (noEsq->fDir)
            noEsq->fDir->pai = noEsq;

        noPai->fEsq = noEsq;
        noEsq->pai = noPai;

        noPai->fDir = converterNo234(noOriginal->vetFilhos[2]);
        if (noPai->fDir)
            noPai->fDir->pai = noPai;

        return noPai;
        break;
    case 3: // Nó com 3 de ocupação e 4 filhos
        // cria uma raiz preta com dois filhos vermelhos
        noPai = alocaNoRB(noOriginal->vetChaves[1], 'P');
        noEsq = alocaNoRB(noOriginal->vetChaves[0], 'V');
        noDir = alocaNoRB(noOriginal->vetChaves[2], 'V');

        // Chama a função recursivamente para os filhos
        noEsq->fEsq = converterNo234(noOriginal->vetFilhos[0]);
        if (noEsq->fEsq)
            noEsq->fEsq->pai = noEsq;

        noEsq->fDir = converterNo234(noOriginal->vetFilhos[1]);
        if (noEsq->fDir)
            noEsq->fDir->pai = noEsq;

        noDir->fEsq = converterNo234(noOriginal->vetFilhos[2]);
        if (noDir->fEsq)
            noDir->fEsq->pai = noDir;

        noDir->fDir = converterNo234(noOriginal->vetFilhos[3]);
        if (noDir->fDir)
            noDir->fDir->pai = noDir;

        // Faz as conexões com os filhos da esquerda e da direita
        noPai->fEsq = noEsq;
        noEsq->pai = noPai;

        noPai->fDir = noDir;
        noDir->pai = noPai;

        return noPai;
        break;
    }
}

// ------------------------- Operações árvore RB ------------------------- //

arvoreRB *alocaArvoreRB()
{
    // Aloca nova árvore RB
    arvoreRB *novaArvore = (arvoreRB *)malloc(sizeof(arvoreRB));

    // Define os valores iniciais da árvore
    noRB *sentinela = alocaNoRB(-1000, 'P');
    sentinela->fDir = NULL;
    novaArvore->sentinela = sentinela;
    novaArvore->alturaPreto = 0;

    return novaArvore;
}

noRB *alocaNoRB(int chave, char cor)
{
    // Aloca novo nó RB
    noRB *novoNo = (noRB *)malloc(sizeof(noRB));

    // Define os valores iniciais do nó
    novoNo->chave = chave;
    novoNo->cor = cor;
    novoNo->fEsq = NULL;
    novoNo->fDir = NULL;
    novoNo->pai = NULL;
    novoNo->alturaPreto = 0;

    return novoNo;
}

void percorreArvoreRBPreOrdem(arvoreRB *arv, noRB *aux)
{
    if (!aux)
        return;
    // Imprime a raiz
    printf("%d -- %c -- %d\n", aux->chave, aux->cor, aux->alturaPreto);
    // Percorre sub-árvore da esquerda
    percorreArvoreRBPreOrdem(arv, aux->fEsq);
    // Percorre sub-árvore da direita
    percorreArvoreRBPreOrdem(arv, aux->fDir);
}

void insereNoRB(arvoreRB *arv, noRB *novoNo)
{
    noRB *aux = arv->sentinela->fDir;
    noRB *auxPai = arv->sentinela;
    while (aux != NULL)
    {
        auxPai = aux;
        if (novoNo->chave < aux->chave)
            aux = aux->fEsq;
        else
            aux = aux->fDir;
    }
    if (novoNo->chave < auxPai->chave)
        auxPai->fEsq = novoNo;
    else
        auxPai->fDir = novoNo;
    novoNo->pai = auxPai;
    balanceamentoInsercao(arv, novoNo);
    atualiza_Altura_Preto(arv, arv->sentinela->fDir);
    atualiza_Altura_Preto_RB(arv);
}

int removeNoRB(arvoreRB *arv, int valor)
{
    noRB *aux = arv->sentinela->fDir;
    noRB *sub, *predecessor;
    while (aux && aux->chave != valor)
    {
        if (valor < aux->chave)
            aux = aux->fEsq;
        else
            aux = aux->fDir;
    }
    if (!aux)
        return 0;
    char corRemovida = aux->cor;
    if (!aux->fEsq && !aux->fDir)
    {
        if (aux->pai->fEsq == aux)
            aux->pai->fEsq = NULL;
        else
            aux->pai->fDir = NULL;
        if (corRemovida == 'P')
            balanceamentoRemocao(arv, NULL, aux->pai);
    }
    else if (aux->fEsq && aux->fDir)
    {
        predecessor = aux->fEsq;
        sub = predecessor;
        while (sub->fDir)
            sub = sub->fDir;
        aux->chave = sub->chave;
        if (sub->fEsq)
        {
            if (sub->pai->fEsq == sub)
                sub->pai->fEsq = sub->fEsq;
            else
                sub->pai->fDir = sub->fEsq;
            sub->fEsq->pai = sub->pai;
        }
        else
        {
            if (sub->pai->fEsq == sub)
                sub->pai->fEsq = NULL;
            else
                sub->pai->fDir = NULL;
        }
        if (sub->cor == 'P')
            balanceamentoRemocao(arv, sub->fEsq, sub->pai);
        aux = sub;
    }
    else if (aux->fEsq)
    {
        sub = aux->fEsq;
        if (aux->pai->fEsq == aux)
            aux->pai->fEsq = sub;
        else
            aux->pai->fDir = sub;
        sub->pai = aux->pai;
        if (aux->cor == 'P')
            balanceamentoRemocao(arv, sub, aux->pai);
    }
    else if (aux->fDir)
    {
        sub = aux->fDir;
        if (aux->pai->fEsq == aux)
            aux->pai->fEsq = sub;
        else
            aux->pai->fDir = sub;
        sub->pai = aux->pai;
        if (aux->cor == 'P')
            balanceamentoRemocao(arv, sub, aux->pai);
    }
    free(aux);
    atualiza_Altura_Preto(arv, arv->sentinela->fDir);
    atualiza_Altura_Preto_RB(arv);
    return 1;
}

void balanceamentoInsercao(arvoreRB *arv, noRB *novoNo)
{
    noRB *tio, *avo;
    while (novoNo->pai && novoNo->pai->cor == 'V')
    {
        avo = novoNo->pai->pai;
        if (novoNo->pai == avo->fEsq)
        {
            tio = avo->fDir;
            if (tio && tio->cor == 'V')
            {
                novoNo->pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                novoNo = avo;
            }
            else
            {
                if (novoNo == novoNo->pai->fDir)
                {
                    novoNo = novoNo->pai;
                    rotacaoEsquerda(arv, novoNo);
                }
                novoNo->pai->cor = 'P';
                avo->cor = 'V';
                rotacaoDireita(arv, avo);
            }
        }
        else
        {
            tio = avo->fEsq;
            if (tio && tio->cor == 'V')
            {
                novoNo->pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                novoNo = avo;
            }
            else
            {
                if (novoNo == novoNo->pai->fEsq)
                {
                    novoNo = novoNo->pai;
                    rotacaoDireita(arv, novoNo);
                }
                novoNo->pai->cor = 'P';
                avo->cor = 'V';
                rotacaoEsquerda(arv, avo);
            }
        }
    }
    arv->sentinela->fDir->cor = 'P';
}

void balanceamentoRemocao(arvoreRB *arv, noRB *NoSucessor, noRB *NoPai)
{
    noRB *irmao;
    while (NoSucessor != arv->sentinela->fDir && (!NoSucessor || NoSucessor->cor == 'P'))
    {
        if (NoSucessor == NoPai->fEsq)
        {
            irmao = NoPai->fDir;
            if (irmao && irmao->cor == 'V')
            {
                irmao->cor = 'P';
                NoPai->cor = 'V';
                rotacaoEsquerda(arv, NoPai);
                irmao = NoPai->fDir;
            }
            if ((!irmao->fEsq || irmao->fEsq->cor == 'P') && (!irmao->fEsq || irmao->fDir->cor == 'P'))
            {
                irmao->cor = 'V';
                NoSucessor = NoPai;
            }
            else
            {
                if (!irmao->fDir || irmao->fDir->cor == 'P')
                {
                    irmao->fEsq->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoDireita(arv, irmao);
                    irmao = NoPai->fDir;
                }
                irmao->cor = NoPai->cor;
                NoPai->cor = 'P';
                irmao->fDir->cor = 'P';
                rotacaoEsquerda(arv, NoPai);
                NoSucessor = arv->sentinela->fDir;
            }
        }
        else
        {
            irmao = NoPai->fEsq;
            if (irmao && irmao->cor == 'V')
            {
                irmao->cor = 'P';
                NoPai->cor = 'V';
                rotacaoDireita(arv, NoPai);
                irmao = NoPai->fEsq;
            }
            if ((!irmao->fEsq || irmao->fEsq->cor == 'P') && (!irmao->fEsq || irmao->fDir->cor == 'P'))
            {
                irmao->cor = 'V';
                NoSucessor = NoPai;
            }
            else
            {
                if (!irmao->fEsq || irmao->fEsq->cor == 'P')
                {
                    irmao->fDir->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoEsquerda(arv, irmao);
                    irmao = NoPai->fEsq;
                }
                irmao->cor = NoPai->cor;
                NoPai->cor = 'P';
                irmao->fEsq->cor = 'P';
                rotacaoDireita(arv, NoPai);
                NoSucessor = arv->sentinela->fDir;
            }
        }
    }
    NoSucessor->cor = 'P';
}

void rotacaoEsquerda(arvoreRB *arv, noRB *noDesbalanceado)
{
    noRB *pai = noDesbalanceado->pai;
    noRB *filho = noDesbalanceado->fDir;
    noRB *neto = filho->fEsq;
    noDesbalanceado->fDir = neto;
    if (neto)
        neto->pai = noDesbalanceado;
    if (pai == arv->sentinela)
    {
        arv->sentinela->fDir = filho;
    }
    else if (noDesbalanceado == pai->fEsq)
    {
        pai->fEsq = filho;
    }
    else
    {
        pai->fDir = filho;
    }

    filho->pai = pai;
    filho->fEsq = noDesbalanceado;
    noDesbalanceado->pai = filho;
}

void rotacaoDireita(arvoreRB *arv, noRB *noDesbalanceado)
{
    noRB *pai = noDesbalanceado->pai;
    noRB *filho = noDesbalanceado->fEsq;
    noRB *neto = filho->fDir;
    noDesbalanceado->fEsq = neto;
    if (neto)
        neto->pai = noDesbalanceado;
    if (pai == arv->sentinela)
    {
        arv->sentinela->fDir = filho;
    }
    else if (noDesbalanceado == pai->fEsq)
    {
        pai->fEsq = filho;
    }
    else
    {
        pai->fDir = filho;
    }
    filho->pai = pai;
    filho->fDir = noDesbalanceado;
    noDesbalanceado->pai = filho;
}

int atualiza_Altura_Preto(arvoreRB *arv, noRB *noAux)
{
    if (!noAux)
        return 0;
    int alturaEsq = atualiza_Altura_Preto(arv, noAux->fEsq);
    int alturaDir = atualiza_Altura_Preto(arv, noAux->fDir);
    int noPreto = 0;
    if (noAux->cor == 'P')
        noPreto = 1;
    noAux->alturaPreto = alturaEsq + noPreto;
    return noAux->alturaPreto;
}

void atualiza_Altura_Preto_RB(arvoreRB *arv)
{
    arv->alturaPreto = arv->sentinela->fDir->alturaPreto;
}
