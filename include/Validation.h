//Módulo de validação dos dados

#ifndef VALIDATION_H
#define VALIDATION_H

#include "../include/Statistics.h"
#include "../include/Catalogs.h"

int validate_passenger(char parametros[][FIELD_SIZE]);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de passageiros, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

int validate_flight(char parametros[][FIELD_SIZE]);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de voos, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

int validate_user(char parametros[][FIELD_SIZE]);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de utilizadores, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

int validate_reservation(char parametros[][FIELD_SIZE]);
    //    |->função que verifica parâmetro a parâmetro de cada elemento do array de reservas, e caso algum elemento seja inválido
    //       a função altera o parâmetro que indica se esse elemento é válido ou não para 0

#endif