#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_DEQUE 100
#include "item.h"

typedef struct deque_ {
    ITEM *itens[MAX_DEQUE];
    int inicio;
    int fim;
    int tam;
}DEQUE;

DEQUE *deque_criar(){
    DEQUE *deque = (DEQUE *)malloc(sizeof(DEQUE));
    if(deque != NULL){
        deque->inicio = 0;
        deque->fim = 0;
        deque->tam = 0;
    }
    return NULL;
}

bool deque_cheia(DEQUE *deque){
    if(deque != NULL){
        return deque->tam == MAX_DEQUE;
    }
    return false;
}
bool deque_vazia(DEQUE *deque){
    if(deque != NULL){
        return deque->tam == 0;
    }
    return false;
}

bool deque_enqueue_fim(DEQUE *deque, ITEM *item){
    if(deque != NULL && !deque_cheia(deque)){ 
        deque->itens[deque->tam] = item;
        deque->fim = (deque->fim + 1) % MAX_DEQUE; // circular
        deque->tam++;

        return true;
    }
    return false;
}

bool deque_enqueue_inicio(DEQUE *deque, ITEM *item){
    if(deque != NULL && !deque_cheia(deque)){ 
        deque->itens[deque->inicio] = item;
        deque->inicio = (deque->inicio - 1 + MAX_DEQUE) % MAX_DEQUE; // circular
        deque->tam++;

        return true;
    }
    return false;
}
ITEM *deque_dequeue_inicio(DEQUE *deque){
    if(deque != NULL && !deque_vazia(deque)){
        ITEM *item = deque->itens[deque->inicio]; 
        deque->itens[deque->inicio] = NULL;
        deque->inicio = (deque->inicio + 1) % MAX_DEQUE; // circular
        deque->tam--;

        return item;
    }
    return NULL;
}

ITEM *deque_dequeue_fim(DEQUE *deque){
    if(deque != NULL && !deque_vazia(deque)){
        ITEM *item = deque->itens[deque->fim]; 
        deque->itens[deque->fim] = NULL;
        deque->fim = (deque->fim - 1 + MAX_DEQUE) % MAX_DEQUE; // circular
        deque->tam--;

        return item;
    }
    return NULL;
}

void deque_apagar(DEQUE **deque){
    if(deque != NULL && !deque_vazia(deque)){
        free(*deque);
        *deque = NULL;
    }
}

void deque_imprimir(DEQUE *deque){
    if(deque != NULL){
        for(int i = 0; i < deque->tam; i++){
            printf("%d ", item_get_chave(deque->itens[i]));
        }
        printf("\n");
    }
}
int deque_tamanho(DEQUE *deque){
    if(deque != NULL){
        return deque->tam;
    }
    return NULL;
}
ITEM *deque_frente(DEQUE *deque){
    if(deque != NULL &&!deque_vazia(deque)){
        return deque->itens[deque->inicio];
    }
    return NULL;
}

ITEM *deque_final(DEQUE *deque){
    if(deque != NULL &&!deque_vazia(deque)){
        return deque->itens[deque->fim];
    }
    return NULL;
}

void deque_inverter(DEQUE *deque){
    if(deque != NULL){
        for(int i = 0; i < deque->tam / 2; i++){
            ITEM *temp = deque->itens[i];
            deque->itens[i] = deque->itens[deque->tam - i - 1];
            deque->itens[deque->tam - i - 1] = temp;
        }
    }
}