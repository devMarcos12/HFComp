#ifndef FREQUENCY_H
#define FREQUENCY_H

#include "tabela_de_frequencias.h"
#include "meustipos.h"

// Função que conta a frequência de cada caracter em um arquivo
boolean contar_frequencias(const U8 *nome_arquivo, Tabela_de_frequencias *tab);

// Imprime as frequências de cada caracter que aparecer no arquivo
void imprimir_frequencias(const Tabela_de_frequencias *tab);


#endif
