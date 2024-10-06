#ifndef PILHA_H
    #define PILHA_H
    #define  ERRO -32000
    #define  MAX_PILHA 1000

    #include "item.h"
    #include <stdbool.h>

    typedef struct pilha_ PILHA;

    PILHA *pilha_criar();
    bool pilha_cheia(PILHA *pilha);
    bool pilha_vazia(PILHA *pilha);
    bool pilha_push(PILHA *pilha, ITEM *item);
    ITEM *pilha_pop(PILHA *pilha);
    void pilha_apagar(PILHA **pilha);
    ITEM *pilha_topo(PILHA *pilha);
    int pilha_tamanho(PILHA *pilha);
    void pilha_imprimir(PILHA *pilha);
    void pilha_inverter(PILHA *pilha);
#endif