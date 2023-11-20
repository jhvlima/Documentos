#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int codigo_1;
    int codigo_2;
    float valor;
} tSimilaridade;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s input_binary_file\n", argv[0]);
        return 1;
    }

    char *input_file_name = argv[1];
    FILE *input_file = fopen(input_file_name, "rb");

    if (input_file == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    tSimilaridade similarity;

    printf("Codigo 1  |Codigo 2| Valor\n");
    printf("--------------------------\n");

    while (fread(&similarity, sizeof(tSimilaridade), 1, input_file) == 1)
    {
        printf("%d, %d, %f\n", similarity.codigo_1, similarity.codigo_2, similarity.valor);
    }

    fclose(input_file);

    return 0;
}
