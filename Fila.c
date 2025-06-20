#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char **documentos;
    int inicio, final, qtd, capacidade;
}fi_impressao;

void inicializar(fi_impressao *fila, int capacidade_inicial){
    fila->documentos = (char **)malloc(capacidade_inicial * sizeof(char *));
    fila->capacidade = capacidade_inicial;
    fila->inicio = 0;
    fila->final = -1;
    fila-> qtd = 0;
}

bool filaVazia(fi_impressao *fila){
    return (fila->qtd == 0);
}

void resize(fi_impressao *fila){
    int nova_cap = fila->capacidade * 2;
    char **novosDocs = (char **)malloc(nova_cap * sizeof(char *));

    for(int i=0; i < fila->qtd; i++){
        int j = (fila->inicio + i) % fila->capacidade;
        novosDocs[i] = fila -> documentos[j];

    }

    free(fila->documentos);
    fila->documentos = novosDocs;
    fila->inicio = 0;
    fila->final =  fila->qtd -1;
    fila->capacidade = nova_cap;
}

void addDocs(fi_impressao *fila, char *documento){
    if(fila->qtd == fila->capacidade){
            resize(fila);
    }

    fila->final = (fila->final + 1) % fila->capacidade;
    fila->documentos[fila->final] = malloc(strlen(documento) + 1);
    strcpy(fila->documentos[fila->final], documento);
    fila->qtd++;
    printf("Documento '%s' adicionado a fila.\n\n", documento);
}

void imprimirNext(fi_impressao *fila){
    if(filaVazia(fila)){
        printf("A fila está vazia.\n");
        return;
    }

    char *documento = fila->documentos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->qtd--;

    printf("Imprimindo: %s\n\n", documento);
    free(documento);
}

void mostrarFila(fi_impressao *fila){
     if(filaVazia(fila)){
        printf("A fila está vazia.\n");
        return;
    }

    printf("\n\tFila de impressão(%d/%d):\n\n", fila->qtd,fila->capacidade);
    for(int i = 0; i < fila->qtd; i++){
        int j = (fila->inicio + i) % fila->capacidade;
        printf("%d. %s\n", i + 1, fila->documentos[j]);
    }
    printf("\n");
}

void liberarFila(fi_impressao *fila){
    for(int i = 0; i<fila->qtd; i++){
        int j = (fila->inicio + i) % fila->capacidade;
        free(fila->documentos[j]);
    }
    free(fila->documentos);
}

int main(){
    fi_impressao fila;
    inicializar(&fila, 2);

    int opcao;
    char documento[300];

    do{
        printf("\tMenu\n\n");
        printf("1 - Adicionar documento:\n");
        printf("2 - Imprimir proximo documento:\n");
        printf("3 - Mostrar fila de impressao\n");
        printf("4 - Sair\n");
        printf("\nEscolha uma opcao: ");
        char input[10];
        fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%d", &opcao) != 1) {
                opcao = -1; 
                }

        switch(opcao){
            case 1:
                printf("Digite o nome do documento: ");
                fgets(documento, sizeof(documento), stdin);
                documento[strcspn(documento, "\n")] = '\0';
                addDocs(&fila, documento);
                break;
            
            case 2:
                imprimirNext(&fila);
                break;
                
            case 3:
                mostrarFila(&fila);
                break;

            case 4: 
                printf("\nEncerrando...");
                break;
                
            default:
                printf("Opção inválida!\n");    
        }   

        
    } while (opcao != 4);

    liberarFila(&fila);

    return 0;
}
