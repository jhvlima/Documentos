#!/bin/bash

# gera os aqruivos .vet 
./vetorizador.sh

# compila o codigo que calcula o cosseno de 2 vetores
gcc -o cosseno_vetores cosseno_vetores.c -lm

# obtem a quantidade total de palavras
wc -l banco.txt > num_palavras.txt

# chama o programa que calcula o coseno dos vetores passados como argumento e precisa da quantidade de palavras
./cosseno_vetores num_palavras.txt vet/teste1.bin vet/teste2.bin > cosseno.txt
./cosseno_vetores num_palavras.txt vet/teste2.bin vet/teste3.bin >> cosseno.txt
./cosseno_vetores num_palavras.txt vet/teste1.bin vet/teste3.bin >> cosseno.txt


