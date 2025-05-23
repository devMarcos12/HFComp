#include "frequency.h"
#include "filaprioridade.h"
#include "meustipos.h"
#include "tabela_de_frequencias.h"
#include "binarytree.h"
#include "compactar.h"
#include "descompactar.h"
#include "codigo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME 256


void limpar_buffer();
void compactar();
void descompactar();
void exibir_menu();


I32 main() {
    U8 opcao;

    do {
        exibir_menu();
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                compactar();
                break;
            case 2:
                descompactar();
                break;
            case 3:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Por favor, tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}


void limpar_buffer() {
    I32 c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void compactar() {
    U8 arquivo_entrada[MAX_FILENAME];
    U8 arquivo_saida[MAX_FILENAME];
    
    printf("\n=== Compactacao de Arquivo ===\n");
    printf("Digite o nome do arquivo a ser compactado: ");
    scanf("%s", arquivo_entrada);
    printf("Digite o nome do arquivo de saida (compactado): ");
    scanf("%s", arquivo_saida);

    Tabela_de_frequencias tab;
    if (!contar_frequencias(arquivo_entrada, &tab)) {
        printf("Erro ao contar frequencias do arquivo.\n");
        return;
    }

    FilaPrioridade *fila_arvore = criar_fila_prioridade(&tab);
    FilaPrioridade *fila_para_salvar = criar_fila_prioridade(&tab);

    if (!fila_arvore || !fila_para_salvar) {
        printf("Erro ao criar fila de prioridade.\n");
        return;
    }

    Ptr_de_no_de_arvore_binaria raiz = contruir_arvore(&fila_arvore);
    if (!raiz) {
        printf("Erro ao construir arvore de Huffman.\n");
        return;
    }

    Codigo tabela_de_codigos[256];
    for (U32 i = 0; i < 256; i++) {
        novo_codigo(&tabela_de_codigos[i]);
    }

    Codigo codigo_atual;
    novo_codigo(&codigo_atual);
    gerar_codigos(raiz, &codigo_atual, tabela_de_codigos);

    printf("\nArquivo sendo compactado...\n");

    if (compactar_arquivo(arquivo_entrada, arquivo_saida, raiz, tabela_de_codigos, fila_para_salvar)) {
        printf("\nArquivo compactado com sucesso!\n");
    } else {
        printf("Erro ao compactar o arquivo.\n");
    }

    // Liberação de memória
    for (U32 i = 0; i < 256; i++) {
        free_codigo(&tabela_de_codigos[i]);
    }
    free_codigo(&codigo_atual);
    liberar_arvore_binaria(raiz);
    free(fila_arvore);
    free(fila_para_salvar);
}


void descompactar() {
    U8 arquivo_entrada[MAX_FILENAME];
    U8 arquivo_saida[MAX_FILENAME];

    printf("\n=== Descompactacao de Arquivo ===\n");
    printf("Digite o nome do arquivo compactado: ");
    scanf("%s", arquivo_entrada);
    printf("Digite o nome do arquivo de saida (descompactado): ");
    scanf("%s", arquivo_saida);

    printf("\nArquivo sendo descompactado...\n");

    if (descompactar_arquivo(arquivo_entrada, arquivo_saida)) {
        printf("\nArquivo descompactado com sucesso!\n");
    } else {
        printf("Erro ao descompactar o arquivo.\n");
    }
}


void exibir_menu() {
    printf("\n === Menu ===\n");
    printf("Escolha uma opcao:\n");
    printf("1. Compactar arquivo\n");
    printf("2. Descompactar arquivo\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
}
