//módulo da execução das interrogações
// módulo responsável por implementar a lógica das 
//interrogações, delegando responsabilidades aos respetivos catálogos conforme necessário

#ifndef QUERIES_H
#define QUERIES_H

#include "../include/Aux_structs.h"

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

Mediana create_mediana (char *airport, int mediana);
    //     |->função que cria um elemento individual do array de medianas dos aeroportos

void query1(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 1

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