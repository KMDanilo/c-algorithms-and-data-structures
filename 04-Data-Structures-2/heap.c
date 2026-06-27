#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct{
    int urgencia;//para a heap maxima
    float tempo;//para a heap minima
    int id;
}Informacoes;

typedef struct{
    Informacoes *info;
    int n;//quantidade de elementos
}Heap;

int pai(int i){
    return ((i - 1)/2);//calcula indice do pai
}

int esq(int i){
    return (i*2);//calcula o indice do filho esquerdo
}

int dir(int i){
    return (i*2+1);//calcula o indice do filho direito
}

Heap *criarheap(){
    Heap *heap = (Heap*)malloc(sizeof(Heap));//aloca memória para a heap
    heap->n = 0;
    heap->info = NULL;
    return heap;
}

//trocar o valor da estruturas
void troca(Informacoes *a, Informacoes *b){//por ser ponteiro n precisa retornar
    Informacoes temp = *a;
    *a = *b;
    *b = temp;
}

//se inserir filho menor ele sobe
void subir(Heap *heap, int i, int qualheap){
    int j = pai(i);
    if(i > 0){//se o no nao eh raiz
        if(qualheap == 1){//heap maxima
            if(heap->info[i].urgencia > heap->info[j].urgencia){//se o elemento i tem mais urgencia que o pai troca, compara urgencias
                troca(&heap->info[i], &heap->info[j]);
                subir(heap, j, qualheap);
            }
        }else{//heap minima
            if(heap->info[i].tempo < heap->info[j].tempo){//se o elemento i tem menor tempo que o pai troca, compara tempos
                troca(&heap->info[i], &heap->info[j]);
                subir(heap, j, qualheap);
            }
        }
    }
}

//inserir novo elemento
void insere(Heap *heap, int id, int urgencia, float tempo, int qualheap){
    heap->n++;
    //aumenta o vetor
    heap->info = (Informacoes*)realloc(heap->info, heap->n * sizeof(Informacoes));//realocar o array para o novo tamanho
    //coloca as infos
    heap->info[heap->n - 1].id = id;//usando o array comecando no 0 precisa ter o -1
    heap->info[heap->n - 1].urgencia = urgencia;
    heap->info[heap->n - 1].tempo = tempo;
    subir(heap, heap->n - 1, qualheap);//manda para o subir para manter as prioridades
}


void descer(Heap *heap, int i, int qualheap){
    //quem eh o maior filho de i
    int e = esq(i);//indice do filho da esquerda
    int d = dir(i);//indice do filho da direita
    int maiormenor = i;//se for heap maximo sera o maior, se for heap minimo sera o menor/ inicia com com o indice do no atual

    //ve se o filho a esquerda deve ser o novo maior/menor
    if(e < heap->n  && ((qualheap == 1 && heap->info[e].urgencia > heap->info[maiormenor].urgencia) || (qualheap == 0 && heap->info[e].tempo < heap->info[maiormenor].tempo))){
        maiormenor = e;
    }

    //ve se o filho a direita deve ser o novo maior/menor
    if(d < heap->n  && ((qualheap == 1 && heap->info[d].urgencia > heap->info[maiormenor].urgencia) || (qualheap == 0 && heap->info[d].tempo < heap->info[maiormenor].tempo))){
        maiormenor = d;
    }

    //se o filho nao for o no atual, troca e desce
    if(maiormenor != i){
        troca(&heap->info[i], &heap->info[maiormenor]);
        descer(heap, maiormenor, qualheap);
    }
}

//remover a raiz especificada
Informacoes remover(Heap *maxheap, Heap *minheap, int qualheap){
    if((qualheap == 1 && maxheap->n <= 0) || (qualheap == 0 && minheap->n <= 0)){//ver se a heap esta vazia
        printf("Heap Vazia\n");
    }

    Heap *heapexcluir;//aponta para a heap da qual o elemento sera removido
    if(qualheap == 1){
        heapexcluir = maxheap;
    }else{
        heapexcluir = minheap;
    }

    Informacoes raiz = heapexcluir->info[0];//guarda o elemento raiz que vai ser removido
    heapexcluir->info[0] = heapexcluir->info[heapexcluir->n - 1];//substitui a raiz do ultimo elemento
    heapexcluir->n--;
    heapexcluir->info = (Informacoes*)realloc(heapexcluir->info, heapexcluir->n * sizeof(Informacoes));//reajusta o tamanho da memoria alocada

    if(heapexcluir->n > 0){//se tem elementos desce o elemento raiz
        descer(heapexcluir, 0, 1);//desce o elemento
    }else{//se ficou vazia exclui
        free(heapexcluir->info);
        heapexcluir->info = NULL;
    }

    //remover da outra heap
    Heap *outraheap;
    if(qualheap == 1){
        outraheap = minheap;
    }else{
        outraheap = maxheap;
    }

    for(int i = 0; i < outraheap->n; i++){//percorre a outra heap para encontrar o elemento
        if(outraheap->info[i].id == raiz.id){
            outraheap->info[i] = outraheap->info[outraheap->n - 1];
            outraheap->n--;
            outraheap->info = (Informacoes*)realloc(outraheap->info, outraheap->n * sizeof(Informacoes));
            if(outraheap->n > 0){
                descer(outraheap, i, 0);
            }else{
                free(outraheap->info);
                outraheap->info = NULL;
            }
            break;
        }
    }
    return raiz;
}

