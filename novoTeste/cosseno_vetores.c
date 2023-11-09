/*
Este codigo deve receber como primeiro argumento o arquivo contendo a quantidade total de palavras do banco de dados
e calcula o coseno de vetores passados como argumento
./main qnt_palavras.txt vet/path/file.txt vet/path/file.vet

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// eh calculado o cosseno dos vetores usando a formula: cos = vet_1 * vet_2/(|vet_1|*|vet_2|)
// ou seja, eh o produto escalar(ou produto interno) de vet_1 e vet_2 dividido produto dos modulos de vet_1 e vet_2
float CalculaCossenoVetores(int *vetor_1, int *vetor_2, int NUM_PALAVRAS)
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
void ImprimeVetorEmDisco(int *vet, int nomeVet, int NUM_PALAVRAS)
{
    printf("Vetor %d : ", nomeVet);
    for (int i = 0; i < NUM_PALAVRAS; i++)
    {
        // se a frequencia eh igual a 0, entao nao imprime
        if (vet[i] != 0)
        {
            printf("<%d,%d> ", i, vet[i]); // a frequencia seria em float
        }
    }
    printf("\n");
}

// recebe um vetor e seu nome, e imprime todas as posicoes com valores nao nulos
void ImprimeVetorEmMemoria(int *vet, int nomeVet, int NUM_PALAVRAS)
{
    printf("Vetor %d : ", nomeVet);
    for (int i = 0; i < NUM_PALAVRAS; i++)
    {
        if (i == 0)
        {
            printf("[%d", vet[i]);
        }
        else
        {
            printf(",%d", vet[i]);
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
    FILE *vet_1_file = fopen(vet_1_name, "r");
    if (vet_1_file == NULL)
    {
        perror("Error opening vet_1 file");
        fclose(palavras_file);
        return 1;
    }

    // Open the vet_2 file
    FILE *vet_2_file = fopen(vet_2_name, "r");
    if (vet_2_file == NULL)
    {
        perror("Error opening vet_2 file");
        fclose(palavras_file);
        fclose(vet_1_file);
        return 1;
    }

    int total_palavras;
    fscanf(palavras_file, "%d", &total_palavras);
   

    long int pos_1 = 0, pos_2 = 0;
    float  freq_1 = 0, freq_2 = 0;
    char car;

    int *vet_1 = calloc(total_palavras, sizeof(int));

    while (fscanf(vet_1_file, "%ld%f%c", &pos_1, &freq_1, &car) && car != '\n')
    {
        vet_1[pos_1] = freq_1;
    }

    int *vet_2 = calloc(total_palavras, sizeof(int));
    while (fscanf(vet_2_file, "%ld%f%c", &pos_2, &freq_2, &car) && car != '\n')
    {
        vet_2[pos_2] = freq_2;
    }

    fclose(palavras_file);
    fclose(vet_1_file);
    fclose(vet_2_file);

    // impressao para facilitar a visualizacao dos vetores
    printf("\n");
    printf("Padrao em disco: <posicao,frequencia>\n");
    ImprimeVetorEmDisco(vet_1, 1, total_palavras);
    ImprimeVetorEmDisco(vet_2, 2, total_palavras);
    printf("Padrao em memoria:\n");
    ImprimeVetorEmMemoria(vet_1, 1, total_palavras);
    ImprimeVetorEmMemoria(vet_2, 2, total_palavras);

    printf("Cosseno de 1 e 2: %f\n", CalculaCossenoVetores(vet_1, vet_2, total_palavras));
    free(vet_1);
    free(vet_2);
    return 0;
}
