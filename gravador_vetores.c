#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL)
    {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    char c;

    while ((c = fgetc(input_file)) != EOF)
    {
        fputc(c, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    printf("File copied successfully.\n");

    return 0;
}
