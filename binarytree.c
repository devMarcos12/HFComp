#include "filaprioridade.h"
#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>

arvore* criar_no_arvore(U8 caractere, U32 peso) {
    arvore *novo = malloc(sizeof(arvore));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o nó da árvore\n");
        return NULL;
    }
    novo->caractere = caractere;
    novo->peso = peso;
    novo->filhoesquerda = NULL;
    novo->filhodireita = NULL;
    return novo;
}   

arvore* criar_no_interno(arvore *esquerdo, arvore *direito) {
    arvore *no = malloc(sizeof(arvore)); 
    
    if (no == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o nó interno\n");
        return NULL;
    }

    no->caractere = '\0';
    no->peso = esquerdo->peso + direito->peso; // soma os pesos dos dois nós
    no->filhoesquerda = esquerdo; 
    no->filhodireita = direito;

    return no;
}

arvore* combinar_nos(FilaPrioridade **fila) {
    if (*fila == NULL || (*fila)->proximo == NULL) {
        fprintf(stderr, "Não é possível combinar nós, fila vazia ou com apenas um nó\n");
        return NULL;
    }

    FilaPrioridade *esquerdo = *fila;
    *fila = (*fila)->proximo;

    FilaPrioridade *direito = *fila;
    *fila = (*fila)->proximo;

    arvore *no_esquerdo, *no_direito;

    if (esquerdo->no_arvore != NULL) {
        no_esquerdo = esquerdo->no_arvore;
    } else {
        no_esquerdo = criar_no_arvore(esquerdo->caractere, esquerdo->peso);
    }

    if (direito->no_arvore != NULL) {
        no_direito = direito->no_arvore;
    } else {
        no_direito = criar_no_arvore(direito->caractere, direito->peso);
    }

    arvore *no_interno = criar_no_interno(no_esquerdo, no_direito);

    inserir_na_fila(fila, no_interno->caractere, no_interno->peso);
    
    // Encontrar o nó recém-inserido na fila
    FilaPrioridade *atual = *fila;
    while (atual != NULL && atual->peso != no_interno->peso) {
        atual = atual->proximo;
    }
    
    if (atual != NULL) {
        atual->no_arvore = no_interno;
    }

    free(esquerdo);
    free(direito);

    return no_interno;
}
arvore* construir_arvore_huffman(FilaPrioridade **fila) {
    if (*fila == NULL) {
        fprintf(stderr, "Fila vazia, não é possível construir a árvore\n");
        return NULL;
    }

    // Pode ser tanto o ultimo elemento da fila quanto o único elemento da fila
    // Se torna a raiz da árvore
    if ((*fila)->proximo == NULL)  {
        arvore *no = criar_no_arvore((*fila)->caractere, (*fila)->peso);
        free(*fila);
        *fila = NULL; // Limpa a fila após a construção da árvore
        return no;
    }

    FilaPrioridade *atual = *fila;
    while (atual != NULL) {
        if (atual->no_arvore == NULL) {
            atual->no_arvore = criar_no_arvore(atual->caractere, atual->peso);
        }
        atual = atual->proximo;
    }

    while (*fila != NULL && (*fila)->proximo != NULL){
        combinar_nos(fila);
    }

    arvore *raiz = NULL;
    if (*fila != NULL){
        raiz = (*fila)->no_arvore; // A raiz da árvore é o nó que sobrou na fila
        free(*fila); // Libera a fila após a construção da árvore
        *fila = NULL;
    }
    return raiz;
}

void imprimir_arvore(arvore *raiz, U32 nivel) {
    if (raiz == NULL) {
        return;
    }
    
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    if (raiz->caractere != '\0') {
        printf("'%c' (%u)\n", raiz->caractere, raiz->peso);
    } else {
        printf("* (%u)\n", raiz->peso);
    }
        
    imprimir_arvore(raiz->filhoesquerda, nivel + 1);
    imprimir_arvore(raiz->filhodireita, nivel + 1);
}

void liberar_memoria(arvore *raiz) {
    if (raiz == NULL) {
        return;
    }
    
    liberar_memoria(raiz->filhoesquerda);
    liberar_memoria(raiz->filhodireita);
    
    free(raiz);
}
