#include "frequency.h"
#include "tabela_de_frequencias.h"
#include <stdio.h>

boolean contar_frequencias(const U8 *nome_arquivo, Tabela_de_frequencias *tab) {

    U8 byte;

    nova_tabela_de_frequencias(tab);

    FILE *arquivo = fopen(nome_arquivo, "rb+");
    if (arquivo != NULL) {
        while (fread(&byte, sizeof(U8), 1, arquivo) == 1) {
            if (inclua_byte(byte, tab) == false) {
                fclose(arquivo);
                return false;
            }
        }
        junte_nodos_no_inicio_do_vetor(tab);
    } else {
        return false;
    } 

    fclose(arquivo);
    return true;
}

void imprimir_frequencias(const Tabela_de_frequencias *tab) {
    for (U16 i = 0; i < 256; i++) {
        if (tab->vetor[i] != NULL) {
            // printf("Byte: %u, Frequencia: %llu\n", tab->vetor[i]->informacao.byte, tab->vetor[i]->informacao.frequencia);
        }
    }
}
