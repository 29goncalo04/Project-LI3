#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/Catalogs.h"
#include "../include/Validation.h"
#include "../include/Statistics.h"
#include "../include/Hash.h"
#include "../include/Aux_functions.h"
#include "../include/Output_errors.h"

UList user_array_valid[NUM_LINHAS_VALID_USER];

User create_user(char parametros[][FIELD_SIZE]) {    
    User nova;                                           
    nova.id = strdup(parametros[0]);                          
    nova.name = strdup(parametros[1]);
    nova.birth_date = strdup(parametros[4]);
    nova.sex = strdup(parametros[5]);
    nova.passport = strdup(parametros[6]);
    nova.country_code = strdup(parametros[7]);
    nova.account_creation = strdup(parametros[9]);
    nova.account_status = strdup(parametros[11]);
    nova.reservations = 0;
    nova.list_reservations = NULL;
    nova.flights = 0;
    nova.list_flights = NULL;
    nova.total_spent = 0;
    nova.validation = 1;
    return nova;
}

void create_array_users(char parametros[][FIELD_SIZE]) {
    int val = validate_user(parametros);
    if (val == 1) {
        User nova = create_user(parametros);
        UList list;
        list.init = malloc(sizeof(UNo)); // Asignar memoria para el primer nodo
        list.init->prox = NULL;
        list.init->user = nova;
        users_hash_sort(user_array_valid, list);
    } 
    else {
       complete_files_users(parametros); 
    //    free(nova.id);
    //    free(nova.name);
    //    free(nova.birth_date);
    //    free(nova.sex);
    //    free(nova.passport);
    //    free(nova.country_code);
    //    free(nova.account_creation);
    //    free(nova.account_status);
    }
}

HList hotel_array_valid[NUM_LINHAS_VALID_HOTEL];

Hotel create_hotel(char *hotel_id, int stars, char *begin_date, char *end_date, int price_per_night, int rating) {
    Hotel nova;
    nova.id = strdup(hotel_id);
    nova.stars = stars;
    nova.begin_date = strdup(begin_date);
    nova.end_date = strdup(end_date);
    nova.price_per_night = price_per_night;
    nova.rating = rating;
    return nova;
}

void create_array_hotels(char *hotel_id, int stars, char *begin_date, char *end_date, int price_per_night, int rating) {
    Hotel nova = create_hotel(hotel_id, stars, begin_date, end_date, price_per_night, rating);
    HList list;
    list.init = malloc(sizeof(HNo));
    list.init->prox = NULL;
    list.init->hotel = nova;
    hotels_hash_sort(hotel_array_valid, list);
}

RList reservation_array_valid[NUM_LINHAS_VALID_RESERVATION];

Reservation create_reservation(char parametros[][FIELD_SIZE]) {  
    Reservation nova;                                              
    nova.id = strdup(parametros[0]);                                   
    nova.user_id = strdup(parametros[1]);
    nova.hotel_id = strdup(parametros[2]);
    nova.hotel_name = strdup(parametros[3]);
    nova.hotel_stars = strdup(parametros[4]);
    nova.city_tax = strdup(parametros[5]);
    nova.begin_date = strdup(parametros[7]);
    nova.end_date = strdup(parametros[8]);
    nova.price_per_night = strdup(parametros[9]);
    nova.includes_breakfast = strdup(parametros[10]);
    nova.rating = strdup(parametros[12]);
    nova.validation = 1;
    return nova;
}

void create_array_reservations(char parametros[][FIELD_SIZE]){
    int val = validate_reservation(parametros);
    if (val == 1){  //se essa linha for válida os seus parâmetros são armazenados no array de reservas válidas
        Reservation nova = create_reservation(parametros);
        RList list;
        list.init = malloc(sizeof(RNo)); // Asignar memoria para el primer nodo
        list.init->prox = NULL;
        list.init->reservation = nova;

        //tentar fazer isto noutro ficheiro(modulação)
        int ind = found_index_users(list.init->reservation.user_id); 
        UNo *pointer = user_array_valid[ind].init;
        while (pointer != NULL) {
            if (strcmp(list.init->reservation.user_id, pointer->user.id) == 0) {
                pointer->user.list_reservations = realloc(pointer->user.list_reservations, (pointer->user.reservations+1)*sizeof(int));
                pointer->user.list_reservations[pointer->user.reservations] = -1;
                pointer->user.reservations++;
                pointer->user.total_spent += total_price(list.init->reservation.price_per_night, nights(list.init->reservation.begin_date, list.init->reservation.end_date), list.init->reservation.city_tax);
                break;
            }
            else pointer = pointer->prox;
        }
        
        reservations_hash_sort(reservation_array_valid, list);
        create_array_hotels(parametros[2], atoi(parametros[4]), parametros[7], parametros[8], atoi(parametros[9]), atoi(parametros[12]));
    }
    else{
        complete_files_reservations(parametros);
        // free(nova.id);
        // free(nova.user_id);
        // free(nova.hotel_id);
        // free(nova.hotel_name);
        // free(nova.hotel_stars);
        // free(nova.city_tax);
        // free(nova.begin_date);
        // free(nova.end_date);
        // free(nova.price_per_night);
        // free(nova.includes_breakfast);
        // free(nova.rating);
    }
}

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

