#!/bin/bash
# Check if the correct number of arguments is provided
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 input_vector_file_1 input_vector_file_2"
    exit 1
fi

# Get the input vector file (first argument)
input_vector_file_1="$1"
input_vector_file_2="$2"

shift # Remove the first argument from the list of arguments

# gera os aqruivos .vet 
./vetorizador.sh

# compila a main
gcc -o cosseno_vetores cosseno_vetores.c -lm

# obtem a quantidade total de palavras
wc -l banco.txt > num_palavras.txt

# chama o programa que calcula o coseno dos vetores passados como argumento e precisa da quantidade de palavras
    ./cosseno_vetores num_palavras.txt "$input_vector_file_1" "$input_vector_file_2"