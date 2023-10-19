#!/bin/bash
# este script gera um .txt com todas as palavras de um diretorio 

# find [dir] -type f: encontra arquivos simples no diretorio passado 
# tr -s [1][2]: substitui todas as sequencias do primeiro parametro por uma do segundo parametro
# sort : ordena em ordem  alfabetica
# uniq : elimina linhas sequencias iguais

find dados/ -type f -exec cat {} \; | tr -s '[:space:]' '\n' | sort | uniq > "banco.txt"