FList* get_flight_array_valid(int pos) {
    return &flight_array_valid[pos];
}

FList* get_all_flight_array() {
    return flight_array_valid;
}

FNo* getFListInit(FList* FList){
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

const char* get_flight_id(FNo* FNo){
    return FNo->id;
}
const char* get_flight_airline(FNo* FNo){
    return FNo->airline;
}
const char* get_flight_plane_model(FNo* FNo){
    return FNo->plane_model;
}
const char* get_flight_total_seats(FNo* FNo){
    return FNo->total_seats;
}
const char* get_flight_origin(FNo* FNo){
    return FNo->origin;
}
const char* get_flight_destination(FNo* FNo){
    return FNo->destination;
}
const char* get_flight_schedule_departure_date(FNo* FNo){
    return FNo->schedule_departure_date;
}
const char* get_flight_schedule_arrival_date(FNo* FNo){
    return FNo->schedule_arrival_date;
}
const char* get_flight_real_departure_date(FNo* FNo){
    return FNo->real_departure_date;
}
const char* get_flight_real_arrival_date(FNo* FNo){
    return FNo->real_arrival_date;
}
int get_flight_passengers(FNo* FNo){
    return FNo->passengers;
}
int get_flight_delay_time(FNo* FNo){
    return FNo->delay_time;
}

FNo* get_flight_prox(FNo* FNo){
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
        create_array_atrasos(list.init, NUM_LINHAS_VALID_FLIGHT, parametros);
        flights_hash_sort(flight_array_valid, list);
    }
    else{
        complete_files_flights(parametros);
    }
}

void free_list_flight(FNo *nodo) {
    if (nodo == NULL) return;
    else {
        free(nodo->id);
        free(nodo->airline);
        free(nodo->plane_model);
        free(nodo->total_seats);
        free(nodo->origin);
        free(nodo->destination);
        free(nodo->schedule_departure_date);
        free(nodo->schedule_arrival_date);
        free(nodo->real_departure_date);
        free(nodo->real_arrival_date);
        free_list_flight(nodo->prox);
    } 
}

void free_flight_valid(FList *flight_array_valid, int num_linhas_valid) {
    FNo *list;
    for (int i = 0; i < num_linhas_valid; i++) {
        list = flight_array_valid[i].init;
        free_list_flight(list);
        free(flight_array_valid[i].init);
    }
}

void create_array_passengers(char parametros[][FIELD_SIZE]){
    //Passenger nova = create_passenger(parametros);
    int ind_u, ind_f, val;
    val = validate_passenger(parametros);
    if (val==1){
        //create_array_contador(nova, parametros);            //basura que va ser borrada
        //previous_flight_id_validation = 1;                  //basura que va ser borrada
        //strcpy(previous_flight_id, nova.flight_id);         //basura que va ser borrada

        //tentar fazer isto noutro ficheiro(modulação)
        ind_u = found_index_users(parametros[1]); //id_u
        UNo *upointer = user_array_valid[ind_u].init;
        while (upointer != NULL) {
            if (strcmp(parametros[1], upointer->user.id) == 0) {
                upointer->user.list_flights = realloc(upointer->user.list_flights, (upointer->user.flights+1)*sizeof(int));
                upointer->user.list_flights[upointer->user.flights] = -1;
                upointer->user.flights++;

                //maybe seria bom fazer isto noutro modulo
                ind_f = found_index_flights(parametros[0]);
                ordena_list_flights(ind_f, get_flight_schedule_departure_date(flight_array_valid[ind_f].init), parametros[0], &(upointer->user.list_flights), upointer->user.flights);
                break;
            }
            else upointer = upointer->prox;
        }

        //tentar fazer isto noutro ficheiro(modulação)
        ind_f = found_index_flights(parametros[0]); //id_f
        FNo *fpointer = flight_array_valid[ind_f].init;
        while (fpointer != NULL) {
            if (strcmp(parametros[0], get_flight_id(fpointer)) == 0) {
                fpointer->passengers++;
                break;
            }
            else fpointer = fpointer->prox;
        }
        //passenger_array_valid = realloc(passenger_array_valid, (num_linhas_valid_passenger+1)*sizeof(Passenger));
        //passenger_array_valid[num_linhas_valid_passenger] = nova;
        //num_linhas_valid_passenger++;
    }
    else{
        complete_files_passengers(parametros);
        //free(nova.flight_id);
        //free(nova.user_id);
    }
}