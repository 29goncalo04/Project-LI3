//módulo para catálogos de dados
//módulos responsáveis por armazenar e processar informações
//das diversas entidades, como utilizadores, voos, etc.

#ifndef CATALOGS_H
#define CATALOGS_H

#define FIELD_SIZE 100

typedef struct User{            //struct com os parâmetros dos utilizadores
    char *id;
    char *name;
    char *birth_date;
    char *sex;
    char *passport;
    char *country_code;
    char *account_creation;
    char *account_status;
    int reservations;
    int *list_reservations;
    int flights;
    int *list_flights;
    double total_spent;
    int validation;
} User;

typedef struct UNo {
    User user;
    struct UNo *prox;
} UNo;

typedef struct {
    UNo *init;
    int tam;
} UList;

#define NUM_LINHAS_VALID_USER 1000000
extern UList user_array_valid[NUM_LINHAS_VALID_USER]; //um milhão de users validos no pior caso

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
    char *begin_date;
    char *end_date;
    char *price_per_night;
    char *includes_breakfast;
    char *rating;
    int validation;
} Reservation;

typedef struct RNo {
    Reservation reservation;
    struct RNo *prox;
} RNo;

typedef struct {
    RNo *init;
    int tam;
} RList;

#define NUM_LINHAS_VALID_RESERVATION 6000000
extern RList reservation_array_valid[NUM_LINHAS_VALID_RESERVATION];

Reservation create_reservation(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de reservas
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

void create_array_reservations(char parametros[][FIELD_SIZE]);

typedef struct Flight{           //struct com os parâmetros dos voos
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
    int passengers;
    int delay_time;
    int validation;
} Flight;

typedef struct FNo {
    Flight flight;
    struct FNo *prox;
} FNo;

typedef struct {
    FNo *init;
    int tam;
} FList;

#define NUM_LINHAS_VALID_FLIGHT 200000
extern FList flight_array_valid[NUM_LINHAS_VALID_FLIGHT];

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
extern Passenger *passenger_array_valid;

Passenger create_passenger(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de passageiros
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o  

void create_array_passengers(char parametros[][FIELD_SIZE]);

#endif