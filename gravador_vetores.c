#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    FILE *output_file = fopen(output_file_name, "w");
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
    int position = 0;
    int found = 0;

    // Read a word from the database file
    fscanf(database_file, "%s", search_word);

    // Search for the word in the input file
    while (fscanf(input_file, "%s", palavra_texto) != EOF)
    {
        position++;
        if (strcmp(palavra_texto, search_word) == 0)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        fprintf(output_file, "Word '%s' found in the database at position %d.\n", search_word, position);
    }
    else
    {
        fprintf(output_file, "Word '%s' not found in the database.\n", search_word);
    }

    fclose(input_file);
    fclose(output_file);
    fclose(database_file);

    printf("Search complete.\n");

    return 0;
}
