#ifndef COMPACTAR_H
#define COMPACTAR_H

#include <stdio.h>
#include "codigo.h"  // Definição do struct Codigo
#include "binarytree.h"  // Definição do struct Ptr_de_no_de_arvore_binaria
#include "meustipos.h"  // Definição de tipos como U8, U16, etc.

U32 compactar_arquivo(const U8 *nome_entrada, const U8 *nome_saida, Ptr_de_no_de_arvore_binaria raiz, Codigo tabela_de_codigos[256]);

#endif // COMPACTAR_H