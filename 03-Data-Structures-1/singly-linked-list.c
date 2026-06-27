//Fazer um vetor de 10 posicoes onde cada posicao aponta para uma lista ligada dinamica
//As listas armazenam chaves ordenadas
//O que determina em qual das listas o número vai ser inserido é seu último algarismo. 
//Ex:números terminados em 0, devem ser inseridos na lista indicada pela posição 0 do array.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux* prox;
}NODE;

typedef NODE* PONT;

typedef struct{
    PONT inicio;
}LISTA;

void inicializarLista(LISTA *l){
    l->inicio = NULL;
}

int descobrirPosVet(TIPOCHAVE chave){
    return chave % 10;//retorna o ultimo digito da chave como posição do vetor
}

void inserirOrdenado(LISTA *l, REGISTRO reg){
    PONT ant = NULL;
    PONT atual = l->inicio;

    while(atual != NULL && atual->reg.chave < reg.chave){
        ant = atual;
        atual = atual->prox;
    }

    PONT novo = (PONT)malloc(sizeof(NODE));
    novo->reg = reg;

    if(ant == NULL){
        novo->prox = l->inicio;
        l->inicio = novo;
    }else{
        novo->prox = ant->prox;
        ant->prox = novo;
    }
}

void inserirElemento(LISTA *vetor, REGISTRO reg){
    int posicao = descobrirPosVet(reg.chave);
    inserirOrdenado(&vetor[posicao], reg);
}

PONT buscaSequencial(TIPOCHAVE chave, LISTA *l){
    PONT atual = l->inicio;
    while(atual != NULL){
        if(atual->reg.chave == chave)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

void excluirElemento(TIPOCHAVE chave, LISTA *l){
    PONT ant = NULL;
    PONT atual = l->inicio;

    while(atual != NULL && atual->reg.chave != chave){
        ant = atual;
        atual = atual->prox;
    }

    if(atual == NULL)//nao achou o elemento
        return;

    if(ant == NULL)//o elemento eh o primeiro
        l->inicio = atual->prox;
    else
        ant->prox = atual->prox;

    free(atual);
}

void destruirLista(LISTA *l){
    PONT atual = l->inicio;
    while (atual != NULL) {
        PONT apagar = atual;
        atual = atual->prox;
        free(apagar);
    }
    l->inicio = NULL;
}

void imprimirLista(LISTA *l){
    PONT atual = l->inicio;
    while(atual != NULL){
        printf("%d -> ", atual->reg.chave);
        atual = atual->prox;
    }
    printf("NULL\n");
}

int main(){
    LISTA vetor[MAX];

    int opcao;
    REGISTRO reg;
    TIPOCHAVE chave;

    do{
        printf("\nEscolha uma opcao:\n");
        printf("1 - Inicializar lista\n");
        printf("2 - Inserir elemento\n");
        printf("3 - Buscar elemento\n");
        printf("4 - Excluir elemento\n");
        printf("5 - Destruir lista\n");
        printf("6 - Imprimir lista\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                for(int i = 0; i < MAX; i++){
                    inicializarLista(&vetor[i]);
                }
                printf("Listas inicializadas com sucesso!\n");
                break;
            case 2:
                printf("Digite a chave do elemento a ser inserido: ");
                scanf("%d", &reg.chave);
                inserirElemento(vetor, reg);
                printf("Elemento inserido com sucesso!\n");
                break;
            case 3:
                printf("Digite a chave do elemento a ser buscado: ");
                scanf("%d", &chave);
                for(int i = 0; i < MAX; i++){
                    PONT encontrado = buscaSequencial(chave, &vetor[i]);
                    if(encontrado != NULL){
                        printf("Elemento encontrado na lista %d.\n", i);
                        break;
                    }
                }
                break;
            case 4:
                printf("Digite a chave do elemento a ser excluido: ");
                scanf("%d", &chave);
                for(int i = 0; i < MAX; i++){
                    excluirElemento(chave, &vetor[i]);
                }
                printf("Elemento excluido com sucesso!\n");
                break;
            case 5:
                for(int i = 0; i < MAX; i++){
                    destruirLista(&vetor[i]);
                }
                printf("Listas destruidas com sucesso!\n");
                break;
            case 6:
                for(int i = 0; i < MAX; i++){
                    printf("Lista %d: ", i);
                    imprimirLista(&vetor[i]);
                }
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }while(opcao != 0);

    return 0;
}