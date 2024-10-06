#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct item_ {
    int chave;
    void *comp;
} ITEM;

ITEM *item_criar(int chave, void *comp) {
    ITEM *item = (ITEM *)malloc(sizeof(ITEM));
    if (item) {
        item->chave = chave;
        item->comp = comp;
    }
    return item;
}

bool item_apagar(ITEM **item) {
    if (item && *item) {
        free(*item);
        *item = NULL;
        return true;
    }
    return false;
}

int item_get_chave(ITEM *item) {
    if (item) {
        return item->chave;
    }
    return -1; 
}

bool item_set_chave(ITEM *item, int chave) {
    if (item) {
        item->chave = chave;
        return true;
    }
    return false;
}

void *item_get_dados(ITEM *item) {
    if (item) {
        return item->comp;
    }
    return NULL;
}