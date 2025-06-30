#ifndef ARVOREB_ARVOREB_H
#define ARVOREB_ARVOREB_H

typedef struct no noB;
typedef struct arv arvoreB;

//Aloca uma nova árvore que recebe a ordem da árvore
arvoreB *alocaArvore(int m);

//Aloca um novo nó
//Recebe a ordem
noB *alocaNo(int m);

//Insere uma nova chave na árvore
void insereChave(int valor, arvoreB *arv);

//Faz o split de um nó cheio
//Retorna o nó pai
noB *split(noB *noCheio, arvoreB *arv);

//Remove uma chave da árvore
void removeChave(int valor, arvoreB *arv);

//Faz a rotação para evitar que o nó
//fique com menos que a ocupação mínima permitida
void rotacao(noB *noDesbalanceado, noB *noIrmao);

//Faz o merge entre o nó desbalanceado e um irmão
void merge(noB *noDesbalanceado, noB *noIrmao);

#endif