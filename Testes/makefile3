# Define variables
CC = gcc
CFLAGS = -lm
SRC_DIR = src
OUTPUT_DIR = compilados
RESULTS_DIR = resultados
DATA_DIR = vet

# List of source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Generate object file names
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OUTPUT_DIR)/%.o, $(SRC_FILES))

# Main targets
all: cosseno_vetores banco vetorizador

cosseno_vetores: $(OUTPUT_DIR)/cosseno_vetores
	./compilados/cosseno_vetores resultados/num_palavras.txt vet/teste.vet vet/caminho1/teste2.vet > log.txt
	mv log.txt resultados

banco: $(RESULTS_DIR)/banco.txt
	wc -l $(RESULTS_DIR)/banco.txt > $(RESULTS_DIR)/num_palavras.txt

vetorizador: $(OUTPUT_DIR)/grava_vetores
	./scripts/gerador_banco.sh
	./scripts/contador.sh
	find $(DATA_DIR) -type f -name "*.txt" | while read txt_file; do \
		./compilados/grava_vetores "$$txt_file" \
		"$(OUTPUT_DIR)/$$(basename "$$txt_file" .txt).vet" \
		"$(RESULTS_DIR)/banco.txt"; \
		rm "$$txt_file"; \
	done

# Pattern rule for compiling .c files to .o files
$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

# Pattern rule for linking executables
$(OUTPUT_DIR)/%: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

clear:
	rm -rf $(OUTPUT_DIR) $(RESULTS_DIR) $(DATA_DIR) cosseno.txt

# Clean target
clean: clear
