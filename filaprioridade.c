#include "filaprioridade.h"
#include <stdio.h>
#include <stdlib.h>

void inserir_na_fila(FilaPrioridade **fila, U8 caractere, U32 peso) {
    FilaPrioridade *aux, *novo = malloc(sizeof(FilaPrioridade));

    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória");
        return;
    }

    novo->caractere = caractere;
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

void criar_fila_prioridade(const U32 frequencias[256], FilaPrioridade **fila) {
    *fila = NULL;

    for (U16 i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            inserir_na_fila(fila, (U8)i, frequencias[i]);
        }
    }
}

void imprimir_fila(FilaPrioridade *fila) {
    FilaPrioridade *aux = fila;
    while (aux) {
        printf("Caractere: %c, Peso: %u\n", aux->caractere, aux->peso);
        aux = aux->proximo;
    }
}
