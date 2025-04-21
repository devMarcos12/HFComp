#include "frequency.h"
#include "meustipos.h"
#include "filaprioridade.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    U32 frequencias[256];
    const U8 *nome = (const U8 *)"test.txt";
    FilaPrioridade *fila = NULL;

    contar_frequencias(nome, frequencias);
    imprimir_frequencias(frequencias);

    criar_fila_prioridade(frequencias, &fila);
    imprimir_fila(fila);

    FilaPrioridade *atual = fila;
    FilaPrioridade *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    return 0;
}
