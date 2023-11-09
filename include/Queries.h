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

void identify_query();
    //     |->função responsável por identificar
    //        o id da querie que o comando chama

void query1(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 1



#endif 