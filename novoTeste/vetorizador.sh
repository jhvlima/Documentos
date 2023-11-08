#!/bin/bash

# compila
gcc -o grava_vetores grava_vetores.c

# executa o script que gera o banco.txt com todas as palavras de todos os aquivos do diretorio
# especificado (dados)
./gerador_banco.sh

# executa o script para todos os arquivos do diretotio especificado (dados) que gera um aquivo file.txt
# temporario que elimina duplicatas e lista a ocorrencia de todas as palavras do arquivo original no diretorio vet/path/file.txt
./contador.sh

# localiza todos os arquivos .txt dentro do diretorio especificado (vet) e seus sub diretorios
find vet/ -type f -name "*.txt" | while read txt_file; do
    if [ -f "$txt_file" ]; then
        # obtem o nome do arquivo sem extensao
        filename_without_extension=$(basename -- "$txt_file" .txt)

        # obtem o nome do arquivo com extensao .vet
        output_vet_file="$(dirname "${txt_file}")/$filename_without_extension.vet"

        # chama a main com os argumento: 1-input.txt 2-output.vet 3-input_banco.txt
        ./grava_vetores "$txt_file" "$output_vet_file" "banco.txt"

        # apagar o arquivo temporario
        #rm "$txt_file"
    fi
done

#   Onde melhorar:
# passar o diretorio dados no terminal
# passar o nome do banco de palavras por uma variavel
# escolher se mantem os arquivos temporarios
#
#