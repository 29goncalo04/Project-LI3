#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Catalogs.h"
#include "../include/Validation.h"
#include "../include/Statistics.h"

User *user_array_valid = NULL;
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
    nova.validation = 1;
    return nova;
}

void create_array_users(char parametros[][FIELD_SIZE]){
    User nova = create_user(parametros);
    validate_user(&nova, parametros);
    if (nova.validation == 1){  //se essa linha for válida os seus parâmetros são armazenados no array de utilizadores válidos
        user_array_valid = realloc(user_array_valid, (num_linhas_valid_user+1)*sizeof(User));
        user_array_valid[num_linhas_valid_user] = nova;
        num_linhas_valid_user++;
    }
    else{
        user_array_invalid = realloc(user_array_invalid, (num_linhas_invalid_user+1)*sizeof(User));
        user_array_invalid[num_linhas_invalid_user] = nova;
        num_linhas_invalid_user++;
    }
}


Reservation *reservation_array_valid = NULL;
Reservation *reservation_array_invalid = NULL;
int num_linhas_invalid_reservation = 0, num_linhas_valid_reservation = 0;

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
    Reservation nova = create_reservation(parametros);
    validate_reservation(&nova, parametros);
    if (nova.validation == 1){  //se essa linha for válida os seus parâmetros são armazenados no array de reservas válidas
        reservation_array_valid = realloc(reservation_array_valid, (num_linhas_valid_reservation+1)*sizeof(Reservation));
        reservation_array_valid[num_linhas_valid_reservation] = nova;
        num_linhas_valid_reservation++;
    }
    else{
        reservation_array_invalid = realloc(reservation_array_invalid, (num_linhas_invalid_reservation+1)*sizeof(Reservation));
        reservation_array_invalid[num_linhas_invalid_reservation] = nova;
        num_linhas_invalid_reservation++;
    }
}


Flight *flight_array_valid = NULL;                          
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
    Flight nova = create_flight(parametros);    //é criado um novo elemento do array com os parâmetros lidos
    validate_flight(&nova, parametros, contador_array, num_linhas_contador);
    if (nova.validation == 1){    //se essa linha for válida os seus parâmetros são armazenados no array de voos válidos
        create_array_atrasos(nova, num_linhas_valid_flight, parametros);
        flight_array_valid = realloc(flight_array_valid, (num_linhas_valid_flight+1)*sizeof(Flight));   
        flight_array_valid[num_linhas_valid_flight] = nova;        //esse novo elemento é adicionado ao array de válidos
        num_linhas_valid_flight++;
    }
    else{
        flight_array_invalid = realloc(flight_array_invalid, (num_linhas_invalid_flight+1)*sizeof(Flight));   
        flight_array_invalid[num_linhas_invalid_flight] = nova;        //esse novo elemento é adicionado ao array de inválidos
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
    if (num_linhas_contador==0) {
        validate_passenger(&nova, parametros, 0);  //se for a primeira vez que está a ler uma linha
        if (nova.validation_flight==0) previous_flight_id_validation = 0;
        else previous_flight_id_validation = 1;
    }
    else{
        if (strcmp(nova.flight_id, previous_flight_id)==0){
            if (previous_flight_id_validation == 1){
                validate_passenger(&nova, parametros, 1);    //se o id de voo que está a ler é igual ao anterior e esse era válido
            }
            else {
                nova.validation = 0;
                previous_flight_id_validation = 0;
                nova.validation_flight = 0;
            }
        }
        else{
            validate_passenger(&nova, parametros, 0);
            if (nova.validation_flight==0) previous_flight_id_validation = 0;
            else previous_flight_id_validation = 1;
        }
    }
    if (nova.validation==1){
        create_array_contador(nova, parametros);
        previous_flight_id_validation = 1;
        strcpy(previous_flight_id, nova.flight_id);
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