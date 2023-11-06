//módulo de parsing dos dados
//módulo no qual é realizada a leitura dos ficheiros de entrada CSV e é efetuado um parsing genérico;

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Data_Types_&_Data_Structures.h"


void free_flight(Flight *flight_array, int num_linhas);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de voos, e libera elemento a elemento

void free_passenger(Passenger *passenger_array, int num_linhas);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de passageiros, e libera elemento a elemento

void free_reservation(Reservation *reservation_array, int num_linhas);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de reservas, e libera elemento a elemento

void free_user(User *user_array, int num_linhas);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de utilizadores, e libera elemento a elemento

void free_contador(Contador_id *contador_array, int num_linhas_contador);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de contador de passageiros num voo, e libera elemento a elemento

Flight create_flight(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de voos
    //        com todos os respetivos parâmetros, e a função "strdup" 
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

Passenger create_passenger(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de passageiros
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o  

Reservation create_reservation(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de reservas
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

User create_user(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de utilizadores
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

Contador_id create_contador(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de contadores
    //        que guarda o número de passageiros num determinado voo

void validate_flight(Flight *nova, char parametros[][FIELD_SIZE], Contador_id *contador_array, int num_linhas_contador);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de voos, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

void validate_user(User *nova, char parametros[][FIELD_SIZE]);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de utilizadores, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

void validate_reservation(Reservation *nova, char parametros[][FIELD_SIZE]);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de reservas, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

void free_all();
    //    |->função responsável por libertar toda a memória alocada durante o programa

void create_files();
    //    |->função responsável por criar os ficheiros de erro e escrever lá as entradas inválidas

void open_files();


#endif 