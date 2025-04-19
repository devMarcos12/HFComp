#include "frequency.h"
#include "meustipos.h"

int main() {
    U32 frequencias[256];
    const U8 *nome = (const U8 *)"test.txt";

    contar_frequencias(nome, frequencias);
    imprimir_frequencias(frequencias);
    return 0;
}