//ajustar a urgencia e ajustar as heaps
void atualizaurgencia(Heap *maxheap, Heap *minheap, int id, int novaurgencia){
    int encontrado = 0;
    //na heap maxima
    for(int i = 0; i < maxheap->n; i++){//percorre a heap maxima
        if(maxheap->info[i].id == id){//se encontrar atualiza e ajusta
            maxheap->info[i].urgencia = novaurgencia;
            subir(maxheap, i, 1);
            descer(maxheap, i, 1);
            encontrado = 1;
            break;
        }
    }

    //na heap minima
    for(int i = 0; i < minheap->n; i++){
        if(minheap->info[i].id == id){
            minheap->info[i].urgencia = novaurgencia;
            encontrado = 1;
            break;
        }
    }

    if(encontrado == 1){
        printf("Atualizado\n");
    }else{
        printf("Nao encontrado\n");
    }
}


void printar(Heap *heap){
    for(int i = 0; i < heap->n; i++){
        printf("[ID: %d, Urgencia: %d, Tempo: %.2f] ", heap->info[i].id, heap->info[i].urgencia, heap->info[i].tempo);
    }
    printf("\n");
}

int main(){
    int escolha, id, urgencia;
    float tempo;
    Informacoes informacoes;
    
    Heap *maxheap = criarheap();
    Heap *minheap = criarheap();
    //qualheap = se for 1 eh a heap maxima, se for 0 eh a heapminima
    printf("0 para sair do programa \n");

    do{
        printf("Escolha: \n1: Inserir \n2: Atualizar urgencia \n3: Remover tarefa mais urgente \n4: Remover tarefa com menor tempo \n5: Consultar tarefa mais urgente\n6: Consultar tarefa com menor tempo \n7: Imprimir heaps\n");
        scanf("%d", &escolha);
        switch(escolha){
        case 1:
            printf("ID do elemento: \n");
            scanf("%d", &id);
            printf("Urgencia do elemento: \n");
            scanf("%d", &urgencia);
            printf("Tempo do elemento em horas: \n");
            scanf("%f", &tempo);
            insere(maxheap, id, urgencia, tempo, 1);
            insere(minheap, id, urgencia, tempo, 0);
            break;
        case 2:
            printf("ID do elemento: \n");
            scanf("%d", &id);
            printf("Nova urgencia do elemento: \n");
            scanf("%d", &urgencia);
            atualizaurgencia(maxheap, minheap, id, urgencia);
            break;
        case 3:
            informacoes = remover(maxheap, minheap, 1);
            printf("Tarefa removida: ID: %d, Urgencia: %d, Tempo: %.2f\n", informacoes.id, informacoes.urgencia, informacoes.tempo);
            break;
        case 4:
            informacoes = remover(maxheap, minheap, 0); 
            printf("Tarefa removida: ID: %d, Urgencia: %d, Tempo: %.2f\n", informacoes.id, informacoes.urgencia, informacoes.tempo);
            break;
        case 5:
            if(maxheap->n > 0){
                informacoes = maxheap->info[0];
                printf("Tarefa mais urgente: ID: %d, Urgencia: %d, Tempo: %.2f\n", informacoes.id, informacoes.urgencia, informacoes.tempo);
            }else{
                printf("Heap vazia\n");
            }
            break;
        case 6:
            if(minheap->n > 0){
                informacoes = minheap->info[0];
                printf("Tarefa com menor tempo: ID: %d, Urgencia: %d, Tempo: %.2f\n", informacoes.id, informacoes.urgencia, informacoes.tempo);
            }else{
                printf("Heap vazia\n");
            }
            break;
        case 7:
            printf("Heaps: ");
            printf("Heap maxima (por urgencia): ");
            printar(maxheap);
            printf("Heap minima (por tempo): ");
            printar(minheap); 
            break;
        default:
            printf("Escolha invalida");
            break;
        }
    }while(escolha != 0);

    return 0;
}