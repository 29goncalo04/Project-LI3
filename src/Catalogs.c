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
    User nova = create_user(parametros);
    int val = validate_user(parametros);
    if (val == 1) {
        UList list;
        list.init = malloc(sizeof(UNo)); // Asignar memoria para el primer nodo
        list.init->prox = NULL;
        list.init->user = nova;
        users_hash_sort(user_array_valid, list);
    } 
    else {
       complete_files_users(parametros); 
       free(nova.id);
       free(nova.name);
       free(nova.birth_date);
       free(nova.sex);
       free(nova.passport);
       free(nova.country_code);
       free(nova.account_creation);
       free(nova.account_status);
    }
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
    Reservation nova = create_reservation(parametros);
    int val = validate_reservation(parametros);
    if (val == 1){  //se essa linha for válida os seus parâmetros são armazenados no array de reservas válidas
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
    }
    else{
        complete_files_reservations(parametros);
        free(nova.id);
        free(nova.user_id);
        free(nova.hotel_id);
        free(nova.hotel_name);
        free(nova.hotel_stars);
        free(nova.city_tax);
        free(nova.begin_date);
        free(nova.end_date);
        free(nova.price_per_night);
        free(nova.includes_breakfast);
        free(nova.rating);
    }
}

FList flight_array_valid[NUM_LINHAS_VALID_FLIGHT];

Flight create_flight(char parametros[][FIELD_SIZE]) {           
    Flight nova;                                              
    nova.id = strdup(parametros[0]);                                   
    nova.airline = strdup(parametros[1]);                                                                        
    nova.plane_model = strdup(parametros[2]);
    nova.total_seats = strdup(parametros[3]);
    nova.origin = strdup(parametros[4]);
    nova.destination = strdup(parametros[5]);
    nova.schedule_departure_date = strdup(parametros[6]);
    nova.schedule_arrival_date = strdup(parametros[7]);
    nova.real_departure_date = strdup(parametros[8]);
    nova.real_arrival_date = strdup(parametros[9]);
    nova.validation = 1;
    return nova;
}

void create_array_flights(char parametros[][FIELD_SIZE]){
    Flight nova = create_flight(parametros);
    int val = validate_flight(parametros);

    if (val == 1){    //se essa linha for válida os seus parâmetros são armazenados no array de voos válidos
        FList list;
        list.init = malloc(sizeof(FNo)); // Asignar memoria para el primer nodo
        list.init->prox = NULL;
        list.init->flight = nova;
        create_array_atrasos(list.init->flight, NUM_LINHAS_VALID_FLIGHT, parametros);
        flights_hash_sort(flight_array_valid, list);
    }
    else{
        complete_files_flights(parametros);
        free(nova.id);
        free(nova.airline);
        free(nova.plane_model);
        free(nova.total_seats);
        free(nova.origin);
        free(nova.destination);
        free(nova.schedule_departure_date);
        free(nova.schedule_arrival_date);
        free(nova.real_departure_date);
        free(nova.real_arrival_date);
    }
}




Passenger *passenger_array_valid = NULL;
int num_linhas_valid_passenger = 0, previous_flight_id_validation = 0;
char previous_flight_id[11] = "0000000000";

Passenger create_passenger(char parametros[][FIELD_SIZE]) {  
    Passenger nova;                                           
    nova.flight_id = strdup(parametros[0]);                         
    nova.user_id = strdup(parametros[1]);                                                                     
    nova.validation_flight = 1;
    nova.validation = 1;
    return nova;
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
                ordena_list_flights(ind_f, flight_array_valid[ind_f].init->flight.schedule_departure_date, parametros[0], &(upointer->user.list_flights), upointer->user.flights);
                break;
            }
            else upointer = upointer->prox;
        }

        //tentar fazer isto noutro ficheiro(modulação)
        ind_f = found_index_flights(parametros[0]); //id_f
        FNo *fpointer = flight_array_valid[ind_f].init;
        while (fpointer != NULL) {
            if (strcmp(parametros[0], fpointer->flight.id) == 0) {
                fpointer->flight.passengers++;
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