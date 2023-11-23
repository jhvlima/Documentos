/*
    Esse programa gera um arquivo binario com a similaridade de todos os documentos de um diretrio entre si

    Eh preciso passar no argumento o diretorio com os arquivos com vetores de documentos em formato binario e um arquivo que
    contem a quantidade total de palavras que o banco de palavras possui.

*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

// padrao de impressão binario na matriz de similaridade binária 
typedef struct
{
    int codigo_1; // neste caso os codigos sao os ino dos documentos 
    int codigo_2;
    float valor;
}tSimilaridade;

typedef struct
{
    long int posicao; // duas palavras sao da mesma dimensao se seus valores de posicao sao iguais
    float frequencia; // se for 0 entao, a palavra nao eh gravada
} tDado;

/*
    Gera um arquivo com os arquivos presente no diretorio passado e seus respectivos ino
*/
void listFilesInDirectory(const char *directoryPath)
{
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    if ((dir = opendir(directoryPath)) == NULL)
    {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    FILE *file;
    file = fopen("codigos_documentos.txt", "w");
    while ((entry = readdir(dir)) != NULL)
    {
        char filePath[256]; // Adjust the size as needed
        snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, entry->d_name);

        if (stat(filePath, &fileStat) == 0)
        {
            if (S_ISREG(fileStat.st_mode))
            { // Check if it's a regular file
                fprintf(file, "%s %lu\n", filePath, (unsigned long)fileStat.st_ino);
            }
        }
        else
        {
            perror("Error getting file status");
        }
    }
    fclose(file);
    closedir(dir);
}

/*
    Le o arquivo passado e armazena seu conteudo em um vetor na memoria e retorna o ponteiro do vetor
*/
float *MemorizaVetor(FILE *file, int total_palavras)
{
    tDado palavra;
    float *vet = calloc(1, total_palavras * sizeof(float));

    // while (fscanf(vet_1_file, "%ld %f ", &pos_1, &freq_1) != EOF) // Check if two values were successfully read
    while (fread(&palavra, sizeof(tDado), 1, file) == 1)
    {
        if (palavra.posicao < 0 || palavra.posicao >= total_palavras)
        {
            fprintf(stderr, "Invalid position %ld\n", palavra.posicao);
            free(vet);
            return NULL;
        }
        vet[palavra.posicao] = palavra.frequencia;
        // printf("Read position %ld\n", pos_1);
    }
    if (!feof(file))
    {
        // fscanf did not reach the end of the file, possibly due to a format mismatch
        fprintf(stderr, "Error ao ler um domcumento\n");
        free(vet);
        return NULL;
    }
    return vet;
}

/*
    Calcula o cosseno de dois vetores,

*/
float CalculaCossenoVetores(float *vetor_1, float *vetor_2, int NUM_PALAVRAS)
{
    float ProdutoEscalar = 0, SomaNormaVet_1 = 0, SomaNormaVet_2 = 0, NormaVet_1 = 0, NormaVet_2 = 0;

    for (int i = 0; i < NUM_PALAVRAS; i++)
    {
        // se a palavra possui frequncia igual a 0 em algum dos dois, pula essa iteracao
        if (vetor_1[i] == 0 || vetor_2[i] == 0)
        {
            continue;
        }

        // ProdutoEscalar armazena o somatorio do produto escalar de A vet_1 vet_2, cada iteracao seria uma dimensao do vetor
        ProdutoEscalar = ProdutoEscalar + (vetor_1[i] * vetor_2[i]);
        // SomaNorma armazena o somatorio do quadrado
        SomaNormaVet_1 = SomaNormaVet_1 + pow(vetor_1[i], 2);
        SomaNormaVet_2 = SomaNormaVet_2 + pow(vetor_2[i], 2);
    }

    NormaVet_1 = sqrt(SomaNormaVet_1);
    NormaVet_2 = sqrt(SomaNormaVet_2);

    // se os vetores nao possuem nenhuma palavra igual, o produto escalar eh 0, logo o cosseno eh 0
    if (ProdutoEscalar == 0)
    {
        return 0;
    }
    // senao o cosseno eh calculado
    else
    {
        return ProdutoEscalar / (NormaVet_1 * NormaVet_2);
    }
}

