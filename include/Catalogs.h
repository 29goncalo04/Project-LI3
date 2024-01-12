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

#define NUM_LINHAS_VALID_USER 2000003
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

typedef struct {           //struct com os parâmetros das reservas
    char *id;
    int stars;
    char *begin_date;
    char *end_date;
    int price_per_night;
    int rating;
} Hotel;

typedef struct HNo {
    Hotel hotel;
    struct HNo *prox;
} HNo;

typedef struct {
    HNo *init;
} HList;

#define NUM_LINHAS_VALID_HOTEL 6000000
extern HList hotel_array_valid[NUM_LINHAS_VALID_HOTEL];

Hotel create_hotel(char *hotel_id, int stars, char *begin_date, char *end_date, int price_per_night, int rating);
    //     |->função que cria um elemento individual do array de hotels
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o

void create_array_hotels(char *hotel_id, int stars, char *begin_date, char *end_date, int price_per_night, int rating);

typedef struct FNo FNo;
typedef struct FList FList;
#define NUM_LINHAS_VALID_FLIGHT 200000
FList* get_flight_array_valid(int pos);
FList* get_all_flight_array();
void set_flight_id(FNo* FNo, const char* id);
void set_flight_airline(FNo* FNo, const char* airline);
void set_flight_plane_model(FNo* FNo, const char* plane_model);
void set_flight_total_seats(FNo* FNo, const char* total_seats);
void set_flight_origin(FNo* FNo, const char* origin);
void set_flight_destination(FNo* FNo, const char* destination);
void set_flight_schedule_departure_date(FNo* FNo, const char* schedule_departure_date);
void set_flight_schedule_arrival_date(FNo* FNo, const char* schedule_arrival_date);
void set_flight_real_departure_date(FNo* FNo, const char* real_departure_date);
void set_flight_real_arrival_date(FNo* FNo, const char* real_arrival_date);
void set_flight_passengers(FNo* FNo, int passengers);
void set_flight_delay_time(FNo* FNo, int delay_time);
void set_flight_validation(FNo* FNo, int validation);
void set_flight_prox(FNo* FNo);
FNo* getFListInit(FList* FList);
FNo* create_flight(char parametros[][FIELD_SIZE]);        
const char* get_flight_id(FNo* FNo);
const char* get_flight_airline(FNo* FNo);
const char* get_flight_plane_model(FNo* FNo);
const char* get_flight_total_seats(FNo* FNo);
const char* get_flight_origin(FNo* FNo);
const char* get_flight_destination(FNo* FNo);
const char* get_flight_schedule_departure_date(FNo* FNo);
const char* get_flight_schedule_arrival_date(FNo* FNo);
const char* get_flight_real_departure_date(FNo* FNo);
const char* get_flight_real_arrival_date(FNo* FNo);
int get_flight_passengers(FNo* FNo);
int get_flight_delay_time(FNo* FNo);
FNo* get_flight_prox(FNo* FNo);
void flights_hash_sort(FList *flight_array_valid, FList list);
void create_array_flights(char parametros[][FIELD_SIZE]);
void free_list_flight(FNo *nodo);
void free_flight_valid(FList *flight_array_valid, int num_linhas_valid);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de voos, e libera elemento a elemento

void create_array_passengers(char parametros[][FIELD_SIZE]);

#endif