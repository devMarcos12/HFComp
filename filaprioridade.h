#ifndef FILAPRIORIDADE_H
#define FILAPRIORIDADE_H

#include "meustipos.h"
#include "tabela_de_frequencias.h"

typedef struct arvore arvore;

typedef struct FilaPrioridade {
    Ptr_de_no_de_arvore_binaria no_arvore;
    U32 peso;
    struct FilaPrioridade *proximo;
}FilaPrioridade;

void inserir_na_fila(FilaPrioridade **fila, Ptr_de_no_de_arvore_binaria no);

FilaPrioridade* criar_fila_prioridade(const Tabela_de_frequencias *tab);

void imprimir_fila(FilaPrioridade *fila);

Ptr_de_no_de_arvore_binaria contruir_arvore(FilaPrioridade **fila); 

#endif
