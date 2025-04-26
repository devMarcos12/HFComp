#include "frequency.h"
#include "filaprioridade.h"
#include "meustipos.h"
#include "tabela_de_frequencias.h"
#include <stdio.h>

int main() {
    Tabela_de_frequencias tab;
    if (contar_frequencias("montanha.jpeg", &tab)) {
        imprimir_frequencias(&tab);
    } else {
        printf("Erro ao contar frequências.\n");
    }

    FilaPrioridade *fila = criar_fila_prioridade(&tab);
    if (fila) {
        printf("Fila de prioridade criada com sucesso:\n");
        imprimir_fila(fila);
    } else {
        printf("Erro ao criar fila de prioridade.\n");
    }

    return 0;
}