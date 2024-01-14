//módulo para catálogos de dados
//módulos responsáveis por armazenar e processar informações
//das diversas entidades, como utilizadores, voos, etc.

#ifndef CATALOGS_H
#define CATALOGS_H

#define FIELD_SIZE 100


////////////////////////USERS///////////////////////////
typedef struct UNo UNo;
typedef struct UList UList;
#define NUM_LINHAS_VALID_USER 2000003
void set_user_id(UNo* UNo, const char* id);
void set_user_name(UNo* UNo, const char* name);
void set_user_birth_date(UNo* UNo, const char* birth_date);
void set_user_sex(UNo* UNo, const char* sex);
void set_user_passport(UNo* UNo, const char* passport);
void set_user_country_code(UNo* UNo, const char* country_code);
void set_user_account_creation(UNo* UNo, const char* account_creation);
void set_user_account_status(UNo* UNo, const char* account_status);
void set_user_reservations(UNo* UNo, int reservations);
void set_user_list_reservations(UNo* UNo);
void set_user_flights(UNo* UNo, int flights);
void set_user_list_flights(UNo* UNo);
void set_user_total_spent(UNo* UNo, double total_spent);
void set_user_validation(UNo* UNo, int validation);
void set_user_prox(UNo* UNo);
const UList* get_user_array_valid(int pos);
const UNo* getUListInit(const UList* UList);
UNo* create_user(char parametros[][FIELD_SIZE]);
const char* get_user_id(const UNo* UNo);
const char* get_user_name(const UNo* UNo);
const char* get_user_birth_date(const UNo* UNo);
const char* get_user_sex(const UNo* UNo);
const char* get_user_passport(const UNo* UNo);
const char* get_user_country_code(const UNo* UNo);
const char* get_user_account_creation(const UNo* UNo);
const char* get_user_account_status(const UNo* UNo);
int get_user_reservations(const UNo* UNo);
const int* get_user_list_reservations(const UNo* UNo);
int get_user_flights(const UNo* UNo);
const int* get_user_list_flights(const UNo* UNo);
double get_user_total_spent(const UNo* UNo);
int get_user_validation(const UNo* UNo);
const UNo* get_user_prox(const UNo* UNo);
void users_hash_sort(UList *user_array_valid, UList list);
void create_array_users(char parametros[][FIELD_SIZE]);
void free_list_user(const UNo *nodo);
void free_user_valid();





////////////////////////RESERVATIONS///////////////////////////
typedef struct RNo RNo;
typedef struct RList RList;
#define NUM_LINHAS_VALID_RESERVATION 6000000
void set_reservation_id(RNo* RNo, const char* id);
void set_reservation_user_id(RNo* RNo, const char* user_id);
void set_reservation_hotel_id(RNo* RNo, const char* hotel_id);
void set_reservation_hotel_name(RNo* RNo, const char* hotel_name);
void set_reservation_hotel_stars(RNo* RNo, const char* hotel_stars);
void set_reservation_city_tax(RNo* RNo, const char* city_tax);
void set_reservation_begin_date(RNo* RNo, const char* begin_date);
void set_reservation_end_date(RNo* RNo, const char* end_date);
void set_reservation_price_per_night(RNo* RNo, const char* price_per_night);
void set_reservation_includes_breakfast(RNo* RNo, const char* includes_breakfast);
void set_reservation_rating(RNo* RNo, const char* rating);
void set_reservation_validation(RNo* RNo, int validation);
void set_reservation_prox(RNo* RNo);
const RList* get_reservation_array_valid(int pos);
const RNo* getRListInit(const RList* RList);
RNo* create_reservation(char parametros[][FIELD_SIZE]);
const char* get_reservation_id(const RNo* RNo);
const char* get_reservation_user_id(const RNo* RNo);
const char* get_reservation_hotel_id(const RNo* RNo);
const char* get_reservation_hotel_name(const RNo* RNo);
const char* get_reservation_hotel_stars(const RNo* RNo);
const char* get_reservation_city_tax(const RNo* RNo);
const char* get_reservation_begin_date(const RNo* RNo);
const char* get_reservation_end_date(const RNo* RNo);
const char* get_reservation_price_per_night(const RNo* RNo);
const char* get_reservation_includes_breakfast(const RNo* RNo);
const char* get_reservation_rating(const RNo* RNo);
int get_reservation_validation(const RNo* RNo);
const RNo* get_reservation_prox(const RNo* RNo);
void ordena_list_reservations(int ind, const char *date_ind, const char *id_r, int **list, int n);
void reservations_hash_sort(RList *reservation_array_valid, RList list);
void create_array_reservations(char parametros[][FIELD_SIZE]);
void free_list_reservation(const RNo *nodo);
void free_reservation_valid();
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de reservas, e libera elemento a elemento




