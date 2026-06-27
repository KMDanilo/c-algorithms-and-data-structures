//LISTA LIGADA DINAMICA
//Para simplificar o cOdigo coloquei os alunos como letras
//A frequencia e nota estao sendo utilizadas como inteiros
//1A esta no papel
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct{
    char aluno;
    TIPOCHAVE matricula;
    TIPOCHAVE nota;
    TIPOCHAVE frequencia;
}REGISTRO;


typedef struct aux{
    struct aux *prox;
    REGISTRO reg;
}NODE, *PONT;

typedef struct{
    PONT inicio;
}LISTA;

void inicializarLista(LISTA *l){
    l->inicio = NULL;
}

PONT posicao(LISTA *l, REGISTRO reg){//pegar a posicao do registro pedido
    PONT aux = l->inicio;
    PONT ant = NULL;
    while(aux < reg.matricula){//roda enquanto o valor que o usuario colocou for diferente do valor da posicao
        ant = aux;
        aux = aux->prox;
    }
    if(aux == NULL){
        return NULL;
    }
    return aux;

}

bool inserirLista(LISTA *l, REGISTRO reg){
    PONT novo = (PONT)malloc(sizeof (NODE));//alocar o novo
    novo->reg = reg;//igualar ele ao valor desejado
    if(novo == NULL){//se a aloca��o der errado retornar falso
        return false;
    }
    PONT i = posicao(l, reg);
    if(i == NULL){
        novo->prox = l->inicio;
        l->inicio = novo;
    }else{
        novo->prox = i;
        i->prox = novo;
    }
    return true;
}

bool removerAluno(LISTA *l, REGISTRO reg){
    PONT i = posicao(l, reg);//pegar a posicao
    PONT apagar = i;
    if(i == NULL){
        return false;
    }else{
        i = i->prox;
        free(apagar);
    }
    return true;
}

void imprimirAlunos(LISTA *l, REGISTRO reg){
    PONT aux = l->inicio;
    while(aux != NULL){
        printf("Aluno %c: ", reg.aluno);
        printf("%d ", reg.matricula);
        printf("%d ", reg.nota);
        printf("%d ", reg.frequencia);
        aux = aux->prox;
    }
}

void imprimirAlunosAprovados(LISTA *l, REGISTRO reg){
    PONT aux = l->inicio;
    printf("Aluno(s) aprovado(s): ");
    while(aux != NULL){
        if(reg.nota >= 6 && reg.frequencia >= 75){
            printf("%c ", reg.aluno);
        }
        aux = aux->prox;
    }
}

void imprimirAlunosExame(LISTA *l, REGISTRO reg){
    PONT aux = l->inicio;
    printf("Aluno(s) de exame: ");
    while(aux != NULL){
        if(reg.nota < 6 && reg.nota > 3 && reg.frequencia >= 75){
            printf("%c ", reg.aluno);
        }
        aux = aux->prox;
    }
}

void imprimirAlunosReprovados(LISTA *l, REGISTRO reg){
    PONT aux = l->inicio;
    printf("Aluno(s) reprovado(s): ");
    while(aux != NULL){
        if(reg.nota < 3 || reg.frequencia < 75){
            printf("%c ", reg.aluno);
        }
        aux = aux->prox;
    }
}

void liberarLista(LISTA *l, REGISTRO reg){
    PONT aux = l->inicio;//ponteiro auxiliar para percorrer a lista
    while(aux != l->inicio){
        PONT apagar;//ponteiro auxiliar utilizado para apagar
        apagar = aux;
        aux = aux->prox;
        free(apagar);
    }
    l->inicio = NULL;//arrumar o inicio
}









