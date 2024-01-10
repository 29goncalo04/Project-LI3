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

UList *user_array_valid = NULL;
User *user_array_invalid = NULL;
int num_linhas_invalid_user = 0, num_linhas_valid_user = 0;

User create_user(char parametros[][FIELD_SIZE]) {    
    User nova;                                           
    nova.id = strdup(parametros[0]);                          
    nova.name = strdup(parametros[1]);
    nova.email = strdup(parametros[2]);
    nova.phone_number = strdup(parametros[3]);
    nova.birth_date = strdup(parametros[4]);
    nova.sex = strdup(parametros[5]);
    nova.passport = strdup(parametros[6]);
    nova.country_code = strdup(parametros[7]);
    nova.address = strdup(parametros[8]);
    nova.account_creation = strdup(parametros[9]);
    nova.pay_method = strdup(parametros[10]);
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
    UList list;
    list.init = malloc(sizeof(UNo)); // Asignar memoria para el primer nodo
    list.init->prox = NULL;
    list.init->user = create_user(parametros);
    list.tam = 1;

    validate_user(&(list.init->user), parametros);
    if (list.init->user.validation == 1) {
        user_array_valid = realloc(user_array_valid, (num_linhas_valid_user + 1) * sizeof(UList));
        user_array_valid[num_linhas_valid_user] = list;
        num_linhas_valid_user++;
        free(list.init->user.email);
        free(list.init->user.phone_number);
        free(list.init->user.address);
        free(list.init->user.pay_method);
    } else {
        user_array_invalid = realloc(user_array_invalid, (num_linhas_invalid_user + 1) * sizeof(User));
        user_array_invalid[num_linhas_invalid_user] = list.init->user;
        num_linhas_invalid_user++;
    }
}

RList *reservation_array_valid = NULL;
Reservation *reservation_array_invalid = NULL;
int num_linhas_valid_reservation = 0, num_linhas_invalid_reservation = 0;

Reservation create_reservation(char parametros[][FIELD_SIZE]) {  
    Reservation nova;                                              
    nova.id = strdup(parametros[0]);                                   
    nova.user_id = strdup(parametros[1]);
    nova.hotel_id = strdup(parametros[2]);
    nova.hotel_name = strdup(parametros[3]);
    nova.hotel_stars = strdup(parametros[4]);
    nova.city_tax = strdup(parametros[5]);
    nova.address = strdup(parametros[6]);
    nova.begin_date = strdup(parametros[7]);
    nova.end_date = strdup(parametros[8]);
    nova.price_per_night = strdup(parametros[9]);
    nova.includes_breakfast = strdup(parametros[10]);
    nova.room_details = strdup(parametros[11]);
    nova.rating = strdup(parametros[12]);
    nova.comment = strdup(parametros[13]);
    nova.validation = 1;
    return nova;
}

void create_array_reservations(char parametros[][FIELD_SIZE]){
    RList list;
    list.init = malloc(sizeof(RNo)); // Asignar memoria para el primer nodo
    list.init->prox = NULL;
    list.init->reservation = create_reservation(parametros);
    list.tam = 1;

    validate_reservation(&(list.init->reservation), parametros);
    if (list.init->reservation.validation == 1){  //se essa linha for válida os seus parâmetros são armazenados no array de reservas válidas
        
        //tentar fazer isto noutro ficheiro(modulação)
        int ind = found_index_users(list.init->reservation.user_id); 
        UNo *pointer = user_array_valid[ind].init;
        while (pointer != NULL) {
            if (strcmp(list.init->reservation.user_id, pointer->user.id) == 0) {
                //printf("antes de esto\n");
                pointer->user.list_reservations = realloc(pointer->user.list_reservations, (pointer->user.reservations+1)*sizeof(int));
                pointer->user.list_reservations[pointer->user.reservations] = -1;
                pointer->user.reservations++;
                // printf("%s tiene: %d reservas-> ", pointer->user.id, pointer->user.reservations);
                // for (int i = 0; i < pointer->user.reservations; i++) {
                //     printf("%d ", pointer->user.list_reservations[i]);
                // }
                // printf("\n");
                //printf("despues de realocar memoria, guardar un -1 y aumentar el tamaño\n");
                //printf("sumado, actual: %d\n", pointer->user.reservations);
                pointer->user.total_spent += total_price(list.init->reservation.price_per_night, nights(list.init->reservation.begin_date, list.init->reservation.end_date), list.init->reservation.city_tax);
                //printf("sumado, actual: %f\n", pointer->user.total_spent);
                break;
            }
            else pointer = pointer->prox;
        }
        
        reservation_array_valid = realloc(reservation_array_valid, (num_linhas_valid_reservation+1)*sizeof(RList));
        reservation_array_valid[num_linhas_valid_reservation] = list;
        num_linhas_valid_reservation++;
        free(list.init->reservation.address);
        free(list.init->reservation.room_details);
        free(list.init->reservation.comment);
    }
    else{
        //create_files_reservations(parametros);
        reservation_array_invalid = realloc(reservation_array_invalid, (num_linhas_invalid_reservation+1)*sizeof(Reservation));
        reservation_array_invalid[num_linhas_invalid_reservation] = list.init->reservation;
        num_linhas_invalid_reservation++;
    }
}

