// coseno.h

#ifndef COSENO_H
#define COSENO_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    long int posicao; // duas palavras sao da mesma dimensao se seus valores de posicao sao iguais
    float frequencia; // se for 0 entao, a palavra nao eh gravada
} tDado;

float CalculaCossenoVetores(float *vetor_1, float *vetor_2, int NUM_PALAVRAS);

void ImprimeVetorEmDisco(float *vet, int nomeVet, int NUM_PALAVRAS);

void ImprimeVetorEmMemoria(float *vet, int nomeVet, int NUM_PALAVRAS);

float *MemorizaVetor(FILE *file);

#endif // COSENO_H
