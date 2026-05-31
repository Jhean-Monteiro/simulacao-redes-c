#include <stdio.h>
#include "pilha.h"

static PacotePilha pilha[PILHA_MAX];
static int topo = -1;


void adicionarErro(int numero) {
    if (topo >= PILHA_MAX - 1) {
        printf("[PILHA] Pilha cheia! Pacote %d não registrado. \n", numero);
        return;
    }

    topo++;
    pilha[topo].numero = numero;
}

void retransmitirPacote(void) {
    if (topo == -1) {
        printf("[PILHA] Pilha Vazia!\n");
        return;
    }

    printf("[PILHA] Retransmitido pacote %d\n", pilha[topo].numero);
    topo--;
}

void mostrarPilha(void) {
    int i;
    printf("\n[PILHA] Pacotes com erro (topo -> base):\n");

    if (topo == -1) {
        printf(" (vazia)\n");
        return;
    }

    for (i = topo; i >= 0; i--) {
        printf(" Pacote %d\n", pilha[i].numero);
    }
}