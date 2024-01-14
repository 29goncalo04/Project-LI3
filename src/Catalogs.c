#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/Catalogs.h"
#include "../include/Validation.h"
#include "../include/Statistics.h"
#include "../include/Hash.h"
#include "../include/Aux_functions.h"
#include "../include/Aux_validation.h"
#include "../include/Output_errors.h"

////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////

struct UNo{
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
    struct UNo *prox;
};

void set_user_id(UNo* UNo, const char* id){
    UNo->id = strdup(id);
}
void set_user_name(UNo* UNo, const char* name){
    UNo->name = strdup(name);
}
void set_user_birth_date(UNo* UNo, const char* birth_date){
    UNo->birth_date = strdup(birth_date);
}
void set_user_sex(UNo* UNo, const char* sex){
    UNo->sex = strdup(sex);
}
void set_user_passport(UNo* UNo, const char* passport){
    UNo->passport = strdup(passport);
}
void set_user_country_code(UNo* UNo, const char* country_code){
    UNo->country_code = strdup(country_code);
}
void set_user_account_creation(UNo* UNo, const char* account_creation){
    UNo->account_creation = strdup(account_creation);
}
void set_user_account_status(UNo* UNo, const char* account_status){
    UNo->account_status = strdup(account_status);
}
void set_user_reservations(UNo* UNo, int reservations){
    UNo->reservations = reservations;
}
void set_user_list_reservations(UNo* UNo){
    UNo->list_reservations = NULL;
}
void set_user_flights(UNo* UNo, int flights){
    UNo->flights = flights;
}
void set_user_list_flights(UNo* UNo){
    UNo->list_flights = NULL;
}
void set_user_total_spent(UNo* UNo, double total_spent){
    UNo->total_spent = total_spent;
}
void set_user_validation(UNo* UNo, int validation){
    UNo->validation = validation;
}
void set_user_prox(UNo* UNo){
    UNo->prox = NULL;
}

struct UList{
    UNo *init;
};

UList user_array_valid[NUM_LINHAS_VALID_USER];

const UList* get_user_array_valid(int pos) {
    return &user_array_valid[pos];
}
const UNo* getUListInit(const UList* UList){
    return UList->init;
}

UNo* create_user(char parametros[][FIELD_SIZE]) {    
    UNo* nova = malloc(sizeof(struct UNo));
    set_user_id(nova, parametros[0]);                                           
    set_user_name(nova, parametros[1]);
    set_user_birth_date(nova, parametros[4]);
    set_user_sex(nova, parametros[5]);
    set_user_passport(nova, parametros[6]);
    set_user_country_code(nova, parametros[7]);
    set_user_account_creation(nova, parametros[9]);
    set_user_account_status(nova, parametros[11]);
    set_user_reservations(nova, 0);
    set_user_list_reservations(nova);
    set_user_flights(nova, 0);
    set_user_list_flights(nova);
    set_user_total_spent(nova, 0);
    set_user_validation(nova, 1);
    set_user_prox(nova);
    return nova;
}

const char* get_user_id(const UNo* UNo){
    return UNo->id;
}
const char* get_user_name(const UNo* UNo){
    return UNo->name;
}
const char* get_user_birth_date(const UNo* UNo){
    return UNo->birth_date;
}
const char* get_user_sex(const UNo* UNo){
    return UNo->sex;
}
const char* get_user_passport(const UNo* UNo){
    return UNo->passport;
}
const char* get_user_country_code(const UNo* UNo){
    return UNo->country_code;
}
const char* get_user_account_creation(const UNo* UNo){
    return UNo->account_creation;
}
const char* get_user_account_status(const UNo* UNo){
    return UNo->account_status;
}
int get_user_reservations(const UNo* UNo){
    return UNo->reservations;
}
const int* get_user_list_reservations(const UNo* UNo){
    return UNo->list_reservations;
}
int get_user_flights(const UNo* UNo){
    return UNo->flights;
}
const int* get_user_list_flights(const UNo* UNo){
    return UNo->list_flights;
}
double get_user_total_spent(const UNo* UNo){
    return UNo->total_spent;
}
int get_user_validation(const UNo* UNo){
    return UNo->validation;
}
const UNo* get_user_prox(const UNo* UNo){
    return UNo->prox;
}

void users_hash_sort(UList *user_array_valid, UList list) {
    char* aux = strdup(get_user_id(list.init));
    int ind = found_index_users(aux);
    free(aux);
    if (user_array_valid[ind].init == NULL) { //esta tudo NULL (vacio)
        user_array_valid[ind] = list;
    }
    else {
        list.init->prox = user_array_valid[ind].init;
        user_array_valid[ind] = list;
    }
}

