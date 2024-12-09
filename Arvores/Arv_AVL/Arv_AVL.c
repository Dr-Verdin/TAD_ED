#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Arv_AVL.h"
#include "item.h"

typedef struct no {
    ITEM *item;
    NO *esq;
    NO *dir;
    int FB;
} NO;

typedef struct avl {
    NO *raiz;
    int profundidade;
    // ...
} AVL;

AVL *avl_criar(void){
    AVL *avl = (AVL*)malloc(sizeof(AVL));

    if(avl!= NULL){
        avl->raiz = NULL;
        avl->profundidade = -1;
        return avl;
    }
    return NULL;
}

/* ------------------------------ Rotações ------------------------------ */

NO *rot_dir(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->FB = b->FB = 0;

    return b;
}

NO *rot_esq(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->FB = b->FB = 0;

    return b;
}

NO *rot_esqDir(NO *a){
    a->esq = rot_esq(a->esq);
    return rot_dir(a);
}

NO *rot_dirEsq(NO *a){
    a->dir = rot_dir(a->dir);
    return rot_esq(a);
}

/* ---------------------------------------------------------------------- */

int altura_no(NO *no){
    if (no == NULL)
        return 0;
    
    // Recursivamente calcula as alturas das sub-árvores esquerda e direita
    int altura_esq = altura_no(no->esq);
    int altura_dir = altura_no(no->dir);

    // A altura do nó é 1 + a maior altura das subárvores
    if(altura_esq > altura_dir)
        return altura_esq + 1;
    else 
        return altura_dir + 1;
}

NO *cria_no(ITEM *item){
    NO *newNode = (NO*)malloc(sizeof(NO));

    if(newNode!= NULL){
        newNode->item = item;
        newNode->esq = NULL;
        newNode->dir = NULL;
        newNode->FB = 0;

        return newNode;
    }
    return NULL;
}

NO *inserir_no(NO *raiz, ITEM *item){
    if(raiz == NULL)
        raiz = cria_no(item);
    else if(item_get_chave(item) < item_get_chave(raiz->item))
        raiz->esq = inserir_no(raiz->esq, item);
    else if(item_get_chave(item) > item_get_chave(raiz->item))
        raiz->dir = inserir_no(raiz->dir, item);

    // Atualizar o fator de balanceamento
    raiz->FB = ((altura_no(raiz->esq)) - (altura_no(raiz->dir)));

    if(raiz->FB == -2)
        if(raiz->dir->FB <= 0)
            raiz = rot_esq(raiz);
        else
            raiz = rot_dirEsq(raiz);
    else if(raiz->FB == 2)
        if(raiz->esq->FB >= 0)
            raiz = rot_dir(raiz);
        else
            raiz = rot_esqDir(raiz);

    return raiz;
}

bool avl_inserir(AVL *avl, ITEM *item){
    if(avl != NULL)
        return(avl->raiz = inserir_no(avl->raiz, item));
    return false;
}

void troca_max_esq(NO *troca, NO *raiz, NO *anterior){
    if(troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }

    if(raiz == anterior)
        anterior->esq = troca->esq;
    else
        anterior->dir =  troca->esq;
    
    raiz->item = troca->item;
    free(troca);
    troca = NULL;
}

NO *avl_remover_aux(NO **raiz, int chave){ // Igual ABB
    NO *aux;

    if(chave == item_get_chave((*raiz)->item)){
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            aux = *raiz;

            if((*raiz)->esq == NULL)
                (*raiz) = (*raiz)->dir;
            else 
                (*raiz) = (*raiz)->esq;

            item_apagar(aux);
            free(aux);
            aux = NULL;
        } else {
            troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
        }
    } else {
        if(chave < item_get_chave((*raiz)->item))
            (*raiz)->esq = avl_remover_aux(&(*raiz)->esq, chave);
        else
            (*raiz)->dir = avl_remover_aux(&(*raiz)->dir, chave);
    }

    if(*raiz != NULL){
        (*raiz)->FB = altura_no((*raiz)->esq) - altura_no((*raiz)->dir);
    
        if((*raiz)->FB == 2){
            if((*raiz)->esq->FB >= 0)
                *raiz = rot_dir(*raiz);
            else
                *raiz = rot_esqDir(*raiz);
        }

        if((*raiz)->FB == -2){
            if((*raiz)->dir->FB <= 0)
                *raiz = rot_esq(*raiz);
            else
                *raiz = rot_dirEsq(*raiz);
        }
    }

    return *raiz;
}

bool avl_remover(AVL *avl, int chave){
    if(avl != NULL)
        return(avl->raiz = avl_remover_aux(&avl->raiz, chave));
}

void avl_apagar_aux(NO **raiz){
    if(*raiz != NULL){
        avl_apagar_aux(&(*raiz)->esq);
        avl_apagar_aux(&(*raiz)->dir);

        item_apagar(&(*raiz)->item);
        free(*raiz);
        *raiz = NULL;
    }
}

void avl_apagar(AVL **avl){
    if(*avl != NULL){
        avl_apagar_aux(&(*avl)->raiz);
        free(*avl);
        *avl = NULL;
    }
}