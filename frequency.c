#include "meustipos.h"
#include "frequency.h"
#include <stdio.h>

void contar_frequencias(const U8 *nome_arquivo, U32 frequencias[256]) {
    for (I32 i = 0; i < 256; i++) {
        frequencias[i] = 0;
    }

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    I32 c;
    while ((c = fgetc(arquivo)) != EOF){
        frequencias[c]++;
    } 

    fclose(arquivo);

}

void imprimir_frequencias(const U32 frequencias[256]) {
    for (U16 i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            printf("Caractere: %c, Frequencia: %u\n", i, frequencias[i]);
        }
    }
}
