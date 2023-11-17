// matrix_operations.c

#include "matrix_operations.h"
#include <stdlib.h>
#include <stdio.h>

tVetor AlocaVetor(int size)
{
    tVetor vec;
    vec.vetor = malloc(size * sizeof(float));
    vec.size = size;
    return vec;
}

Matrix CriaMatriz(int rows, int cols)
{
    Matrix matrix;
    matrix.matrix = malloc(rows * sizeof(tVetor));
    for (int i = 0; i < rows; ++i)
    {
        matrix.matrix[i] = AlocaVetor(cols);
    }
    matrix.rows = rows;
    matrix.cols = cols;
    return matrix;
}

void AdicionaElemento(Matrix *matrix, int row, int col, float element)
{
    if (row >= 0 && row < matrix->rows && col >= 0 && col < matrix->cols)
    {
        matrix->matrix[row].vetor[col] = element;
    }
}

void RemoveElemento(Matrix *matrix, int row, int col)
{
    AdicionaElemento(matrix, row, col, 0.0); // Assuming 0.0 is the default value to remove an element
}

int EhIgualElemento(Matrix matrix1, Matrix matrix2, int row, int col)
{
    if (row >= 0 && row < matrix1.rows && col >= 0 && col < matrix1.cols)
    {
        return matrix1.matrix[row].vetor[col] == matrix2.matrix[row].vetor[col];
    }
    return 0; // Return 0 for invalid indices
}

int JaGravouElemento(Matrix matrix, int row, int col)
{
    if (row >= 0 && row < matrix.rows && col >= 0 && col < matrix.cols)
    {
        return matrix.matrix[row].vetor[col] != 0.0; // Assuming 0.0 is the default value for not having saved an element
    }
    return 0; // Return 0 for invalid indices
}

void SalvaMatriz(Matrix matrix, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file != NULL)
    {
        for (int i = 0; i < matrix.rows; ++i)
        {
            for (int j = 0; j < matrix.cols; ++j)
            {
                fprintf(file, "%f ", matrix.matrix[i].vetor[j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
}

void DesalocaMatriz(Matrix *matrix)
{
    for (int i = 0; i < matrix->rows; ++i)
    {
        free(matrix->matrix[i].vetor);
    }
    free(matrix->matrix);
    matrix->rows = 0;
    matrix->cols = 0;
}
