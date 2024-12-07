#include  "item.h"
#include "Arv_Bin_Busca.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERRO -32000
#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct no_ {
    ITEM *item;
    NO *esq;
    NO *dir;
} NO;

typedef struct arv_bin {
    NO *raiz;
    int profundidade;
} ABB;

ABB *abb_criar(void) {
    ABB *abb = (ABB*)malloc(sizeof(ABB));
    
    if (abb!= NULL) {
        abb->raiz = NULL;
        abb->profundidade = -1;
        return abb;
    }
    return NULL;
}

NO *cria_no(ITEM *item) {
    NO *newNode = (NO*)malloc(sizeof(NO));

    if(newNode != NULL){
        newNode->item = item;
        newNode->esq = NULL;
        newNode->dir = NULL;

        return newNode;
    }
    return NULL;
}

NO *inserir_no(NO *raiz, NO *newNode){
    if(raiz == NULL)
        raiz = newNode;
    else if(item_get_chave(newNode->item) > item_get_chave(raiz->item))
        raiz->dir = inserir_no(raiz->dir, newNode);
    else if(item_get_chave(newNode->item) < item_get_chave(raiz->item))
        raiz->esq = inserir_no(raiz->esq, newNode);

    return raiz;
}

bool abb_inserir(ABB *abb, ITEM *item){
    if(abb != NULL) {
        NO *newNode = cria_no(item);

        if(newNode != NULL){
            abb->raiz = inserir_no(abb->raiz, newNode);
            abb->profundidade++;
            return true;
        }
    }
    return false;
}

ITEM *busca_bin(NO *raiz, int chave){
    if(raiz == NULL) return NULL;

    if(chave == item_get_chave(raiz->item))
        return raiz->item;
    else if(chave < item_get_chave(raiz->item))
        return busca_bin(raiz->esq, chave);
    else if(chave > item_get_chave(raiz->item))
        return busca_bin(raiz->dir, chave);
    
    return NULL;
}

ITEM *abb_busca(ABB *abb, int chave){
    if(abb != NULL)
        return busca_bin(abb->raiz, chave);
    return NULL;
}

void troca_max_esq(NO *troca, NO *raiz, NO *anterior){ // Troca com o máximo elemento da sub-árvore esquerda
    if(troca->dir != NULL){ // busca o máximo elemento da sub-árv esquerda
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }

    if(raiz == anterior)
        anterior->esq = troca->esq;
    else 
        anterior->dir = troca->dir;

    raiz->item = troca->item;
    free(troca);
    troca = NULL;
}

/*
void troca_min_dir(NO *troca, NO *raiz, NO *anterior){
    if(troca->esq != NULL){
        troca_min_dir(troca->esq, raiz, troca);
        return;
    }

    if(raiz == anterior)
        anterior->dir = troca->dir;
    else
        anterior->esq = troca->esq;
    
    raiz->item = troca->item;
    free(troca);
    troca = NULL;
}
*/

bool abb_remover_aux(NO **raiz, int chave){
    NO *aux;

    if(*raiz == NULL) return false;

    if(chave == item_get_chave((*raiz)->item)){
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){// Caso 1 se resume ao caso 2 tambem: um nó filho ou nenhum
            aux = *raiz;

            if((*raiz)->esq == NULL)
                *raiz = (*raiz)->dir;
            else if((*raiz)->dir == NULL)
                *raiz = (*raiz)->esq;
            item_apagar(&aux->item);
            free(aux);
            aux == NULL;
        } else // Caso 3: há os dois filhos
            troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
            // troca_min_dir((*raiz)->dir, (*raiz), (*raiz));
        return true;
    } else if(chave < item_get_chave((*raiz)->item))
        return(abb_remover_aux(&(*raiz)->esq, chave));
    else if(chave > item_get_chave((*raiz)->item))
        return(abb_remover_aux(&(*raiz)->dir, chave));
}

bool abb_remover(ABB *abb, int chave){
    if(abb != NULL) 
        return (abb_remover_aux(&abb->raiz, chave));
    return false;
}