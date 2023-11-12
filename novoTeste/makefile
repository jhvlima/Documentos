# Variable assignments
DIR_DADOS = dados
DIR_VETORES = vet
UNIVERSO_PALAVRAS = banco.txt

arquivo_teste_1 = vet/teste1.bin
arquivo_teste_2 = vet/teste2.bin
arquivo_teste_3 = vet/teste3.bin

# Targets
all: cosseno

cosseno: vetorizador
	gcc -o cosseno_vetores cosseno_vetores.c -lm
	wc -l "$(UNIVERSO_PALAVRAS)" > num_palavras.txt
	./cosseno_vetores num_palavras.txt ${arquivo_teste_1} ${arquivo_teste_2} > cosseno.txt
	./cosseno_vetores num_palavras.txt ${arquivo_teste_2} ${arquivo_teste_3} >> cosseno.txt
	./cosseno_vetores num_palavras.txt ${arquivo_teste_1} ${arquivo_teste_3} >> cosseno.txt

vetorizador: banco contador
	gcc -o grava_vetor_binario grava_vetor_binario.c
	find $(DIR_VETORES)/ -type f -name "*.txt" | while read txt_file; do \
		if [ -f "$$txt_file" ]; then \
			filename_without_extension="$$(basename -- "$$txt_file" .txt)"; \
			output_bin_file="$$(dirname "$$txt_file")/$$filename_without_extension.bin"; \
			./grava_vetor_binario "$$txt_file" "$$output_bin_file" $(UNIVERSO_PALAVRAS); \
		fi; \
	done


# Targets for generating banco and contador
banco:
	find $(DIR_DADOS)/ -type f -exec cat {} \; | tr -s '[:space:]' '\n' | sort | uniq > ${UNIVERSO_PALAVRAS}

contador:
	find $(DIR_DADOS)/ -type f -exec sh -c 'mkdir -p "$(DIR_VETORES)/$$(dirname "{}")" && cat "{}" | tr -s "[:space:]" "\n" | sort | uniq -c > "$(DIR_VETORES)/$${0#$(DIR_DADOS)/}"' {} \;
	
# Clean target
clean:
	@rm -f banco.txt grava_vetores cosseno_vetores num_palavras.txt cosseno.txt grava_vetor_binario leitorBin
	@rm -rf vet