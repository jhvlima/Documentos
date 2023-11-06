#!/bin/bash
# este script gera um .txt com todas as palavras de um diretorio 

# find [dir] -type f: encontra arquivos simples no diretorio passado 
# tr -s [1][2]: substitui todas as sequencias do primeiro parametro por uma do segundo parametro
# sort : ordena em ordem  alfabetica
# uniq : elimina linhas sequencias iguais

# diretorio que vai ser processado
Dir_dados="dados"


find $Dir_dados/ -type f -exec sh -c 'mkdir -p "vet/$(dirname "${0#dados/}")" && cat "$0" | tr -s "[:space:]" "\n" | sort | uniq -c > "vet/${0#dados/}" && cat "$0" >> "banco.txt"' {} \;

#   Onde melhorar:
# passar o diretorio dados no terminal
# escolher o nome do banco de palavras em uma variavel
#
#
#