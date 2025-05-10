#include <stdio.h>
#include "binarytree.h"
#include "codigo.h"
#include "meustipos.h"
#include "filaprioridade.h"

void juntar_bits(FILE *out, U8 *buffer, I32 *bit_pos, I32 bit) {
    *buffer = (*buffer << 1) | (bit & 1);
    (*bit_pos)++;

    //printf("%d", bit);

    if (*bit_pos == 8) {
        // Print the bits inside the buffer(byte) (for debugging)
        //printf(" -> byte escrito: 0x%02X\n", *buffer);
        fwrite(buffer, 1, 1, out);
        *buffer = 0;
        *bit_pos = 0;
    }
}

void escrever_byte(FILE *out, U8 *buffer, I32 *bit_pos, U8 byte) {
    if (*bit_pos != 0) {
        *buffer <<= (8 - *bit_pos);
        fwrite(buffer, 1, 1, out);
        *buffer = 0;
        *bit_pos = 0;
    }
    printf("Byte escrito diretamente: 0x%02X\n", byte);
    fwrite(&byte, 1, 1, out);
}

// Write the priority queue to the file for descompression
void salvar_fila_prioridade(FILE *fout, FilaPrioridade *fila) {
    U16 count = 0;
    FilaPrioridade *aux = fila;
    while (aux) {
        count++;
        aux = aux->proximo;
    }
    // For debugging purposes use:
    // printf("Quantidade de simbolos na fila: %u\n", count);

    fwrite(&count, sizeof(U16), 1, fout);

    aux = fila;
    U32 idx = 0;
    while (aux) {
        U8 byte = aux->no_arvore->informacao.byte;
        U32 freq = aux->no_arvore->informacao.frequencia;
        
        // Debugging line:
        // printf("Simbolo %d: byte=%u (char=%c), frequencia=%u\n", idx, byte, (byte >= 32 && byte <= 126) ? byte : '.', freq);

        fwrite(&byte, sizeof(U8), 1, fout);
        fwrite(&freq, sizeof(U32), 1, fout);
        aux = aux->proximo;
        idx++;
    }
}

boolean compactar_arquivo(const U8 *nome_entrada, const U8 *nome_saida, Ptr_de_no_de_arvore_binaria raiz, Codigo tabela_de_codigos[256], FilaPrioridade *fila_prioridade) {
    FILE *fin = fopen(nome_entrada, "rb");
    if (!fin) {
        perror("Erro ao abrir arquivo de entrada");
        return false;
    }

    FILE *fout = fopen(nome_saida, "wb");
    if (!fout) {
        perror("Erro ao abrir arquivo de saída");
        fclose(fin);
        return false;
    }

    U8 buffer = 0;
    I32 bit_pos = 0;

    salvar_fila_prioridade(fout, fila_prioridade);

    I32 c;
    while ((c = fgetc(fin)) != EOF) {
        for (I32 i = 0; i < tabela_de_codigos[(U8)c].tamanho; i++) {
            I32 bit = (tabela_de_codigos[(U8)c].byte[i / 8] >> (7 - (i % 8))) & 1;
            juntar_bits(fout, &buffer, &bit_pos, bit);
        }
    }

    if (bit_pos > 0) {
        buffer <<= (8 - bit_pos);
        fwrite(&buffer, 1, 1, fout);
    }

    U8 bits_validos = (bit_pos == 0) ? 8 : bit_pos;
    fwrite(&bits_validos, 1, 1, fout);

    fclose(fin);
    fclose(fout);
    return true;
}