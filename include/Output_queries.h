//módulo de output dos dados
//módulo no qual é realizada a escrita dos resultados de cada instrução do ficheiro de comandos para a respetiva saída (consola ou ficheiro)

#ifndef OUTPUT_QUERIES_H
#define OUTPUT_QUERIES_H

#include "../include/Catalogs.h"
#include "../include/Statistics.h"
#include "../include/Aux_structs.h"

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

void outputs_query2 (Flight_aux *flight_aux_array, Reservation_aux *reservation_aux_array, int index_line, char *argument2, int num_flights_passenger_id, int num_reservations, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 2

void outputs_query3(double med, int flag, int check, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 3

void outputs_query4 (hotel_aux *hotel_aux_array, int index_line, int num_hotels, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 4

void outputs_query5 (flight_date_aux *flight_date_aux_array, int index1_line, int num_flights, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 5

void outputs_query6 (PassengersXairport *passengersXairport_array, int index_pXa, int top, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 6

void outputs_query7 (Mediana *mediana_array, int index_line, int N, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 7

void outputs_query8(int revenue, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 8

void outputs_query9 (idXname *idXname_array, int num_linhas_idXname, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 9

#endif