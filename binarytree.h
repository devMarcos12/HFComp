#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "meustipos.h"

typedef struct  arvore{
    U32 soma;
    struct arvore *filhoesquerda;
    struct arvore *filhodireita;
}arvore;


#endif