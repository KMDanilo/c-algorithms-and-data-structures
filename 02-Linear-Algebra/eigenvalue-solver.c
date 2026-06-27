#include <stdio.h>
#include <stdlib.h>
// Trabalho de Algebra Linear - Danilo Kotaka e Marco Henry
// Função que imprime uma matriz 3x3
void imprimir_matriz(int **mat1){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
           printf("%d ", mat1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
//Função que libera a memória alocada para uma matriz 3x3
void liberar_matriz(int **mat1){
    for(int i = 0; i < 3; i++){
        free(mat1[i]);
    }
    free(mat1);
}
//Função que libera a memória alocada para um vetor de tamanho 3
void liberar_vetor(int *vetor){
    free(vetor);
}
//Função que calcula o polinômio característico de uma matriz 3x3
int* polinomio_caracteristico(int **matriz) {
    int* polinomio = malloc(4 * sizeof(int));
    polinomio[0] = -1;
    polinomio[1] = matriz[0][0] + matriz[1][1] + matriz[2][2];
    polinomio[2] = -(matriz[0][0]*matriz[1][1] - matriz[0][1]*matriz[1][0] + matriz[0][0]*matriz[2][2] - matriz[0][2]*matriz[2][0] + matriz[1][1]*matriz[2][2] - matriz[1][2]*matriz[2][1]);
    polinomio[3] = matriz[0][0] * matriz[1][1] * matriz[2][2] + matriz[0][1] * matriz[1][2] * matriz[2][0] + matriz[0][2] * matriz[1][0] * matriz[2][1] - matriz[0][0] * matriz[1][2] * matriz[2][1] - matriz[0][1] * matriz[1][0] * matriz[2][2] - matriz[0][2] * matriz[1][1] * matriz[2][0];
printf("Polinomio caracteristico: \n");  
printf( "%dx^3 + (%dx)^2 + (%dx) + (%d) = 0\n\n", polinomio[0], polinomio[1], polinomio[2], polinomio[3]);
return polinomio;
}
//Função que calcula o determinante de uma matriz 3x3
int calcular_determinante(int **matriz) {
    int x;
    x = (matriz[0][0] * matriz[1][1] * matriz[2][2]) +
        (matriz[0][1] * matriz[1][2] * matriz[2][0]) +
        (matriz[2][1] * matriz[1][0] * matriz[0][2]) -
        (matriz[0][2] * matriz[1][1] * matriz[2][0]) -
        (matriz[0][0] * matriz[2][1] * matriz[1][2]) -
        (matriz[2][2] * matriz[1][0] * matriz[0][1]);
    return x;
}
//Função que calcula as raízes do polinômio característico
int* raizes_polinomio(int* indices, int y){

    int a = -1;
    int b = indices[1];
    int c = indices[2];
    int d = indices[3];
    int *lambdas = calloc(3,sizeof(int));
    int contador = 0;
    for(int i = -1000; i < 1000; i++){
        if(i*i*i*a + i*i*b + i*c + d == 0){
            lambdas[contador] = i;
            contador++;
        }
    }
    // Casos em que o polinômio possui raízes iguais
    if(y == lambdas[0]*lambdas[1]*lambdas[2]){
    printf("Autovalores: \n");
    for(int i = 0; i < 3; i++){
        printf("lambda[%d] = %d\n",i+1, lambdas[i]);
    }
    }else if(y == lambdas[0]*lambdas[1]*lambdas[1]){
        printf("Autovalores: \n");
        lambdas[2] = lambdas[1];
        for(int i = 0; i < 2; i++){
            printf("lambda[%d] = %d\n",i+1, lambdas[i]);
        }
    }else if(y == lambdas[0]*lambdas[0]*lambdas[1]){
        printf("Autovalores: \n");
        lambdas[2] = lambdas[0];
        for(int i = 0; i < 2; i++){
            printf("lambda[%d] = %d\n",i+1, lambdas[i]);
        }
    }
    printf("\n");
    return lambdas;
}
//Função que calcula a matriz autovalores
void matriz_autovalores(int* lambda){
    int **mat = calloc(3, sizeof(int*));
    for(int i = 0; i < 3; i++){
        mat[i] = calloc(3, sizeof(int));
        for(int j = 0; j < 3; j++){
            if(i == j)
                mat[i][j] = lambda[i];
            else
                mat[i][j] = 0;
        }
    }
    printf("Matriz autovalores: \n");
    imprimir_matriz(mat);
    liberar_matriz(mat);
}
//Função que calcula os autovetores
void calcular_autovetores(int **mat, int *lambda) {
    int *autovetor1 = calloc(3, sizeof(int));
    int *autovetor2 = calloc(3, sizeof(int));
    int *autovetor3 = calloc(3, sizeof(int));
    // Força bruta para encontrar os autovetores com a fórmula mat*v = lambda*v
    for (int i = -100; i <= 100; i++) {
        for (int j = -100; j <= 100; j++) {
            for (int k = -100; k <= 100; k++) {

                if(i != 0 || j != 0 || k != 0){
                    if (mat[0][0] * i + mat[0][1] * j + mat[0][2] * k == lambda[0] * i &&
                        mat[1][0] * i + mat[1][1] * j + mat[1][2] * k == lambda[0] * j &&
                        mat[2][0] * i + mat[2][1] * j + mat[2][2] * k == lambda[0] * k) {                      
                        autovetor1[0] = i;
                        autovetor1[1] = j;
                        autovetor1[2] = k; 
                    }
                    if (mat[0][0] * i + mat[0][1] * j + mat[0][2] * k == lambda[1] * i &&
                        mat[1][0] * i + mat[1][1] * j + mat[1][2] * k == lambda[1] * j &&
                        mat[2][0] * i + mat[2][1] * j + mat[2][2] * k == lambda[1] * k) {
                        autovetor2[0] = i;
                        autovetor2[1] = j; 
                        autovetor2[2] = k;
                    }
                    if (mat[0][0] * i + mat[0][1] * j + mat[0][2] * k == lambda[2] * i &&
                        mat[1][0] * i + mat[1][1] * j + mat[1][2] * k == lambda[2] * j &&
                        mat[2][0] * i + mat[2][1] * j + mat[2][2] * k == lambda[2] * k) {
                        autovetor3[0] = i;
                        autovetor3[1] = j;
                        autovetor3[2] = k;
                    }
                }
            }
        }
    }
    for(int i = -100; i <= 100; i++){
        if(i != 0 && autovetor1[0]%i == 0 && autovetor1[1]%i == 0 && autovetor1[2]%i == 0){
            autovetor1[0] = autovetor1[0] / i;
            autovetor1[1] = autovetor1[1] / i;
            autovetor1[2] = autovetor1[2] / i;
        }
        if(i != 0 && autovetor2[0]%i == 0 && autovetor2[1]%i == 0 && autovetor2[2]%i == 0){
            autovetor2[0] = autovetor2[0] / i;
            autovetor2[1] = autovetor2[1] / i;
            autovetor2[2] = autovetor2[2] / i;
        }       
        if(i != 0 && autovetor3[0]%i == 0 && autovetor3[1]%i == 0 && autovetor3[2]%i == 0){
            autovetor3[0] = autovetor3[0] / i;
            autovetor3[1] = autovetor3[1] / i;
            autovetor3[2] = autovetor3[2] / i;
        }
    }
        printf("Autovetores associados a cada autovalor:\n\n");
        // Casos em que o polinômio possui raízes iguais para printar certo.
    if(lambda[0] != lambda[1] && lambda[0] != lambda[2] && lambda[1] != lambda[2]){
        printf("%d:\n", lambda[0]);
        printf("[(%d,%d,%d)]\n", autovetor1[0], autovetor1[1], autovetor1[2]);
        printf("\n");
        printf("%d:\n", lambda[1]);
        printf("[(%d,%d,%d)]\n", autovetor2[0], autovetor2[1], autovetor2[2]);
        printf("\n");
        printf("%d:\n", lambda[2]);
        printf("[(%d,%d,%d)]\n", autovetor3[0], autovetor3[1], autovetor3[2]);
    }else if(lambda[0] == lambda[1] && lambda[0] != lambda[2]){
        printf("%d:\n", lambda[0]);
        printf("[(%d,%d,%d), (%d,%d,%d)]\n", autovetor1[0], autovetor1[1], autovetor1[2], autovetor2[0], autovetor2[1], autovetor2[2]);
        printf("\n");
        printf("%d:\n", lambda[2]);
        printf("[(%d,%d,%d)]\n", autovetor3[0], autovetor3[1], autovetor3[2]);
    }else if(lambda[0] == lambda[2] && lambda[0] != lambda[1]){
        printf("%d:\n", lambda[0]);
        printf("[(%d,%d,%d), (%d,%d,%d)]\n", autovetor1[0], autovetor1[1], autovetor1[2], autovetor3[0], autovetor3[1], autovetor3[2]);
        printf("\n");
        printf("%d:\n", lambda[1]);
        printf("[(%d,%d,%d)]\n", autovetor2[0], autovetor2[1], autovetor2[2]);
    }else if(lambda[1] == lambda[2] && lambda[0] != lambda[1]){
        printf("%d:\n", lambda[0]);
        printf("[(%d,%d,%d)]\n", autovetor1[0], autovetor1[1], autovetor1[2]);
        printf("\n");
        printf("%d:\n", lambda[1]);
        printf("[(%d,%d,%d), (%d,%d,%d)]\n", autovetor2[0], autovetor2[1], autovetor2[2], autovetor3[0], autovetor3[1], autovetor3[2]);
    }
    liberar_vetor(autovetor1);
    liberar_vetor(autovetor2);
    liberar_vetor(autovetor3);
}

int main(int argc, char** argv){
    // Abre o arquivo de entrada e o arquivo de saída
    FILE* output = freopen("danilokotakaemarcohenry.txt", "w",stdout);
        if(output == NULL){
            printf("Erro ao abrir arquivo\n");
            return 0;
        }
    printf("Nomes: Danilo Kotaka e Marco Henry \n\n");
    FILE* input = fopen(argv[1], "r");
    if(input == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 0;
    }
    //Lê a matriz de entrada
    int** matriz = calloc(3, sizeof(int*));
    for(int i = 0; i < 3; i++){
        matriz[i] = calloc(3, sizeof(int));
        for(int j = 0; j < 3; j++){
            fscanf(input, "%d", &matriz[i][j]);
        }
    }
    //Chamada das funções
    printf("Matriz de entrada: \n");
    imprimir_matriz(matriz);
    int * indices_polinomio = polinomio_caracteristico(matriz);
    int * lamb = raizes_polinomio(indices_polinomio, calcular_determinante(matriz));
    matriz_autovalores(lamb);
    calcular_autovetores(matriz, lamb);  
    liberar_matriz(matriz);
    liberar_vetor(indices_polinomio);
    liberar_vetor(lamb);
    fclose(output);
    fclose(input);
    return 0; 
}