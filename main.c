#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **dados;      // Ponteiro genérico para os elementos da fila
    int inicio;        // Índice do primeiro elemento
    int fim;           // Índice do último elemento
    int tamanho;       // Quantidade atual de elementos na fila
    int capacidade;    // Capacidade total da fila
} Fila;

Fila* criarFila(int capacidadeInicial) {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    if (fila == NULL) return NULL;

    fila->dados = (void **) malloc(sizeof(void*) * capacidadeInicial);
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    fila->capacidade = capacidadeInicial;

    return fila;
}

void dobrarCapacidade(Fila *fila) {
    int novaCapacidade = fila->capacidade * 2;
    void **novosDados = (void **) malloc(sizeof(void*) * novaCapacidade);

    for (int i = 0; i < fila->tamanho; i++) {
        int indice = (fila->inicio + i) % fila->capacidade;
        novosDados[i] = fila->dados[indice];
    }

    free(fila->dados);
    fila->dados = novosDados;
    fila->inicio = 0;
    fila->fim = fila->tamanho - 1;
    fila->capacidade = novaCapacidade;
}

int inserirNaFila(Fila *fila, void *item) {
    if (fila->tamanho == fila->capacidade) {
        dobrarCapacidade(fila);
    }

    fila->fim = (fila->fim + 1) % fila->capacidade;
    fila->dados[fila->fim] = item;
    fila->tamanho++;
    return 1;
}

void* removerDaFila(Fila *fila) {
    if (fila->tamanho == 0) {
        return NULL;
    }

    void *item = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;
    return item;
}

void limparFila(Fila *fila) {
    if (fila != NULL) {
        free(fila->dados);
        free(fila);
    }
}

int main() {
    int capacidadeInicial;
    printf("Digite a capacidade inicial da fila: ");
    scanf("%d", &capacidadeInicial);

    Fila *fila = criarFila(capacidadeInicial);

    int quantidade;
    printf("Quantos números você quer adicionar à fila? ");
    scanf("%d", &quantidade);

    for (int i = 0; i < quantidade; i++) {
        int *valor = (int *) malloc(sizeof(int));
        printf("Digite o valor %d: ", i + 1);
        scanf("%d", valor);
        inserirNaFila(fila, valor);
        printf("Inserido: %d\n", *valor);
    }

    printf("\nRemovendo valores da fila:\n");
    for (int i = 0; i < quantidade; i++) {
        int *valor = (int *) removerDaFila(fila);
        if (valor != NULL) {
            printf("Removido: %d\n", *valor);
            free(valor);
        }
    }

    limparFila(fila);
    return 0;
}
