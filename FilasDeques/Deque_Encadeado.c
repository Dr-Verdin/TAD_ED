#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "item.h"

#define MAX_DEQUE 100

typedef struct node_{
    ITEM *item;
    struct node_ *proximo;
} NODE;

typedef struct deque_ {
    NODE *inicio;
    NODE *fim;
    int tam;
}DEQUE;

DEQUE *deque_criar(){
    DEQUE *deque = (DEQUE *)malloc(sizeof(DEQUE));

    if(deque!= NULL){
        deque->inicio = NULL;
        deque->fim = NULL;
        deque->tam = 0;
    }
    return NULL;
}

bool deque_cheia(DEQUE *deque){
    if(deque!= NULL){
        return deque->tam == MAX_DEQUE;
    }
    return false;
}
bool deque_vazia(DEQUE *deque){
    if(deque!= NULL){
        return deque->tam == 0; 
    }
    return false;
}

bool deque_enqueue_fim(DEQUE *deque, ITEM *item){
    if(deque != NULL && !deque_cheia(deque)){
        NODE *new = (NODE *)malloc(sizeof(NODE));

        if(new!= NULL){
            new->item = item;
            new->proximo =  NULL;

            if(deque->inicio == NULL){
                deque->inicio = new;
            } else {
                deque->fim->proximo = new;
            }

            deque->fim = new;
            deque->tam++;

            return true;
        }
    }
    return false;
}

bool deque_enqueue_inicio(DEQUE *deque, ITEM *item){
    if(deque != NULL && !deque_cheia(deque)){
        NODE *new = (NODE *)malloc(sizeof(NODE));

        if(new!= NULL){
            new->item = item;
            new->proximo =  deque->inicio;

            if(deque->inicio == NULL){
                deque->inicio = new;
            }

            deque->inicio = new;
            deque->tam++;

            return true;
        }
    }
    return false;
}

ITEM *deque_dequeue_inicio(DEQUE *deque){
    if(deque != NULL && !deque_vazia(deque)){
        NODE *temp = deque->inicio;
        ITEM *item = temp->item;
        deque->inicio = deque->inicio->proximo;
        if(deque->inicio == NULL){
            deque->fim = NULL;  // deque ficou vazia após o dequeue
        }
        deque->tam--;

        free(temp);
        return item;
    }
    return NULL;
}

ITEM *deque_dequeue_fim(DEQUE *deque){
    if(deque != NULL && !deque_vazia(deque)){
        NODE *temp = deque->fim;
        ITEM *item = temp->item;

        if(deque->inicio == deque->fim){
            deque->inicio = NULL;  // deque ficou vazia após o dequeue
            deque->fim = NULL;
        } else {
            NODE *atual = deque->inicio;
            while(atual->proximo != deque->fim){
                atual = atual->proximo;
            }
            deque->fim = atual;
            deque->fim->proximo = NULL;
        }

        deque->tam--;
        free(temp);
        return item;
    }
    return NULL;
}

void deque_apagar(DEQUE **deque){
    if(deque != NULL){
        NODE *temp;

        while((*deque)->inicio != NULL){
            temp = (*deque)->inicio;
            (*deque)->inicio = (*deque)->inicio->proximo;
            item_apagar(&temp->item);
            temp->proximo = NULL;
            free(temp);
        }

        free(*deque);
        *deque = NULL;  
    }
}

void deque_imprimir(DEQUE *deque){
    if(deque != NULL){
        if(deque_vazia(deque)){
            printf("deque vazia.\n");
        }

        NODE *aux = deque->inicio;
 
        while(aux!= NULL){
            printf("%d ", item_get_chave(aux->item));
            aux = aux->proximo;
        }
        printf("\n");
    }
}

int deque_tamanho(DEQUE *deque){
    if(deque!= NULL){
        return deque->tam;
    }
    return NULL;
}

ITEM *deque_frente(DEQUE *deque){
    if(deque != NULL && !deque_vazia(deque)){
        ITEM *item = deque->inicio;
        return item;
    }
    return NULL;
}

ITEM *deque_final(DEQUE *deque){
    if(deque != NULL && !deque_vazia(deque)){
        ITEM *item = deque->fim;
        return item;
    }
    return NULL;
}