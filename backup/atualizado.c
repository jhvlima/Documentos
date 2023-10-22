/*
Neste caso temos 6 (NUM_DOCUMENTOS) vetores que representam documentos, cada um com 6 espacos (NUM_PALAVRAS) diferentes, e o indice do vetor
representa a posicao de determinada palavra e o valor armazenado eh a sua frequencia, entao a frequencia de uma palavra que esta na posicao [i]
de um vetor que representa um documento esta armazenada no endereco: documento[i]

int *vetor : um documento
vetor[i] : frequencia da palavra tem como posicao i

o vetor em si = documento
o indice de posicao do vetor = posicao de determinada palavra
valor armazenado no indice de posicao do vetor = frequencia de determinada palavra palavra
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUM_DOCUMENTOS 4 
#define NUM_PALAVRAS 6   // esse eh numero total de palavras de todos os documentos, pode-se usar o script em shell para obter esse numero

// eh calculado o cosseno dos vetores usando a formula: cos = vet_1 * vet_2/(|vet_1|*|vet_2|)
// ou seja, eh o produto escalar(ou produto interno) de vet_1 e vet_2 dividido produto dos modulos de vet_1 e vet_2
float CalculaCossenoVetores(int *vetor_1, int *vetor_2)
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
// recebe um vetor e o seu nome, inicializa tudo com 0 e preenche com alguns valores
// poderia ser preenchido pela entrada padrao
void PreencheVetor(int *vet, int nomeVet)
{
    // inicializa todas as frequencias  com 0
    for (int i = 0; i < NUM_PALAVRAS; i++)
    {
        vet[i] = 0;
    }
    
    if (nomeVet == 1)
    {
        vet[0] = 1;
        vet[1] = 1;
        vet[2] = 2;
        vet[5] = 3;
        vet[4] = 2;
        vet[3] = 1;
    }
    else if (nomeVet == 2)
    {
        vet[4] = 99;
        vet[5] = 1;
    }
}

// recebe um vetor e seu nome, e imprime todas as posicoes com valores nao nulos 
void ImprimeVetorEmDisco(int *vet, int nomeVet)
{
    printf("Vetor %d : ", nomeVet);
    for (int i = 0; i < NUM_PALAVRAS; i++)
    {
        // se a frequencia eh igual a 0, entao nao imprime
        if (vet[i] != 0)
        {
            printf("<%d,%d> ", i, vet[i]); //a frequencia seria em float
        }
    }
    printf("\n");
}

// recebe um vetor e seu nome, e imprime todas as posicoes com valores nao nulos 
void ImprimeVetorEmMemoria(int *vet, int nomeVet)
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

int main()
{
    int vet_1[NUM_PALAVRAS], vet_2[NUM_PALAVRAS];
    PreencheVetor(vet_1, 1);
    PreencheVetor(vet_2, 2);
    
    // impressao para facilitar a visualizacao dos vetores
    printf("Padrao em disco: <posicao,frequencia>\n");
    ImprimeVetorEmDisco(vet_1, 1);
    ImprimeVetorEmDisco(vet_2, 2);
    printf("Padrao em memoria:\n");
    ImprimeVetorEmMemoria(vet_1, 1);
    ImprimeVetorEmMemoria(vet_2, 2);
    
    printf("Cosseno de 1 e 2: %f\n", CalculaCossenoVetores(vet_1, vet_2));
    return 0;
}
