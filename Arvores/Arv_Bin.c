#include "item.h"
#include <stdio.h>

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
	}
	return(ab);
}

void ab_inserir(AB *ab, ITEM *item){
    
}

void ab_preOrdem(NO *raiz){
    if(raiz == NULL){
        return;
    }
    printf("%d ", item_get_chave(raiz->item));
    ab_preOrdem(raiz->esq);
    ab_preOrdem(raiz->dir);
}
