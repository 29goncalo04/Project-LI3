//módulo de output dos dados
//módulo no qual é realizada a escrita dos resultados de cada instrução do ficheiro de comandos para a respetiva saída (consola ou ficheiro)

#ifndef OUTPUT_QUERIES_H
#define OUTPUT_QUERIES_H

#include "../include/Data_Types_&_Data_Structures.h"

void create_output(int n, int conteudo);
    //     |->função responsável por criar os outputs

void outputs_query1_flights (Flight *flight_array_valid, Contador_id *contador_array, int wanted_id, int wanted_id_2, int index_line, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 1 com um voo como argumento

void outputs_query1_reservations (Reservation *reservation_array_valid, char *breakfast, int wanted_id, int index_line, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 1 com uma reserva como argumento

void outputs_query1_users (User *user_array_valid, double total_spent, int reservations, int wanted_id, int index_line, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 1 com um utilizador como argumento

void outputs_query2 (Flight_aux *flight_aux_array, Reservation_aux *reservation_aux_array, int index_line, char *argument2, int num_flights_passenger_id, int num_reservations, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 2

void outputs_query3 (double media, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 3

void outputs_query4 (hotel_aux *hotel_aux_array, int index_line, int num_hotels, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 4

void outputs_query5 (flight_date_aux *flight_date_aux_array, int index1_line, int num_flights, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 5

void outputs_query6 (PassengersXairport *passengersXairport_array, int index_pXa, int top, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 6

void outputs_query7 (Mediana *mediana_array, int index_line, int N, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 7

void outputs_query9 (idXname *idXname_array, int num_linhas_idXname, int flag, int n);
    //     |->função responsável por escrever nos outputs de todos os comandos que chamam a query 9

#endif