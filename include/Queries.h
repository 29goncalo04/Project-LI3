//módulo da execução das interrogações
// módulo responsável por implementar a lógica das 
//interrogações, delegando responsabilidades aos respetivos catálogos conforme necessário

#ifndef QUERIES_H
#define QUERIES_H

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Data_Types_&_Data_Structures.h"

extern int num_linhas_PassengersXairport;
extern PassengersXairport *passengersXairport_array;

void swap_contador(int *a, int *b);
void swapStrings(char **str1, char **str2);

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

int compare_hotels (const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array das reservas
    //        para o ordenar por data de início (ou id, caso a data seja igual)

int is_date_between (char *date, char *i, char *f);
    //     |->função que verifica se uma data (date) está entre duas outras datas (i e f)

int compare_flights (const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array dos voos
    //        para o ordenar por data de partida (ou id, caso a data seja igual)

void free_flight_id_passenger(Flight_id_passenger *flight_id_passenger_array, int num_flights_passenger_id);
    //     |->função responsável por fazer free do array com os id's dos 
    //        voos em que um passageiro voou

void free_flight_aux(Flight_aux *flight_aux_array, int num_flights_passenger_id);
    //     |->função responsável por fazer free do array com os parâmetros dos 
    //        voos em que um passageiro voou

void free_reservation_aux(Reservation_aux *reservation_aux_array, int num_reservations);
    //     |->função responsável por fazer free do array com os parâmetros das 
    //        reservas que um utilizador fez

void free_PassengersXairport(PassengersXairport *passengersXairport_array, int num_linhas_PassengersXairport);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de passengersXairport, e libera elemento a elemento
    
void free_idXname(idXname *idXname_array, int num_linhas_idXname);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de ideXname, e libera elemento a elemento

void free_hotel_aux(hotel_aux *hotel_aux_array, int num_hotels);
    //     |->função responsável por fazer free do array com os parâmetros das 
    //        reservas de um dado hotel

void free_flight_date_aux (flight_date_aux *flight_date_aux_array, int num_flights);
    //     |->função responsável por fazer free do array com os parâmetros dos 
    //        voos com origem num dado aeroporto

void free_Mediana(Mediana *mediana_array, int num_medianas);
    //     |->função responsável por fazer free do array com as medianas de todos os aeroportos 

Flight_id_passenger create_flight_id(char *flight_id);
    //     |->função que cria um elemento individual do array de id's de voos
    //        de um passageiro

Flight_aux create_flight_aux(char *flight_id, char *schedule_departure_date, int exists_argument2);
    //     |->função que cria um elemento individual do array de voos de um passageiro

Reservation_aux create_reservation_aux(char *reservation_id, char *begin_date, int exists_argument2);
    //     |->função que cria um elemento individual do array de reservas de um utilizador

PassengersXairport create_PassengersXairport(char* origin, int passengers);
    //     |->função que cria um elemento individual do array de passengersXairport
    //        que guarda o origin e o número de passageiros num determinado voo

hotel_aux create_hotel_aux (char *id, char *begin_date, char *end_date, char *user_id, char *rating, double total_price);
    //     |->função que cria um elemento individual do array das reservas de um hotel

flight_date_aux create_flight_date_aux (char *id, char *schedule_departure_date, char *destination, char *airline, char *plane_model);
    //     |->função que cria um elemento individual do array dos voos com origem num dado aeroporto

void identify_query(char* path);
    //     |->função responsável por identificar
    //        o id da query que o comando chama

Mediana create_mediana (char *airport, int mediana);
    //     |->função que cria um elemento individual do array de medianas dos aeroportos

char *only_date(char *schedule_departure_date);
    //     |->função responsável por retornar apenas a data após ler a data 
    //        prevista de partida que inicialmente também contém as horas

void insertionSort_flights(Flight_aux *flight_aux_array, int size);
    //     |->função responsável por ordenar o array que tem as informações 
    //        de voo em que um passageiro voou

void insertionSort_medianas(Mediana *mediana_array, int num_medianas);
    //     |->função responsável por ordenar o array que tem as medianas 
    //        dos vários aeroportos

int calculate_mediana(int *atrasos, int num_atrasos);
    //     |->função responsável por calcular a mediana de um aeroporto 

void query1(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 1

int compare_date_time2(char *i, char *f);
    //     |->função que compara duas datas para saber qual a mais antiga

void query2(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 2

void query3(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 3

void query4(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 4

void query5 (char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 5

void query6(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 6

void query7(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 7

void query9(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 9



#endif 