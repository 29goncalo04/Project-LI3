//módulo dos tipos e estruturas de dados
//Tipos e estruturas de dados necessários para a representação e armazenamento de dados, respetivamente

#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_SIZE 100
#define DATE 20231001    /////////

typedef struct {           //struct com os parâmetros dos voos
    char *id;
    char *airline;
    char *plane_model;
    char *total_seats;
    char *origin;
    char *destination;
    char *schedule_departure_date;
    char *schedule_arrival_date;
    char *real_departure_date;
    char *real_arrival_date;
    char *pilot;
    char *copilot;
    char *notes;
    int validation;
} Flight;


typedef struct {       //struct com os parâmetros dos passageiros
    char *flight_id;
    char *user_id;
    int validation_flight;
    int validation;
} Passenger;


typedef struct {           //struct com os parâmetros das reservas
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    char *hotel_stars;
    char *city_tax;
    char *address;
    char *begin_date;
    char *end_date;
    char *price_per_night;
    char *includes_breakfast;
    char *room_details;
    char *rating;
    char *comment;
    int validation;
} Reservation;


typedef struct {            //struct com os parâmetros dos utilizadores
    char *id;
    char *name;
    char *email;
    char *phone_number;
    char *birth_date;
    char *sex;
    char *passport;
    char *country_code;
    char *address;
    char *account_creation;
    char *pay_method;
    char *account_status;
    int validation;
} User;


/*typedef struct flights_valid {
    char* id;
    char* airline;
    char* plane_model;
    char* total_seats;
    char* origin;
    char* destination;
    char* schedule_departure_date;
    char* schedule_arrival_date;
    char* real_departure_date;
    char* real_arrival_date;
    char* pilot;
    char* copilot;
    char* notes;
    int validation;
    struct flights_valid* next;
} flights_valid;

typedef struct flights_invalid {
    char* id;
    char* airline;
    char* plane_model;
    char* total_seats;
    char* origin;
    char* destination;
    char* schedule_departure_date;
    char* schedule_arrival_date;
    char* real_departure_date;
    char* real_arrival_date;
    char* pilot;
    char* copilot;
    char* notes;
    int validation;
    struct flights_invalid* next;
} flights_invalid;*/


typedef struct {       //struct com os dados do array de contadores
    char *id_flight;
    int contador;
} Contador_id;


typedef struct {       //struct com os id's dos voos de um passageiro
    char *flight_id;
} Flight_id_passenger;

typedef struct{     //struct com os pârametros do voo de um passageiro
    char *flight_id;
    char *schedule_departure_date;
    char *type;
} Flight_aux;

typedef struct{     //struct com os pârametros da reserva de um passageiro
    char *reservation_id;
    char *begin_date;
    char *type;
} Reservation_aux;
 


#endif 