#!/bin/bash

# gera os aqruivos .vet 
./vetorizador.sh

# compila a main
gcc -o cosseno_vetores cosseno_vetores.c -lm

# obtem a quantidade total de palavras
wc -l banco.txt > num_palavras.txt

# chama o programa que calcula o coseno dos vetores passados como argumento e precisa da quantidade de palavras
./cosseno_vetores num_palavras.txt vet/teste.vet vet/TESTE3.vet

