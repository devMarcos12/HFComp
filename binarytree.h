#ifndef BINARY_TREE
#define BINARY_TREE
#include "meustipos.h"
#include "tabela_de_frequencias.h" 
#include "codigo.h"

boolean novo_no_de_arvore_binaria (Ptr_de_no_de_arvore_binaria* novo /* por referencia */,
                                           Ptr_de_no_de_arvore_binaria esq /* por valor */,
                                           Elemento inf /* por valor */,
                                           Ptr_de_no_de_arvore_binaria dir /* por valor */);

void liberar_arvore_binaria (Ptr_de_no_de_arvore_binaria raiz);

void imprimir_arvore_binaria (Ptr_de_no_de_arvore_binaria raiz, U16 nivel);

void gerar_codigos(Ptr_de_no_de_arvore_binaria no, Codigo* codigo_atual, Codigo* tabela_de_codigos);

#endif
