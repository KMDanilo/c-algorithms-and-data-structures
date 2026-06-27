#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux *ant;
    struct aux* prox;
}NODE, *PONT;

typedef struct{
    PONT cabeca;
}DEQUE;

void inicializarDeque(DEQUE *d){
    d->cabeca = (PONT)malloc(sizeof(NODE));//aloca a cabeca do deque
    d->cabeca->prox = d->cabeca;//arruma os ponteiros
    d->cabeca->ant = d->cabeca;
}
bool inserirElementosFim(DEQUE *d, REGISTRO reg){
    PONT novo = (PONT)malloc(sizeof(NODE));//aloca o novo nó
    novo->reg = reg;
    if(novo = NULL){//se a alocação der errado retorna 0
        return false;
    }
    //arrumar os 4 ponteiros
    novo->prox = d->cabeca->ant;
    novo->ant = d->cabeca->prox;
    d->cabeca->prox = novo->ant;
    d->cabeca->ant = novo->prox;
    return true;
}
