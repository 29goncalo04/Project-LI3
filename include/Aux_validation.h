//módulo de funções auxiliares para a validação dos dados

#ifndef AUX_VALIDATION_H
#define AUX_VALIDATION_H

#include "../include/Statistics.h"

int compare_date_time (char *i, char *f);
    //    |->função que compara duas datas e retorna 1 caso a primeira data seja a mais antiga

int compare_date_time3 (const char *i, const char *f);

int verify_email (char *e);
    //    |->função que verifica se um email que lhe é passado como argumento é válido ou não de acordo com as regras especificadas

int verify_account_status(char *status);
    //    |->função que verifica se o status de um utilizador é ativo (1) ou inativo (0) ou for inválido (2)

int verify_airport (char *airport);
    //    |->função que verifica se o nome dum aeroporto tem 3 letras 

void toLowerCase(char *str);
     //    |->função que passa uma string para caracteres em minuscula

void toUpperCase(char *str);
     //    |->função que passa uma string para caracteres em maiuscula

int verify_breakfast(char *breakfast);
    //    |->função que verifica se o breakfast está incluido (1) ou não (0) ou é inválido (2) 

int verify_country_code (char *c);
    //    |->função que verifica se o country_code é constituído por exatamente duas letras

int compare_seats_passengers (char *seats, int num_passengers);
    //    |->função que compara o número de assentos num avião com o número de passageiros nesse mesmo avião

int verify_hotel_stars (char *s);
    //    |->função que verifica se o número de estrelas de um hotel é válido

int verify_city_tax (char *t);
    //    |->função que verifica se o imposto que se paga numa cidade é válido 

char* strnCpy(char *d, char *s, int n, int p);
    //    |->função semelhante à "strcpy" mas esta modificada consegue copiar uma string para uma posição específica de outra string

int check_date(char *d);
    //    |->função que verifica se uma data é válida

int check_time(char *t);
    //    |->função que verifica se uma hora é válida

int check_dateWtime(char *dateT);
    //    |->função que verifica se uma data com hora é válida

int check_price_per_night(char *p);
    //    |->função que verifica se o preço por noite de estadia num hotel é válido

int check_reserva_rating(char *r);
    //    |->função que verifica se as classificações de reserva de um hotel são válidas

int check_length(char *s);
    //    |->função que verifica se uma string é vazia ou não

#endif