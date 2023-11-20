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
    if (argc != 3)
    {
        printf("Erro ao receber o path do arquivo com os codigos dos documentos.\n");
        return EXIT_FAILURE;
    }

    // Open the directory
    DIR *dir_1 = opendir(argv[1]);
    if (dir_1 == NULL)
    {
        printf("Erro ao abrir o diretorio %s.\n", argv[1]);
        return 1;
    }

     DIR *dir_2 = opendir(argv[1]);
    if (dir_2 == NULL)
    {
        printf("Erro ao abrir o diretorio %s.\n", argv[1]);
        return 1;
    }

    struct dirent *entry_1;
    struct dirent *entry_2;


    // Read the directory entries
    while ((entry_1 = readdir(dir_1)) != NULL)
    {

            // Read the directory entries
        while ((entry_2 = readdir(dir_2)) != NULL)
        {
            // Skip "." and ".." entries
            if (strcmp(entry_1->d_name, ".") == 0 || strcmp(entry_1->d_name, "..") == 0)
            {
                continue;
            }

            if (entry_1->d_ino == entry_2->d_ino)
            {
                continue;
            }

        // Construct the full path to the file
        char full_path_1[1024];
        snprintf(full_path_1, sizeof(full_path_1), "%s/%s", argv[1], entry_1->d_name);
        // Open the file
        FILE *file_1 = fopen(full_path_1, "rb");
        if (file_1 == NULL)
        {
            perror("fopen");
            closedir(dir_1);
            return EXIT_FAILURE;
        }
            // Construct the full path to the file
        char full_path_2[1024];
        snprintf(full_path_2, sizeof(full_path_2), "%s/%s", argv[1], entry_2->d_name);
        // Open the file
        FILE *file_2 = fopen(full_path_2, "rb");
        if (file_2 == NULL)
        {
            perror("fopen");
            closedir(dir_2);
            return EXIT_FAILURE;
        }

        float valor =  CalculaSimilaridade(file_1, file_2);

        if (valor)
        {
            fwrite();
        }

        // Close the file
        fclose(file_1);
        fclose(file_2);
    }

    // Close the directory
    closedir(dir_1);

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
