#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux{
    TIPOCHAVE chave;
    //dados
    struct aux *esq;
    struct aux *dir;
    int h;//altura
}NO, *PONT;

int altura(PONT raiz){//facilitar mandar a altura
    if(raiz == NULL){
        return -1;
    }
    return raiz->h;
}

int difalt(PONT raiz){//diferença do h das subarvores dir e esq
    if(raiz == NULL){
        return 0;
    }
    return altura(raiz->esq) - altura(raiz->dir);
}

int maiorvalor(int a, int b){//ver o maior valor para o balanceamento
    if(a > b){
        return a;
    }else{
        return b;
    }
}

PONT rotacaoesq(PONT x){//fazer a rotacao esquerda
    PONT y = x->dir;//igualar y = filho direito de x
    PONT z = y->esq;//igualar z = filho esquerdo de y
    //faz a rotacao
    y->esq = x;
    x->dir = z;
    //atualiza altura
    x->h = maiorvalor(altura(x->esq), altura(x->dir)) + 1;//
    y->h = maiorvalor(altura(y->esq), altura(y->dir)) + 1;
    return y;//nova raiz
}

PONT rotacaodir(PONT y){//fazer a rotacao direita
    PONT x = y->esq;// x = filho esquerdo de y
    PONT z = x->dir;// z = filho direito de x
    //faz a rotacao
    x->dir = y;
    y->esq = z;
    //atualiza altura
    //altura do filho esquerdo, altura do filho direito, encontra a maior altura, +1 para a altura do proprio nó, dps atualiza a altura
    y->h = maiorvalor(altura(y->esq), altura(y->dir)) + 1;
    x->h = maiorvalor(altura(x->esq), altura(x->dir)) + 1;
    return x;//nova raiz
}

PONT rotacaoesqdir(PONT raiz){//rotacao esquerda direita
    raiz->esq = rotacaoesq(raiz->esq);//rotaciona a esquerda o filho esquerdo
    return rotacaodir(raiz);//rotaciona a direita a raiz
}

PONT rotacaodiresq(PONT raiz){//rotacao direita esquerda
    raiz->dir = rotacaodir(raiz->dir);//rotaciona a direita o filho direito
    return rotacaoesq(raiz);//rotaciona a esquerda a raiz
}

PONT inserir(PONT raiz, TIPOCHAVE chave){
    if(raiz == NULL){
        //cria o a raiz se n tem
        PONT novo = (PONT)malloc(sizeof(NO));
        novo->chave = chave;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->h = 0;
        return novo;
    }
    //insere na subarvore direita ou esquerda
    if(chave < raiz->chave){
        raiz->esq = inserir(raiz->esq, chave);
    }else if(chave > raiz->chave){
        raiz->dir = inserir(raiz->dir, chave);
    }else{
        return raiz;//duplicou
    }
    //atualiza o h da raiz
    raiz->h = maiorvalor(altura(raiz->esq), altura(raiz->dir)) + 1;

    //ver se ta balanceado
    int bal = difalt(raiz);
    //rotacao direita
    if(bal > 1 && chave < raiz->esq->chave){
        return rotacaodir(raiz);
    }
    //rotacao esquerda
    if(bal < -1 && chave > raiz->dir->chave){
        return rotacaoesq(raiz);
    }
    //rotacao esquerda direita
    if(bal > 1 && chave > raiz->esq->chave){
        raiz->esq = rotacaoesq(raiz->esq);
        return rotacaodir(raiz);
    }
    //rotacao direita esquerda
    if(bal < -1 && chave < raiz->dir->chave){
        raiz->dir = rotacaodir(raiz->dir);
        return rotacaoesq(raiz);
    }
    //se balanceado só volta a raiz
    return raiz;
}
//encontrar o menor nó (esquerda)
PONT encontrarmin(PONT raiz){
    PONT atual = raiz;
    while(atual->esq != NULL){
        atual = atual->esq;
    }
    return atual;
}

