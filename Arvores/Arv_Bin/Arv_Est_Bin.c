#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include  "item.h"

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
    // ...
} AB;

AB *ab_criar(void){
    AB *newAb = (AB *) malloc(sizeof(AB));

    if(newAb!= NULL){
        newAb->raiz = NULL;
        newAb->profundidade = -1;
    }
    
    return newAb;
}

NO *ab_cria_no(ITEM *item){
    NO *newNode = (NO *)malloc(sizeof(NO));

    if(newNode!= NULL){
        newNode->item = item;
        newNode->esq = NULL;
        newNode->dir = NULL;

        return newNode;
    }
    return NULL;
}

void ab_inserir_no(NO *raiz, NO *newNode, int lado, int chave_pai){
    if(raiz != NULL){
        ab_inserir_no(raiz->esq, newNode, lado, chave_pai);
        ab_inserir_no(raiz->dir, newNode, lado, chave_pai);

        if(chave_pai == item_get_chave(raiz->item)){
            if(lado == FILHO_ESQ)
                raiz->esq = newNode;
            else if(lado == FILHO_DIR)
                raiz->dir = newNode;
        }
    }

    return;
}

bool ab_inserir (AB *T, ITEM *item, int lado, int chave){
    if(T->raiz == NULL){
        return((T->raiz = ab_cria_no(item)) != NULL);
    } else {
        NO *newNode = ab_cria_no(item);
        
        if(newNode == NULL){
            ab_inserir_no(T->raiz, newNode, lado, chave);

            return true;
        }

        return false;
    }
    return false;
}

void ab_imprimir (AB *T){ // imprimir em preOrdem
    if(T->raiz != NULL){
        printf("%d ", item_get_dados(T->raiz->item));
        ab_imprimir(T->raiz->esq);
        ab_imprimir(T->raiz->dir);
    }
}

void apagar_arv(NO **raiz){
    if(*raiz != NULL){
        apagar_arv(&(*raiz)->esq);
        apagar_arv(&(*raiz)->dir);

        item_apagar(&(*raiz)->item);
        free(*raiz);
        *raiz = NULL;
    }
}

void ab_apagar_arvore(AB **T){
    apagar_arv(&(*T)->raiz);
    free(*T);
    *T = NULL;
}

int ab_est_bin_aux(AB *T, NO *raiz){
    if(raiz->esq == NULL && raiz->dir == NULL){
        return 1;
    }

    if(raiz->dir != NULL && raiz->dir != NULL){
        return (
            ab_est_bin_aux(T, raiz->esq) &&
            ab_est_bin_aux(T, raiz->dir)
        );
    } else {
        return 0;
    }
}

int ab_estritamente_binaria (AB *T){ /*Essa função devolve 0 se a Árvore é estritamente binária e 1 caso contrário*/
    if(T->raiz != NULL){
        return ab_est_bin_aux(T, T->raiz);
    }

    return 0;
}