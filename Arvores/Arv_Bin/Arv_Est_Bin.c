#include "item.h"
#include <stdio.h>
#include <stdlib.h>

#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct no_ {
    ITEM *item;
    NO *esq;
    NO *dir;
} NO;

typedef struct ab_ {
    NO *raiz;
    int profundidade;
    // ...
} AB;

AB *ab_criar(void){
	AB *ab = (AB*)malloc(sizeof(AB));
	
	if(ab != NULL){
		ab->raiz = NULL;
		ab->profundidade = -1;

        return(ab);
	}
	return NULL;
}


void ab_inserir_no(NO *raiz, NO *node, int lado, int chave_pai){
    if(raiz != NULL){
        ab_inserir_no(raiz->esq, node, lado, chave_pai);
        ab_inserir_no(raiz->dir, node, lado, chave_pai);
        
        if(chave_pai ==  item_get_chave(raiz->item)){
            if(lado == FILHO_ESQ)
                raiz->esq = node;
            else if (lado == FILHO_DIR)
                raiz->dir = node;
        }
    }

    return;
}

void ab_inserir(AB *ab, ITEM *item, int lado, int chave_pai){
    if(ab->raiz == NULL)
        return((ab->raiz = ab_cria_no(item)) != NULL);
    else {
        NO *newNode = ab_cria_no(item);
        
        if(newNode != NULL){
            ab_inserir_no(ab->raiz, newNode, lado, chave_pai);
            return(true);
        }

        return(false);
    }
}

void apagar_arvore(NO **raiz){
    if(*raiz != NULL){
        ab_apagar_arvore(&(*raiz)->esq);
        ab_apagar_arvore(&(*raiz)->dir);

        item_apagar(&(*raiz)->item);
        free(*raiz);
        *raiz = NULL;
    }
}

void ab_apagar(AB **T){
    apagar_arvore(&(*T)->raiz);
    free(*T);
    *T = NULL;
}

void ab_imprimir (AB *T){ // imprimir em preOrdem, tentar imprimir por níveis
    if(T->raiz != NULL){
        printf("%d ", item_get_dados(T->raiz->item));
        ab_imprimir(T->raiz->esq);
        ab_imprimir(T->raiz->dir);
    }
}

int ab_profundidade(AB *ab){
    if(ab != NULL)
        return ab->profundidade;
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