void create_array_users(char parametros[][FIELD_SIZE]) {
    int val = validate_user(parametros);
    if (val == 1) {
        UNo* nova = create_user(parametros);
        UList list;
        list.init = nova;
        users_hash_sort(user_array_valid, list);
    } 
    else {
       complete_files_users(parametros); 
    }
}

void free_list_user(const UNo *nodo) {
    const UNo *atual = nodo;
    const UNo *next;
    while (atual!=NULL){
        next = atual->prox;
        free((char*)atual->id);
        free((char*)atual->name);
        free((char*)atual->birth_date);
        free((char*)atual->sex);
        free((char*)atual->passport);
        free((char*)atual->country_code);
        free((char*)atual->account_creation);
        free((char*)atual->account_status);
        free((int*)atual->list_reservations);
        free((int*)atual->list_flights);
        free((char*)atual);
        atual = next;
    }
}

void perform_operation_on_user_array(void (*operation)(UList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_USER; i++) {
        operation(&user_array_valid[i]);
    }
}

void free_user_element(UList *user_element) {
    free_list_user(getUListInit(user_element));
}

void free_user_valid() {
    perform_operation_on_user_array(free_user_element);
}










////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////

struct HNo {
    int reservations;
    int *list_reservations;
};

void set_hotel_reservations(HNo* HNo, int reservations){
    HNo->reservations = reservations;
}
void set_hotel_list_reservations(HNo* HNo){
    HNo->list_reservations = NULL;
}

struct HList{
    HNo *init;
};

HList hotel_array_valid[NUM_LINHAS_VALID_HOTEL];

const HList* get_hotel_array_valid(int pos) {
    return &hotel_array_valid[pos];
}
const HNo* getHListInit(const HList* HList){
    return HList->init;
}
const int* get_hotel_list_reservations(const HNo* HNo){
    return HNo->list_reservations;
}
int get_hotel_reservations(const HNo* HNo){
    return HNo->reservations;
}

void create_array_hotels() {
    for (int i = 0; i < NUM_LINHAS_VALID_HOTEL; i++) { 
        HNo* nova = malloc(sizeof(struct HNo));
        set_hotel_reservations(nova, 0);                                           
        set_hotel_list_reservations(nova);
        hotel_array_valid[i].init = nova;
    }
    return;
}

void free_list_hotel(const HNo *nodo) {
    const HNo* atual = nodo;
    free((int*)atual->list_reservations);
    free((char*)atual);
}

void perform_operation_on_hotel_array(void (*operation)(HList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_HOTEL; i++) {
        operation(&hotel_array_valid[i]);
    }
}

void free_hotel_element(HList *hotel_element) {
    free_list_hotel(getHListInit(hotel_element));
}

void free_hotel_valid() {
    perform_operation_on_hotel_array(free_hotel_element);
}










////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////

struct RNo {
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    int hotel_stars;
    int city_tax;
    char *begin_date;
    char *end_date;
    int price_per_night;
    char *includes_breakfast;
    int rating;
    int validation;
    struct RNo *prox;
};

void set_reservation_id(RNo* RNo, const char* id){
    RNo->id = strdup(id);
}
void set_reservation_user_id(RNo* RNo, const char* user_id){
    RNo->user_id = strdup(user_id);
}
void set_reservation_hotel_id(RNo* RNo, const char* hotel_id){
    RNo->hotel_id = strdup(hotel_id);
}
void set_reservation_hotel_name(RNo* RNo, const char* hotel_name){
    RNo->hotel_name = strdup(hotel_name);
}
void set_reservation_hotel_stars(RNo* RNo, int hotel_stars){
    RNo->hotel_stars = hotel_stars;
}
void set_reservation_city_tax(RNo* RNo, int city_tax){
    RNo->city_tax = city_tax;
}
void set_reservation_begin_date(RNo* RNo, const char* begin_date){
    RNo->begin_date = strdup(begin_date);
}
void set_reservation_end_date(RNo* RNo, const char* end_date){
    RNo->end_date = strdup(end_date);
}
void set_reservation_price_per_night(RNo* RNo, int price_per_night){
    RNo->price_per_night = price_per_night;
}
void set_reservation_includes_breakfast(RNo* RNo, const char* includes_breakfast){
    RNo->includes_breakfast = strdup(includes_breakfast);
}
void set_reservation_rating(RNo* RNo, int rating){
    RNo->rating = rating;
}
void set_reservation_validation(RNo* RNo, int validation){
    RNo->validation = validation;
}
void set_reservation_prox(RNo* RNo){
    RNo->prox = NULL;
}

