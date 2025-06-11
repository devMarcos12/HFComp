# Makefile simples
CC = gcc
TARGET = huffman

all: $(TARGET)

$(TARGET): main.c frequency.c tabela_de_frequencias.c filaprioridade.c binarytree.c codigo.c compactar.c descompactar.c
	$(CC) -o $(TARGET) main.c frequency.c tabela_de_frequencias.c filaprioridade.c binarytree.c codigo.c compactar.c descompactar.c

clean:
	rm -f $(TARGET) *.exe

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
