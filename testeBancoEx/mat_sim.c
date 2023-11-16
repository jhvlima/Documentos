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

    // Read the directory entries
    while ((entry = readdir(dir)) != NULL)
    {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
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

    return EXIT_SUCCESS;
}
