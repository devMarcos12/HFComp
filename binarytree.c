#include "filaprioridade.h"
#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>

struct arvore* combinar_nos(FilaPrioridade **fila) {
    if (*fila == NULL || (*fila)->proximo == NULL) {
        return NULL; 
    }

    
    FilaPrioridade *esquerdo = *fila;
    *fila = (*fila)->proximo; // atualizando o inicio da fila para não perder a referencia

    FilaPrioridade *direito = *fila;
    *fila = (*fila)->proximo; 

    
    struct arvore *novo = malloc(sizeof(struct arvore));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o novo nó da árvore\n");
        return NULL; 
    }

    
    novo->soma = esquerdo->peso + direito->peso;


    novo->filhoesquerda = malloc(sizeof(struct arvore));
    novo->filhodireita = malloc(sizeof(struct arvore));

    if (novo->filhoesquerda == NULL || novo->filhodireita == NULL) {
        printf("Erro ao alocar memória para os filhos da árvore\n");
        free(novo); 
        return NULL; 
    }

    novo->filhoesquerda->soma = esquerdo->peso;
    novo->filhodireita->soma = direito->peso;

    novo->filhoesquerda->filhoesquerda = NULL;
    novo->filhoesquerda->filhodireita = NULL;

    novo->filhodireita->filhoesquerda = NULL;
    novo->filhodireita->filhodireita = NULL;

    
    free(esquerdo);
    free(direito);

    return novo; 
}
