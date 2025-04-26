#include "filaprioridade.h"
#include <stdio.h>
#include <stdlib.h>

void inserir_na_fila(FilaPrioridade **fila, U8 byte, U32 peso) {
    FilaPrioridade *aux, *novo = malloc(sizeof(FilaPrioridade));

    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória");
        return;
    }

    novo->byte = byte;
    novo->peso = peso;
    novo->proximo = NULL;

    if (*fila == NULL){
        *fila = novo;
    } else {
        if (peso < (*fila)->peso) {
            novo->proximo = *fila;
            *fila = novo;
            return;
        } else {
            aux = *fila;
            while(aux->proximo && aux->proximo->peso < peso) {
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    }
}

FilaPrioridade* criar_fila_prioridade(const Tabela_de_frequencias *tab) {
    FilaPrioridade *fila = NULL;
    for (U16 i = 0; i < 256; i++) {
        if (tab->vetor[i] != NULL) {
            inserir_na_fila(&fila, tab->vetor[i]->informacao.byte, tab->vetor[i]->informacao.frequencia);
        }
    }
    return fila;
}

void imprimir_fila(FilaPrioridade *fila) {
    FilaPrioridade *aux = fila;
    while (aux) {
        printf("Caractere: %u, Peso: %u\n", aux->byte, aux->peso);
        aux = aux->proximo;
    }
}
