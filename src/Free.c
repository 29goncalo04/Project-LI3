#include <stdlib.h>

#include "../include/Catalogs.h"
#include "../include/Statistics.h"
#include "../include/Aux_structs.h"
#include "../include/Free.h"

void free_list_flight(FNo *nodo) {
    //printf("init\n");
    if (nodo == NULL) return;
    else {
        free_list_flight(nodo->prox);
        free(nodo->flight.id);
        free(nodo->flight.airline);
        free(nodo->flight.plane_model);
        free(nodo->flight.total_seats);
        free(nodo->flight.destination);
        free(nodo->flight.schedule_departure_date);
        free(nodo->flight.real_departure_date);
        free(nodo->flight.real_arrival_date);
        // free(nodo->flight.pilot);
        // free(nodo->flight.copilot);
        // free(nodo->flight.notes);
    } 
}

void free_flight_valid(FList *flight_array_valid, int num_linhas_valid) {
    FNo *list;
    for (int i = 0; i < num_linhas_valid; i++) {
        list = flight_array_valid[i].init;
        free_list_flight(list);
        free(flight_array_valid[i].init);
    }
    free(flight_array_valid);
}

void free_flight_invalid(Flight *flight_array_invalid, int num_linhas_invalid) {      
    for (int i = 0; i < num_linhas_invalid; i++) {                             
        free(flight_array_invalid[i].id);
        free(flight_array_invalid[i].airline);
        free(flight_array_invalid[i].plane_model);
        free(flight_array_invalid[i].total_seats);
        free(flight_array_invalid[i].origin);
        free(flight_array_invalid[i].destination);
        free(flight_array_invalid[i].schedule_departure_date);
        free(flight_array_invalid[i].schedule_arrival_date);
        free(flight_array_invalid[i].real_departure_date);
        free(flight_array_invalid[i].real_arrival_date);
        free(flight_array_invalid[i].pilot);
        free(flight_array_invalid[i].copilot);
        free(flight_array_invalid[i].notes);
    }
    free(flight_array_invalid);
}


void free_passenger_valid(Passenger *passenger_array_valid, int num_linhas_valid) {
    for (int i = 0; i < num_linhas_valid; i++) {                               
        free(passenger_array_valid[i].flight_id);
        free(passenger_array_valid[i].user_id);
    }
    free(passenger_array_valid);
}

void free_passenger_invalid(Passenger *passenger_array_invalid, int num_linhas_invalid) {
    for (int i = 0; i < num_linhas_invalid; i++) {                               
        free(passenger_array_invalid[i].flight_id);
        free(passenger_array_invalid[i].user_id);
    }
    free(passenger_array_invalid);
}

void free_list_reservation(RNo *nodo) {
    if (nodo == NULL) return;
    else {
        free_list_reservation(nodo->prox);
        free(nodo->reservation.id);
        free(nodo->reservation.user_id);
        free(nodo->reservation.hotel_id);
        free(nodo->reservation.hotel_name);
        free(nodo->reservation.hotel_stars);
        free(nodo->reservation.city_tax);
        free(nodo->reservation.begin_date);
        free(nodo->reservation.end_date);
        free(nodo->reservation.price_per_night);
        free(nodo->reservation.includes_breakfast);
        free(nodo->reservation.rating);
    } 
}


void free_reservation_valid(RList *reservation_array_valid, int num_linhas_valid) {
    RNo *list;
    for (int i = 0; i < num_linhas_valid; i++) {
        list = reservation_array_valid[i].init;
        free_list_reservation(list);
        free(reservation_array_valid[i].init);
    }
    free(reservation_array_valid);
}

