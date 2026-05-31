#include <stdio.h>
#include "fila.h"
#include "pilha.h"
#include "lista.h"


int main(void) {

    // FILA
    adicionarFila(1, 500, 1.2);
    adicionarFila(2, 300, 0.8);
    adicionarFila(3, 700, 2.0);
    adicionarFila(4, 200, 0.5);

    mostrarFila();

    printf("\n[SIMULACAO] Transmitindo 2 pacotes...\n");
    transmitirPacote();
    transmitirPacote();

    mostrarFila();

    
    // PILHA
    adicionarErro(2);

    mostrarPilha();

    retransmitirPacote();

    
    // LISTA
    inserirPacoteLista(1, "Servidor A", "Cliente X", "Em transito");
    inserirPacoteLista(2, "Servidor B", "Cliente Y", "Entregue");
    inserirPacoteLista(3, "Servidor C", "Cliente Z", "Em transito");

    listarPacotes();

    buscarPacote(2);

    removerPacote(2);

    listarPacotes();

    return 0;
}