////////////////////////HOTELS///////////////////////////
typedef struct HNo HNo;
typedef struct HList HList;
#define NUM_LINHAS_VALID_HOTEL 6000000
void set_hotel_id(HNo* HNo, const char* id);
void set_hotel_stars(HNo* HNo, int stars);
void set_hotel_begin_date(HNo* HNo, const char* begin_date);
void set_hotel_end_date(HNo* HNo, const char* end_date);
void set_hotel_price_per_night(HNo* HNo, int price_per_night);
void set_hotel_rating(HNo* HNo, int rating);
void set_hotel_prox(HNo* HNo);
const HList* get_hotel_array_valid(int pos);
const HNo* getHListInit(const HList* HList);
HNo* create_hotel(char *hotel_id, int stars, char *begin_date, char *end_date, int price_per_night, int rating);
    //     |->função que cria um elemento individual do array de hotels
    //        com todos os respetivos parâmetros, e a função "strdup"
    //        aloca a memória necessária que cada parâmetro ocupa e escreve-o
const char* get_hotel_id(const HNo* HNo);
int get_hotel_stars(const HNo* HNo);
const char* get_hotel_begin_date(const HNo* HNo);
const char* get_hotel_end_date(const HNo* HNo);
int get_hotel_price_per_night(const HNo* HNo);
int get_hotel_rating(const HNo* HNo);
const HNo* get_hotel_prox(const HNo* HNo);
void hotels_hash_sort (HList *hotel_array_valid, HList list);
void create_array_hotels(char *hotel_id, int stars, char *begin_date, char *end_date, int price_per_night, int rating);
void free_list_hotel(const HNo *nodo);
void free_hotel_valid();




////////////////////////FLIGHTS///////////////////////////
typedef struct FNo FNo;
typedef struct FList FList;
#define NUM_LINHAS_VALID_FLIGHT 200000
const FList* get_flight_array_valid(int pos);
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
const FNo* getFListInit(const FList* FList);
FNo* create_flight(char parametros[][FIELD_SIZE]);        
const char* get_flight_id(const FNo* FNo);
const char* get_flight_airline(const FNo* FNo);
const char* get_flight_plane_model(const FNo* FNo);
const char* get_flight_total_seats(const FNo* FNo);
const char* get_flight_origin(const FNo* FNo);
const char* get_flight_destination(const FNo* FNo);
const char* get_flight_schedule_departure_date(const FNo* FNo);
const char* get_flight_schedule_arrival_date(const FNo* FNo);
const char* get_flight_real_departure_date(const FNo* FNo);
const char* get_flight_real_arrival_date(const FNo* FNo);
int get_flight_passengers(const FNo* FNo);
int get_flight_delay_time(const FNo* FNo);
const FNo* get_flight_prox(const FNo* FNo);
void flights_hash_sort(FList *flight_array_valid, FList list);
void create_array_flights(char parametros[][FIELD_SIZE]);
void free_list_flight(const FNo *nodo);
void free_flight_valid();
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de voos, e libera elemento a elemento



////////////////////////PASSENGERS///////////////////////////
void ordena_list_flights(int ind, const char *date_ind, char *id_f, int **list, int n);
void create_array_passengers(char parametros[][FIELD_SIZE]);

#endif