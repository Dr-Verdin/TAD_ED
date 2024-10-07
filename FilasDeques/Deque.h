#ifndef DEQUE_H
	#define DEQUE_H
	
	#include <stdbool.h>
    #include "item.h"

	typedef struct deque_ DEQUE;

	DEQUE *deque_criar();
    bool deque_cheia(DEQUE *deque);
    bool deque_vazia(DEQUE *deque);
    bool deque_enqueue_fim(DEQUE *deque, ITEM *item);
    bool deque_enqueue_inicio(DEQUE *deque, ITEM *item);
    ITEM *deque_dequeue_inicio(DEQUE *deque);
    ITEM *deque_dequeue_fim(DEQUE *deque);
    void deque_apagar(DEQUE **deque);
    void deque_imprimir(DEQUE *deque);
    int deque_tamanho(DEQUE *deque);
    ITEM *deque_frente(DEQUE *deque);
    ITEM *deque_final(DEQUE *deque);
    void deque_inverter(DEQUE *deque);
#endif