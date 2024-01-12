#include <stdlib.h>

#include "../include/Free.h"
#include "../include/Catalogs.h"
#include "../include/Statistics.h"
#include "../include/Aux_structs.h"

void free_list_hotel(HNo *nodo) {
    HNo *atual = nodo;
    HNo *next;
    while (atual!=NULL){
        next = atual->prox;
        free(atual->hotel.id);
        free(atual->hotel.begin_date);
        free(atual->hotel.end_date);
        free(atual);
        atual = next;
    }
}

void free_hotel_valid(HList *hotel_array_valid, int num_linhas_valid) {
    HNo *list;
    for (int i = 0; i < num_linhas_valid; i++) {
        list = hotel_array_valid[i].init;
        free_list_hotel(list);
    }
}

void free_list_reservation(RNo *nodo) {
    RNo *atual = nodo;
    RNo *next;
    while (atual!=NULL){
        next = atual->prox;
        free(atual->reservation.id);
        free(atual->reservation.user_id);
        free(atual->reservation.hotel_id);
        free(atual->reservation.hotel_name);
        free(atual->reservation.hotel_stars);
        free(atual->reservation.city_tax);
        free(atual->reservation.begin_date);
        free(atual->reservation.end_date);
        free(atual->reservation.price_per_night);
        free(atual->reservation.includes_breakfast);
        free(atual->reservation.rating);
        free(atual);
        atual = next;
    }
}

void free_reservation_valid(RList *reservation_array_valid, int num_linhas_valid) {
    RNo *list;
    for (int i = 0; i < num_linhas_valid; i++) {
        list = reservation_array_valid[i].init;
        free_list_reservation(list);
    }
}

void free_list_user(UNo *nodo) {
    UNo *atual = nodo;
    UNo *next;
    while (atual!=NULL){
        next = atual->prox;
        free(atual->user.id);
        free(atual->user.name);
        free(atual->user.birth_date);
        free(atual->user.sex);
        free(atual->user.passport);
        free(atual->user.country_code);
        free(atual->user.account_creation);
        free(atual->user.account_status);
        free(atual->user.list_reservations);
        free(atual->user.list_flights);
        free(atual);
        atual = next;
    }
}

void free_user_valid(UList *user_array_valid, int num_linhas_valid) {
    UNo *list;
    for (int i = 0; i < num_linhas_valid; i++) {
        list = user_array_valid[i].init;
        free_list_user(list);
    }
}

void free_Atrasos(Atrasos *Atrasos_array, int num_Atrasos){
    for (int i = 0; i<num_Atrasos; i++){
        free(Atrasos_array[i].airport);
        free(Atrasos_array[i].atraso);
    }
    free(Atrasos_array);
}

void free_flight_id_passenger(Flight_id_passenger *flight_id_passenger_array, int num_flights_passenger_id){
    for (int i = 0; i<num_flights_passenger_id; i++){
        free(flight_id_passenger_array[i].flight_id);
    }
    free(flight_id_passenger_array);
}

void free_flight_aux(Flight_aux *flight_aux_array, int num_flights_passenger_id){
    for (int i = 0; i<num_flights_passenger_id; i++){
        free(flight_aux_array[i].flight_id);
        free(flight_aux_array[i].schedule_departure_date);
        free(flight_aux_array[i].type);
    }
    free(flight_aux_array);
}

void free_reservation_aux(Reservation_aux *reservation_aux_array, int num_reservations){
    for (int i = 0; i<num_reservations; i++){
        free(reservation_aux_array[i].reservation_id);
        free(reservation_aux_array[i].begin_date);
        free(reservation_aux_array[i].type);
    }
    free(reservation_aux_array);
}

void free_PassengersXairport(PassengersXairport *passengersXairport_array, int num_linhas_PassengersXairport) {
    for (int i = 0; i < num_linhas_PassengersXairport; i++) {                         
        free(passengersXairport_array[i].origin);
    }
    free(passengersXairport_array);
}

void free_idXname(idXname *idXname_array, int num_linhas_idXname) {
    for (int i = 0; i < num_linhas_idXname; i++){
        free(idXname_array[i].id);
        free(idXname_array[i].name);

    }
    free(idXname_array);
}

void free_hotel_aux (hotel_aux *hotel_aux_array, int num_hotels){
    for (int i = 0; i<num_hotels; i++){
        free (hotel_aux_array[i].id);
        free (hotel_aux_array[i].begin_date);
        free (hotel_aux_array[i].end_date);
        free (hotel_aux_array[i].user_id);
        free (hotel_aux_array[i].rating);
    }
    free (hotel_aux_array);
}

void free_flight_date_aux (flight_date_aux *flight_date_aux_array, int num_flights){
    for (int i = 0; i<num_flights; i++){
        free (flight_date_aux_array[i].id);
        free (flight_date_aux_array[i].schedule_departure_date);
        free (flight_date_aux_array[i].destination);
        free (flight_date_aux_array[i].airline);
        free (flight_date_aux_array[i].plane_model);
    }
    free (flight_date_aux_array);
}

void free_Mediana(Mediana *mediana_array, int num_medianas){
    for (int i = 0; i<num_medianas; i++){
        free(mediana_array[i].airport);
    }
    free(mediana_array);
}

void free_all() {
    free_flight_valid(get_all_flight_array(), NUM_LINHAS_VALID_FLIGHT);
    free_reservation_valid(reservation_array_valid, NUM_LINHAS_VALID_RESERVATION);
    free_user_valid(user_array_valid, NUM_LINHAS_VALID_USER);
    free_hotel_valid(hotel_array_valid, NUM_LINHAS_VALID_HOTEL);
    free_Atrasos(Atrasos_array, num_Atrasos); //array_atrasos_valid acho que n vai ser usado, vai para o lixo
}