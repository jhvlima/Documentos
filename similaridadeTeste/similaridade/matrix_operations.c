// matrix_operations.c

#include <stdlib.h>
#include <stdio.h>
#include "matrix_operations.h"

tMatrix *CriaMatriz(int rows, int cols)
{
    tMatrix *matrix;
    matrix->valor = malloc(rows * sizeof(float *));
    matrix->rows = rows;
    matrix->cols = cols;

    for (int i = 0; i < rows; ++i)
    {
        matrix->valor[i] = malloc(cols * sizeof(float));
    }

    return matrix;
}

void AdicionaElemento(tMatrix *matrix, int row, int col, float element)
{
    if (row < matrix->rows && col < matrix->cols)
    {
        matrix->valor[row][col] = element;
    }
}

void RemoveElemento(tMatrix *matrix, int row, int col)
{
    AdicionaElemento(matrix, row, col, 0.0);
}

int EhIgualElemento(int row, int col)
{
    return row == col; 
}

int JaGravouElemento(tMatrix *matrix, int row, int col)
{
    return matrix->valor[row][col] != 0.0;
}

void SalvaMatriz(tMatrix matrix, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file != NULL)
    {
        fwrite(&matrix.rows, sizeof(unsigned int), 1, file);
        fwrite(&matrix.cols, sizeof(unsigned int), 1, file);

        for (unsigned int i = 0; i < matrix.rows; ++i)
        {
            fwrite(matrix.valor[i], sizeof(float), matrix.cols, file);
        }

        fclose(file);
    }
}

void DesalocaMatriz(tMatrix *matrix)
{
    for (unsigned int i = 0; i < matrix->rows; ++i)
    {
        free(matrix->valor[i]);
    }

    free(matrix->valor);
    matrix->rows = 0;
    matrix->cols = 0;
}
