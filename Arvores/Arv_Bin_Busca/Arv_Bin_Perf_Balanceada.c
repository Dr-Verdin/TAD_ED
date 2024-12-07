// Refazer depois

#include  "item.h"
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

typedef struct arv_bin{
    NO *raiz;
    int profundidade;
} ABB;
 
ABB *abb_criar (void){
    ABB *abb = (ABB*)malloc(sizeof(ABB));
	
	if(abb != NULL){
		abb->raiz = NULL;
		abb->profundidade = -1;
	}
	return(abb);
}

NO *abb_cria_no (ITEM *item){
    NO *newNode = (NO *)malloc(sizeof(NO));

    if(newNode!= NULL){
        newNode->item = item;
        newNode->esq = NULL;
        newNode->dir = NULL;

        return newNode;
    }
    return NULL;  
}

NO *abb_inserir_no (NO *raiz, NO *newNode){
    if(raiz == NULL)
        raiz = newNode;
    else if(item_get_chave(newNode->item) < item_get_chave(raiz->item))
        raiz->esq = abb_inserir_no(raiz->esq, newNode);
    else if(item_get_chave(newNode->item) > item_get_chave(raiz->item))
        raiz->dir = abb_inserir_no(raiz->dir, newNode);
}

bool abb_inserir (ABB *T, ITEM *item){
    NO *newNode;

    if(T != NULL){
        newNode = abb_cria_no(item);
        
        if(newNode != NULL){
            T-> raiz = abb_inserir_no(T->raiz, newNode);
            T->profundidade++;

            return true;
        }
    }

    return false;
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

void abb_apagar (ABB **T){
    apagar_arvore(&(*T)->raiz);
    free(*T);
    *T = NULL;
}

void troca_max_esq(NO *esq, NO *raiz, NO *pai_raiz) {
    NO *p = esq;
    NO *pai_max = NULL;

    while (p->dir != NULL) {
        pai_max = p;
        p = p->dir;
    }

    item_set_chave(raiz->item, item_get_chave(p->item));  // Troca as chaves
    
    if (pai_max != NULL) {
        pai_max->dir = p->esq;
    } else {
        raiz->esq = p->esq;
    }

    item_apagar(p->item);
    free(p);
}


bool abb_remover_aux(NO **raiz, int chave){
    NO *p;

    if(*raiz == NULL) return false;

    if(chave == item_get_chave((*raiz)->item)){
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            p = *raiz;
            if((*raiz)->esq == NULL)
                *raiz = (*raiz)->dir;
            else 
               *raiz = (*raiz)->esq;
            item_apagar(&p->item);
            free(p);
            p = NULL;
        } else 
            troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
        return true;
    } else {
        if(chave < item_get_chave((*raiz)->item))
            return (abb_remover_aux(&(*raiz)->esq, chave));
        else
            return (abb_remover_aux(&(*raiz)->dir, chave));
    } 
}

bool abb_remover(ABB *T, int chave){
    if(T != NULL)
        return(abb_remover_aux(&T->raiz, chave));
    return false;
}

ITEM *abb_busca_aux(NO *raiz, int chave){
    if(raiz != NULL){
        int chave_raiz = item_get_chave(raiz->item);

        if(chave_raiz > chave)
            return abb_busca_aux(raiz->esq, chave);
        else if(chave_raiz < chave)
            return abb_busca_aux(raiz->dir, chave);
        else if(chave_raiz == chave)
            return raiz->item;
    }

    return NULL;
}

ITEM *abb_busca(ABB *T, int chave){
    if(T != NULL)
        return(abb_busca_aux(T->raiz, chave));

    return NULL;
}

void abb_imprimir (ABB *T){ // imprimir em ordem crescente?
    if(T->raiz != NULL){
        printf("%d ", item_get_dados(T->raiz->item));
        ab_imprimir(T->raiz->esq);
        ab_imprimir(T->raiz->dir);
    }
}

bool abb_vazia(ABB *T){
    if (T != NULL){
        if(T->raiz != NULL && T->profundidade != -1)
            return false;
        else if (T->raiz == NULL && T->profundidade == -1)
            return true;
    }
}

int altura_balanceada(NO *raiz, bool *balanciado) {
    if (raiz == NULL) {
        return 1;
    }

    // Calcula a altura da subárvore esquerda
    int altura_esq = altura_balanceada(raiz->esq, balanciado);
    // Se a subárvore esquerda não for balanceada, propaga o "false"
    if (!*balanciado) return 0;

    // Calcula a altura da subárvore direita
    int altura_dir = altura_balanceada(raiz->dir, balanciado);
    // Se a subárvore direita não for balanceada, propaga o "false"
    if (!*balanciado) return 0;

    // Verifica a diferença de altura entre as subárvores esquerda e direita
    if (abs(altura_esq - altura_dir) > 1) {
        *balanciado = false;
    }

    // Retorna a altura da árvore
    return 1 + (altura_esq > altura_dir ? altura_esq : altura_dir);
}

bool abb_perfeitamente_balanceada(ABB *T){
    if(T != NULL){
        bool balanciado = true;
        altura_balanceada(T->raiz, &balanciado);
        return balanciado;
    }

    return false;
} 