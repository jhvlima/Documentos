#!/bin/bash
# este script gera um .txt com todas as palavras de um arquivo com um texto em um diretorio vet/path/file 
# com o mesmo path do arquivo original 

# mkdir -p "vet/$(dirname "${0#dados/}")": 
#   -p cria diretorios parentais se eles nao existirem, 
#   dirname: extrai o diretorio do path do arquivo
#   ${0#dados/}: remove "dados/" do path do arquivo
#   cat "$0": le o arquivo original

# find [dir] -type f: encontra arquivos simples no diretorio passado 
# tr -s [1][2]: substitui todas as sequencias do primeiro parametro por uma do segundo parametro
# sort: ordena em ordem  alfabetica
# uniq: elimina linhas sequencias iguais

find dados/ -type f -exec sh -c 'mkdir -p "vet/$(dirname "${0#dados/}")" && cat "$0" | tr -s "[:space:]" "\n" | sort | uniq  > "vet/${0#dados/}"' {} \;

#agora temos que usar um programa em c para criar e armazerar esses vetores