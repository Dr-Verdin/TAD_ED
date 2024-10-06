#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_FILA 100
#include "item.h"

typedef struct fila_ {
    ITEM *itens[MAX_FILA];
    int inicio;
    int fim;
    int tam;
}FILA;

FILA *fila_criar(){
    FILA *fila = (FILA *)malloc(sizeof(FILA));
    if(fila != NULL){
        fila->inicio = 0;
        fila->fim = 0;
        fila->tam = 0;
    }
    return NULL;
}

bool fila_cheia(FILA *fila){
    if(fila != NULL){
        return fila->tam == MAX_FILA;
    }
    return false;
}
bool fila_vazia(FILA *fila){
    if(fila != NULL){
        return fila->tam == 0;
    }
    return false;
}

bool fila_enqueue(FILA *fila, ITEM *item){
    if(fila != NULL && !fila_cheia(fila)){ 
        fila->itens[fila->tam] = item;
        fila->fim = (fila->fim + 1) % MAX_FILA; // circular
        fila->tam++;

        return true;
    }
    return false;
}
ITEM *fila_dequeue(FILA *fila){
    if(fila != NULL && !fila_vazia(fila)){
        ITEM *item = fila->itens[fila->inicio]; 
        fila->itens[fila->inicio] = NULL;
        fila->inicio = (fila->inicio + 1) % MAX_FILA; // circular
        fila->tam--;

        return item;
    }
    return NULL;
}
void fila_apagar(FILA **fila){
    if(fila != NULL && !fila_vazia(fila)){
        free(*fila);
        *fila = NULL;
    }
}

void fila_imprimir(FILA *fila){
    if(fila != NULL){
        for(int i = 0; i < fila->tam; i++){
            printf("%d ", item_get_chave(fila->itens[i]));
        }
        printf("\n");
    }
}
int fila_tamanho(FILA *fila){
    if(fila != NULL){
        return fila->tam;
    }
    return NULL;
}
ITEM *fila_frente(FILA *fila){
    if(fila != NULL &&!fila_vazia(fila)){
        return fila->itens[fila->inicio];
    }
    return NULL;
}