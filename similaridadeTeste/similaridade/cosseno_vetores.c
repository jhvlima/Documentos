/*
Este codigo deve receber como primeiro argumento o arquivo contendo a quantidade total de palavras do banco de dados
e calcula o coseno de vetores passados como argumento
./main qnt_palavras.txt vet/path/file.txt vet/path/file.vet

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "cosseno_vetores.h"

typedef struct
{
    long int posicao; // duas palavras sao da mesma dimensao se seus valores de posicao sao iguais
    float frequencia; // se for 0 entao, a palavra nao eh gravada
} tDado;

float PassaVetorMemoria(const char *file_name)
{
    FILE *file = fopen(file_name, "rb");
    if (file == NULL)
    {
        perror("Error opening vet_1 file");
        return 1;
    }
}








// eh calculado o cosseno dos vetores usando a formula: cos = vet_1 * vet_2/(|vet_1|*|vet_2|)
// ou seja, eh o produto escalar(ou produto interno) de vet_1 e vet_2 dividido produto dos modulos de vet_1 e vet_2
float CalculaCossenoVetores(float *vetor_1, float *vetor_2, int NUM_PALAVRAS)
{
    float ProdutoEscalar = 0, SomaNormaVet_1 = 0, SomaNormaVet_2 = 0, NormaVet_1 = 0, NormaVet_2 = 0;

    for (int i = 0; i < NUM_PALAVRAS; i++)
    {
        // se a palavra possui frequncia igual a 0 em algum dos dois, pula essa iteracao
        if (vetor_1[i] == 0 || vetor_2[i] == 0)
        {
            continue;
        }

        // ProdutoEscalar armazena o somatorio do produto escalar de A vet_1 vet_2, cada iteracao seria uma dimensao do vetor
        ProdutoEscalar = ProdutoEscalar + (vetor_1[i] * vetor_2[i]);
        // SomaNorma armazena o somatorio do quadrado
        SomaNormaVet_1 = SomaNormaVet_1 + pow(vetor_1[i], 2);
        SomaNormaVet_2 = SomaNormaVet_2 + pow(vetor_2[i], 2);
    }

    NormaVet_1 = sqrt(SomaNormaVet_1);
    NormaVet_2 = sqrt(SomaNormaVet_2);

    // se os vetores nao possuem nenhuma palavra igual, o produto escalar eh 0, logo o cosseno eh 0
    if (ProdutoEscalar == 0)
    {
        return 0;
    }
    // senao o cosseno eh calculado
    else
    {
        return ProdutoEscalar / (NormaVet_1 * NormaVet_2);
    }
}
// recebe um vetor e seu nome, e imprime todas as posicoes com valores nao nulos
void ImprimeVetorEmDisco(float *vet, int nomeVet, int NUM_PALAVRAS)
{
    printf("Vetor %d : ", nomeVet);
    for (int i = 0; i < NUM_PALAVRAS; i++)
    {
        // se a frequencia eh igual a 0, entao nao imprime
        if (vet[i] != 0)
        {
            printf("<%d,%f> ", i, vet[i]); // a frequencia seria em float
        }
    }
    printf("\n");
}

// recebe um vetor e seu nome, e imprime todas as posicoes com valores nao nulos
void ImprimeVetorEmMemoria(float *vet, int nomeVet, int NUM_PALAVRAS)
{
    printf("Vetor %d : ", nomeVet);
    for (int i = 0; i < NUM_PALAVRAS; i++)
    {
        if (i == 0)
        {
            printf("[%f", vet[i]);
        }
        else
        {
            printf(",%f", vet[i]);
        }
    }
    printf("]\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Precisa passar o path de pelo menos 2 vetores no argumento.\n");
        return 1;
    }

    char *palvras_name = argv[1];
    char *vet_1_name = argv[2];
    char *vet_2_name = argv[3];

    // Open the vet_1 file
    FILE *palavras_file = fopen(palvras_name, "r");
    if (palavras_file == NULL)
    {
        perror("Error opening vet_1 file");
        return 1;
    }

    // Open the vet_1 file
    FILE *vet_1_file = fopen(vet_1_name, "rb");
    if (vet_1_file == NULL)
    {
        perror("Error opening vet_1 file");
        fclose(palavras_file);
        return 1;
    }

    // Open the vet_2 file
    FILE *vet_2_file = fopen(vet_2_name, "rb");
    if (vet_2_file == NULL)
    {
        perror("Error opening vet_2 file");
        fclose(palavras_file);
        fclose(vet_1_file);
        return 1;
    }

    int palvras;
    fscanf(palavras_file, "%d", &palvras);

    long int total_palavras = palvras;

    long int pos_1 = 0, pos_2 = 0;
    float freq_1 = 0, freq_2 = 0;

float *vet_1 = calloc(total_palavras, sizeof(float));
if (vet_1 == NULL)
{
    perror("Memory allocation error for vet_1");
    fclose(palavras_file);
    fclose(vet_1_file);
    fclose(vet_2_file);
    return 1;
}
    tDado palavra;

//while (fscanf(vet_1_file, "%ld %f ", &pos_1, &freq_1) != EOF) // Check if two values were successfully read
while (fread(&palavra, sizeof(tDado), 1, vet_1_file) == 1)
{
    if (palavra.posicao < 0 || palavra.posicao >= total_palavras)
    {
        fprintf(stderr, "Invalid position %ld\n", palavra.posicao);
        free(vet_1);
        fclose(palavras_file);
        fclose(vet_1_file);
        fclose(vet_2_file);
        return 1;
    }
    vet_1[palavra.posicao] = palavra.frequencia;
    //printf("Read position %ld\n", pos_1);
}

if (!feof(vet_1_file))
{
    // fscanf did not reach the end of the file, possibly due to a format mismatch
    fprintf(stderr, "Error reading from vet_1_file\n");
    free(vet_1);
    fclose(palavras_file);
    fclose(vet_1_file);
    fclose(vet_2_file);
    return 1;
}


float *vet_2 = calloc(total_palavras, sizeof(float));
if (vet_2 == NULL)
{
    perror("Memory allocation error for vet_2");
    fclose(palavras_file);
    fclose(vet_1_file);
    fclose(vet_2_file);
    return 1;
}

//while (fscanf(vet_1_file, "%ld %f ", &pos_1, &freq_1) != EOF) // Check if two values were successfully read
while (fread(&palavra, sizeof(tDado), 1, vet_2_file) == 1)
{
    if (palavra.posicao < 0 || palavra.posicao >= total_palavras)
    {
        fprintf(stderr, "Invalid position %ld\n", palavra.posicao);
        free(vet_1);
        fclose(palavras_file);
        fclose(vet_1_file);
        fclose(vet_2_file);
        return 1;
    }
    vet_2[palavra.posicao] = palavra.frequencia;
    //printf("Read position %ld\n", pos_1);
}

if (!feof(vet_2_file))
{
    // fscanf did not reach the end of the file, possibly due to a format mismatch
    fprintf(stderr, "Error reading from vet_1_file\n");
    free(vet_1);
    free(vet_2);
    fclose(palavras_file);
    fclose(vet_1_file);
    fclose(vet_2_file);
    return 1;
}

    fclose(palavras_file);
    fclose(vet_1_file);
    fclose(vet_2_file);
/*
    // impressao para facilitar a visualizacao dos vetores
    printf("\n");
    printf("Padrao em disco: <posicao,frequencia>\n");
    ImprimeVetorEmDisco(vet_1, 1, total_palavras);
    ImprimeVetorEmDisco(vet_2, 2, total_palavras);

    printf("Padrao em memoria:\n");

    ImprimeVetorEmMemoria(vet_1, 1, total_palavras);
    ImprimeVetorEmMemoria(vet_2, 2, total_palavras);

    printf("Cosseno de 1 e 2: %f\n", CalculaCossenoVetores(vet_1, vet_2, total_palavras));
*/

    fwrite()


    free(vet_1);
    free(vet_2);
    return 0;
}
