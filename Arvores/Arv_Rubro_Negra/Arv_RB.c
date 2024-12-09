#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"
#include "Arv_RB.h"

#define RED 1
#define BLACK 0

typedef struct no {
    ITEM *item;
    NO *esq;
    NO *dir;
    int cor;
} NO;

typedef struct llrbt{
    NO *raiz;
    int profundidade;
    // ... */
}LLRBT;
    
LLRBT *llrbt_criar(void){
    LLRBT *llrbt = (LLRBT *)malloc(sizeof(LLRBT));

    if(llrbt != NULL){
        llrbt->raiz = NULL;
        llrbt->profundidade = -1;

        return llrbt;
    }
}

/* ------------------------------ Operações ------------------------------ */
void inverte(NO *no){
    no->cor = !no->cor;

    if(no->esq != NULL)
        no->esq->cor = !no->esq->cor;
    if(no->dir != NULL)
        no->dir->cor =!no->dir->cor;
}

NO *rot_dir(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    b->cor = a->cor;
    a->cor = RED;

    return b;
}

NO *rot_esq(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = RED;

    return b;
}

void vermelho(NO *no){
    if(no != NULL)
        return(no->cor == RED);
    return 0;
}

/* -------------------------------------------------------------------------- */

NO* cria_no(ITEM *item, int cor){
    NO* newNode = (NO*)malloc(sizeof(NO));

    if(newNode != NULL){
        newNode->item = item;
        newNode->cor = cor;
        newNode->esq = NULL;
        newNode->dir = NULL;
    }

    return newNode;
}

NO* inserir_aux(NO* raiz, NO* newNode){
    if(raiz == NULL){
        raiz = newNode;
    } else if(item_get_chave(raiz->item) > item_get_chave(newNode->item)){
        raiz->esq = inserir_aux(raiz->esq, newNode);
    } else if(item_get_chave(raiz->item) < item_get_chave(newNode->item)){
        raiz->dir=inserir_aux(raiz->dir, newNode);
    }

    if(vermelho(raiz->dir) && !vermelho(raiz->esq))
        raiz=rotacao_esq(raiz);
    
    if(vermelho(raiz->esq) && vermelho(raiz->esq->esq))
        raiz=rotacao_dir(raiz);
    
    if(vermelho(raiz->esq) && vermelho(raiz->dir))
        inverte(raiz);

    return raiz;
}

bool llrbt_inserir(LLRBT* T, ITEM *item){
    if(T != NULL){
        NO* newNode=cria_no(item, RED);

        if(newNode != NULL){
            T->raiz = inserir_aux(T->raiz, newNode);
            T->raiz->cor = BLACK;
            return true;
        }
    }

return false;
}

bool llrbt_remover(LLRBT *llrbt, int chave);
void llrbt_imprimir (LLRBT *llrbt);
void llrbt_apagar(LLRBT **llrbt);