#include "binarytree.h"
#include "meustipos.h"
#include <stdio.h>  
#include <stdlib.h>

boolean novo_no_de_arvore_binaria (Ptr_de_no_de_arvore_binaria* novo /* por referencia */,
                                            Ptr_de_no_de_arvore_binaria esq /* por valor */,
                                            Elemento informacao /* por valor */,
                                            Ptr_de_no_de_arvore_binaria dir /* por valor */) {
                                             
    *novo = malloc(sizeof(Struct_do_no_de_arvore_binaria));
    
    if (*novo == NULL) return false;

    (*novo)->esquerda=esq;
    (*novo)->informacao=informacao;
    (*novo)->direita=dir;

    return true;
}

void liberar_arvore_binaria (Ptr_de_no_de_arvore_binaria raiz) {
    if (raiz == NULL) return;

    liberar_arvore_binaria(raiz->esquerda);
    liberar_arvore_binaria(raiz->direita);

    free(raiz);
}

void imprimir_arvore_binaria (Ptr_de_no_de_arvore_binaria raiz, U16 nivel) {

    if (raiz == NULL) return;

    for(U16 i=0; i<nivel; i++){
        printf("\t");
    }

    if(raiz->esquerda == NULL && raiz->direita == NULL) {
        printf("Byte: %u, Frequencia: %llu\n", raiz->informacao.byte, raiz->informacao.frequencia);
    } else {
        printf("Byte: %u, Frequencia: %llu\n", raiz->informacao.byte, raiz->informacao.frequencia);
    }

    imprimir_arvore_binaria(raiz->esquerda, nivel + 1);
    imprimir_arvore_binaria(raiz->direita, nivel + 1);
}

//Tabela de códigos
void gerar_codigos(Ptr_de_no_de_arvore_binaria no, Codigo* codigo_atual, Codigo* tabela_de_codigos) {
    if (no == NULL) return;

    if (no->esquerda == NULL && no->direita == NULL) {
        clone(*codigo_atual, &tabela_de_codigos[no->informacao.byte]);
        return;
    }

    adiciona_bit(codigo_atual, 0);
    gerar_codigos(no->esquerda, codigo_atual, tabela_de_codigos);
    joga_fora_bit(codigo_atual);

    adiciona_bit(codigo_atual, 1);
    gerar_codigos(no->direita, codigo_atual, tabela_de_codigos);
    joga_fora_bit(codigo_atual);
}
    