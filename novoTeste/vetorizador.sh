#!/bin/bash

# diretorio qeue contem os vetores binarios dos documentos 
Dir_Vetores="vet"

Uiniverso_palavras="banco.txt"

# compila o codigo que grava os vetores
gcc -o grava_vetor_binario grava_vetor_binario.c

# executa o script que gera o banco.txt com todas as palavras de todos os aquivos do diretorio
# especificado (dados)
./gerador_banco.sh

# executa o script para todos os arquivos do diretotio especificado (dados) que gera um aquivo file.txt
# temporario que elimina duplicatas e lista a ocorrencia de todas as palavras do arquivo original no diretorio vet/path/file.txt
./contador.sh

# localiza todos os arquivos .txt dentro do diretorio especificado (vet) e seus sub diretorios
find $Dir_Vetores/ -type f -name "*.txt" | while read txt_file; do
    if [ -f "$txt_file" ]; then
        # obtem o nome do arquivo sem extensao
        filename_without_extension=$(basename -- "$txt_file" .txt)

        # obtem o nome do arquivo com extensao .bin
        output_bin_file="$(dirname "${txt_file}")/$filename_without_extension.bin"

        # chama a main com os argumento: 1-input.txt 2-output.bin 3-input_banco.txt
        ./grava_vetor_binario "$txt_file" "$output_bin_file" $Uiniverso_palavras

        # apagar o arquivo temporario
        #rm "$txt_file"
    fi
done