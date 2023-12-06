//módulo para catálogos de dados
//módulos responsáveis por armazenar e processar informações
//das diversas entidades, como utilizadores, voos, etc.

#ifndef CATALOGS_H
#define CATALOGS_H

#define FIELD_SIZE 100

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

extern int num_linhas_valid_user;
extern int num_linhas_invalid_user;
extern User *user_array_valid;
extern User *user_array_invalid;

User create_user(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de utilizadores
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

void create_array_users(char parametros[][FIELD_SIZE]);


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

extern int num_linhas_valid_reservation;
extern int num_linhas_invalid_reservation;
extern Reservation *reservation_array_valid;
extern Reservation *reservation_array_invalid;

Reservation create_reservation(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de reservas
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

void create_array_reservations(char parametros[][FIELD_SIZE]);




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

extern int num_linhas_valid_flight;
extern int num_linhas_invalid_flight;
extern Flight *flight_array_valid;
extern Flight *flight_array_invalid;

Flight create_flight(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de voos
    //        com todos os respetivos parâmetros, e a função "strdup" 
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

void create_array_flights(char parametros[][FIELD_SIZE]);



typedef struct {       //struct com os parâmetros dos passageiros
    char *flight_id;
    char *user_id;
    int validation_flight;
    int validation;
} Passenger;

extern int num_linhas_valid_passenger;
extern int num_linhas_invalid_passenger;
extern Passenger *passenger_array_valid;
extern Passenger *passenger_array_invalid;

Passenger create_passenger(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de passageiros
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o  

void create_array_passengers(char parametros[][FIELD_SIZE]);

#endif