#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "item.h"

#define MAX_LISTA 100

typedef struct node_ {
    ITEM *item;
    struct node_ *proximo;
} NODE;

typedef struct lista_ {
    NODE *inicio;
    NODE *fim;
    int tam;
    bool ordenada;  // true se a lista está ordenada por chave, false caso contrário.
} LISTA;

LISTA *lista_criar(bool ordenada){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));

    if(lista != NULL){
        lista->tam = 0;
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->ordenada = ordenada;
        return(lista);
    }
    return NULL;
}

bool lista_cheia(LISTA *lista){
    if(lista != NULL){
        return lista->tam == MAX_LISTA;
    }
    return false;
}

bool lista_vazia(LISTA *lista){
    if(lista != NULL){
        return lista->tam == 0;
    }
    return false;
}

bool lista_inserir(LISTA *lista, ITEM *item){
    
}
ITEM *lista_buscar(LISTA *lista, int chave);
ITEM *lista_remover(LISTA *lista, int chave);
int lista_tamanho(LISTA *lista);
void lista_imprimir(LISTA *lista);
bool lista_apagar(LISTA **lista);
void lista_alterar_item(LISTA *lista, ITEM *item, ITEM *newitem);