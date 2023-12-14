#include <stdio.h>
#include <stdlib.h>

#define SCRIPT_CONTA_DOCS_1 "find %s -type f | wc -l"
#define SCRIPT_CONTA_DOCS_2 "find %s -type f -name %s | wc -l"

#define SCRIPT_CONTA_PALAVRAS_1 "find %s type f -exec sh -c cat {} | wc -w"
#define SCRIPT_CONTA_PALAVRAS_2 "cat $(find %s -type f) | wc -w"

void ContaDocumentos(const char *caminho, const char *parametros)
{
    // Construir o comando usando o caminho fornecido
    char comando[1024];
    char par[256];
    
    if (parametros == NULL)
    {
        sprintf(comando, SCRIPT_CONTA_DOCS_1, caminho);
    }
    else
    {
        sprintf(par, "\"%s\"", parametros);
        sprintf(comando, SCRIPT_CONTA_DOCS_2, caminho, par);
    }

    printf("Executando: %s\n", comando);
    int resultado = system(comando);

    if (resultado == -1)
    {
        perror("Erro ao executar o comando");
    }
}

void ContaPalavras(const char *caminho, const char *parametros)
{
    // Construir o comando usando o caminho fornecido
    char comando[1024];
    char par[256];
    
    if (parametros == NULL)
    {
        sprintf(comando, SCRIPT_CONTA_PALAVRAS_2, caminho);
    }
    else
    {
        sprintf(comando, SCRIPT_CONTA_PALAVRAS_2, caminho, par);
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
    const char *parametros = "";

    if (argc >= 2)
    {
        parametros = argv[2];
    }

    char opcao;
    scanf("%c", &opcao);

    switch (opcao)
    {
    case 'd':
        ContaDocumentos(path, parametros);
        break;
    case 'p':
        ContaPalavras(path, parametros);
        break;
    }

    return 0;
}
