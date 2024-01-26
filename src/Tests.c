#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../include/Tests.h"

void find_equal_files(char* path3){
    FILE *output_tests = fopen("../trabalho-pratico/Resultados/output_tests.csv", "w");
    DIR *dir_path3 = opendir(path3);
    DIR *dir_resultados = opendir("../trabalho-pratico/Resultados");
    struct dirent *entry_path3;

    while ((entry_path3 = readdir(dir_path3)) != NULL){   //vai percorrer todos os ficheiros da pasta dos outputs corretos
        if (entry_path3->d_type == DT_REG) {  //verificar se é um arquivo regular
            char file_path3[500];
            snprintf(file_path3, sizeof(file_path3), "%s%s", path3, entry_path3->d_name);
            char file_resultados[500];
            snprintf(file_resultados, sizeof(file_resultados), "../trabalho-pratico/Resultados/%s", entry_path3->d_name);
            FILE *file_resultados_check = fopen(file_resultados, "r");
            if (file_resultados_check != NULL) {    //caso esse ficheiro exista na pasta 'Resultados' vai compará-lo com a solução para esse ficheiro
                fclose(file_resultados_check);
                char *result = compare_files(file_path3, file_resultados);
                if (result == NULL) fprintf(output_tests, "File '%s' is correct.\n", entry_path3->d_name);
                else {
                    if (strcmp(result, "File is empty")==0) fprintf(output_tests, "File '%s' is empty.\n", entry_path3->d_name);
                    else fprintf(output_tests, "File '%s' differs on the line -> %s", entry_path3->d_name, result);
                }
                free(result);
            }
        }
    }
    closedir(dir_path3);
    closedir(dir_resultados);
    fclose(output_tests);
}


char* compare_files(const char *file1, const char *file2){
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    // Verifica se o output de resultado está indevidamente vazio
    int firstChar1 = fgetc(f1);
    int firstChar2 = fgetc(f2);
    if (firstChar1 != EOF && firstChar2 == EOF) {
        fclose(f1);
        fclose(f2);
        return strdup("File is empty");
    }
    char line1[200], line2[200];
    int line = 1;

    while (fgets(line1, sizeof(line1), f1) != NULL && fgets(line2, sizeof(line2), f2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            fclose(f1);
            fclose(f2);
            char *difference = strdup(line2);
            return difference;  // Retorna a linha onde os arquivos são diferentes
        }
        line++;
    }
    // Verifica se os tamanhos dos arquivos são diferentes
    if (fgets(line1, sizeof(line1), f1) != NULL || fgets(line2, sizeof(line2), f2) != NULL) {
        char *difference = strdup(line2);
        fclose(f1);
        fclose(f2);
        return difference;  // Retorna a linha onde os arquivos são diferentes
    }
    fclose(f1);
    fclose(f2);
    return NULL;  // Retorna NULL se os arquivos são iguais
}