/*
    Esse codigo gera uma matriz binaria de similitude entre todos os documentos de um diretorio passado
    como argumento.
    A matriz vai possuir no maximo n(n-1)/2 elementos,uma vez que:
    Sendo o elemento[a][b] = elemento[b][a], logo apenas um elemento sera gravado,
    Sendo o elemento[a][a] = 1, nao sera gravado,
    Sendo o elemento[a][b] = 0, nao sera gravado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "matrix_operations.h"
#include "cosseno_vetores.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open the directory
    DIR *dir = opendir(argv[1]);
    if (dir == NULL)
    {
        perror("opendir");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    struct dirent *duplicata;

    Matrix *mat;

    // Read the directory entries
    while ((entry = readdir(dir)) != NULL)
    {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        // Read the directory entries
        while ((duplicata = readdir(dir)) != NULL)
        {
            if (entry->d_ino == duplicata->d_ino)
            {
                continue;
            }

            if (JaGravouElemento(mat, entry->d_ino, duplicata->d_ino))
            {
                continue;
            }
            int valor = CalculaCossenoVetores();

            if (!valor)
            {
                continue;
            }
            AdicionaElemento(mat, entry->d_ino, duplicata->d_ino);
        }
    }
    return EXIT_SUCCESS;
}