struct RList {
    RNo *init;
};

RList reservation_array_valid[NUM_LINHAS_VALID_RESERVATION];

const RList* get_reservation_array_valid(int pos) {
    return &reservation_array_valid[pos];
}
const RNo* getRListInit(const RList* RList){
    return RList->init;
}

RNo* create_reservation(char parametros[][FIELD_SIZE]) {  
    RNo* nova = malloc(sizeof(struct RNo));  
    set_reservation_id(nova, parametros[0]);
    set_reservation_user_id(nova, parametros[1]);                                           
    set_reservation_hotel_id(nova, parametros[2]);                                           
    set_reservation_hotel_name(nova, parametros[3]);                                           
    set_reservation_hotel_stars(nova, atoi(parametros[4]));                                           
    set_reservation_city_tax(nova, atoi(parametros[5]));                                           
    set_reservation_begin_date(nova, parametros[7]);                                           
    set_reservation_end_date(nova, parametros[8]);                                           
    set_reservation_price_per_night(nova, atoi(parametros[9]));                                           
    set_reservation_includes_breakfast(nova, parametros[10]);                                           
    set_reservation_rating(nova, atoi(parametros[12]));                                           
    set_reservation_validation(nova, 1);                                           
    set_reservation_prox(nova);                                           
    return nova;
}

const char* get_reservation_id(const RNo* RNo){
    return RNo->id;
}
const char* get_reservation_user_id(const RNo* RNo){
    return RNo->user_id;
}
const char* get_reservation_hotel_id(const RNo* RNo){
    return RNo->hotel_id;
}
const char* get_reservation_hotel_name(const RNo* RNo){
    return RNo->hotel_name;
}
int get_reservation_hotel_stars(const RNo* RNo){
    return RNo->hotel_stars;
}
int get_reservation_city_tax(const RNo* RNo){
    return RNo->city_tax;
}
const char* get_reservation_begin_date(const RNo* RNo){
    return RNo->begin_date;
}
const char* get_reservation_end_date(const RNo* RNo){
    return RNo->end_date;
}
int get_reservation_price_per_night(const RNo* RNo){
    return RNo->price_per_night;
}
const char* get_reservation_includes_breakfast(const RNo* RNo){
    return RNo->includes_breakfast;
}
int get_reservation_rating(const RNo* RNo){
    return RNo->rating;
}
int get_reservation_validation(const RNo* RNo){
    return RNo->validation;
}
const RNo* get_reservation_prox(const RNo* RNo){
    return RNo->prox;
}

