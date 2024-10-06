// Obs: Pilha.h serve pra esse ED
#include "item.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define  MAX_PILHA 1000

typedef struct node_ {
    ITEM *item;
    struct node_ *anterior;
}NODE;

typedef struct pilha_ {
    NODE *topo;
    int tam;
}PILHA;

PILHA *pilha_criar(){
    PILHA *pilha = (PILHA *)malloc(sizeof(PILHA));

    if(pilha!= NULL){
        pilha->topo = NULL;
        pilha->tam = 0;
        return(pilha);
    }
    return NULL;
}
bool pilha_cheia(PILHA *pilha){
    if(pilha!= NULL){
        return pilha->tam == MAX_PILHA;
    }
    return false;
}
bool pilha_vazia(PILHA *pilha){
    if(pilha!= NULL){
        return pilha->topo == NULL; // ou pilha->tam == 0;
    }
    return false;
}
bool pilha_push(PILHA *pilha, ITEM *item){
    if(pilha!= NULL &&!pilha_cheia(pilha)){
        NODE *new = (NODE *)malloc(sizeof(NODE));

        if(new!= NULL){
            new->item = item;
            new->anterior = pilha->topo;
            pilha->topo = new;
            pilha->tam++;
            return true;
        }
    }
    return false;
}
ITEM *pilha_pop(PILHA *pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        NODE *temp = pilha->topo;
        ITEM *item = temp->item;
        pilha->topo = pilha->topo->anterior;
        pilha->tam--;
        
        free(temp);
        return item;
    }
    return NULL;
}

void pilha_apagar(PILHA **pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        NODE *temp;

        while((*pilha)->topo != NULL){
            temp = (*pilha)->topo;
            (*pilha)->topo = (*pilha)->topo->anterior;
            item_apagar(&temp->item);
            temp->anterior = NULL;
            free(temp);
        }

        free(*pilha);
        *pilha = NULL;
    }
}

ITEM *pilha_topo(PILHA *pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        return pilha->topo->item;
    }
    return NULL;
}

int pilha_tamanho(PILHA *pilha){
    if(pilha!= NULL){
        return pilha->tam;
    }
    return NULL;
}

void pilha_imprimir(PILHA *pilha){
    if(pilha != NULL){
        if(pilha_vazia(pilha)){
            printf("Pilha vazia.\n");
        }

        NODE *atual = pilha->topo;

        while(atual != NULL){
            printf("%d -> ", item_get_chave(atual->item));
            atual = atual->anterior;
        }
        printf("\n");
    }
}

void pilha_inverter(PILHA *pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        NODE *temp = NULL;
        NODE *atual = pilha->topo;
        
        while(atual != NULL){
            NODE *aux = atual; // guarda o no atual
            atual = atual->anterior; // avança
            aux->anterior = temp; // inverte a direção
            temp = aux; // atualiza o temp_topo para o proximo no
        }

        pilha->topo = temp; // troca o topo da pilha
    }
}