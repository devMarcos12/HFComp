#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "meustipos.h"

typedef struct FilaPrioridade FilaPrioridade;

typedef struct arvore {
    U8 caractere; 
    U32 peso;
    struct arvore *filhoesquerda;
    struct arvore *filhodireita;
} arvore;

arvore* criar_no_arvore(U8 caractere, U32 peso);
arvore* criar_no_interno(arvore *esquerdo, arvore *direito);

#endif
