#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 23

typedef struct{
    int isbn;
    char *titulo;
    char *autor;
    int ano;
    int ocupado;
}Livro;

Livro* tabelaHash;

//hash primaria
int hash1(int isbn){
    return isbn % TAMANHO;
}

//hash secundaria, no caso de colisoes
int hash2(int isbn){
    //TAMANHO - 1, sempre ser menor que a tabela
    //+1 para nao ser 0
    return(isbn % (TAMANHO - 1)) + 1;
}

//inicializa a tabela
void inicializar(){
    tabelaHash = (Livro*)malloc(TAMANHO * sizeof(Livro));
    for(int i = 0; i < TAMANHO; i++){
        tabelaHash[i].ocupado = 0;//marca as posicoes como vazias
        tabelaHash[i].titulo = NULL;
        tabelaHash[i].autor = NULL;
    }
}

//alocar as strings dinamicamente
char *alocarString(const char* str){
    char *novoStr = (char*)malloc(strlen(str) + 1);//memoria para a nova string
    strcpy(novoStr, str);//copia o conteudo da string original para a nova
    return novoStr;//retorna o ponteiro
}

//inserir os livros
void inserirLivro(int isbn, char *titulo, char *autor, int ano){
    int indice = hash1(isbn);//indice inicial
    int desloca = hash2(isbn);//passo de deslocamento/incremento da hash secundaria
    int i = 0;

    //procura uma posicao livre na tabela
    while(tabelaHash[(indice + i * desloca) % TAMANHO].ocupado){//incrementa o indice inicial pelo i++, cada tentativa avanca "desloca" posicoes
        i++;
    }

    indice = (indice + i * desloca) % TAMANHO;//indice final onde o livro vai ser colocado
    //aloca as informacoes
    tabelaHash[indice].isbn = isbn;
    tabelaHash[indice].titulo = alocarString(titulo);//aloca e copia
    tabelaHash[indice].autor = alocarString(autor);
    tabelaHash[indice].ano = ano;
    tabelaHash[indice].ocupado = 1;//posicao ocupada
}

//buscar
int buscarLivro(int isbn){
    int indice = hash1(isbn);//indice inicial 
    int desloca = hash2(isbn);//deslocamento
    int i = 0;

    //percorre a tabela procurando o livro
    while(tabelaHash[(indice + i * desloca) % TAMANHO].ocupado){
        if(tabelaHash[(indice + i * desloca) % TAMANHO].isbn == isbn){//achou o livro
            return (indice + i * desloca) % TAMANHO;//retorna o indice do livro
        }
        i++;
    }
    return -1;//nao encontrou
}

//remover um livro
void removerLivro(int isbn){
    int indice = buscarLivro(isbn);//pega o indice do livro que vai ser removido
    if(indice != -1){
        free(tabelaHash[indice].titulo);
        free(tabelaHash[indice].autor);
        tabelaHash[indice].ocupado = 0;//posicao vazia
        printf("Removido\n");
    }else{
        printf("Livro nao existe\n");
    }
}

//printar os livros
void print(){
    for(int i = 0; i < TAMANHO; i++){
        if(tabelaHash[i].ocupado){//se a posicao ta ocupada 
            printf("Index %d: ISBN: %d, Title: %s, Author: %s, Year: %d\n", i, tabelaHash[i].isbn, tabelaHash[i].titulo, tabelaHash[i].autor, tabelaHash[i].ano);
        }
    }
}

int main() {
    inicializar();
    int escolha;
    int isbn;
    char titulo[100];
    char autor[100];
    int ano;

    do{
        printf("Escolha: \n1. Inserir livro\n2. Buscar livro\n3. Remover livro\n4. Imprimir todos os livros\n5. Sair\n");
        scanf("%d", &escolha);
        getchar();

        switch(escolha){
            case 1:
                printf("Coloque o ISBN (somente os numeros): ");
                scanf("%d", &isbn);
                getchar();
                printf("Coloque o titulo: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("Coloque o autor: ");
                fgets(autor, sizeof(autor), stdin);
                autor[strcspn(autor, "\n")] = '\0';
                printf("Coloque o ano: ");
                scanf("%d", &ano);
                inserirLivro(isbn, titulo, autor, ano);
                break;
            case 2:
                printf("Digite o ISBN para buscar: ");
                scanf("%d", &isbn);
                int indice = buscarLivro(isbn);
                if(indice != -1){
                    printf("Livro encontrado no indice %d: ISBN: %d, Titulo: %s, Autor: %s, Ano: %d\n", indice, tabelaHash[indice].isbn, tabelaHash[indice].titulo, tabelaHash[indice].autor, tabelaHash[indice].ano);
                }else{
                    printf("Livro nao encontrado.\n");
                }
                break;
            case 3:
                printf("Digite o ISBN para remover: ");
                scanf("%d", &isbn);
                removerLivro(isbn);
                break;
            case 4:
                print();
                break;
            case 5:
                for(int i = 0; i < TAMANHO; i++){
                    if(tabelaHash[i].ocupado){
                        //n da free no ano e no isbn pq eh int
                        free(tabelaHash[i].titulo);
                        free(tabelaHash[i].autor);
                    }
                }
                free(tabelaHash);
                exit(0);
            default:
                printf("Opcao invalida\n");
        }
    }while(escolha != 5);

    return 0;
}
