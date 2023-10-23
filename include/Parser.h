//módulo de parsing dos dados
//módulo no qual é realizada a leitura dos ficheiros de entrada CSV e é efetuado um parsing genérico;

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Data_Types_&_Data_Structures.h"


void free_flight(Flight_temp *flight_array, int num_linhas);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de voos, e libera elemento a elemento

void free_passenger(Passenger_temp *passenger_array, int num_linhas);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de passageiros, e libera elemento a elemento

void free_reservation(Reservation_temp *reservation_array, int num_linhas);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de reservas, e libera elemento a elemento

void free_user(User_temp *user_array, int num_linhas);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de utilizadores, e libera elemento a elemento

void free_contador(Contador_id *contador_array, int num_linhas_contador);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de contador de passageiros num voo, e libera elemento a elemento

Flight_temp create_flight(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de voos
    //        com todos os respetivos parâmetros, e a função "strdup" 
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

Passenger_temp create_passenger(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de passageiros
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o  

Reservation_temp create_reservation(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de reservas
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

User_temp create_user(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de utilizadores
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

Contador_id create_contador(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de contadores
    //        que guarda o número de passageiros num determinado voo

void validate_flight(Flight_temp *nova, char parametros[][FIELD_SIZE], Contador_id *contador_array, int num_linhas_contador);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de voos, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

void validate_user(User_temp *nova, char parametros[][FIELD_SIZE]);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de utilizadores, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0


void open_files();


#endif 