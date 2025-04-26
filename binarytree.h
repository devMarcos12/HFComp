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
arvore* combinar_nos(FilaPrioridade **fila);
arvore* construir_arvore_huffman(FilaPrioridade **fila);
void imprimir_arvore(arvore *raiz, U32 nivel);
void liberar_memoria(arvore *raiz);


#endif
