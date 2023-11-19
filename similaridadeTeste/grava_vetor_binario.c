/*
    Este programa grava o vetor em forma binaria de um documento.
    Os argmentos devem ser:
        documento que vai ser veorizado (ordenado)
        documento que vai receber o vetor binario
        documento com o banco de palavras do seu universo (ordenado).

    Os scripts contador.sh e gera_banco.sh ja ordenaram os documentos.

    O programa grava uma palavra por vez com a struct tDado onde existe um long int para a posicao e um float para a frequencia, sendo que a 
    posicao comeca do 0 e a se a frequencia de uma palavra for 0, ela nao sera gravada no vetor

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    long int posicao; 
    float frequencia; 
} tDado;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s input_file output_file database_file\n", argv[0]);
        return 1;
    }

    char *input_file_name = argv[1]; // nome do arquivo que contem o documento que vai ser vetorizado
    char *output_file_name = argv[2]; // nome do arquivo binario de saida 
    char *database_file_name = argv[3]; // nome do arquivo que contem a lista com todas as palavras 

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

    char palavra_banco[1000], palavra_documento[1000]; // variavel que recebe uma palavra por vez dos documentos
    long int position = -1;
    int frequency = 0; // recebe um int com a frequencia de uma palavra oriunda do comando 'uniq -c' de shell
    tDado palavra; // estrutra que sera gravada no arquivo .bin

    //printf("long int tem %d bytes\n", sizeof(long int));
    //printf("long int tem %d bytes\n", sizeof(float));
    // Read a word from the database file
    while (fscanf(input_file, "%d %s", &frequency, palavra_documento) != EOF)
    {
        // Search for the word in the input file
        while (fscanf(database_file, "%s", palavra_banco) != EOF)
        {
            position++;
            if (!strcmp(palavra_documento, palavra_banco))
            {
                break;
            }
        }
        palavra.frequencia = (float)frequency;
        palavra.posicao = position;
        fwrite(&palavra, sizeof(tDado), 1, output_file);
    }

    fclose(input_file);
    fclose(output_file);
    fclose(database_file);
    return 0;
}
