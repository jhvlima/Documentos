/*
Neste caso temos 4 documentos com 6 palavras diferentes, ou seja um vetor de palavras, o indice da palavra representa a sua
posicao e o valor armazenado a sua frequencia, entao a estrutura de uma da frequencia de uma palavra i contida em um 
documento a eh igual a: documento[a].palavra[i]
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUM_DOCUMENTOS 4 // defini uma qunatidade de documentos para definir a strucut tDocumento
#define NUM_PALAVRAS 6   // esse e numero total de palavras de todos os documentos, pode-se usar o script em shell para obter esse numero

typedef struct
{
    int *palavra; // cada palavra sera uma dimensao do vetor que representa um documento
} tDocumento;

// eh calculado o coseno dos documentos de indices B e A usando a formula: cos = vetA * vetB/(|vetA|*|vetB|)
// ou seja, eh o produto escalar(ou produto interno) de A e B dividido produto escalar das normas(ou modulo) de A e B
void CalculaCosVetores(tDocumento *doc, int a, int b)
{
    double ProdutoEscalar = 0, SomaNormaDeA = 0, SomaNormaDeB = 0, NormaDeA = 0, NormaDeB = 0, cos = 0;

    for (int i = 0; i < NUM_PALAVRAS; i++)
    {
        // se a palavra nao possui frequncia em algum dos dois, pula essa iteracao
        if (doc[b].palavra[i] == 0 || doc[a].palavra[i] == 0)
        {
            continue;
        }

        // ProdutoEscalar armazena o somatorio do produto escalar de A e B, cada iteracao seria uma dimensao do vetor
        ProdutoEscalar = ProdutoEscalar + (doc[a].palavra[i] * doc[b].palavra[i]);
        // o SomaNorma eh o mesmo de distancia euclidiana
        SomaNormaDeA = SomaNormaDeA + pow(doc[a].palavra[i], 2);
        SomaNormaDeB = SomaNormaDeB + pow(doc[b].palavra[i], 2);
    }

    NormaDeA = sqrt(SomaNormaDeA);
    NormaDeB = sqrt(SomaNormaDeB);

    // se os vetores nao possuem nenhuma palavra igual siggnifica que o coseno eh 0
    if (ProdutoEscalar == 0)
    {
        printf("Coseno de %d %d : 0\n", a, b);
    }
    // senao o coseno eh calculado
    else
    {
        cos = ProdutoEscalar / (NormaDeA * NormaDeB);
        printf("Coseno de %d %d : %f\n", a, b, cos);
    }
}

void PreencheDocumentos(tDocumento *documento)
{
    for (int i = 0; i < NUM_DOCUMENTOS; i++)
    {
        // calloc inicializa todas as frequencias de todos documentos com 0
        documento[i].palavra = (int *)calloc(NUM_PALAVRAS, sizeof(int));
        // inicializa  do documento 0 e 1 iguais, o 2 eh totalmente diferente de todos, e o 3 eh semelhante ao 1
        if (i == 0 || i == 1)
        {
            documento[i].palavra[0] = 1;
            documento[i].palavra[1] = 1;
            documento[i].palavra[2] = 2;
        }
        else if (i == 2)
        {
            documento[i].palavra[5] = 3;
            documento[i].palavra[4] = 4;
            documento[i].palavra[3] = 5;
        }
        else if (i == 3)
        {
            documento[i].palavra[0] = 3;
            documento[i].palavra[5] = 2;
            documento[i].palavra[2] = 1;
            documento[i].palavra[3] = 1;
        }
    }
}

void FinalizaDocumentos(tDocumento *documento)
{
    // os documentos 0 e 1 sao iguais e o 2 eh totalmente diferente
    for (int i = 0; i < NUM_DOCUMENTOS; i++)
    {
        free(documento[i].palavra);
    }
}
// imprime todos os documentos na sua represntacao na forma de vetor
void ImprimeDocumentos(tDocumento *documento)
{
    printf("Padrao de impressao: <poscao,frequencia>\n");
    for (int j = 0; j < NUM_DOCUMENTOS; j++)
    {
        printf("DOCUMENTO %d : ", j);
        for (int i = 0; i < NUM_PALAVRAS; i++)
        {
            // se a eh 0, entao nao eh gravado
            if (documento[j].palavra[i] != 0)
            {
                printf("<%d,%d> ", i, documento[j].palavra[i]);
            }
        }
        printf("\n");
    }
}

int main()
{
    tDocumento *documento = (tDocumento *)malloc(NUM_DOCUMENTOS * sizeof(tDocumento));
    PreencheDocumentos(documento);
    ImprimeDocumentos(documento);
    CalculaCosVetores(documento, 1, 0);
    CalculaCosVetores(documento, 1, 2);
    CalculaCosVetores(documento, 1, 3);
    FinalizaDocumentos(documento);
    free(documento);
    return 0;
}
