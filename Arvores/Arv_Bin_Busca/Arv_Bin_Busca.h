#ifndef _ARVORE_BINARIA_H
#define _ARVORE_BINARIA_H
 
    #include  "item.h"
    #define ERRO -32000
    #define FILHO_ESQ 0
    #define FILHO_DIR 1

    typedef struct arv_bin ABB;
 
    ABB *abb_criar (void);
    bool abb_inserir (ABB *T, ITEM *item); 
    void abb_imprimir (ABB *T); // x
    void abb_apagar (ABB **T); 
    bool abb_remover(ABB *T, int chave); 
    ITEM *abb_busca(ABB *T, int chave); 
    bool abb_vazia(ABB *T); 
    
    bool abb_perfeitamente_balanceada(ABB *T); /*Essa função devolve 0 se a Árvore é perfeitamente balanceada e 1 caso contrário*/
    
#endif