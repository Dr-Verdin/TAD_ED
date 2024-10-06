#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "item.h"

#define MAX_FILA 100

typedef struct node_{
    ITEM *item;
    struct node_ *proximo;
} NODE;

typedef struct fila_ {
    NODE *inicio;
    NODE *fim;
    int tam;
}FILA;

FILA *fila_criar(){
    FILA *fila = (FILA *)malloc(sizeof(FILA));

    if(fila!= NULL){
        fila->inicio = NULL;
        fila->fim = NULL;
        fila->tam = 0;
    }
    return NULL;
}

bool fila_cheia(FILA *fila){
    if(fila!= NULL){
        return fila->tam == MAX_FILA;
    }
    return false;
}
bool fila_vazia(FILA *fila){
    if(fila!= NULL){
        return fila->tam == 0; 
    }
    return false;
}

bool fila_enqueue(FILA *fila, ITEM *item){
    if(fila != NULL && !fila_cheia(fila)){
        NODE *new = (NODE *)malloc(sizeof(NODE));

        if(new!= NULL){
            new->item = item;
            new->proximo =  NULL;

            if(fila->inicio == NULL){
                fila->inicio = new;
            }

            fila->fim = new;
            fila->tam++;

            return true;
        }
    }
    return false;
}

ITEM *fila_dequeue(FILA *fila){
    if(fila != NULL && !fila_vazia(fila)){
        NODE *temp = fila->inicio;
        ITEM *item = temp->item;
        fila->inicio = fila->inicio->proximo;
        if(fila->inicio == NULL){
            fila->fim = NULL;  // fila ficou vazia após o dequeue
        }
        fila->tam--;

        free(temp);
        return item;
    }
    return NULL;
}

void fila_apagar(FILA **fila){
    if(fila != NULL){
        NODE *temp;

        while((*fila)->inicio != NULL){
            temp = (*fila)->inicio;
            (*fila)->inicio = (*fila)->inicio->proximo;
            item_apagar(&temp->item);
            temp->proximo = NULL;
            free(temp);
        }

        free(*fila);
        *fila = NULL;  
    }
}

void fila_imprimir(FILA *fila){
    if(fila != NULL){
        if(fila_vazia(fila)){
            printf("Fila vazia.\n");
        }

        NODE *aux = fila->inicio;
 
        while(aux!= NULL){
            printf("%d ", item_get_chave(aux->item));
            aux = aux->proximo;
        }
        printf("\n");
    }
}

int fila_tamanho(FILA *fila){
    if(fila!= NULL){
        return fila->tam;
    }
    return NULL;
}

ITEM *fila_frente(FILA *fila){
    if(fila != NULL && !fila_vazia(fila)){
        ITEM *item = fila->inicio;
        return item;
    }
    return NULL;
}