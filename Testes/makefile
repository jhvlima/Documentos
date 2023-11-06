# Define the compiler (not needed in this case)
CC = gcc

# Define any flags (not needed in this case)
CFLAGS = 

# Define targets and their corresponding shell commands
cosseno:

# gera os aqruivos .vet 
	vetorizador

# compila a main
	gcc -o cosseno_vetores scripts/cosseno_vetores.c -lm
	mv cosseno_vetores compilados

# chama o programa que calcula o coseno dos vetores passados como argumento e precisa da quantidade de palavras
	./compilados/cosseno_vetores resultados/num_palavras.txt vet/teste.vet vet/caminho1/teste2.vet > log.txt
	mv log.txt resultados

banco:
	./scripts/gerador_banco.
# obtem a quantidade total de palavras
	wc -l resultados/banco.txt > resultados/num_palavras.txt

vetorizador:

# compila
	gcc -o grava_vetores scripts/grava_vetores.c
	mkdir -p compilados
	mv  grava_vetores compilados

# executa o script que gera o banco.txt com todas as palavras de todos os aquivos do diretorio especificado (dados)
	./scripts/gerador_banco.sh

# executa o script para todos os arquivos do diretotio especificado (dados) que gera um aquivo file.txt
# temporario que elimina duplicatas e lista a ocorrencia de todas as palavras do arquivo original no diretorio vet/path/file.txt
	./scripts/contador.sh

# localiza todos os arquivos .txt dentro do diretorio especificado (vet) e seus sub diretorios
	find vet/ -type f -name "*.txt" | while read txt_file; do
		if [ -f "$txt_file" ]; then
			# obtem o nome do arquivo sem extensao
			filename_without_extension=$(basename -- "$txt_file" .txt)

			# obtem o nome do arquivo com extensao .vet
			output_vet_file="$(dirname "${txt_file}")/$filename_without_extension.vet"

			# chama a main com os argumento: 1-input.txt 2-output.vet 3-input_banco.txt
			./compilados/grava_vetores "$txt_file" "$output_vet_file" "resultados/banco.txt"

			# apagar o arquivo temporario
			rm "$txt_file"
		fi
	done

clear:
	rm -f banco.txt grava_vetores cosseno_vetores num_palavras.txt cosseno.txt
	rm -rf vet compilados resultados

#add:

# Define a target for cleaning up all generated files
clean: clear
