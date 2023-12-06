//módulo dos argumentos dos inputs
// módulo responsável por identificar quais os argumentos dos inputs
//consoante o número da query

#ifndef ARGUMENTS_OF_INPUTS_H
#define ARGUMENTS_OF_INPUTS_H

char* arguments_query1(char *line, int i, int *index_line);

char* arguments_query2(char *line, int i, int *exists_argument2, char **argument2, int *index_line);

char* arguments_query3(char *line, int i, int *index_line);

char* arguments_query4(char *line, int i, int *index_line);

char* arguments_query5(char *line, int i, int *index1_line, char **arg_begin_date, char **arg_end_date);

char* arguments_query6(char *line, int i, int *index_line);

char* arguments_query7(char *line, int i, int *index_line);

char* arguments_query9(char *line, int i, int *index_line);

#endif