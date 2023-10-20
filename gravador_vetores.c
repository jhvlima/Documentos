#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findWordPosition(FILE *database_file, const char *search_word, int *frequency) {
    char line[100];  // Adjust the size as needed
    int position = 0;
    *frequency = 0;

    while (fgets(line, sizeof(line), database_file) != NULL) {
        position++;
        if (strcmp(line, search_word) == 0) {
            (*frequency)++;
        }
    }

    if (*frequency > 0) {
        return position;
    } else {
        return -1;  // Return -1 if the word is not found
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s input_file output_file database_file\n", argv[0]);
        return 1;
    }

    char *input_file_name = argv[1];
    char *output_file_name = argv[2];
    char *database_file_name = argv[3];

    // Open the input file
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open the output file
    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    // Open the database file
    FILE *database_file = fopen(database_file_name, "r");
    if (database_file == NULL) {
        perror("Error opening database file");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    char search_word[100];  // Adjust the size as needed
    int position;
    int frequency;

    // Read a word from the input file
    fscanf(input_file, "%s", search_word);

    // Call the findWordPosition function to get the position and frequency
    position = findWordPosition(database_file, search_word, &frequency);

    if (position != -1) {
        fprintf(output_file, "Word '%s' found in the database at position %d. Frequency: %d\n", search_word, position, frequency);
    } else {
        fprintf(output_file, "Word '%s' not found in the database.\n", search_word);
    }

    fclose(input_file);
    fclose(output_file);
    fclose(database_file);

    printf("Search complete.\n");

    return 0;
}
