//Pilha(pode usar malloc e realloc) com capacidade inicial de 10, aumenta em 50% 3 vezes
//Array com duas pilhas, ou dois topos

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct{
    REGISTRO *A;
    int tamanho;
    int topo1;
    int topo2;
    int contador1;
    int contador2;
    int vezesaumentada;
}PILHA;

void inicializarPilha(PILHA *p){
    if(p == NULL){
        printf("Erro!\n");
        return;
    }
    p->A = (REGISTRO *)malloc(10 * sizeof(REGISTRO));
    if(p->A == NULL){
        printf("Erro!\n");
        exit(EXIT_FAILURE);
    }
    p->topo1 = -1;
    p->topo2 = 10;
    p->tamanho = 10;
    p->contador1 = 0;
    p->contador2 = 0;
    p->vezesaumentada = 0;
}

bool inserirnaPilha1(PILHA *p, REGISTRO reg){
    if(p == NULL){
        printf("Erro!\n");
        return false;
    }
    if(p->topo1 >= p->topo2 - 1){//limita a pilha 1
        return false;
    }
    p->topo1++;
    p->A[p->topo1] = reg;
    p->contador1++;
    return true;
}

bool inserirnaPilha2(PILHA *p, REGISTRO reg){
    if(p == NULL){
        printf("Erro!\n");
        return false;
    }
    if(p->topo2 <= p->topo1 + 1){//limita a pilha 2
        return false;
    }
    p->topo2--;
    p->A[p->topo2] = reg;
    p->contador2++;
    return true;
}

void aumentarPilha(PILHA *p){
    if(p == NULL){
        printf("Erro!\n");
        return;
    }
    if(p->contador1 + p->contador2 >= p->tamanho){//verificar se a pilha esta cheia
        if(p->vezesaumentada < 3){//verificar se aumentou 3 vezes
            int novo_tamanho = p->tamanho * 1.5;
            REGISTRO *novoA = (REGISTRO *)malloc(novo_tamanho * sizeof(REGISTRO));
            if(novoA != NULL){//verificar se deu erro
                for(int i = 0; i <= p->topo1; i++){
                    novoA[i] = p->A[i];
                }
                int j = novo_tamanho - 1;//comeca em 0 por isso -1
                for(int i = p->tamanho - 1; i >= p->topo2; i--){
                    novoA[j--] = p->A[i];
                }
                free(p->A);
                p->A = novoA;
                p->topo2 += (novo_tamanho - p->tamanho);
                p->tamanho = novo_tamanho;
                p->vezesaumentada++;
                printf("Pilha aumentou para: %d.\n", p->tamanho);
            }else{
                printf("Erro ao aumentar a pilha.\n");
            }
        }else{
            printf("A pilha ja foi aumentada 3 vezes.\n");
        }
    }
}

bool removerdaPilha1(PILHA *p, REGISTRO *reg){
    if(p == NULL || p->topo1 == -1){
        printf("Erro: Pilha 1 vazia.\n");
        return false;
    }
    *reg = p->A[p->topo1--];
    p->contador1--;
    return true;
}

bool removerdaPilha2(PILHA *p, REGISTRO *reg){
    if(p == NULL || p->topo2 == p->tamanho){
        printf("Erro: Pilha 2 vazia.\n");
        return false;
    }
    *reg = p->A[p->topo2++];
    p->contador2--;
    return true;
}

void imprimirPilha(PILHA *p){
    if(p == NULL){
        printf("Erro\n");
        return;
    }
    printf("Pilha 1:\n");
    for(int i = 0; i <= p->topo1; i++){
        printf("%d ", p->A[i].chave);
    }
    printf("\n");

    printf("Pilha 2:\n");
    for(int i = p->tamanho - 1; i >= p->topo2; i--){
        printf("%d ", p->A[i].chave);
    }
    printf("\n");
}

int main(){
    PILHA pilha;
    REGISTRO reg;
    int opcao;

    inicializarPilha(&pilha);

    do{
        printf("\nMenu:\n");
        printf("1. Inserir na Pilha 1\n");
        printf("2. Inserir na Pilha 2\n");
        printf("3. Remover da Pilha 1\n");
        printf("4. Remover da Pilha 2\n");
        printf("5. Imprimir Pilhas\n");
        printf("6. Aumentar Pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Digite o valor a ser inserido na Pilha 1: ");
                scanf("%d", &reg.chave);
                if(inserirnaPilha1(&pilha, reg)){
                    printf("Valor inserido na Pilha 1 com sucesso.\n");
                }else{
                    printf("Erro: Pilha 1 cheia.\n");
                }
                break;
            case 2:
                printf("Digite o valor a ser inserido na Pilha 2: ");
                scanf("%d", &reg.chave);
                if(inserirnaPilha2(&pilha, reg)){
                    printf("Valor inserido na Pilha 2 com sucesso.\n");
                }else{
                    printf("Erro: Pilha 2 cheia.\n");
                }
                break;
            case 3:
                if(removerdaPilha1(&pilha, &reg)){
                    printf("Elemento %d removido da Pilha 1.\n", reg.chave);
                }
                break;
            case 4:
                if(removerdaPilha2(&pilha, &reg)){
                    printf("Elemento %d removido da Pilha 2.\n", reg.chave);
                }
                break;
            case 5:
                imprimirPilha(&pilha);
                break;
            case 6:
                aumentarPilha(&pilha);
                break;
            case 0:
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }while(opcao != 0);

    free(pilha.A);
    return 0;
}