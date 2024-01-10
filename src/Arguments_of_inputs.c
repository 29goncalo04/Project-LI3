#include <stdlib.h>
#include <string.h>

#include "../include/Arguments_of_inputs.h"

char* arguments_query1(char *line, int i, int *index_line){
    *index_line = i;
    for (; line[*index_line]== ' ' || line[*index_line]=='"'; (*index_line)++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j = *index_line; line[j]!='\0' && line[j]!='\n' ; j++, argument_length++);  //conta o tamanho do argumento
    char *argument = (char*)malloc((argument_length + 1) * sizeof(char));
    for (int k=0, j = *index_line; k<argument_length; k++, j++) argument[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    argument[argument_length] = '\0';
    return argument;
}

char* arguments_query2(char *line, int i, int *exists_argument2, char **argument2, int *index_line) {
    *index_line = i;
    for (; line[*index_line] == ' ' || line[*index_line] == '"'; (*index_line)++);   // encontra o índice do primeiro argumento ignorando os espaços e as aspas
    int argument1_length = 0;
    int argument2_length = 0;
    for (int j = *index_line; line[j] != '\0' && line[j] != '\n' && line[j] != ' '; j++, argument1_length++);
    char *argument1 = (char*)malloc((argument1_length + 1) * sizeof(char));
    for (int k = 0, j = *index_line; k < argument1_length; k++, j++) argument1[k] = line[j];   // copia o argumento da query para um array que guarda esse argumento
    argument1[argument1_length] = '\0';
    int index2_line = *index_line;
    for (; line[index2_line + argument1_length] == ' '; index2_line++);  // vai encontrar o índice do segundo argumento caso exista
    free(*argument2);
    *argument2 = strdup("");  // reinicializa argument2
    if (line[index2_line + argument1_length] != '\0' && line[index2_line + argument1_length] != '\n') {   // existe segundo argumento para ler
        for (int j = index2_line + argument1_length; line[j] != '\0' && line[j] != '\n' && line[j] != ' '; j++, argument2_length++);  // calcula o tamanho do segundo argumento
        char *argument2_aux = (char*)malloc((argument2_length + 1) * sizeof(char));
        for (int k = 0, j = index2_line + argument1_length; k < argument2_length; k++, j++) argument2_aux[k] = line[j];
        argument2_aux[argument2_length] = '\0';
        free(*argument2);
        *argument2 = strdup(argument2_aux);
        *exists_argument2 = 1;
        free(argument2_aux);
    }
    return argument1;
}

char* arguments_query3(char *line, int i, int *index_line){
    *index_line = i;
    for (; line[*index_line]== ' ' || line[*index_line] == '"'; (*index_line)++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j = *index_line; line[j] != '\0' && line[j] != '\n'; j++, argument_length++);  //conta o tamanho do argumento
    char *argument = (char*)malloc((argument_length + 1) * sizeof(char));
    for (int k = 0, j = *index_line; k < argument_length; k++, j++) argument[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    argument[argument_length] = '\0';
    return argument;
}

char* arguments_query4(char *line, int i, int *index_line){
    *index_line = i;
    for (; line[*index_line] == ' ' || line[*index_line] == '"'; (*index_line)++);   // encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j = *index_line; line[j]!='\0' && line[j] != '\n'; j++, argument_length++);  // conta o tamanho do argumento
    char *argument = (char*)malloc((argument_length + 1) * sizeof(char));
    for (int k=0, j = *index_line; k<argument_length; k++, j++) argument[k] = line[j];   // opia o argumento da query (id) para o array que guarda esse argumento
    argument[argument_length] = '\0';
    return argument;
}

char* arguments_query5(char *line, int i, int *index1_line, char **arg_begin_date, char **arg_end_date){
    *index1_line = i;
    for (; line[*index1_line] == ' ' || line[*index1_line] == '"'; (*index1_line)++);   // encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int arg_origin_length = 0;
    for (int j = *index1_line; line[j]!='\0' && line[j] != '\n' && line[j] != ' '; j++, arg_origin_length++);  // conta o tamanho do primeiro argumento (origin)
    char *arg_origin = (char*)malloc((arg_origin_length + 1) * sizeof(char)); // array que vai guardar o primeiro argumento da query
    for (int k=0, j = *index1_line; k<arg_origin_length; k++, j++) arg_origin[k] = line[j];   // copia o primeiro argumento da query para o array que guarda esse argumento
    arg_origin[arg_origin_length] = '\0';
    
    int index2_line = *index1_line + arg_origin_length; // index2_line = 2+3 = 5
    for (; line[index2_line] == ' '; index2_line++);  // encontra o indice do segundo argumento
    int arg_begin_date_length = 0;
    if (line[index2_line] == '"') {  // caso seja data com hora
        index2_line++;
        for (int j=index2_line; line[j] != '"'; j++, arg_begin_date_length++);  //conta o tamanho do segundo argumento (begin_date)
    }
    else {  // caso seja apenas data
        for (int j=index2_line; line[j] != ' '; j++, arg_begin_date_length++);  // conta o tamanho do segundo argumento (begin_date)
    }
    char *arg_begin_date_aux = (char*)malloc((arg_begin_date_length + 1) * sizeof(char));
    for (int k=0, j=index2_line; k<arg_begin_date_length; k++, j++) arg_begin_date_aux[k] = line[j];   // copia o segundo argumento da query para o array que guarda esse argumento
    arg_begin_date_aux[arg_begin_date_length] = '\0';
    free(*arg_begin_date);
    *arg_begin_date = strdup(arg_begin_date_aux);
    free(arg_begin_date_aux);

    int index3_line = index2_line + arg_begin_date_length;
    for (; line[index3_line] == ' ' || line[index3_line] == '"'; index3_line++);  // encontra o indice do terceiro argumento
    int arg_end_date_length = 0;
    if (line[index3_line - 1] == '"') {  // caso seja data com hora
        for (int j=index3_line; line[j] != '"'; j++, arg_end_date_length++);  //conta o tamanho do terceiro argumento (end_date)
    }
    else {  // caso seja apenas data
        for (int j=index3_line; line[j] != '\0' && line[j] != '\n'; j++, arg_end_date_length++);  // conta o tamanho do terceiro argumento (end_date)
    }
    char *arg_end_date_aux = (char*)malloc((arg_end_date_length + 1) * sizeof(char));
    for (int k=0, j=index3_line; k<arg_end_date_length; k++, j++) arg_end_date_aux[k] = line[j];   // copia o terceiro argumento da query para o array que guarda esse argumento
    arg_end_date_aux[arg_end_date_length] = '\0';
    free(*arg_end_date);
    *arg_end_date = strdup(arg_end_date_aux);
    free(arg_end_date_aux);

    return arg_origin;
}

char* arguments_query6(char *line, int i, int *index_line){
    *index_line = i;
    for (; line[*index_line] == ' '; (*index_line)++);
    int l_date = 0, j;
    for (j = *index_line; line[j] != ' '; j++, l_date++);  //conta o tamanho do argumento
    char *date = (char*)malloc((l_date + 1) * sizeof(char));
    for (int k = 0, j = *index_line; k < l_date; k++, j++) date[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    date[l_date] = '\0';
    return date;
}

char* arguments_query7(char *line, int i, int *index_line){
    *index_line = i;
    for (; line[*index_line]==' ' || line[*index_line]=='"'; (*index_line)++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j = *index_line; line[j]!='\0' && line[j]!='\n' && line[j]!='"'; j++, argument_length++);  //conta o tamanho do argumento
    char *argument = (char*)malloc((argument_length + 1) * sizeof(char));
    for (int k=0, j = *index_line; k<argument_length; k++, j++) argument[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    argument[argument_length] = '\0';
    return argument;
}

char* arguments_query9(char *line, int i, int *index_line){
    *index_line = i;
    for (; line[*index_line]==' ' || line[*index_line]=='"'; (*index_line)++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j = *index_line; line[j]!='\0' && line[j]!='\n' && line[j]!='"'; j++, argument_length++);  //conta o tamanho do argumento
    char *name = (char*)malloc((argument_length + 1) * sizeof(char));
    for (int k=0, j = *index_line; k<argument_length; k++, j++) name[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    name[argument_length] = '\0';
    return name;
}