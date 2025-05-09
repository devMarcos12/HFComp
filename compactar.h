#ifndef COMPACTAR_H
#define COMPACTAR_H

#include <stdio.h>
#include "codigo.h"
#include "binarytree.h"
#include "meustipos.h"
#include "filaprioridade.h"

boolean compactar_arquivo(const U8 *nome_entrada, const U8 *nome_saida, Ptr_de_no_de_arvore_binaria raiz, Codigo tabela_de_codigos[256], FilaPrioridade *fila_prioridade);

#endif // COMPACTAR_H