PONT excluir(PONT raiz, TIPOCHAVE chave){
    if(raiz == NULL){//arvore sem nada
        return raiz;
    }

    if(chave < raiz->chave){//nó na subarvore esquerda
        raiz->esq = excluir(raiz->esq, chave);
    }else if(chave > raiz->chave){//nó na subarvere direita
        raiz->dir = excluir(raiz->dir, chave);
    }else{//nó achado
        if(raiz->esq == NULL && raiz->dir == NULL){//sem filhos, folha
            free(raiz);
            raiz = NULL;
        }else if(raiz->esq == NULL){//filho na direita
            PONT temp = raiz->dir;
            *raiz = *temp;
            free(temp);
        }else if(raiz->dir == NULL){//filho na esquerda
            PONT temp = raiz->esq;
            *raiz = *temp;
            free(temp);
        }else{//tem dois filhos
            PONT temp = encontrarmin(raiz->dir);
            raiz->chave = temp->chave;
            raiz->dir = excluir(raiz->dir, temp->chave);
        }
    }

    if(raiz == NULL){
        return raiz;
    }

    //atualiza a altura
    raiz->h = maiorvalor(altura(raiz->esq), altura(raiz->dir)) + 1;
    //ver se ta balanceado
    int bal = difalt(raiz);
    //rotacao direita
    if(bal > 1 && difalt(raiz->esq) >= 0){
        return rotacaodir(raiz);
    }
    //rotacao esquerda
    if(bal < -1 && difalt(raiz->dir) <= 0){
        return rotacaoesq(raiz);
    }
    //rotacao esquerda direita
    if(bal > 1 && difalt(raiz->esq) < 0){
        return rotacaoesqdir(raiz);
    }
    //rotacao direita esquerda
    if(bal < -1 && difalt(raiz->dir) > 0){
        return rotacaodiresq(raiz);
    }
    //se n teve rotacoes, volta a raiz
    return raiz;
}

void imprimiremordem(PONT raiz){
    if(raiz != NULL){
        imprimiremordem(raiz->esq);
        printf("%d ", raiz->chave);
        imprimiremordem(raiz->dir);
    }
}

void imprimirpreordem(PONT raiz){
    if(raiz != NULL){
        printf("%d ", raiz->chave);
        imprimirpreordem(raiz->esq);
        imprimirpreordem(raiz->dir);
    }
}

void imprimiremposordem(PONT raiz){
    if(raiz != NULL){
        imprimiremposordem(raiz->esq);
        imprimiremposordem(raiz->dir);
        printf("%d ", raiz->chave);
    }
}

PONT buscar(PONT raiz, TIPOCHAVE chave){
    if(raiz == NULL || raiz->chave == chave){
        return raiz;
    }
    if(chave < raiz->chave){
        return buscar(raiz->esq, chave);
    }else{
        return buscar(raiz->dir, chave);
    }
}

int altarvore(PONT raiz){
    if(raiz == NULL){
        return -1;
    }
    return 1 + maiorvalor(altarvore(raiz->esq), altarvore(raiz->dir));
}

void destruirarvore(PONT raiz){
    if(raiz != NULL){
        destruirarvore(raiz->esq);
        destruirarvore(raiz->dir);
        free(raiz);
    }
}

int main(){
    PONT raiz = NULL;
    int escolha, chave;

    do{
        printf("Escolha:\n1: Inserir\n2: Excluir\n3: Imprimir Em Ordem\n4: Imprimir Pre Ordem\n5: Imprimir Pos Ordem\n6: Buscar\n7: Altura\n8: Destruir Arvore\n0: Sair\n");
        scanf("%d", &escolha);

        switch(escolha){
            case 1:
                printf("Digite a chave para inserir: ");
                scanf("%d", &chave);
                raiz = inserir(raiz, chave);
                break;
            case 2:
                printf("Digite a chave para excluir: ");
                scanf("%d", &chave);
                raiz = excluir(raiz, chave);
                break;
            case 3:
                printf("Arvore em ordem:\n");
                imprimiremordem(raiz);
                printf("\n");
                break;
            case 4:
                printf("Arvore em pre-ordem:\n");
                imprimirpreordem(raiz);
                printf("\n");
                break;
            case 5:
                printf("Arvore em pos-ordem:\n");
                imprimiremposordem(raiz);
                printf("\n");
                break;
            case 6:
                printf("Digite a chave para buscar: ");
                scanf("%d", &chave);
                PONT encontrado = buscar(raiz, chave);
                if(encontrado != NULL){
                    printf("Chave %d encontrada na arvore.\n", chave);
                }else{
                    printf("Chave %d nao encontrada na arvore.\n", chave);
                }
                break;
            case 7:
                printf("Altura da arvore: %d\n", altarvore(raiz));
                break;
            case 8:
                destruirarvore(raiz);
                raiz = NULL;
                printf("Arvore destruida.\n");
                break;
            case 0:
                destruirarvore(raiz);
                break;
            default:
                printf("Invalido\n");
        }
    }while(escolha != 0);

    return 0;
}
