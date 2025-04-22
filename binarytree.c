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

    no->caractere = "\0";
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
    *fila = (*fila)->proximo; // atualizando o inicio da fila para não perder a referencia

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

    arvore *no_interno = criar_no_interno(esquerdo->no_arvore, direito->no_arvore);

    FilaPrioridade *novo_no_fila = malloc(sizeof(FilaPrioridade));
    if (!novo_no_fila) {
        fprintf(stderr, "Erro ao alocar memória para novo nó da fila\n");
        return NULL;
    }  

    novo_no_fila->caractere = "\0";
    novo_no_fila->peso = no_interno->peso;
    novo_no_fila->proximo = NULL;
    novo_no_fila->no_arvore = no_interno;

    inserir_na_fila(fila, no_interno->caractere, no_interno->peso); 

    free(esquerdo);
    free(direito);
    free(novo_no_fila);

    return no_interno;
}

/*
arvore* construir_arvore_huffman(FilaPrioridade **fila) {
    while (*fila && (*fila)->proximo) {
        arvore *nova_arvore = combinar_nos(fila);

        FilaPrioridade *novo_no = malloc(sizeof(FilaPrioridade));
        if (!novo_no) {
            fprintf(stderr, "Erro ao alocar memória para novo nó\n");
            return NULL;
        }

        novo_no->caractere = 0;
        novo_no->peso = nova_arvore->peso;
        novo_no->proximo = NULL;

        // reutilizando a fila de prioridade pra organizar por peso
        inserir_na_fila(fila, novo_no->caractere, novo_no->peso);
    }

    return NULL;
}

*/
