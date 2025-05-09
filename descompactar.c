#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filaprioridade.h"
#include "binarytree.h"
#include "meustipos.h"

FilaPrioridade* ler_fila_prioridade(FILE *file_in) {
    U16 count;
    if (fread(&count, sizeof(U16), 1, file_in) != 1) return NULL;

    // Count how many symbols are in the file (debugging purposes)
    // printf("Count lido: %u\n", count);

    FilaPrioridade *fila = NULL;
    for (U16 i = 0; i < count; i++) {
        U8 byte;
        U32 freq;
        if (fread(&byte, sizeof(U8), 1, file_in) != 1) return NULL;
        if (fread(&freq, sizeof(U32), 1, file_in) != 1) return NULL;

        // Debugging line:
        // printf("Byte: %u, Freq: %u\n", byte, freq);

        Elemento elem;
        elem.byte = byte;
        elem.frequencia = freq;
        Ptr_de_no_de_arvore_binaria novo_no;
        if (!novo_no_de_arvore_binaria(&novo_no, NULL, elem, NULL)) return NULL;
        inserir_na_fila(&fila, novo_no);
    }
    return fila;
}

boolean descompactar_arquivo(const U8 *nome_entrada, const U8 *nome_saida) {
    FILE *file_in = fopen(nome_entrada, "rb");
    if (!file_in) {
        return false;
    }

    FILE *file_out = fopen(nome_saida, "wb");
    if (!file_out) {
        fclose(file_in);
        return false;
    }

    FilaPrioridade *fila = ler_fila_prioridade(file_in);
    if (!fila) {
        fclose(file_in);
        fclose(file_out);
        return false;
    }

    Ptr_de_no_de_arvore_binaria raiz = contruir_arvore(&fila);
    if (!raiz) {
        fclose(file_in);
        fclose(file_out);
        return false;
    }

    I64 pos_dados = ftell(file_in);
    fseek(file_in, 0, SEEK_END);
    I64 tamanho_arquivo = ftell(file_in);
    I64 tamanho_dados = tamanho_arquivo - pos_dados - 1;
    fseek(file_in, pos_dados, SEEK_SET);

    U8 *dados = malloc(tamanho_dados);
    if (!dados) {
        printf("Erro de memoria.\n");
        fclose(file_in);
        fclose(file_out);
        return false;
    }
    fread(dados, 1, tamanho_dados, file_in);

    U8 bits_validos;
    fread(&bits_validos, 1, 1, file_in);

    Ptr_de_no_de_arvore_binaria atual = raiz;
    I64 total_bits = (tamanho_dados - 1) * 8 + bits_validos;
    I64 bits_lidos = 0;
    for (I64 i = 0; i < tamanho_dados; i++) {
        U8 byte = dados[i];
        U32 limite = (i == tamanho_dados - 1) ? bits_validos : 8;
        for (U32 b = 7; b >= 8 - limite; b--) {
            U32 bit = (byte >> b) & 1;
            if (bit == 0) atual = atual->esquerda;
            else atual = atual->direita;

            if (!atual->esquerda && !atual->direita) {
                fwrite(&atual->informacao.byte, 1, 1, file_out);
                atual = raiz;
            }
            bits_lidos++;
        }
    }

    free(dados);
    fclose(file_in);
    fclose(file_out);
    liberar_arvore_binaria(raiz);
    return true;
}