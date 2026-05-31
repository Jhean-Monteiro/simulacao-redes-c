#include <stdio.h>
#include "fila.h"

static PacoteFila fila[FILA_MAX];
static int inicio = 0;
static int fim = 0;

void adicionarFila(int numero, int tamanho, float tempo) {
    if (fim >= FILA_MAX) {
        printf("[FILA] Fila cheia! Pacote %d descartado.\n", numero);
        return;
    }

    fila[fim].numero = numero;
    fila[fim].tamanho = tamanho;
    fila[fim].tempo = tempo;
    fim++;
}

void transmitirPacote(void) {
    if (inicio == fim) {
        printf("[FILA] fila vazia \n");
        return;
    }
    printf("[FILA] Transmitindo pacote %d \n", fila[inicio].numero);
    inicio++;
}

void mostrarFila(void) {
    int i;
    printf("\n[FILA] Pacotes aguardando transmissão:\n");

    if (inicio == fim) {
        printf(" (vazia)\n");
        return;
    }

    for (i = inicio; i < fim; i++) {
        printf(" Pacote %d - %d KB - %1f ms\n", fila[i].numero, fila[i].tamanho, fila[i].tempo);
    }
}