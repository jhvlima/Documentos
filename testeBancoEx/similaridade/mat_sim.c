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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Precisa passar o path do diretorio no argumento.\n");
        return 1;
    }

    // Open the directory
    DIR *dir_1 = opendir(argv[1]);
    DIR *dir_2 = opendir(argv[1]);
    if (dir_1 == NULL || dir_2 == NULL)
    {
        printf("Erro ao abrir o diretorio %s.\n", argv[1]);
        return 1;
    }

    struct dirent *entry_1;
    struct dirent *entry_2;

    // Read the directory entries
    while ((entry_1 = readdir(dir_1)) != NULL)
    {
        while ((entry_2 = readdir(dir_2)) != NULL)
        {
            if (entry_1->d_ino == entry_2->d_ino)
            {
                continue;
            }
            




        // Skip "." and ".." entries
        if (strcmp(entry_1->d_name, ".") == 0 || strcmp(entry_1->d_name, "..") == 0)
        {
            continue;
        }

        // Construct the full path to the file
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", argv[1], entry->d_name);

        // Open the file
        FILE *file = fopen(full_path, "r");
        if (file == NULL)
        {
            perror("fopen");
            closedir(dir);
            return EXIT_FAILURE;
        }

        // Process the file (you can replace this with your own logic)
        printf("Opened file: %s\n", full_path);

        // Close the file
        fclose(file);
    }

    // Close the directory
    closedir(dir);

void GeraMatrizSim(DIR *entrada)
{
    CriaMatriz();
    for (long int i = 0; i < count; i++)// documnto a
    {
        for (long int i = 0; i < count; i++) // documento b
        {
            if (JaFoiGravado(mat,i,j) || EhIgual(i,j))
            {
                continue;
            }
            valor = Sim(i,j);
            if (!valor)
            {
                continue;
            }
            GravaValor(mat, i, j);
        }
    }
}   





    return EXIT_SUCCESS;
}
