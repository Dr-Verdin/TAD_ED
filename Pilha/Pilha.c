#include "item.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define  ERRO -32000
#define  MAX_PILHA 1000

typedef struct pilha_ {
    ITEM *itens[MAX_PILHA];
    int tam;
}PILHA;

PILHA *pilha_criar(){
    PILHA *pilha = (PILHA *)malloc(sizeof(PILHA));

    if(pilha != NULL){
        pilha->tam = 0;
        return(pilha);
    }
    return NULL;
}

bool pilha_cheia(PILHA *pilha){
    if(pilha != NULL){
        return pilha->tam == MAX_PILHA;
    }
    return false;
}

bool pilha_vazia(PILHA *pilha){
    if(pilha != NULL){
        return pilha->tam == 0;
    }
    return false;
}

bool pilha_push(PILHA *pilha, ITEM *item){
    if(pilha != NULL && !pilha_cheia(pilha)){
        pilha->itens[pilha->tam] = item;
        pilha->tam++;
        return true;
    }
    return false;
}

ITEM *pilha_pop(PILHA *pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        ITEM *item = pilha->itens[pilha->tam]; // ou pilha_topo(pilha);
        pilha->tam--;
        return item;
    }
}

void pilha_apagar(PILHA **pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        free(*pilha);
        *pilha = NULL;
    }
}

ITEM *pilha_topo(PILHA *pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        ITEM *item = pilha->itens[pilha->tam];
        return item;
    }
    return NULL;
}

int pilha_tamanho(PILHA *pilha){
    if(pilha != NULL){
        return pilha->tam;
    }
    return NULL;
}

void pilha_imprimir(PILHA *pilha){
    if(pilha != NULL){
        if(pilha_vazia(pilha)){
            printf("Pilha vazia.\n");
            return;
        }

        for(int i = 0; i < pilha->tam; i++){
            printf("%d ", item_get_chave(pilha->itens[i]));
        }
        printf("\n");
    }
}
void pilha_inverter(PILHA *pilha){
    if(pilha != NULL){
        PILHA *aux = pilha_criar(aux);

        while(!pilha_vazia(pilha)){
            pilha_push(&aux, pilha_pop(pilha));
        }

        while(!pilha_vazia(aux)){
            pilha_push(pilha, pilha_pop(&aux));
        }

        pilha_apagar(&aux);
    }
}