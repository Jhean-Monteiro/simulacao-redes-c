#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

static No *cabeca = NULL;

void inserirPacoteLista(int id, const char *origem, const char *destino, const char *status) {
    
    No *novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("[LISTA] Erro: memória insuficiente.\n");
        return;
    }

    novo->id = id;
    strncpy(novo->origem, origem, sizeof(novo->origem) - 1);
    strncpy(novo->destino, destino, sizeof(novo->destino) - 1);
    strncpy(novo->status, status, sizeof(novo->status) - 1);

    novo->prox = cabeca;
    cabeca = novo;
    
}

void listarPacotes(void) {
    No *aux = cabeca;

    printf("\n[LISTA] Pacotes ativos na rede:\n");

    if (aux == NULL) {
        printf("  (nenhum)\n");
        return;
    }

    while (aux != NULL) {
        printf("  ID: %d | Origem: %-12s | Destino: %-12s | Status: %s\n",
               aux->id,
               aux->origem,
               aux->destino,
               aux->status);

        aux = aux->prox;
    }
}

void buscarPacote(int id) {
    No *aux = cabeca;

    while (aux != NULL) {
        if (aux->id = id) {
            printf("\n[LISTA] Pacote %d encontrado!\n", id);
            printf("  Origem:  %s\n", aux->origem);
            printf("  Destino: %s\n", aux->destino);
            printf("  Status:  %s\n", aux->status);
            return;
        }
        aux = aux->prox;
    }
    printf("\n[LISTA] Pacote %d nao encontrado.\n", id);
}

void removerPacote(int id) {
    No *aux = cabeca;
    No *anterior = NULL;

    while (aux != NULL && aux->id != id) {
        anterior = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("\n[LISTA] Pacote %d nao encontrado para remocao.\n", id);
        return;
    }

    if (anterior == NULL) {
        cabeca = aux->prox;
    } else {
        anterior-> prox = aux-> prox;
    }

    free(aux);
    printf("\n[LISTA] Pacote %d removido.\n", id);
}