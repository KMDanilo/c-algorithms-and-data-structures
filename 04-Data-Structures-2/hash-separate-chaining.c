#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 23

typedef struct Livro {
    int isbn;
    char *titulo;
    char *autor;
    int ano;
    struct Livro *proximo;//ponteiro para o proximo livro na lista encadeada
} Livro;

Livro* tabelaHash[TAMANHO];//tabela hash, cada posicao eh uma lista

//funcao hash primaria baseada na soma dos valores ASCII do titulo
int hash(const char *titulo){
    int somaAscii = 0;
    while(*titulo){//percorre cada caractere do titulo
        somaAscii += (unsigned char)*titulo;//soma o valor ASCII do caractere
        titulo++;
    }

    return somaAscii % TAMANHO;//indice da tabela hash
}

//inicializa
void inicializar(){
    for(int i = 0;i < TAMANHO;i++){
        tabelaHash[i] = NULL; // Inicializa cada posição da tabela como NULL (lista vazia)
    }
}

//aloca string dinamicamente
char *alocarString(const char* str){
    char *novoStr = (char*)malloc(strlen(str) + 1);
    strcpy(novoStr, str);//pega a string original e passa pra nova
    return novoStr;//ponteiro para a nova string
}

//insere um livro
void inserirLivro(int isbn, const char *titulo, const char *autor, int ano){
    int indice = hash(titulo);//indice da tabela pela funcao hash
    Livro *novoLivro = (Livro*)malloc(sizeof(Livro));//cria um novo livro
    novoLivro->isbn = isbn;
    novoLivro->titulo = alocarString(titulo);//aloca e copia o titulo
    novoLivro->autor = alocarString(autor);//aloca e copia o autor
    novoLivro->ano = ano;                     
    novoLivro->proximo = tabelaHash[indice];//insere no inicio da lista encadeada
    tabelaHash[indice] = novoLivro;//atualiza a tabela hash com o livro novo
}

//busca o livro pelo titulo
Livro* buscarLivro(const char *titulo){
    int indice = hash(titulo);//indice da tabela pela funcao hash
    Livro *atual = tabelaHash[indice];//busca na lista encadeada

    while(atual){//percorre a lista encadeada
        if(strcmp(atual->titulo, titulo) == 0){//se o titulo eh igual
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;//nao achou
}

//remove pelo titulo
void removerLivro(const char *titulo){
    int indice = hash(titulo);//indice da tabela pela funcao hash
    Livro *atual = tabelaHash[indice];
    Livro *anterior = NULL;

    while(atual){//percore a lista
        if(strcmp(atual->titulo, titulo) == 0){//se o titulo eh igual
            if(anterior){//se nao for o primeiro da lista
                anterior->proximo = atual->proximo;//remove
            }else{
                tabelaHash[indice] = atual->proximo;//atualiza o inicio
            }

            free(atual->titulo);
            free(atual->autor);
            free(atual);
            printf("Removido\n");
            return;
        }
        anterior = atual;//atualiza o ponteiro para o livro anterior
        atual = atual->proximo;//pega o próximo livro na lista
    }
    printf("Livro nao encontrado\n");
}

//imprime os livros na posicao
void imprimirLivrosNaPosicao(int posicao){
    if(posicao < 0 || posicao >= TAMANHO){
        printf("Posicao invalida\n");
        return;
    }

    Livro *atual = tabelaHash[posicao];//impressao da lista
    while(atual){//percorre a lista encadeada
        printf("ISBN: %d, Titulo: %s, Autor: %s, Ano: %d\n", atual->isbn, atual->titulo, atual->autor, atual->ano);
        atual = atual->proximo;//pega o proximo da lista
    }
}

//imprime tydo
void imprimirTodos(){
    for(int i = 0;i < TAMANHO;i++){//percorre cada posicao
        printf("Posicao %d:\n", i);
        imprimirLivrosNaPosicao(i);
    }
}

int main(){
    inicializar();
    int escolha;
    int isbn;
    char titulo[100];
    char autor[100];
    int ano;

    do{
        printf("Escolha:\n1. Inserir livro\n2. Buscar livro\n3. Remover livro\n4. Imprimir livros em posicao\n5. Imprimir todos os livros\n6. Sair\n");
        scanf("%d", &escolha);
        getchar();//pra n bugar

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
                printf("Digite o titulo para buscar: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                {
                    Livro *livro = buscarLivro(titulo);
                    if(livro){
                        printf("Livro encontrado: ISBN: %d, Titulo: %s, Autor: %s, Ano: %d\n", livro->isbn, livro->titulo, livro->autor, livro->ano);
                    }else{
                        printf("Livro nao encontrado.\n");
                    }
                }
                break;
            case 3:
                printf("Digite o titulo para remover: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                removerLivro(titulo);
                break;
            case 4:
                {
                    int posicao;
                    printf("Digite a posicao para imprimir os livros: ");
                    scanf("%d", &posicao);
                    imprimirLivrosNaPosicao(posicao);
                }
                break;
            case 5:
                imprimirTodos();
                break;
            case 6:
                //limpa td
                for(int i = 0;i < TAMANHO;i++){
                    Livro *atual = tabelaHash[i];
                    while(atual){
                        Livro *proximo = atual->proximo;
                        //n da free no int e no isbn pq eh int
                        free(atual->titulo);
                        free(atual->autor);
                        free(atual);
                        atual = proximo;//avança para o proximo livro na lista
                    }
                }
                exit(0);
            default:
                printf("Opcao invalida\n");
        }
    }while(escolha != 6);

    return 0;
}
