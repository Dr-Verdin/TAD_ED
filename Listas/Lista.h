#ifndef LISTA_H
    #define LISTA_H
    #include <stdbool.h>
    #include "item.h"

    #define MAX_LISTA 100

    typedef struct lista_ LISTA;

    LISTA *lista_criar(bool ordenada);
    bool lista_cheia(LISTA *lista);
    bool lista_vazia(LISTA *lista);
    bool lista_inserir(LISTA *lista, ITEM *item);
    ITEM *lista_buscar(LISTA *lista, int chave);
    ITEM *lista_remover(LISTA *lista, int chave);
    int lista_tamanho(LISTA *lista);
    void lista_imprimir(LISTA *lista);
    bool lista_apagar(LISTA **lista);
    void lista_alterar_item(LISTA *lista, ITEM *item, ITEM *newitem);
    /*LISTA *lista_concatenar(LISTA *lista1, LISTA *lista2);*/
#endif