#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "item.h"

#define MAX_LISTA 100

typedef struct lista_ {
    ITEM *itens[MAX_LISTA];
    int fim;
    int inicio;
    int tam;
    bool ordenada;  // true se a lista está ordenada por chave, false caso contrário.
} LISTA;

LISTA *lista_criar(bool ordenada){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));

    if(lista!= NULL){
        lista->tam = 0;
        lista->inicio = 0;
        lista->fim = 0;
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
    if(lista != NULL && !lista_cheia(lista)){ 
        if(lista->ordenada){
            return lista_inserir_ord(lista, item);
        } else {
            lista->itens[lista->tam] = item;
            lista->fim++;
            lista->tam++;
            return true;
        }
    }
    return false;
}

bool lista_inserir_ord(LISTA *lista, ITEM *item){
    if(lista->tam == 0){
        lista->itens[lista->tam] = item;
        lista->fim++;
        lista->tam++;
        return true;
    }

    int i;
    int chave = item_get_chave(item);
    for(i = 0; i < lista->tam; i++){
        int chave_idx = lista->itens[i];
        if(chave > chave_idx){
            break;
        }
    }

    for(int j = lista->tam; j > i; j--){ // move para direita
        lista->itens[j] = lista->itens[j - 1];
    }

    lista->itens[i] = item;
    lista->tam++;
    lista->fim++;
    return true;
}

ITEM *lista_buscar_idx(LISTA *lista, int chave){
    if(lista != NULL){
        for(int i = 0; i < lista->tam; i++){
            if(item_get_chave(lista->itens[i]) == chave){
                return i;
            }
        }
    }
    return NULL;
}

ITEM *lista_buscar(LISTA *lista, int chave){
    if(lista != NULL){
        int  inf = lista->inicio;
        int sup = lista->fim - 1;

        if(lista->ordenada){
            while(inf <= sup - 1){
                int meio = (inf + sup) / 2;

                if(item_get_chave(lista->itens[meio]) == chave){
                    return lista->itens[meio];
                } else if(item_get_chave(lista->itens[meio]) < chave){
                    sup = meio + 1;
                } else {
                    inf = meio - 1;
                }
            }
        } else {
            for(int i = 0; i < lista->tam; i++){
                if(item_get_chave(lista->itens[i]) == chave){
                    return lista->itens[i];
            }
        }
        }
    }
    return NULL;
}

ITEM *lista_remover(LISTA *lista, int chave){
    if(lista != NULL && !lista_vazia(lista)){
        int pos = lista_buscar_idx(lista, chave);

        ITEM *item = lista->itens[pos];

        for(int i = pos; i < lista->tam - 1; i++){
            lista->itens[i] = lista->itens[i + 1];
        }
        
        lista->tam--;
        lista->fim--;
        lista->itens[lista->tam] = NULL;
        return item;
    }
    return NULL;
}

int lista_tamanho(LISTA *lista){
    if(lista != NULL){
        return lista->tam;
    }
    return NULL;
}

void lista_imprimir(LISTA *lista){
    if(lista != NULL){
        for(int i = 0; i < lista->tam; i++){
            printf("%d ", lista->itens[i]);
        }
        printf("\n");
    }
}
void lista_apagar(LISTA **lista){
    if(lista!= NULL &&!lista_vazia(lista)){
        for(int i = 0; i < (*lista)->tam; i++){
            item_apagar((*lista)->itens[i]);
        }
        
        free(*lista);
        *lista = NULL;
    }
}

void lista_alterar_item(LISTA *lista, int chave, ITEM *newitem){
    if(lista != NULL){
        int chave = lista_buscar_idx(lista, chave);

        lista->itens[chave] = newitem;
    }
}
/*LISTA *lista_concatenar(LISTA *lista1, LISTA *lista2);{
    if(lista1 != NULL  && lista2 != NULL){
        if(lista->ordenada){
            LISTA *nova_lista = lista_criar(lista1->ordenada || lista2->ordenada);

        } else {

        }
    }
}*/
