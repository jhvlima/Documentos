// matrix_operations.h

#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

typedef struct
{
    float **valor;
    int rows;
    int cols;
} tMatrix;

tMatrix *CriaMatriz(int rows, int cols);
void AdicionaElemento(tMatrix *matrix, int row, int col, float element);
void RemoveElemento(tMatrix *matrix, int row, int col);
int EhIgualElemento(int row, int col);
int JaGravouElemento(tMatrix *matrix, int row, int col);
void SalvaMatriz(tMatrix matrix, const char *filename);
void DesalocaMatriz(tMatrix *matrix);

#endif // MATRIX_OPERATIONS_H
