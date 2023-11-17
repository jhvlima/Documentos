// matrix_operations.h

#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

typedef struct
{
    float *vetor;
    int size;
} tVetor;

typedef struct
{
    tVetor *matrix;
    int rows;
    int cols;
} Matrix;

tVetor AlocaVetor(int size);
Matrix CriaMatriz(int rows, int cols);
void AdicionaElemento(Matrix *matrix, int row, int col, float element);
void RemoveElemento(Matrix *matrix, int row, int col);
int EhIgualElemento(Matrix matrix1, Matrix matrix2, int row, int col);
int JaGravouElemento(Matrix matrix, int row, int col);
void SalvaMatriz(Matrix matrix, const char *filename);
void DesalocaMatriz(Matrix *matrix);

#endif // MATRIX_OPERATIONS_H
