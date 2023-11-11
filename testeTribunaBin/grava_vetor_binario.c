#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    long int posicao; // duas palavras sao da mesma dimensao se seus valores de posicao sao iguais
    float frequencia; // se for 0 entao, a palavra nao eh gravada
} tDado;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s input_file output_file database_file\n", argv[0]);
        return 1;
    }

    char *input_file_name = argv[1];
    char *output_file_name = argv[2];
    char *database_file_name = argv[3];

    // Open the input file
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    // Open the output file
    FILE *output_file = fopen(output_file_name, "wb");
    if (output_file == NULL)
    {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    // Open the database file
    FILE *database_file = fopen(database_file_name, "r");
    if (database_file == NULL)
    {
        perror("Error opening database file");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    char search_word[100]; // Adjust the size as needed
    char palavra_texto[100];
    float frequencia = 0;
    long int position = 0, posicao = 0;
    int frequency = 0;

    tDado palavra;

    // Read a word from the database file
    while (fscanf(input_file, "%d %s", &frequency, palavra_texto) != EOF)
    {
        // Search for the word in the input file
        while (fscanf(database_file, "%s", search_word) != EOF)
        {
            if (!strcmp(palavra_texto, search_word))
            {
                position++;
                break;
            }
            position++;
        }
        posicao = position -1;
        // frequencia = (float)frequency;
        // fprintf(output_file, "%ld %f ", position-1, frequencia);
        palavra.frequencia = (float)frequency;
        palavra.posicao = posicao;
        fwrite(&palavra, sizeof(tDado), 1, output_file);
    }

    fclose(input_file);
    fclose(output_file);
    fclose(database_file);
    return 0;
}
