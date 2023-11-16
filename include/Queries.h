//módulo da execução das interrogações
// módulo responsável por implementar a lógica das 
//interrogações, delegando responsabilidades aos respetivos catálogos conforme necessário

#ifndef QUERIES_H
#define QUERIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Data_Types_&_Data_Structures.h"

int delay(char *schedule, char *real);
    //     |->função responsável por calcular a diferença de segundos entre
    //        a hora estimada de partida e a hora real de partida do voo

int nights(char *begin, char *end);
    //     |->função responsável por calcular o número de noites
    //        disponíveis na reserva de um utilizador

double total_price(char *price_per_night, int nights, char *city_tax);
    //     |->função responsável por calcular os gastos numa reserva

int age_user(char *birth_date);
    //     |->função responsável por calcular a idade de um utilizador

int number_of_flights(char *user);
    //     |->função responsável por calcular o número de voos
    //        em que um utilizador andou 

void free_flight_id_passenger(Flight_id_passenger *flight_id_passenger_array, int num_flights_passenger_id);
    //     |->função responsável por fazer free do array com os id's dos 
    //        voos em que um passageiro voou

void free_flight_aux(Flight_aux *flight_aux_array, int num_flights_passenger_id);
    //     |->função responsável por fazer free do array com os parâmetros dos 
    //        voos em que um passageiro voou

void free_reservation_aux(Reservation_aux *reservation_aux_array, int num_reservations);
    //     |->função responsável por fazer free do array com os parâmetros das 
    //        reservas que um utilizador fez

Flight_id_passenger create_flight_id(char *flight_id);
    //     |->função que cria um elemento individual do array de id's de voos
    //        de um passageiro

Flight_aux create_flight_aux(char *flight_id, char *schedule_departure_date, int exists_argument2);
    //     |->função que cria um elemento individual do array de voos de um passageiro

Reservation_aux create_reservation_aux(char *reservation_id, char *begin_date, int exists_argument2);
    //     |->função que cria um elemento individual do array de reservas de um utilizador

void identify_query(char* path);
    //     |->função responsável por identificar
    //        o id da querie que o comando chama

char *only_date(char *schedule_departure_date);
    //     |->função responsável por retornar apenas a data após ler a data 
    //        prevista de partida que inicialmente também contém as horas

void insertionSort_flights(Flight_aux *flight_aux_array, int size);
    //     |->função responsável por ordenar o array que tem as informações 
    //        de voo em que um passageiro voou

void query1(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 1

void query2(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 2

void query3(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 3



#endif 