#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countWordFrequency(FILE *input_file, const char *search_word) {
    char word[100];  // Adjust the size as needed
    int frequency = 0;

    while (fscanf(input_file, "%s", word) != EOF) {
        if (strcmp(word, search_word) == 0) {
            frequency++;
        }
    }

    return frequency;
}

int findWordPosition(FILE *database_file, const char *search_word) {
    char word[100];  // Adjust the size as needed
    int position = 0;

    while (fscanf(database_file, "%s", word) != EOF) {
        position++;
        if (strcmp(word, search_word) == 0) {
            return position;
        }
    }

    return -1;  // Return -1 if the word is not found
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

    // Read a word from the input file
    fscanf(input_file, "%s", search_word);

    // Call the findWordPosition function to get the position
    position = findWordPosition(database_file, search_word);

    int frequency;

    // Call the countWordFrequency function to get the frequency in the input file
    frequency = countWordFrequency(input_file, search_word);

    if (position != -1) {
        fprintf(output_file, "Word '%s' found in the database at position %d. Frequency in input: %d\n", search_word, position, frequency);
    } else {
        fprintf(output_file, "Word '%s' not found in the database. Frequency in input: %d\n", search_word, frequency);
    }

    fclose(input_file);
    fclose(output_file);
    fclose(database_file);

    printf("Search complete.\n");

    return 0;
}
