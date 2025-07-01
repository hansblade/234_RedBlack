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


// Operações árvore B

//Aloca uma nova árvore que recebe a ordem da árvore
arvoreB *alocaArvoreB();

//Aloca um novo nó
//Recebe a ordem
noB *alocaNoB();

void percorreArvoreB(noB *no);

void percorreArvoreBPreOrdem(noB *no);

//Insere uma nova chave na árvore
void insereChaveB(int chave, arvoreB *arv);

void insereNaoCheio(noB *no, int chave);

//Faz o split de um nó cheio
void split(noB *pai, int posicaoFilho);

//Remove uma chave da árvore
void removeChaveB(int valor, arvoreB *arv);

//Faz a rotação para evitar que o nó
//fique com menos que a ocupação mínima permitida
void rotacao(noB *noDesbalanceado, noB *noIrmao);

//Faz o merge entre o nó desbalanceado e um irmão
void merge(noB *noDesbalanceado, noB *noIrmao);

arvoreRB *converter234ParaRB(arvoreB *arv);

noRB *converterNo234(noB *no);

// Operações Árvore RB


arvoreRB *alocaArvoreRB();

noRB *alocaNoRB(int chave, char cor);

void percorreArvoreRBPreOrdem(arvoreRB *arv, noRB *aux);

#endif