FList *flight_array_valid = NULL; 
Flight *flight_array_invalid = NULL;
int num_linhas_invalid_flight = 0, num_linhas_valid_flight = 0;

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
    nova.pilot = strdup(parametros[10]);
    nova.copilot = strdup(parametros[11]);
    nova.notes = strdup(parametros[12]);
    nova.validation = 1;
    return nova;
}

void create_array_flights(char parametros[][FIELD_SIZE]){
    FList list;
    list.init = malloc(sizeof(FNo)); // Asignar memoria para el primer nodo
    list.init->prox = NULL;
    list.init->flight = create_flight(parametros);
    list.tam = 1;

    validate_flight(&(list.init->flight), parametros);
    if (list.init->flight.validation == 1){    //se essa linha for válida os seus parâmetros são armazenados no array de voos válidos
        create_array_atrasos(list.init->flight, num_linhas_valid_flight, parametros);
        flight_array_valid = realloc(flight_array_valid, (num_linhas_valid_flight+1)*sizeof(FList));   
        flight_array_valid[num_linhas_valid_flight] = list;        //esse novo elemento é adicionado ao array de válidos
        num_linhas_valid_flight++;
        free(list.init->flight.pilot);
        free(list.init->flight.copilot);
        free(list.init->flight.notes);
    }
    else{
        flight_array_invalid = realloc(flight_array_invalid, (num_linhas_invalid_flight+1)*sizeof(Flight));   
        flight_array_invalid[num_linhas_invalid_flight] = list.init->flight;        //esse novo elemento é adicionado ao array de inválidos
        num_linhas_invalid_flight++;
    }
}




Passenger *passenger_array_valid = NULL;
Passenger *passenger_array_invalid = NULL;
int num_linhas_invalid_passenger = 0, num_linhas_valid_passenger = 0, previous_flight_id_validation = 0;
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
    Passenger nova = create_passenger(parametros);
    int ind_u, ind_f, val;
    val = validate_passenger(parametros);
    if (val==1){

        create_array_contador(nova, parametros);            //basura que va ser borrada
        previous_flight_id_validation = 1;                  //basura que va ser borrada
        strcpy(previous_flight_id, nova.flight_id);         //basura que va ser borrada

        //tentar fazer isto noutro ficheiro(modulação)
        ind_u = found_index_users(parametros[1]); //id_u
        UNo *upointer = user_array_valid[ind_u].init;
        while (upointer != NULL) {
            //printf("%s\n", upointer->user.id);
            if (strcmp(parametros[1], upointer->user.id) == 0) {
                //printf("somando\n");
                upointer->user.list_flights = realloc(upointer->user.list_flights, (upointer->user.flights+1)*sizeof(int));
                upointer->user.list_flights[upointer->user.flights] = -1;
                upointer->user.flights++;

                //maybe seria bom fazer isto noutro modulo
                ind_f = found_index_flights(parametros[0]);
                ordena_list_flights(ind_f, only_date(flight_array_valid[ind_f].init->flight.schedule_departure_date), parametros[0], &(upointer->user.list_flights), upointer->user.flights);

                // printf("%s tiene num_voos: %d\n", parametros[1], upointer->user.flights);
                // if (strcmp("JéssiTavares910", parametros[1]) == 0) sleep(1);
                break;
            }
            else upointer = upointer->prox;
            //sleep(2);
        }

        //tentar fazer isto noutro ficheiro(modulação)
        ind_f = found_index_flights(parametros[0]); //id_f
        FNo *fpointer = flight_array_valid[ind_f].init;
        while (fpointer != NULL) {
            if (strcmp(parametros[0], fpointer->flight.id) == 0) {
                //printf("somando\n");
                fpointer->flight.passengers++;
                break;
            }
            else fpointer = fpointer->prox;
        }

        passenger_array_valid = realloc(passenger_array_valid, (num_linhas_valid_passenger+1)*sizeof(Passenger));
        passenger_array_valid[num_linhas_valid_passenger] = nova;
        num_linhas_valid_passenger++;
    }
    else{
        strcpy(previous_flight_id, nova.flight_id);
        passenger_array_invalid = realloc(passenger_array_invalid, (num_linhas_invalid_passenger+1)*sizeof(Passenger));
        passenger_array_invalid[num_linhas_invalid_passenger] = nova;
        num_linhas_invalid_passenger++;
    }
}