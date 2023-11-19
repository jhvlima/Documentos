#include <stdio.h>

int main()
{
    FILE *matriz = fopen("sim_cosseno.bin", "rb");
    if (matriz == NULL)
    {
        perror("fopen");
        return 1;
    }

    float valor;

    // Assuming you have a similar iteration logic
    // You need to adapt the following loop based on your specific requirements
    while (fread(&valor, sizeof(float), 1, matriz) == 1)
    {
        // Assuming you want to print each value
        printf("%f\n", valor);
    }

    fclose(matriz);

    return 0;
}
