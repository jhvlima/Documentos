#!/bin/bash
# este script gera um .txt com todas as palavras de um diretorio desordenadas
# e o todos os arquivos com o seu path em um diretorio vet

# find [dir] -type f: encontra arquivos simples no diretorio passado 
# tr -s [1][2]: substitui todas as sequencias do primeiro parametro por uma do segundo parametro
# sort : ordena em ordem  alfabetica
# uniq : elimina linhas sequencias iguais

find dados/ -type f -exec sh -c 'mkdir -p "vet/$(dirname "${0#dados/}")" && cat "$0" | tr -s "[:space:]" "\n" | sort | uniq -c > "vet/${0#dados/}" && cat "$0" >> "banco.txt"' {} \;