void ordena_list_reservations(int ind, const char *date_ind, const char *id_r, int **list, int n) {
    int j, check;
    for (int i = 0; i < n; i++) {
        if ((*list)[i] == -1) {
            (*list)[i] = ind;
            return;
        }
        else {
            j = (*list)[i];
            RNo *pointer = reservation_array_valid[j].init;
            if (strcmp(date_ind, get_reservation_begin_date(pointer)) != 0) {
                check = compare_date_time3(date_ind, get_reservation_begin_date(pointer));
                if (check == 1) {
                    for (int k = n-1; i < k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    return;
                }
            } 
            else { //Book00903905
                if (atoi(get_reservation_id(pointer) + 4) - atoi(id_r + 4) < 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                    for (int k = n-1; i < k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    return;
                }
            }
        }
    }
    return;
}

void reservations_hash_sort(RList *reservation_array_valid, RList list) {
    int ind = found_index_reservations(get_reservation_id(list.init));
    if (reservation_array_valid[ind].init == NULL) { //esta tudo NULL (vacio)
        reservation_array_valid[ind] = list;
    }
    else {
        list.init->prox = reservation_array_valid[ind].init;
        reservation_array_valid[ind] = list;
    }
    char* aux = strdup(get_reservation_user_id(list.init));
    int ind_u = found_index_users(aux);
    free(aux);
    UNo *upointer = user_array_valid[ind_u].init;
    while (upointer != NULL) {
        if (strcmp(get_reservation_user_id(list.init), get_user_id(upointer)) == 0) {
            ordena_list_reservations(ind, get_reservation_begin_date(list.init), get_reservation_id(list.init), &(upointer->list_reservations), upointer->reservations);                  
            break;
        }
        else upointer = upointer->prox;
    }
}

void create_array_reservations(char parametros[][FIELD_SIZE]){
    int val = validate_reservation(parametros);
    if (val == 1){  //se essa linha for válida os seus parâmetros são armazenados no array de reservas válidas
        RNo* nova = create_reservation(parametros);
        RList list;
        list.init = nova;
        int ind = found_index_users(parametros[1]);
        UNo *pointer = user_array_valid[ind].init;
        while (pointer != NULL) {
            if (strcmp(get_reservation_user_id(list.init), get_user_id(pointer)) == 0) {
                pointer->list_reservations = realloc(pointer->list_reservations, (pointer->reservations+1)*sizeof(int));
                pointer->list_reservations[pointer->reservations] = -1;
                pointer->reservations++;
                pointer->total_spent += total_price(get_reservation_price_per_night(list.init), nights(get_reservation_begin_date(list.init), get_reservation_end_date(list.init)), get_reservation_city_tax(list.init));
                break;
            }
            else pointer = pointer->prox;
        }
        int ind_hotel = found_index_hotels(parametros[2]), id_reservation_table = found_index_reservations(parametros[0]);
        HNo *pointer_h = hotel_array_valid[ind_hotel].init;
        pointer_h->list_reservations = realloc(pointer_h->list_reservations, (pointer_h->reservations+1)*sizeof(int));
        pointer_h->list_reservations[pointer_h->reservations] = id_reservation_table;
        pointer_h->reservations++;
        reservations_hash_sort(reservation_array_valid, list);
    }
    else{
        complete_files_reservations(parametros);
    }
}

void free_list_reservation(const RNo *nodo) {
    const RNo* atual = nodo;
    const RNo* next;
    while(atual!=NULL){
        next = atual->prox;
        free((char*)atual->id);
        free((char*)atual->user_id);
        free((char*)atual->hotel_id);
        free((char*)atual->hotel_name);
        free((char*)atual->begin_date);
        free((char*)atual->end_date);
        free((char*)atual->includes_breakfast);
        free((char*)atual);
        atual = next;
    }
}

void perform_operation_on_reservation_array(void (*operation)(RList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_RESERVATION; i++) {
        operation(&reservation_array_valid[i]);
    }
}

void free_reservation_element(RList *reservation_element) {
    free_list_reservation(getRListInit(reservation_element));
}

void free_reservation_valid() {
    perform_operation_on_reservation_array(free_reservation_element);
}










////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////


struct ANo {
    int flights;
    int *list_flights;
};

void set_airport_flights(ANo* ANo, int flights){
    ANo->flights = flights;
}
void set_airport_list_flights(ANo* ANo){
    ANo->list_flights = NULL;
}

struct AList {
    ANo *init;
};

AList airport_array_valid[NUM_LINHAS_VALID_AIRPORT];

const AList* get_airport_array_valid(int pos) {
    return &airport_array_valid[pos];
}
const ANo* getAListInit(const AList* AList){
    return AList->init;
}
const int* get_airport_list_flights(const ANo* ANo){
    return ANo->list_flights;
}
int get_airport_flights(const ANo* ANo){
    return ANo->flights;
}

void create_array_airport() {
    for (int i = 0; i < NUM_LINHAS_VALID_AIRPORT; i++) { 
        ANo* nova = malloc(sizeof(struct ANo));
        set_airport_flights(nova, 0);                                           
        set_airport_list_flights(nova);
        airport_array_valid[i].init = nova;
    }
    return;
}

void ordena_list_airport_flights(int ind_f, char *data_estimada, char *id_f, int **list, int n) {
    int j, check;
    for (int i = 0; i < n; i++) {
        if ((*list)[i] == -1) {
            (*list)[i] = ind_f;
            break;
        }
        else {
            j = (*list)[i];
            const FNo *pointer = getFListInit(get_flight_array_valid(j));
            if (strcmp(data_estimada, get_flight_schedule_departure_date(pointer)) != 0) {
                check = compare_date_time3(data_estimada, get_flight_schedule_departure_date(pointer));
                if (check == 1) {
                    for (int k = n-1; i < k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind_f;
                    break;
                }
            } 
            else { //00903905
                if (atoi(get_flight_id(pointer)) - atoi(id_f) < 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                    for (int k = n-1; i <= k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind_f;
                    break;
                }
            }
        }
    }
    return;
}

void free_list_airport(const ANo *nodo) {
    const ANo* atual = nodo;
    free((int*)atual->list_flights);
    free((char*)atual);
}

void perform_operation_on_airport_array(void (*operation)(AList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_AIRPORT; i++) {
        operation(&airport_array_valid[i]);
    }
}

void free_airport_element(AList *airport_element) {
    free_list_airport(getAListInit(airport_element));
}

void free_airport_valid() {
    perform_operation_on_airport_array(free_airport_element);
}





////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////

struct FNo {
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
    struct FNo *prox;
};

void set_flight_id(FNo* FNo, const char* id){
    FNo->id = strdup(id);
}
void set_flight_airline(FNo* FNo, const char* airline){
    FNo->airline = strdup(airline);
}
void set_flight_plane_model(FNo* FNo, const char* plane_model){
    FNo->plane_model = strdup(plane_model);
}
void set_flight_total_seats(FNo* FNo, const char* total_seats){
    FNo->total_seats = strdup(total_seats);
}
void set_flight_origin(FNo* FNo, const char* origin){
    FNo->origin = strdup(origin);
}
void set_flight_destination(FNo* FNo, const char* destination){
    FNo->destination = strdup(destination);
}
void set_flight_schedule_departure_date(FNo* FNo, const char* schedule_departure_date){
    FNo->schedule_departure_date = strdup(schedule_departure_date);
}
void set_flight_schedule_arrival_date(FNo* FNo, const char* schedule_arrival_date){
    FNo->schedule_arrival_date = strdup(schedule_arrival_date);
}
void set_flight_real_departure_date(FNo* FNo, const char* real_departure_date){
    FNo->real_departure_date = strdup(real_departure_date);
}
void set_flight_real_arrival_date(FNo* FNo, const char* real_arrival_date){
    FNo->real_arrival_date = strdup(real_arrival_date);
}
void set_flight_passengers(FNo* FNo, int passengers){
    FNo->passengers = passengers;
}
void set_flight_delay_time(FNo* FNo, int delay_time){
    FNo->delay_time = delay_time;
}
void set_flight_validation(FNo* FNo, int validation){
    FNo->validation = validation;
}
void set_flight_prox(FNo* FNo){
    FNo->prox = NULL;
}

struct FList {
    FNo *init;
};

FList flight_array_valid[NUM_LINHAS_VALID_FLIGHT];

const FList* get_flight_array_valid(int pos) {
    return &flight_array_valid[pos];
}

const FNo* getFListInit(const FList* FList){
    return FList->init;
}

FNo* create_flight(char parametros[][FIELD_SIZE]) {           
    FNo* nova = malloc(sizeof(struct FNo));   
    set_flight_id(nova, parametros[0]);                                           
    set_flight_airline(nova, parametros[1]);
    set_flight_plane_model(nova, parametros[2]);
    set_flight_total_seats(nova, parametros[3]);
    set_flight_origin(nova, parametros[4]);
    set_flight_destination(nova, parametros[5]);
    set_flight_schedule_departure_date(nova, parametros[6]);
    set_flight_schedule_arrival_date(nova, parametros[7]);
    set_flight_real_departure_date(nova, parametros[8]);
    set_flight_real_arrival_date(nova, parametros[9]);
    set_flight_passengers(nova, 0);
    set_flight_delay_time(nova, 0);
    set_flight_validation(nova, 1);
    set_flight_prox(nova);
    return nova;
}

const char* get_flight_id(const FNo* FNo){
    return FNo->id;
}
const char* get_flight_airline(const FNo* FNo){
    return FNo->airline;
}
const char* get_flight_plane_model(const FNo* FNo){
    return FNo->plane_model;
}
const char* get_flight_total_seats(const FNo* FNo){
    return FNo->total_seats;
}
const char* get_flight_origin(const FNo* FNo){
    return FNo->origin;
}
const char* get_flight_destination(const FNo* FNo){
    return FNo->destination;
}
const char* get_flight_schedule_departure_date(const FNo* FNo){
    return FNo->schedule_departure_date;
}
const char* get_flight_schedule_arrival_date(const FNo* FNo){
    return FNo->schedule_arrival_date;
}
const char* get_flight_real_departure_date(const FNo* FNo){
    return FNo->real_departure_date;
}
const char* get_flight_real_arrival_date(const FNo* FNo){
    return FNo->real_arrival_date;
}
int get_flight_passengers(const FNo* FNo){
    return FNo->passengers;
}
int get_flight_delay_time(const FNo* FNo){
    return FNo->delay_time;
}
const FNo* get_flight_prox(const FNo* FNo){
    return FNo->prox;
}


void flights_hash_sort(FList *flight_array_valid, FList list) {
    int ind = found_index_flights(get_flight_id(list.init));
    if (flight_array_valid[ind].init == NULL) { //esta tudo NULL (vacio)
        flight_array_valid[ind] = list;
    }
    else {
        list.init->prox = flight_array_valid[ind].init;
        flight_array_valid[ind] = list;
    }
}

void create_array_flights(char parametros[][FIELD_SIZE]){
    int val = validate_flight(parametros);
    if (val == 1){    //se essa linha for válida os seus parâmetros são armazenados no array de voos válidos
        FNo* nova = create_flight(parametros);
        FList list;
        list.init = nova;
        char *origin_cpy = strdup (parametros[4]);
        toUpperCase (origin_cpy);
        int ind = found_index_airport(origin_cpy), ind_f = found_index_flights(parametros[0]);
        free (origin_cpy);
        ANo *pointer = airport_array_valid[ind].init;
        pointer->list_flights = realloc(pointer->list_flights, (pointer->flights+1)*sizeof(int));
        pointer->list_flights[pointer->flights] = -1;
        pointer->flights++;
        ordena_list_airport_flights(ind_f, parametros[6], parametros[0], &(pointer->list_flights), pointer->flights);
        create_array_atrasos(list.init, NUM_LINHAS_VALID_FLIGHT, parametros);
        flights_hash_sort(flight_array_valid, list);
    }
    else{
        complete_files_flights(parametros);
    }
}

void free_list_flight(const FNo *nodo) {
    const FNo* atual = nodo;
    const FNo* next;
    while(atual!=NULL) {
        next = atual->prox;
        free((char*)atual->id);
        free((char*)atual->airline);
        free((char*)atual->plane_model);
        free((char*)atual->total_seats);
        free((char*)atual->origin);
        free((char*)atual->destination);
        free((char*)atual->schedule_departure_date);
        free((char*)atual->schedule_arrival_date);
        free((char*)atual->real_departure_date);
        free((char*)atual->real_arrival_date);
        free((char*)atual);
        atual = next;
    } 
}

void perform_operation_on_flight_array(void (*operation)(FList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_FLIGHT; i++) {
        operation(&flight_array_valid[i]);
    }
}

void free_flight_element(FList *flight_element) {
    free_list_flight(getFListInit(flight_element));
}

void free_flight_valid() {
    perform_operation_on_flight_array(free_flight_element);
}









////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
void ordena_list_flights(int ind, const char *date_ind, char *id_f, int **list, int n) {
    int j, check;
    for (int i = 0; i < n; i++) {
        if ((*list)[i] == -1) {
            (*list)[i] = ind;
            return;
        }
        else {
            j = (*list)[i];
            const FNo *pointer = getFListInit(get_flight_array_valid(j));
            if (strcmp(date_ind, get_flight_schedule_departure_date(pointer)) != 0) {
                check = compare_date_time3(date_ind, get_flight_schedule_departure_date(pointer));
                if (check == 1) {
                    for (int k = n-1; i < k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    return;
                }
            } 
            else { //00903905
                if (atoi(get_flight_id(pointer)) - atoi(id_f) < 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                    for (int k = n-1; i <= k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    return;
                }
            }
        }
    }
    return;
}

void create_array_passengers(char parametros[][FIELD_SIZE]){
    int ind_u, ind_f, val;
    val = validate_passenger(parametros);
    if (val==1){
        ind_u = found_index_users(parametros[1]); //id_u
        UNo *upointer = user_array_valid[ind_u].init;
        while (upointer != NULL) {
            if (strcmp(parametros[1], get_user_id(upointer)) == 0) {
                upointer->list_flights = realloc(upointer->list_flights, (upointer->flights+1)*sizeof(int));
                upointer->list_flights[upointer->flights] = -1;
                upointer->flights++;
                ind_f = found_index_flights(parametros[0]);
                ordena_list_flights(ind_f, get_flight_schedule_departure_date(flight_array_valid[ind_f].init), parametros[0], &(upointer->list_flights), upointer->flights);
                break;
            }
            else upointer = upointer->prox;
        }
        ind_f = found_index_flights(parametros[0]); //id_f
        FNo *fpointer = flight_array_valid[ind_f].init;
        while (fpointer != NULL) {
            if (strcmp(parametros[0], get_flight_id(fpointer)) == 0) {
                fpointer->passengers++;
                break;
            }
            else fpointer = fpointer->prox;
        }
    }
    else{
        complete_files_passengers(parametros);
    }
}