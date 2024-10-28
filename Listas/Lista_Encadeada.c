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

bool lista_inserir_ord(LISTA *lista, NODE *newnode, ITEM *item){
    NODE *atual = lista->inicio;
    NODE *anterior = NULL;

    while(atual != NULL && item_get_chave(atual->item) < item_get_chave(item)){
        anterior = atual;
        atual = atual->proximo;
    }

    if(anterior == NULL){
        newnode->proximo = atual;
        lista->inicio = newnode;
    } else {
        newnode->proximo = atual;
        anterior->proximo = newnode;
    }

    if(atual == NULL){
        lista->fim = newnode;
    }

    return true;
}

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista != NULL){
        NODE *newnode = (NODE *)malloc(sizeof(NODE));
        if(newnode == NULL)
            return false;

        newnode->item = item;
        newnode->proximo = NULL;

        if(lista->tam == 0){
            lista->inicio = lista->fim = newnode;
        } else if(lista->ordenada){
            return lista_inserir_ord(lista, newnode, item);
        } else {
            lista->fim->proximo = newnode;
            lista->fim = newnode;
        }

        lista->tam++;
        return true;
    }
    return false;
}
ITEM *lista_buscar(LISTA *lista, int chave){
    if(lista!= NULL){
        NODE *atual = lista->inicio;
        while(atual!= NULL){
            if(item_get_chave(atual->item) == chave){
                return atual->item;
            }
            atual = atual->proximo;
        }
    }
    return NULL;
}

ITEM *lista_remover(LISTA *lista, int chave){
    if(lista != NULL && !lista_vazia(lista)){
        NODE *atual = lista->inicio;
        NODE *anterior = NULL;

        while(atual != NULL && item_get_chave(atual->item)!= chave){
            anterior = atual;
            atual = atual->proximo;
        }

        if(atual != NULL){
            if(anterior == NULL){
                lista->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            if(atual == lista->fim){
                lista->fim = anterior;
            }

            ITEM *item_rm = atual->item;
            free(atual);
            lista->tam--;
            return item_rm;
        }
    }
    return NULL;
}

int lista_tamanho(LISTA *lista){
    if(lista!= NULL){
        return lista->tam;
    }
    return NULL;
}

void lista_imprimir(LISTA *lista){
    if(lista!= NULL){
        NODE *atual = lista->inicio;
        while(atual!= NULL){
            printf("%d ", item_get_chave(atual->item));
            atual = atual->proximo;
        }
        printf("\n");
    }
}

bool lista_apagar(LISTA **lista){
    if(lista!= NULL &&!lista_vazia(lista)){
        NODE *atual = (*lista)->inicio;
        NODE *proximo;

        while(atual!= NULL){
            proximo = atual->proximo;
            item_apagar(atual->item);
            free(atual);
            atual = proximo;
        }

        free(*lista);
        *lista = NULL;
        return true;
    }
    return false;
}
void lista_alterar_item(LISTA *lista, int chave, ITEM *newitem){
    if(lista!= NULL){
        NODE *atual = lista->inicio;

        while(atual!= NULL){
            if(item_get_chave(atual->item) == chave){
                item_apagar(atual->item);
                atual->item = newitem;
                return;
            }
            atual = atual->proximo;
        }
    }
}