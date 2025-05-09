# Huffman File Compressor 

This project is a simple file compressor and decompressor based on the Huffman coding algorithm, implemented in C.
It allows you to compress any file, saving space by encoding the most frequent bytes with shorter bit sequences, and decompress it back to its original form.

##  Compilation 

To compile the project, use the following command in your terminal or command prompt:
```
gcc main.c frequency.c tabela_de_frequencias.c filaprioridade.c binarytree.c codigo.c compactar.c descompactar.c -o huffman
```
## Usage

After compiling, you can run the program with:

 Windows:  ``` ./huffman.exe ```
 Linux: ``` ./huffman ```

 ## Notes

 - The compressed file contains the priority queue at the beginning, so decompression does not require any extra information.
 - This project is for educational purposes and does not handle all edge cases or very large files.
