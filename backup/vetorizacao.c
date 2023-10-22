/*
Neste caso temos 4 documentos com 6 palavras diferentes, ou seja um vetor de palavras, que por sua vez eh uma
struct que armazena posicao e frequencia entao pode-se representar cada frequncia e posicao de cada palavra
dos documentos na forma: documento[a].palavra[i].frequencia e documento[a].palavra[i].posicao
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUM_DOCUMENTOS 4 // defini uma qunatidade de documentos para definir a strucut tDocumento
#define NUM_PALAVRAS 6   // esse e numero total de palavras de todos os documentos, pode-se usar o script em shell para obter esse numero

typedef struct
{
    int posicao;    // duas palavras sao da mesma dimensao se seus valores de posicao sao iguais
    int frequencia; // se for 0 entao, a palavra nao eh gravada
} tPalavra;

typedef struct
{
    tPalavra *palavra; // cada palavra sera uma dimensao do vetor que representa um documento
} tDocumento;

// eh calculado o coseno dos documentos de indices B e A usando a formula: cos = vetA * vetB/(|vetA|*|vetB|)
// ou seja, eh o produto escalar(ou produto interno) de A e B dividido produto escalar das normas(ou modulo) de A e B
void CalculaCosVetores(tDocumento *doc, int a, int b)
{
    double ProdutoEscalar = 0, SomaNormaDeA = 0, SomaNormaDeB = 0, NormaDeA = 0, NormaDeB = 0, cos = 0;

    for (int i = 0; i < NUM_PALAVRAS; i++) // cada iteracao seria uma dimensao do vetor
    {
        // se a palavra nao possui frequncia em algum dos dois, pula essa iteracao
        if (doc[b].palavra[i].posicao != i || doc[a].palavra[i].posicao != i)
        {
            continue;
        }

        // ProdutoEscalar armazena o somatorio do produto escalar de A e B
        ProdutoEscalar = ProdutoEscalar + (doc[a].palavra[i].frequencia * doc[b].palavra[i].frequencia);
        // o SomaNorma armazena a somatoria do quadrado da frequencia de cada palavra
        SomaNormaDeA = SomaNormaDeA + pow(doc[a].palavra[i].frequencia, 2);
        SomaNormaDeB = SomaNormaDeB + pow(doc[b].palavra[i].frequencia, 2);
    }

    NormaDeA = sqrt(SomaNormaDeA);
    NormaDeB = sqrt(SomaNormaDeB);

    // se os vetores nao possuem nenhuma palavra igual significa que o coseno eh 0
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
        // calloc inicializa todas as posicoes e frequencia com 0
        documento[i].palavra = (tPalavra *)calloc(NUM_PALAVRAS, sizeof(tPalavra));
        // inicializa `posicao` e `frequencia` do documento 0 e 1 iguais, o 2 eh totalmente diferente de
        // todos, e o 3 eh semelhante ao 1
        if (i == 0 || i == 1)
        {
            documento[i].palavra[0].posicao = 0;
            documento[i].palavra[1].posicao = 1;
            documento[i].palavra[2].posicao = 2;
            documento[i].palavra[0].frequencia = 1;
            documento[i].palavra[1].frequencia = 8;
            documento[i].palavra[2].frequencia = 14;
        }
        else if (i == 2)
        {
            documento[i].palavra[0].posicao = 3;
            documento[i].palavra[1].posicao = 4;
            documento[i].palavra[2].posicao = 5;
            documento[i].palavra[0].frequencia = 1;
            documento[i].palavra[1].frequencia = 8;
            documento[i].palavra[2].frequencia = 14;
        }
        else if (i == 3)
        {
            documento[i].palavra[0].posicao = 0;
            documento[i].palavra[1].posicao = 1;
            documento[i].palavra[2].posicao = 2;
            documento[i].palavra[0].frequencia = 4;
            documento[i].palavra[1].frequencia = 3;
            documento[i].palavra[2].frequencia = 14;
        }
    }
}

// libera as palavras alocadas no documento
void FinalizaDocumentos(tDocumento *documento)
{
    for (int i = 0; i < NUM_DOCUMENTOS; i++)
    {
        free(documento[i].palavra);
    }
}
// imprime todos os documentos na sua represntacao na forma de vetor
void ImprimeDocumentos(tDocumento *documento)
{
    printf("Padrao de impressao: <posicao,frequencia>\n");
    for (int j = 0; j < NUM_DOCUMENTOS; j++)
    {
        printf("DOCUMENTO %d : ", j);
        for (int i = 0; i < NUM_PALAVRAS; i++)
        {
            // se a frequencia eh 0, entao nao eh gravado
            if (documento[j].palavra[i].frequencia != 0)
            {
                printf("<%d,%d> ", documento[j].palavra[i].posicao, documento[j].palavra[i].frequencia);
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
