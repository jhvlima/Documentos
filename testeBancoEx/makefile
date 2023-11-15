# Variable assignments
DIR_DADOS = dados
DIR_VETORES = vet

UNIVERSO_PALAVRAS = banco.txt
BANCO_EXTERNO = fi
BANCO_EXTERNO_ORDENADO = ${BANCO_EXTERNO}_ordenado
STOP_WORDS = portugues

arquivo_teste_1 = vet/teste1.bin
arquivo_teste_2 = vet/teste2.bin
arquivo_teste_3 = vet/teste3.bin

# Targets
all: cosseno

cosseno: vetorizador
	gcc -o cosseno_vetores cosseno_vetores.c -lm
	./cosseno_vetores num_palavras.txt ${arquivo_teste_1} ${arquivo_teste_2} > cosseno.txt
	./cosseno_vetores num_palavras.txt ${arquivo_teste_2} ${arquivo_teste_3} >> cosseno.txt
	./cosseno_vetores num_palavras.txt ${arquivo_teste_1} ${arquivo_teste_3} >> cosseno.txt

vetorizador: banco contador
	gcc -o grava_vetor_binario grava_vetor_binario.c
	find $(DIR_VETORES)/ -type f -name "*.txt" | while read txt_file; do \
		if [ -f "$$txt_file" ]; then \
			filename_without_extension="$$(basename -- "$$txt_file" .txt)"; \
			output_bin_file="$$(dirname "$$txt_file")/$$filename_without_extension.bin"; \
			./grava_vetor_binario "$$txt_file" "$$output_bin_file" $(BANCO_EXTERNO_ORDENADO).txt; \
		fi; \
	done


# Targets for generating banco and contador
banco:
	find $(DIR_DADOS)/ -type f -exec cat {} \; | tr -s '[:space:]' '\n' | sort | uniq > ${BANCO_EXTERNO_ORDENADO}
	wc -l "$(BANCO_EXTERNO_ORDENADO).txt" > num_palavras.txt
ordena:
	sort -k1 ${BANCO_EXTERNO}.txt > ./${BANCO_EXTERNO_ORDENADO}txt
	
contador:
# bash -c 
	# gera um arquivo com a frequencia e os token de cada documento
	find $(DIR_DADOS)/ -type f -exec sh -c 'mkdir -p "$(DIR_VETORES)/$$(dirname "{}")" && cat "{}" | tr -s "[:space:]" "\n" | tr -d "[:punct:][:digit:]" | tr "[:upper:]" "[:lower:]" | iconv -f utf-8 -t ascii//TRANSLIT | LC_COLLATE=C sort | uniq -c > "$(DIR_VETORES)/$${0#$(DIR_DADOS)/}"' {} \;

	# remove stop words
	#grep -v -wFf ${STOP_WORDS} ${BANCO_EXTERNO_ORDENADO}.txt > ${}.txt

# Clean target
clean:
	@rm -f banco.txt grava_vetores cosseno_vetores num_palavras.txt cosseno.txt grava_vetor_binario leitorBin
	@rm -rf vet