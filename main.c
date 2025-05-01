#include "frequency.h"
#include "filaprioridade.h"
#include "meustipos.h"
#include "tabela_de_frequencias.h"
#include "binarytree.h"
#include "compactar.h"
#include "codigo.h"
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

    Codigo tabela_de_codigos[256];

    for (int i = 0; i < 256; i++) {
        novo_codigo(&tabela_de_codigos[i]);
    }

    // Cria um código vazio para começar a gerar os códigos
    Codigo codigo_atual;
    novo_codigo(&codigo_atual);

    // Gera os código a partir da árvore
    gerar_codigos(raiz, &codigo_atual, tabela_de_codigos);

    // Imprime os códigos gerados
    printf("\nCodigos de Huffman gerados:\n");
    for (int i = 0; i < 256; i++) {
        if (tabela_de_codigos[i].tamanho > 0) {
            printf("Byte: ");
            if (i >= 32 && i <= 126) {
                printf("'%c'", i);
            } else {
                printf("0x%02X", i);
            }
            printf(" Codigo: ");
            for (int j = 0; j < tabela_de_codigos[i].tamanho; j++) {
                int bit = (tabela_de_codigos[i].byte[j / 8] >> (7 - (j % 8))) & 1;
                printf("%d", bit);
            }
            printf("\n");
        }
    }

    if (compactar_arquivo("test.txt", "test.bin", raiz, tabela_de_codigos)) {
        printf("Arquivo compactado com sucesso.\n");
    } else {
        printf("Erro ao compactar o arquivo.\n");
    }


    // Libera a memória alocada para os códigos
    for (int i = 0; i < 256; i++) {
        free_codigo(&tabela_de_codigos[i]);
    }
    free_codigo(&codigo_atual);

    liberar_arvore_binaria(raiz);

    return 0;
}