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