void free_reservation_invalid(Reservation *reservation_array_invalid, int num_linhas_invalid) { 
    for (int i = 0; i < num_linhas_invalid; i++) {                                  
        free(reservation_array_invalid[i].id);
        free(reservation_array_invalid[i].user_id);
        free(reservation_array_invalid[i].hotel_id);
        free(reservation_array_invalid[i].hotel_name);
        free(reservation_array_invalid[i].hotel_stars);
        free(reservation_array_invalid[i].city_tax);
        free(reservation_array_invalid[i].address);
        free(reservation_array_invalid[i].begin_date);
        free(reservation_array_invalid[i].end_date);
        free(reservation_array_invalid[i].price_per_night);
        free(reservation_array_invalid[i].includes_breakfast);
        free(reservation_array_invalid[i].room_details);
        free(reservation_array_invalid[i].rating);
        free(reservation_array_invalid[i].comment);
    }
    free(reservation_array_invalid);
}

void free_list_user(UNo *nodo) {
    //printf("init\n");
    if (nodo == NULL) return;
    else {
        free_list_user(nodo->prox);
        //printf("free id\n");
        free(nodo->user.id);
        //printf("free name\n");
        free(nodo->user.name);
        //printf("free anos\n");
        free(nodo->user.birth_date);
        //printf("free sex\n");
        free(nodo->user.sex);
        //printf("free pass\n");
        free(nodo->user.passport);
        //printf("free country\n");
        free(nodo->user.country_code);
        //printf("free creation\n");
        free(nodo->user.account_creation);
        //printf("free status\n");
        free(nodo->user.account_status);
    } 
}

void free_user_valid(UList *user_array_valid, int num_linhas_valid) {
    //printf("%d\n", num_linhas_valid);
    UNo *list;
    for (int i = 0; i < num_linhas_valid; i++) {
        list = user_array_valid[i].init;
        free_list_user(list);
        free(user_array_valid[i].init);
    }
    free(user_array_valid);
}


void free_user_invalid(User *user_array_invalid, int num_linhas_invalid) {  
    for (int i = 0; i < num_linhas_invalid; i++) {         
        free(user_array_invalid[i].id);
        free(user_array_invalid[i].name);
        free(user_array_invalid[i].email);
        free(user_array_invalid[i].phone_number);
        free(user_array_invalid[i].birth_date);
        free(user_array_invalid[i].sex);
        free(user_array_invalid[i].passport);
        free(user_array_invalid[i].country_code);
        free(user_array_invalid[i].address);
        free(user_array_invalid[i].account_creation);
        free(user_array_invalid[i].pay_method);
        free(user_array_invalid[i].account_status);
    }
    free(user_array_invalid);
}


void free_contador(Contador_id *contador_array, int num_linhas_contador) {
    for (int i = 0; i < num_linhas_contador; i++) {                         
        free(contador_array[i].id_flight);
    }
    free(contador_array);
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
    // free_passenger_valid(passenger_array_valid, num_linhas_valid_passenger); //array_pass_valid n vai ser usado, vai para o lixo
    free_flight_valid(flight_array_valid, num_linhas_valid_flight);
    free_reservation_valid(reservation_array_valid, num_linhas_valid_reservation);
    free_user_valid(user_array_valid, num_linhas_valid_user);
    // free_passenger_invalid(passenger_array_invalid, num_linhas_invalid_passenger); //array_pass_invalid n vai ser usado, vai para o lixo
    // free_flight_invalid(flight_array_invalid, num_linhas_invalid_flight); //array_fly_invalid n vai ser usado, vai para o lixo
    // free_reservation_invalid(reservation_array_invalid, num_linhas_invalid_reservation); //array_reservation_invalid n vai ser usado, vai para o lixo
    // free_user_invalid(user_array_invalid, num_linhas_invalid_user); //array_user_invalid n vai ser usado, vai para o lixo
    // free_contador(contador_array, num_linhas_contador); //array_contador_valid n vai ser usado, vai para o lixo
    // free_Atrasos(Atrasos_array, num_Atrasos); //array_atrasos_valid acho que n vai ser usado, vai para o lixo
}