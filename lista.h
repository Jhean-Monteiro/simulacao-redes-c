#ifndef LISTA_H
#define LISTA_H

typedef struct No {
    int id;
    char origem[30];
    char destino[30];
    char status[20];
    struct No *prox;
} No;

void inserirPacoteLista(int id, const char *origem, const char *destino, const char *status);

void listarPacotes(void);
void buscarPacote(int id);
void removerPacote(int id);

#endif