/*
    Calcula a similaridade de dois documentos
*/
float CalculaSimilaridade(FILE *file_1, FILE *file_2, int total_palavras)
{
    float *vet_1 = MemorizaVetor(file_1, total_palavras);
    float *vet_2 = MemorizaVetor(file_2, total_palavras);
    float resultado = CalculaCossenoVetores(vet_1, vet_2, total_palavras);

    if (vet_1 != NULL)
    {
        free(vet_1);
    }
    if (vet_2 != NULL)
    {
        free(vet_2);
    }

    return resultado;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Deve ser passado: %s <diretorio> <universo_palavras.txt>.\n", argv[0]);
        return 1;
    }
    const char *directoryPath = argv[1]; // Replace with your directory path

    //  Le o numero total de palavras no banco de palavras
    FILE *banco_palavras_file;
    const char *banco_palavras_name = argv[2];
    banco_palavras_file = fopen(banco_palavras_name, "r");
    int total_palavras;
    fscanf(banco_palavras_file, "%d", &total_palavras);
    fclose(banco_palavras_file);

    //  Abre o memso diretorio com dois ponteiros diferentes para realizar a iteracao de forma idependente
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

    FILE *matriz;
    tSimilaridade sim;
    matriz = fopen("sim_cosseno.bin", "wb");

    struct dirent *entry_1;
    struct dirent *entry_2;

    int posicao_diretorio_1 = 0, posicao_diretorio_2 = 0;

    printf("Comecou o processo de leitura dos diretorios\n");

    // Read the directory entries
    while ((entry_1 = readdir(dir_1)) != NULL)
    {
        if (strcmp(entry_1->d_name, ".") == 0 || strcmp(entry_1->d_name, "..") == 0 || entry_1->d_type != DT_REG)
        {
            continue;
        }
        posicao_diretorio_2 = posicao_diretorio_1;
        posicao_diretorio_1++;
        // Read the directory entries
        printf("\n");
        printf("LOOP DO %s\n", entry_1->d_name);
        rewinddir(dir_2);
        while ((entry_2 = readdir(dir_2)) != NULL)
        {
            if (posicao_diretorio_2)
            {
                posicao_diretorio_2--;
                continue;
            }
            if (entry_1->d_ino == entry_2->d_ino)
            {
                continue;
            }
            if (strcmp(entry_2->d_name, ".") == 0 || strcmp(entry_2->d_name, "..") == 0 || entry_2->d_type != DT_REG)
            {
                continue;
            }

            //  Se a similaridade desses documentos ainda nao foi guardada entao sera calculada aqui

            // Open the file 1
            char full_path_1[1024];
            snprintf(full_path_1, sizeof(full_path_1), "%s/%s", argv[1], entry_1->d_name);
            FILE *file_1 = fopen(full_path_1, "rb");
            if (file_1 == NULL)
            {
                perror("fopen");
                closedir(dir_1);
                return EXIT_FAILURE;
            }

            // Open the file 2
            char full_path_2[1024];
            snprintf(full_path_2, sizeof(full_path_2), "%s/%s", argv[1], entry_2->d_name);
            FILE *file_2 = fopen(full_path_2, "rb");
            if (file_2 == NULL)
            {
                perror("fopen");
                closedir(dir_2);
                return EXIT_FAILURE;
            }

            printf("file1: %s\n", full_path_1);
            printf("file2: %s\n", full_path_2);

            if (entry_1->d_ino < entry_2->d_ino)
            {
                sim.codigo_1 = entry_1->d_ino;
                sim.codigo_2 = entry_2->d_ino;
            }
            else
            {
                sim.codigo_2 = entry_1->d_ino;
                sim.codigo_1 = entry_2->d_ino;
            }
            
            float valor = CalculaSimilaridade(file_1, file_2, total_palavras);
            if (valor)
            {
                sim.valor = valor;
                fwrite(&sim, sizeof(tSimilaridade), 1, matriz);
                printf("<%s , %s> = %f\n", full_path_1, full_path_2, valor);
            }
            else
            {
                printf("Similaridade 0 \n");
            }
            fclose(file_1);
            fclose(file_2);
        }
    }
    fclose(matriz);
    closedir(dir_1);
    closedir(dir_2);
    return 0;
}
