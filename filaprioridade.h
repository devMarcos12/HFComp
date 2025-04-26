#ifndef FILAPRIORIDADE_H
#define FILAPRIORIDADE_H

#include "meustipos.h"
#include "tabela_de_frequencias.h"

typedef struct arvore arvore;

typedef struct FilaPrioridade {
    U8 byte;
    U32 peso;
    struct FilaPrioridade *proximo;
}FilaPrioridade;

void inserir_na_fila(FilaPrioridade **fila, U8 caractere, U32 peso);

FilaPrioridade* criar_fila_prioridade(const Tabela_de_frequencias *tab);

void imprimir_fila(FilaPrioridade *fila);


#endif
