#include <stdio.h>
#include <stdlib.h>

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
