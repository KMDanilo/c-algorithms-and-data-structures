#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2 

typedef struct no{
    struct no* adjacente;//no adjacente
    char nome[10];        
    int cor;
    struct no* prox;//prox no da lista de vertices
}no, *pont;

typedef struct{
    pont i;//inicio da lista de vertices do grafo
    int numVert;//vertices no grafo
}GRAFO;

//cria com o numero especificado
GRAFO criarGrafo(GRAFO grafo, int pontos){
    //aloca para o primeiro
    grafo.i = (pont)malloc(sizeof(no));
    pont aux = grafo.i;

    for(int i = 0; i < pontos; i++){
        printf("Ponto %d: ", i + 1);
        fgets(aux->nome, 10, stdin);
        aux->nome[strcspn(aux->nome, "\n")] = '\0';//pra n bugar

        //inicializa
        aux->adjacente = NULL;
        aux->cor = BRANCO;

        //aloca para o proximo vertice, se ainda tiver pontos para adicionar
        if(i < pontos - 1){
            aux->prox = (pont)malloc(sizeof(no));
            aux = aux->prox;
        }else{
            aux->prox = NULL;//ultimo nao tem proximo
        }

        grafo.numVert++;
    }

    return grafo;
}

//inserir as ligacoes entre os vertices
GRAFO inserirLigacoes(GRAFO grafo, int ligacoes){
    char ponto1[10], ponto2[10];// armazenar os nomes dos vertices conectados
    pont v1, v2;//para achar os vertices no grafo

    for(int i = 0; i < ligacoes; i++){
        //volta o ponteiro para o inicio da lista de vertices
        v1 = grafo.i;
        v2 = grafo.i;

        printf("\nLigacao %d:\n", i + 1);

        //le o primeiro vertice
        printf("Primeiro vertice: ");
        fgets(ponto1, 10, stdin);
        ponto1[strcspn(ponto1, "\n")] = '\0';

        //le o segundo vertice
        printf("Segundo vertice: ");
        fgets(ponto2, 10, stdin);
        ponto2[strcspn(ponto2, "\n")] = '\0';

        //acha o primeiro vertice da lista
        while(strcmp(v1->nome, ponto1) != 0){
            v1 = v1->prox;
        }

        //acha o segundo vertice da lista
        while(strcmp(v2->nome, ponto2) != 0){
            v2 = v2->prox;
        }

        //segundo vertice vira adjacente ao primeiro vertice
        pont aux1 = v1;

        while(aux1->adjacente != NULL){
            aux1 = aux1->adjacente;//vai ate o ultimo no adjacente
        }

        aux1->adjacente = (pont)malloc(sizeof(no));//novo no adjacente
        strcpy(aux1->adjacente->nome, ponto2);//nome do no adjacente
        aux1->adjacente->adjacente = NULL;//lista de adjacencia como NULL
        aux1->adjacente->cor = BRANCO;//cor do no adjacente BRANCO

        //primeiro vertice vira adjacente ao segundo vertice
        pont aux2 = v2;

        while(aux2->adjacente != NULL){
            aux2 = aux2->adjacente;//ate o ultimo no adjacente
        }
        aux2->adjacente = (pont)malloc(sizeof(no));//novo no adjacente
        strcpy(aux2->adjacente->nome, ponto1);//nome do no adjacente        
        aux2->adjacente->adjacente = NULL;//lista de adjacencia como NULL
        aux2->adjacente->cor = BRANCO;//cor do no adjacente BRANCO
    }

    return grafo;
}

//busca no grafo pelo nome
pont buscarNoGrafo(GRAFO grafo, char* nome){
    pont aux = grafo.i;//iterar sobre a lista de vertices

    //acha o no com o nome
    while (strcmp(aux->nome, nome) != 0) {
        aux = aux->prox;
    }

    return aux;//retorna o no encontrado
}

void DFS(GRAFO grafo, pont partida, pont destino, int *menorCaminho, int *cont){
    pont adj, noI;//noI eh o no adjacente encontrado na lista de adjacentes
    
    if(partida == destino){
        //atualiza o menor caminho encontrado se necessario
        if (*cont < *menorCaminho) *menorCaminho = *cont;
        return;
    }

    partida->cor = CINZA;
    adj = partida;//inicializa o ponteiro adjacente

    *cont = *cont + 1;//contador do caminho
    
    //todos os nos adjacentes
    while(adj->adjacente != NULL){
        noI = buscarNoGrafo(grafo, adj->adjacente->nome);// real correspondente ao no adjacente

        if(noI->cor == BRANCO){
            DFS(grafo, noI, destino, menorCaminho, cont);//DFS recursivo
        }
        
    
        if(noI == destino) break;        
        
        //se o no real ja foi visitado, passa para o proximo no adjacente
        if(noI->cor == CINZA || noI->cor == PRETO){
            adj = adj->adjacente; 
        }
    }

    *cont = *cont - 1;//contador do caminho, voltando

    partida->cor = PRETO;//no de partida como PRETO, visitou td
}

int main(){
    int pontos, ligacoes;
    GRAFO grafo;
    grafo.numVert = 0;

    printf("Coloque o numero de vertices e de ligacoes: ");
    scanf("%d%d", &pontos, &ligacoes);
    getchar();

    grafo = criarGrafo(grafo, pontos);

    grafo = inserirLigacoes(grafo, ligacoes);

    int menor_caminho_total, menorCaminho, cont;//armazenar o menor caminho e contador

    menorCaminho = INT_MAX;//menor caminho como o valor maximo possivel
    cont = 0;//o contador do caminho

    //DFS ate o *
    DFS(grafo, grafo.i, grafo.i->prox->prox, &menorCaminho, &cont);

    menor_caminho_total = menorCaminho;//pega o menor caminho total

    //reinicializa a cor dos vertices para BRANCO
    pont aux2 = grafo.i;
    while (aux2->prox != NULL) {
        aux2->cor = BRANCO;
        aux2 = aux2->prox;
    }

    menorCaminho = INT_MAX;//menor caminho como o valor maximo possivel
    cont = 0;//contador do caminho

    //* ate a saida
    DFS(grafo, grafo.i->prox->prox, grafo.i->prox, &menorCaminho, &cont);

    menor_caminho_total += menorCaminho;
    printf("Caminho: %d\n", menor_caminho_total);//imprime o menor caminho total

    return 0;
}