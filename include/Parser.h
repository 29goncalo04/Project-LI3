//módulo de parsing dos dados
//módulo no qual é realizada a leitura dos ficheiros de entrada CSV e é efetuado um parsing genérico;

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *arquivo;
extern int path_error;

void create_files();
    //    |->função responsável por criar os ficheiros de erro e escrever lá as entradas inválidas

void open_files(char* path);


#endif  