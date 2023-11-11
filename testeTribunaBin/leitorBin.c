#include <stdio.h>

typedef struct {
    long int integer_data;
    float float_data;
} Data;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s input_binary_file\n", argv[0]);
        return 1;
    }

    char *input_file_name = argv[1];
    FILE *input_file = fopen(input_file_name, "rb");

    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    Data data;

    while (fread(&data, sizeof(Data), 1, input_file) == 1) {
        printf("Integer: %ld, Float: %f\n", data.integer_data, data.float_data);
    }

    fclose(input_file);

    return 0;
}
