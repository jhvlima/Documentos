#!/bin/bash
find dados/ -type f -exec cat {} \; | tr -s '[:space:]' '\n' | sort | uniq > "banco.txt"
find "banco.txt" cat {} \; | tr -s '[:space:]' '\n' | sort | uniq > "banco_ordenado.txt"
