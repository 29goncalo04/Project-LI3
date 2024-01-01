#include <stdlib.h>

#include "../include/Catalogs.h"
#include "../include/Statistics.h"
#include "../include/Aux_structs.h"
#include "../include/Free.h"

void free_flight_valid(Flight *flight_array_valid, int num_linhas_valid) {      
    for (int i = 0; i < num_linhas_valid; i++) {                             
        free(flight_array_valid[i].id);
        free(flight_array_valid[i].airline);
        free(flight_array_valid[i].plane_model);
        free(flight_array_valid[i].total_seats);
        free(flight_array_valid[i].origin);
        free(flight_array_valid[i].destination);
        free(flight_array_valid[i].schedule_departure_date);
        free(flight_array_valid[i].schedule_arrival_date);
        free(flight_array_valid[i].real_departure_date);
        free(flight_array_valid[i].real_arrival_date);
        //free(flight_array_valid[i].pilot);
        //free(flight_array_valid[i].copilot);
        //free(flight_array_valid[i].notes);
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


void free_reservation_valid(Reservation *reservation_array_valid, int num_linhas_valid) { 
    for (int i = 0; i < num_linhas_valid; i++) {                                  
        free(reservation_array_valid[i].id);
        free(reservation_array_valid[i].user_id);
        free(reservation_array_valid[i].hotel_id);
        free(reservation_array_valid[i].hotel_name);
        free(reservation_array_valid[i].hotel_stars);
        free(reservation_array_valid[i].city_tax);
        //free(reservation_array_valid[i].address);
        free(reservation_array_valid[i].begin_date);
        free(reservation_array_valid[i].end_date);
        free(reservation_array_valid[i].price_per_night);
        free(reservation_array_valid[i].includes_breakfast);
        //free(reservation_array_valid[i].room_details);
        free(reservation_array_valid[i].rating);
        //free(reservation_array_valid[i].comment);
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

void free_user_valid(User *user_array_valid, int num_linhas_valid) {  
    for (int i = 0; i < num_linhas_valid; i++) {               
        free(user_array_valid[i].id);
        free(user_array_valid[i].name);
        //free(user_array_valid[i].email);
        //free(user_array_valid[i].phone_number);
        free(user_array_valid[i].birth_date);
        free(user_array_valid[i].sex);
        free(user_array_valid[i].passport);
        free(user_array_valid[i].country_code);
        //free(user_array_valid[i].address);
        free(user_array_valid[i].account_creation);
        //free(user_array_valid[i].pay_method);
        free(user_array_valid[i].account_status);
    }
    free(user_array_valid);
    user_array_valid = NULL;
    num_linhas_valid = 0;
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

void free_all(){
    free_passenger_valid(passenger_array_valid, num_linhas_valid_passenger);
    free_flight_valid(flight_array_valid, num_linhas_valid_flight);
    free_reservation_valid(reservation_array_valid, num_linhas_valid_reservation);
    free_user_valid(user_array_valid, num_linhas_valid_user);
    //free_passenger_invalid(passenger_array_invalid, num_linhas_invalid_passenger); 
    //free_flight_invalid(flight_array_invalid, num_linhas_invalid_flight);            
    //free_reservation_invalid(reservation_array_invalid, num_linhas_invalid_reservation); 
    //free_user_invalid(user_array_invalid, num_linhas_invalid_user);
    free_contador(contador_array, num_linhas_contador);
    free_Atrasos(Atrasos_array, num_Atrasos);
}