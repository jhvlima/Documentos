#!/bin/bash
# este script faz a vetorizacao de todos arquivo .txt

#   gera o banco de dados com todas as palavras 
./gerador_banco.sh
#   gera um arquivo .vet para cada aquivo de .txt em um diretorio vet 
./contador.sh
#   chama gravador_vetores.c para cada arquivo
find vet/ -type f -exec  ./gravador_vetores.c $FILE_TXT $FILE_VET $FILE_BANCO
