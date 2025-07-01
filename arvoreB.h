#ifndef ARVOREB_ARVOREB_H
#define ARVOREB_ARVOREB_H

#include <stdio.h>
#include <stdlib.h>


typedef struct no noB;
typedef struct arv arvoreB;

struct arv{
    noB *raiz;
    int ordem;
};

//Aloca uma nova árvore que recebe a ordem da árvore
arvoreB *alocaArvore();

//Aloca um novo nó
//Recebe a ordem
noB *alocaNo();

void percorreArvore(noB *no);

//Insere uma nova chave na árvore
void insereChave(int chave, arvoreB *arv);

void insereNaoCheio(noB *no, int chave);

//Faz o split de um nó cheio
//Retorna o nó pai
void *split(noB *pai, int posicaoFilho);

//Remove uma chave da árvore
void removeChave(int valor, arvoreB *arv);

//Faz a rotação para evitar que o nó
//fique com menos que a ocupação mínima permitida
void rotacao(noB *noDesbalanceado, noB *noIrmao);

//Faz o merge entre o nó desbalanceado e um irmão
void merge(noB *noDesbalanceado, noB *noIrmao);

#endif