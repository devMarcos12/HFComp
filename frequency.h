#ifndef FREQUENCY_H
#define FREQUENCY_H

#include "meustipos.h"

// Função que conta a frequência de cada caracter em um arquivo
void contar_frequencias(const U8 *nome_arquivo, U32 frequencias[256]);

// Imprime as frequências de cada caracter que aparecer no arquivo
void imprimir_frequencias(const U32 frequencias[256]);


#endif