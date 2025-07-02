#ifndef ARVOREB_ARVOREB_H
#define ARVOREB_ARVOREB_H

#include <stdio.h>
#include <stdlib.h>

// Estruturas árvore B
typedef struct no noB;
typedef struct arv arvoreB;

// Estruturas árvore RB
typedef struct noRB noRB;
typedef struct arvRB arvoreRB;

struct arv
{
    noB *raiz;
    int ordem;
    long long splits;
    long long blocosOcupados;
};

struct arvRB
{
    noRB *sentinela;
    int alturaPreto;
};

struct noRB
{
    int chave, alturaPreto;
    noRB *fEsq, *fDir, *pai;
    char cor;
};

// ------------------------- Operações árvore B ------------------------- //

// Aloca uma nova árvore B
arvoreB *alocaArvoreB();

// Aloca um novo nó da árvore B
noB *alocaNoB();

int alturaArvoreB(arvoreB *arvore);

// Percorre a árvore B em ordem a partir de um nó
void percorreArvoreB(noB *no);

// Percorre a árvore B em pré-ordem a partir de um nó
void percorreArvoreBPreOrdem(noB *no);

// Insere uma nova chave na árvore
void insereChaveB(int chave, arvoreB *arv);

// Insere uma nova chave em um nó não cheio
void insereNaoCheio(noB *no, int chave, arvoreB *arv);

// Faz o split de um nó cheio
// Recebe o pai do nó cheio e a posição do nó cheio no vetor de filhos
void split(noB *pai, int posicaoFilho, arvoreB *arv);

// Remove uma chave da árvore
void removeChaveB(int valor, arvoreB *arv);

// Faz a rotação para evitar que o nó
// fique com menos que a ocupação mínima permitida
void rotacao(noB *noDesbalanceado, noB *noIrmao);

// Faz o merge entre o nó desbalanceado e um irmão
void merge(noB *noDesbalanceado, noB *noIrmao);

// ------------------------- Operações de conversão ------------------------- //

// Converte uma árvore 234 em RB
// Recebe uma árvore 234
// Retorna uma árvore RB
arvoreRB *converter234ParaRB(arvoreB *arv);

// Converte um nó da árvore 234 em um nó da árvore RB
// Recebe um nó da árvore 234
// Retorna o nó pai gerado
noRB *converterNo234(noB *no);

// ------------------------- Operações árvore RB ------------------------- //

// Aloca uma árvore RB
arvoreRB *alocaArvoreRB();

// Aloca um nó da árvore RB
// Recebe a chave e a cor do nó
noRB *alocaNoRB(int chave, char cor);

// Percorre a árvore RB em pré-ordem a partir de um nó
void percorreArvoreRBPreOrdem(arvoreRB *arv, noRB *aux);

// Insere novo nó já alocado na árvore RB
void insereNoRB(arvoreRB *arv, noRB *novoNo);

// Remove um nó da árvore RB com base em seu valor
int removeNoRB(arvoreRB *arv, int valor);

// Faz o balanceamento da árvore após uma inserção
void balanceamentoInsercao(arvoreRB *arv, noRB *novoNo);

// Faz o balanceamento da árvore após uma remoção
void balanceamentoRemocao(arvoreRB *arv, noRB *NoSucessor, noRB *NoPai);

// Faz a rotação à esquerda para o balanceamento
void rotacaoEsquerda(arvoreRB *arv, noRB *noDesbalanceado);

// Faz a rotação à direita para o balanceamento
void rotacaoDireita(arvoreRB *arv, noRB *noDesbalanceado);

// Atualiza a altura de preto dos nós recursivamente
int atualiza_Altura_Preto(arvoreRB *arv, noRB *noAux);

// Atualiza a altura de preto da árvore
void atualiza_Altura_Preto_RB(arvoreRB *arv);

#endif