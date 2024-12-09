#ifndef _RBT_H
    #define _RBT_H

    #include <stdbool.h>

    #include "item.h"

    typedef struct llrbt LLRBT;
    
    LLRBT *llrbt_criar(void);
    bool llrbt_inserir (LLRBT *llrbt, ITEM *item);
    bool llrbt_remover(LLRBT *llrbt, int chave);
    void llrbt_imprimir (LLRBT *llrbt);
    bool llrbt_buscar(LLRBT* T, int chave);
    void llrbt_apagar(LLRBT **llrbt);
 
#endif