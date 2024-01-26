//módulo de output dos dados
//módulo no qual é realizada a escrita dos resultados de cada instrução do ficheiro de comandos para a respetiva saída (consola ou ficheiro)

#ifndef OUTPUT_QUERIES_H
#define OUTPUT_QUERIES_H

#include "../include/Catalogs.h"
#include "../include/Queries.h"

void create_output(int check, int n);
    //     |->função responsável por criar os outputs

void outputs_query1_flights (const FNo *pointer, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 1 com um voo como argumento

void outputs_query1_reservations (const RNo *pointer, char *breakfast, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 1 com uma reserva como argumento

void outputs_query1_users (const UNo *pointer, int flag, int check, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 1 com um utilizador como argumento

void outputs_query2_reservations(const int *list, int tam, int flag, int check, int n);
void outputs_query2_flights(const int *list, int tam, int flag, int check, int n);
void outputs_query2_both(const int *list_f, int tam_f, const int *list_r, int tam_r, int flag, int check, int n);

void outputs_query3(double med, int flag, int check, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 3

void outputs_query4(const int *list, int num_reservations, int flag, int check, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 4

void outputs_query5 (char *origin, char *arg_begin_date, char *arg_end_date, const int *list2023, const int *list2022, const int *list2021, int num_flights3, int num_flights2, int num_flights1, int flag, int check, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 5

void outputs_query6 (const int *list, int year, int top, int flag, int n, int tam);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 6

void outputs_query7 (list_mediana *list, int tam, int N, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 7

void outputs_query8(int revenue, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 8

void outputs_query9 (list_users *list, int tam, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 9

void outputs_query10_years(int year, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos sem argumentos que chamam a query 10

void outputs_query10_year(char* year, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos com apenas um ano como argumento que chamam a query 10

void outputs_query10_year_month(char* year, char* month, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos com ano e mês como argumento que chamam a query 10

#endif