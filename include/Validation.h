//Módulo de validação dos dados

#ifndef VALIDATION_H
#define VALIDATION_H

#include "../include/Statistics.h"
#include "../include/Catalogs.h"

void validate_passenger(Passenger *nova, char parametros[][FIELD_SIZE], int flight_validation);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de passageiros, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

void validate_flight(Flight *nova, char parametros[][FIELD_SIZE], Contador_id *contador_array, int num_linhas_contador);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de voos, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

void validate_user(User *nova, char parametros[][FIELD_SIZE]);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de utilizadores, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

void validate_reservation(Reservation *nova, char parametros[][FIELD_SIZE]);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de reservas, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0


#endif