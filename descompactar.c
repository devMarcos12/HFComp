#include <stdio.h>
#include <stdlib.h>
#include "filaprioridade.h"
#include "binarytree.h"
#include "meustipos.h"

FilaPrioridade* ler_fila_prioridade(FILE *fin) {
    U16 count;
    if (fread(&count, sizeof(U16), 1, fin) != 1) return NULL;
    printf("Count lido: %u\n", count);

    FilaPrioridade *fila = NULL;
    for (U16 i = 0; i < count; i++) {
        U8 byte;
        U32 freq;
        if (fread(&byte, sizeof(U8), 1, fin) != 1) return NULL;
        if (fread(&freq, sizeof(U32), 1, fin) != 1) return NULL;
        printf("Byte: %u, Freq: %u\n", byte, freq);

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
    FILE *fin = fopen(nome_entrada, "rb");
    if (!fin) {
        perror("Erro ao abrir arquivo compactado");
        return false;
    }

    FILE *fout = fopen(nome_saida, "wb");
    if (!fout) {
        perror("Erro ao abrir arquivo de saída");
        fclose(fin);
        return false;
    }

    FilaPrioridade *fila = ler_fila_prioridade(fin);
    if (!fila) {
        printf("Erro ao ler fila de prioridade.\n");
        fclose(fin);
        fclose(fout);
        return false;
    }

    Ptr_de_no_de_arvore_binaria raiz = contruir_arvore(&fila);
    if (!raiz) {
        printf("Erro ao reconstruir arvore de Huffman.\n");
        fclose(fin);
        fclose(fout);
        return false;
    }

    long pos_dados = ftell(fin);
    fseek(fin, 0, SEEK_END);
    long tamanho_arquivo = ftell(fin);
    long tamanho_dados = tamanho_arquivo - pos_dados - 1;
    fseek(fin, pos_dados, SEEK_SET);

    U8 *dados = malloc(tamanho_dados);
    if (!dados) {
        printf("Erro de memoria.\n");
        fclose(fin);
        fclose(fout);
        return false;
    }
    fread(dados, 1, tamanho_dados, fin);

    U8 bits_validos;
    fread(&bits_validos, 1, 1, fin);

    Ptr_de_no_de_arvore_binaria atual = raiz;
    long total_bits = (tamanho_dados - 1) * 8 + bits_validos;
    long bits_lidos = 0;
    for (long i = 0; i < tamanho_dados; i++) {
        U8 byte = dados[i];
        I32 limite = (i == tamanho_dados - 1) ? bits_validos : 8;
        for (I32 b = 7; b >= 8 - limite; b--) {
            int bit = (byte >> b) & 1;
            if (bit == 0) atual = atual->esquerda;
            else atual = atual->direita;

            if (!atual->esquerda && !atual->direita) {
                fwrite(&atual->informacao.byte, 1, 1, fout);
                atual = raiz;
            }
            bits_lidos++;
        }
    }

    free(dados);
    fclose(fin);
    fclose(fout);
    liberar_arvore_binaria(raiz);
    return true;
}