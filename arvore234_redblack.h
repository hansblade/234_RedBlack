#ifndef ARVOREB_ARVOREB_H
#define ARVOREB_ARVOREB_H

#include <stdio.h>
#include <stdlib.h>

//Estruturas árvore B
typedef struct no noB;
typedef struct arv arvoreB;

//Estruturas árvore RB
typedef struct noRB noRB;
typedef struct arvRB arvoreRB;

struct arv{
    noB *raiz;
    int ordem;
};

struct arvRB{
    noRB* sentinela;
    int alturaPreto;
};

struct noRB{
    int chave, alturaPreto;
    noRB *fEsq, *fDir, *pai;
    char cor;
};


// ------------------------- Operações árvore B ------------------------- //

//Aloca uma nova árvore B
arvoreB *alocaArvoreB();

//Aloca um novo nó da árvore B
noB *alocaNoB();

//Percorre a árvore B em ordem a partir de um nó
void percorreArvoreB(noB *no);

//Percorre a árvore B em pré-ordem a partir de um nó
void percorreArvoreBPreOrdem(noB *no);

//Insere uma nova chave na árvore
void insereChaveB(int chave, arvoreB *arv);

//Insere uma nova chave em um nó não cheio
void insereNaoCheio(noB *no, int chave);

//Faz o split de um nó cheio
//Recebe o pai do nó cheio e a posição do nó cheio no vetor de filhos
void split(noB *pai, int posicaoFilho);

//Remove uma chave da árvore
void removeChaveB(int valor, arvoreB *arv);

//Faz a rotação para evitar que o nó
//fique com menos que a ocupação mínima permitida
void rotacao(noB *noDesbalanceado, noB *noIrmao);

//Faz o merge entre o nó desbalanceado e um irmão
void merge(noB *noDesbalanceado, noB *noIrmao);

// ------------------------- Operações de conversão ------------------------- //

//Converte uma árvore 234 em RB
//Recebe uma árvore 234
//Retorna uma árvore RB
arvoreRB *converter234ParaRB(arvoreB *arv);

//Converte um nó da árvore 234 em um nó da árvore RB
//Recebe um nó da árvore 234
//Retorna o nó pai gerado
noRB *converterNo234(noB *no);

// ------------------------- Operações árvore RB ------------------------- //

//Aloca uma árvore RB
arvoreRB *alocaArvoreRB();

//Aloca um nó da árvore RB
//Recebe a chave e a cor do nó
noRB *alocaNoRB(int chave, char cor);

//Percorre a árvore RB em pré-ordem a partir de um nó
void percorreArvoreRBPreOrdem(arvoreRB *arv, noRB *aux);

#endif