#include <stdio.h>
#include "binarytree.h"
#include "codigo.h"
#include "meustipos.h"  // Inclua seu header de tipos

// Escreve um bit no arquivo com buffer
void juntar_bits(FILE *out, U8 *buffer, I32 *bit_pos, I32 bit) {
    *buffer = (*buffer << 1) | (bit & 1);
    (*bit_pos)++;

    printf("%d", bit);  // imprime o bit que está sendo escrito

    if (*bit_pos == 8) {
        printf(" -> byte escrito: 0x%02X\n", *buffer);  // imprime o byte completo
        fwrite(buffer, 1, 1, out);
        *buffer = 0;
        *bit_pos = 0;
    }
}

// Escreve um byte no arquivo alinhando o buffer
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

// Serializa a árvore em pré-ordem
void serializar_arvore(FILE *out, Ptr_de_no_de_arvore_binaria no, U8 *buffer, I32 *bit_pos) {
    if (!no) return;

    if (!no->esquerda && !no->direita) {
        // Nó folha: escreve bit 1 + byte armazenado em no->informacao.byte
        juntar_bits(out, buffer, bit_pos, 1);
        escrever_byte(out, buffer, bit_pos, no->informacao.byte);
    } else {
        // Nó interno: escreve bit 0 e serializa filhos
        juntar_bits(out, buffer, bit_pos, 0);
        serializar_arvore(out, no->esquerda, buffer, bit_pos);
        serializar_arvore(out, no->direita, buffer, bit_pos);
    }
}

boolean compactar_arquivo(const U8 *nome_entrada, const U8 *nome_saida, Ptr_de_no_de_arvore_binaria raiz, Codigo tabela_de_codigos[256]) {
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

    // Serializa a árvore no arquivo
    serializar_arvore(fout, raiz, &buffer, &bit_pos);

    // Completa o último byte da serialização se necessário
    if (bit_pos > 0) {
        buffer <<= (8 - bit_pos);
        fwrite(&buffer, 1, 1, fout);
        buffer = 0;
        bit_pos = 0;
    }

    // Escreve os dados compactados
    I32 c;
    while ((c = fgetc(fin)) != EOF) {
        for (I32 i = 0; i < tabela_de_codigos[(U8)c].tamanho; i++) {
            I32 bit = (tabela_de_codigos[(U8)c].byte[i / 8] >> (7 - (i % 8))) & 1;
            juntar_bits(fout, &buffer, &bit_pos, bit);
        }
    }

    // Completa o último byte dos dados compactados se necessário
    if (bit_pos > 0) {
        buffer <<= (8 - bit_pos);
        fwrite(&buffer, 1, 1, fout);
    }

    // Escreve o número de bits válidos no último byte dos dados compactados
    U8 bits_validos = (bit_pos == 0) ? 8 : bit_pos;
    fwrite(&bits_validos, 1, 1, fout);

    fclose(fin);
    fclose(fout);
    return true;
}