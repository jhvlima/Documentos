    fprintf(output_file, "\n");

    fseek(database_file, 0, SEEK_SET);
    // Read a word from the database file
    while (fscanf(database_file, "%s", search_word) != EOF)
    {
        frequencia = 0;
        // volta a o scanf para o inicio do documento
        fseek(input_file, 0, SEEK_SET);
        // Search for the word in the input file
        while (fscanf(input_file, "%f %s", &frequency, palavra_texto) != EOF)
        {
            if (!strcmp(palavra_texto, search_word))
            {
                frequencia = frequency;
            }
        }
        fprintf(output_file, "%d ", frequencia);
    }