#ifndef FILA_H
	#define FILA_H
	
	#include <stdbool.h>
    #include "item.h"

	typedef struct fila_ FILA;

	FILA *fila_criar();
    bool fila_cheia(FILA *fila);
    bool fila_vazia(FILA *fila);
    bool fila_enqueue(FILA *fila, ITEM *item);
    ITEM *fila_dequeue(FILA *fila);
    void fila_apagar(FILA **fila);
    void fila_imprimir(FILA *fila);
    int fila_tamanho(FILA *fila);
    ITEM *fila_frente(FILA *fila);
    void fila_inverter(FILA *fila);
    // void fila_concatenar(FILA *fila1, FILA *fila2);
    // FILA *fila_filtrar(FILA *fila, int chave);

#endif