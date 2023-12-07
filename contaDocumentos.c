#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SCRIPT_1 "find %s -type f | wc -l"
#define SCRIPT_2 "find %s -type f -name %s | wc -l"

void ContaDocumentos(const char *caminho, const char *parametros)
{
    // Construir o comando usando o caminho fornecido
    char comando[1024];
    char par[256];

    if (parametros == NULL)
    {
        snprintf(comando, sizeof(comando), SCRIPT_1, caminho);
    }
    else
    {
        snprintf(par, sizeof(par), "\"%s\"", parametros);
        snprintf(comando, sizeof(comando), SCRIPT_2, caminho, par);
    }

    printf("Executando: %s\n", comando);
    int resultado = system(comando);

    if (resultado == -1)
    {
        perror("Erro ao executar o comando");
    }
}

int main(int argc, char *argv[])
{
    int opt;                  // caracter lido pelo getopt
    extern int optind;        // indice do proximo elmento do argv a ser processado
    extern char *optarg;      // aponta para o argumento da opcao atual
    extern int optopt;        // indice da ultima opcao valida
    extern int opterr;        // flag q determina se os erros vao ser printados ou nao
    char *optstring = "p:d:"; // cada carater representa uma opcao, ':' indica que a opcao requer argumento

    opterr = 0; // Suppress automatic error messages

    while ((opt = getopt(argc, argv, "p:d")) != -1)
    {
        switch (opt)
        {
        case 'p':
            // passou o diretorio
            printf("Option p with argument: %s\n", optarg);
            break;
        case 'd':
            // passou o tipo de documento buscado
            printf("Option d with argument: %s\n", optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        default:
            printf("Unexpected error\n");
            break;
        }
    }

    for (int i = optind; i < argc; i++)
    {
        printf("Non-option argument: %s\n", argv[i]);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    // Verificar se foi fornecido um argumento de caminho
    if (argc < 2)
    {
        fprintf(stderr, "Uso: %s <caminho> [parâmetros]\n", argv[0]);
        return 1;
    }

    // Obter o caminho do argumento da linha de comando
    const char *path = argv[1];
    const char *parametros = NULL;

    if (argc >= 2)
    {
        parametros = argv[2];
    }

    // Chamar a função com o caminho fornecido
    ContaDocumentos(path, parametros);

    return 0;
}
