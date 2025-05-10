#include "filaprioridade.h"
#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>

void inserir_na_fila(FilaPrioridade **fila, Ptr_de_no_de_arvore_binaria no) {  
    FilaPrioridade *aux, *novo = malloc(sizeof(FilaPrioridade));

    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória");
        return;
    }

    novo->no_arvore = no;
    novo->peso = no->informacao.frequencia;
    novo->proximo = NULL;

    if (*fila == NULL || novo->peso	< (*fila)->peso) {
        novo->proximo = *fila;  
        *fila = novo;
    } else {
        aux = *fila;
        while(aux->proximo && aux->proximo->peso <= novo->peso) {
            aux = aux->proximo;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
    }
}

FilaPrioridade* criar_fila_prioridade(const Tabela_de_frequencias *tab) {
    FilaPrioridade *fila = NULL;
    for (U16 i = 0; i < 256; i++) {
        if (tab->vetor[i] != NULL) {
            inserir_na_fila(&fila, tab->vetor[i]);
        }
    }
    return fila;
}

void imprimir_fila(FilaPrioridade *fila) {
    FilaPrioridade *aux = fila;
    while (aux) {
        // printf("Caractere: %c, Peso: %u\n", aux->no_arvore->informacao.byte, aux->peso);
        aux = aux->proximo;
    }
}

static Ptr_de_no_de_arvore_binaria remover_do_inicio(FilaPrioridade **fila) {
    
    if (*fila == NULL) return NULL;

    FilaPrioridade *primeiro = *fila;

    Ptr_de_no_de_arvore_binaria no = primeiro->no_arvore;

    *fila = primeiro->proximo;

    free(primeiro);

    return no;
}

Ptr_de_no_de_arvore_binaria contruir_arvore(FilaPrioridade **fila) {

    while (*fila && (*fila)->proximo) {
        Ptr_de_no_de_arvore_binaria esquerda = remover_do_inicio(fila);
        Ptr_de_no_de_arvore_binaria direita = remover_do_inicio(fila);

        
        Elemento novo_elem;
        novo_elem.byte = 0;
        novo_elem.frequencia = esquerda->informacao.frequencia + direita->informacao.frequencia;


        Ptr_de_no_de_arvore_binaria novo_no;
        if (!novo_no_de_arvore_binaria(&novo_no, esquerda, novo_elem, direita)) {
            fprintf(stderr, "Erro ao criar nó da árvore\n");
            return NULL;
        }

        inserir_na_fila(fila, novo_no);
    }

    if(*fila==NULL) return NULL;
    
    Ptr_de_no_de_arvore_binaria raiz = (*fila)->no_arvore;

    free(*fila);
    *fila = NULL;  

    return raiz;
}
