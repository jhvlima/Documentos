#!/bin/bash

# gera os aqruivos .vet 
./scripts/vetorizador.sh

# compila a main
gcc -o cosseno_vetores scripts/cosseno_vetores.c -lm

mv cosseno_vetores compilados

# obtem a quantidade total de palavras
wc -l resultados/banco.txt > resultados/num_palavras.txt

# chama o programa que calcula o coseno dos vetores passados como argumento e precisa da quantidade de palavras
./compilados/cosseno_vetores resultados/num_palavras.txt vet/teste.vet vet/caminho1/teste2.vet

