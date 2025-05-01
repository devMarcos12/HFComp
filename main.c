#include "frequency.h"
#include "filaprioridade.h"
#include "meustipos.h"
#include "tabela_de_frequencias.h"
#include "binarytree.h"
#include <stdio.h>

int main() {
    Tabela_de_frequencias tab;
    if (contar_frequencias("test.txt", &tab)) {
        imprimir_frequencias(&tab);
    } else {
        printf("Erro ao contar frequencias.\n");
    }

    FilaPrioridade *fila = criar_fila_prioridade(&tab);
    if (fila) {
        printf("Fila de prioridade criada com sucesso:\n");
        imprimir_fila(fila);
    } else {
        printf("Erro ao criar fila de prioridade.\n");
    }

    Ptr_de_no_de_arvore_binaria raiz = contruir_arvore(&fila);

    if(!raiz){
        printf("Erro ao contruir arvore de Huffman. \n");
        return 1;
    }

    printf("Arvore de Huffman criada com sucesso:\n");
    imprimir_arvore_binaria(raiz, 0);

    liberar_arvore_binaria(raiz);

    return 0;
}