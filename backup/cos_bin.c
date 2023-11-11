#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    long int posicao;
    float frequencia;
} tDado;

int main()
{
    FILE *binaryFile;
    char *fileName = "data.bin"; // Replace with your binary file name
    int numDados; // Number of tDado structures in the binary file

    // Open the binary file in read mode
    binaryFile = fopen(fileName, "rb");

    if (binaryFile == NULL)
    {
        printf("Error opening the binary file.\n");
        return 1;
    }

    // Read the number of tDado structures from the binary file
    fread(&numDados, sizeof(int), 1, binaryFile);

    // Allocate memory for the array of tDado structures
    tDado *dados = malloc(numDados * sizeof(tDado));

    // Read the tDado structures from the binary file into the dados array
    fread(dados, sizeof(tDado), numDados, binaryFile);

    // Close the binary file
    fclose(binaryFile);

    // Process the data as needed
    for (int i = 0; i < numDados; i++)
    {
        printf("Posicao: %ld, Frequencia: %f\n", dados[i].posicao, dados[i].frequencia);
    }

    // Free the allocated memory
    free(dados);

    return 0;
}
