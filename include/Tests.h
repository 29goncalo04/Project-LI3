//módulo dos testes
//módulo responsável por comparar os outputs esperados com os outputs obtidos

#ifndef TESTS_H
#define TESTS_H

void find_equal_files(char* path3);
    //     |->função que procura o par do ficheiro lido na pasta do path3 na pasta RESULTADOS

char* compare_files(const char *file1, const char *file2);
    //     |->função que compara dois ficheiros e retorna a primeira linha onde eles diferem

#endif