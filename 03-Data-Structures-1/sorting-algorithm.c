//Danilo Kotaka Marana e Gabriel Henrique Navarro
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tamanho1 10000
#define tamanho2 100000
#define tamanho3 250000
#define tamanho4 1000000
#define tamanho5 10000000
#define tamanho6 100000000
#define liminsertionsort 20 


void bubblesort(int *v, int tam){
    int temp;
    for(int i = 0; i < tam - 1; i++){
        for(int j = 0; j < tam - i - 1;j++){
            if(v[j] > v[j + 1]){
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void selectionsort(int *v, int tam){
    int min, temp;
    for(int i = 0; i < tam - 1; i++){
        min = i;
        for(int j = i + 1; j < tam; j++){
            if(v[j] < v[min]){
                min = j;
            }
        }
        temp = v[min];
        v[min] = v[i];
        v[i] = temp;
    }
}

void insertionsort(int *v, int tam){
    int temp, j;
    for(int i = 1; i < tam; i++){
        temp = v[i];
        j = i - 1;
        while(j >= 0 && v[j] > temp){
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = temp;
    }
}

void mergesort(int *v, int tam);
void mergesortp(int *v, int inicio, int fim);
void mergesorted(int *v, int inicio, int meio, int fim);

void mergesort(int *v, int tam){
    mergesortp(v, 0, tam - 1);
}

void mergesortp(int *v, int inicio, int fim){
    if(inicio < fim){
        int meio = inicio + (fim - inicio) / 2;
        mergesortp(v, inicio, meio);
        mergesortp(v, meio + 1, fim);
        mergesorted(v, inicio, meio, fim);//junta 
    }
}

void mergesorted(int *v, int inicio, int meio, int fim){
    int esquerdo = meio - inicio + 1;
    int direito = fim - meio;

    int vet_esq[esquerdo];
    int vet_dir[direito];

    int i, j, k;

    for(int i = 0; i < esquerdo; i++){
        vet_esq[i] = v[inicio + i];
    }
    for(int i = 0; i < direito; i++){
        vet_dir[i] = v[meio + 1 + i];
    }

    i = 0;
    j = 0;//reiniciar o i e o j
    k = inicio;

    while(i < esquerdo && j < direito){
        if(vet_esq[i] <= vet_dir[j]){
            v[k] = vet_esq[i];
            i++;
        }else{
            v[k] = vet_dir[j];
            j++;
        }
        k++;
    }

    while(i < esquerdo){
        v[k] = vet_esq[i];
        i++;
        k++;
    }

    while(j < direito){
        v[k] = vet_dir[j];
        j++;
        k++;
    }
}

int particiona(int *v, int inicio, int fim){
    int pivo = v[fim];
    int i = inicio - 1;
    for(int j = inicio; j < fim; j++){
        if(v[j] <= pivo){
            i++;
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }
    int aux = v[i + 1];
    v[i + 1] = v[fim];
    v[fim] = aux;
    return i + 1;
}

void quicksortnormal(int *v, int inicio, int fim){
    if(inicio < fim){
        int posicao = particiona(v, inicio, fim);
        quicksortnormal(v, inicio, posicao - 1);
        quicksortnormal(v, posicao + 1, fim);
    }
}

int medianadetres(int *v, int inicio, int meio, int fim){
    if((v[inicio] > v[meio]) != (v[inicio] > v[fim])){
        return inicio;
    }
    if((v[meio] > v[inicio]) != (v[meio] > v[fim])){
        return meio;
    }
    return fim;
}

int particionamediana(int *v, int inicio, int fim){
    int meio = (inicio + fim) / 2;
    int medianaindex = medianadetres(v, inicio, meio, fim);
    int aux = v[medianaindex];
    v[medianaindex] = v[fim];
    v[fim] = aux;
    return particiona(v, inicio, fim);
}

void quicksortmediana(int *v, int inicio, int fim){
    if(inicio < fim){
        int posicao = particionamediana(v, inicio, fim);
        quicksortmediana(v, inicio, posicao - 1);
        quicksortmediana(v, posicao + 1, fim);
    }
}

void quicksortinsertion(int *v, int inicio, int fim){
    if(inicio < fim){
        if(fim - inicio + 1 <= liminsertionsort){
            insertionsort(v + inicio, fim - inicio + 1);
        }else{
            int posicao = particiona(v, inicio, fim);
            quicksortinsertion(v, inicio, posicao - 1);
            quicksortinsertion(v, posicao + 1, fim);
        }
    }
}


/*void imprimir(int *v, int tam){
    for (int i = 0; i < tam; i++){
        printf("%d, ", v[i]);
    }
    printf("\n");
}*/


int main(){
    srand(time(NULL));
    int escolha1, escolha2, tamanho_vet;
    printf("Escolha um numero diferente das escolhas para sair do programa\n");
    do{
    printf("Escolha quantos numeros o vetor tera: \n1: 10000 \n2: 100000 \n3: 250000 \n4: 1M \n5: 10M \n6: 100M\n");
    scanf("%d", &escolha1);

    switch(escolha1){
        case 1:
            tamanho_vet = tamanho1;
            break;
        case 2:
            tamanho_vet = tamanho2;
            break;
        case 3:
            tamanho_vet = tamanho3;
            break;
        case 4:
            tamanho_vet = tamanho4;
            break;
        case 5:
            tamanho_vet = tamanho5;
            break;
        case 6:
            tamanho_vet = tamanho6;
            break;
        default:
            printf("Opcao invalida\n");
            return -1;
    }

    int *vetor = (int*)malloc(tamanho_vet * sizeof(int));
    if(vetor == NULL){
        printf("Erro ao alocar");
        return -1;
    }

    for(int i = 0; i < tamanho_vet; i++){
        vetor[i] = rand() % tamanho_vet;
    }

    printf("Qual tipo de sort para organizar? \n1: Bubble \n2: Selection \n3: Insertion \n4: Merge \n5: Quick normal\n6: Quick Pivo mediana de 3 \n7: Quick + Insertion\n");
    scanf("%d", &escolha2);

    switch(escolha2){
        case 1:{
            clock_t inicio = clock();
            bubblesort(vetor, tamanho_vet);
            clock_t fim = clock();
            double tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo decorrido para ordenar o vetor: %.6f segundos\n", tempo_decorrido);
            //imprimir(vetor, tamanho_vet);
            free(vetor);
            break;
        }
        case 2:{
            clock_t inicio = clock();
            selectionsort(vetor, tamanho_vet);
            clock_t fim = clock();
            double tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo decorrido para ordenar o vetor: %.6f segundos\n", tempo_decorrido);
            //imprimir(vetor, tamanho_vet);
            free(vetor);
            break;
        }
        case 3:{
            clock_t inicio = clock();
            insertionsort(vetor, tamanho_vet);
            clock_t fim = clock();
            double tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo decorrido para ordenar o vetor: %.6f segundos\n", tempo_decorrido);
            //imprimir(vetor, tamanho_vet);
            free(vetor);
            break;
        }
        case 4:{
            clock_t inicio = clock();
            mergesort(vetor, tamanho_vet);
            clock_t fim = clock();
            double tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo decorrido para ordenar o vetor: %.6f segundos\n", tempo_decorrido);
            //imprimir(vetor, tamanho_vet);
            free(vetor);
            break;
        }
        case 5:{
            clock_t inicio = clock();
            quicksortnormal(vetor, 0, tamanho_vet - 1);
            clock_t fim = clock();
            double tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo decorrido para ordenar o vetor: %.6f segundos\n", tempo_decorrido);
            //imprimir(vetor, tamanho_vet);
            free(vetor);
            break;
        }
        case 6:{
            clock_t inicio = clock();
            quicksortmediana(vetor, 0, tamanho_vet - 1);
            clock_t fim = clock();
            double tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo decorrido para ordenar o vetor: %.6f segundos\n", tempo_decorrido);
            //imprimir(vetor, tamanho_vet);
            free(vetor);
            break;
        }
        case 7:{
            clock_t inicio = clock();
            quicksortinsertion(vetor, 0, tamanho_vet - 1);
            clock_t fim = clock();
            double tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo decorrido para ordenar o vetor: %.6f segundos\n", tempo_decorrido);
            //imprimir(vetor, tamanho_vet);
            free(vetor);
            break;
        }
        default:
            printf("Opcao invalida\n");
    }
    }while(escolha1 != 0 && escolha2 != 0);

    return 0;
}