/*
Este codigo deve receber como primeiro argumento o arquivo contendo a quantidade total de palavras do banco de dados
e calcula o coseno de vetores passados como argumento
./main qnt_palavras.txt vet/path/file.txt vet/path/file.vet

*/


#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#define PATH_MAX 1024
#include "cosseno_vetores.h"

typedef struct
{
    long int posicao; // duas palavras sao da mesma dimensao se seus valores de posicao sao iguais
    float frequencia; // se for 0 entao, a palavra nao eh gravada
} tDado;

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

int main(int argc, char *argv[])
{
    // abre o diretorio
    if (argc < 2)
    {
        printf("Precisa passar o path do diretorio no argumento.\n");
        return 1;
    }

    char *diretorio_name = argv[1];
    
    // Open the directory
    DIR *dir = opendir(diretorio_name);
    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;


    printf("Cosseno de 1 e 2: %f\n", CalculaCossenoVetores(vet_1, vet_2, total_palavras));
    free(vet_1);
    free(vet_2);
    return 0;
}
