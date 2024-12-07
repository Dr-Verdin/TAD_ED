#ifndef _ARVORE_AVL_H
    #define _ARVORE_AVL_H
    #define max(a, b) ((a > b) ? a : b)
 
    #include  "item.h"
    #define ERRO -32000
    #define FILHO_ESQ 0
    #define FILHO_DIR 1

    typedef struct avl AVL;
    
    AVL *avl_criar(void);
    bool avl_inserir (AVL *avl, ITEM *item, int lado, int chave);
    void avl_imprimir (AVL *avl);
    void avl_apagar_arvore(AVL **avl);
 
#endif