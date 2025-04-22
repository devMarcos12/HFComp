#ifndef FILAPRIORIDADE_H
#define FILAPRIORIDADE_H

#include "meustipos.h"

typedef struct arvore arvore;

typedef struct FilaPrioridade {
    U8 caractere;
    U32 peso;
    struct FilaPrioridade *proximo;
    arvore *no_arvore;
}FilaPrioridade;

void inserir_na_fila(FilaPrioridade **fila, U8 caractere, U32 peso);

void criar_fila_prioridade(const U32 frequencias[256], FilaPrioridade **fila);

void imprimir_fila(FilaPrioridade *fila);

#endif
