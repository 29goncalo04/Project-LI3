#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/Catalogs.h"
#include "../include/Aux_validation.h"
#include "../include/Statistics.h"
#include "../include/Validation.h"
#include "../include/Hash.h"

int validate_passenger(char parametros[][FIELD_SIZE]) {
    int wanted_flight_id_validation = 0, wanted_user_id_validation = 0, ind_u, ind_f;
    FNo *fnodo;
    ind_f = found_index_flights(parametros[0]); //id_voo
    for (fnodo = flight_array_valid[ind_f].init; fnodo != NULL; fnodo = fnodo->prox){   //procura esse id de utilizador no array que tem os utilizadores válidos guardados   
        if (strcmp(parametros[0], fnodo->flight.id)==0){
            wanted_flight_id_validation = 1;
            break;
        }
    }
    if (wanted_flight_id_validation==1){
        UNo *unodo;
        ind_u = found_index_users(parametros[1]); //id_user
        unodo = user_array_valid[ind_u].init;
        for (unodo = user_array_valid[ind_u].init; unodo != NULL; unodo = unodo->prox){   //procura esse id de utilizador no array que tem os utilizadores válidos guardados   
            if (strcmp(parametros[1], unodo->user.id)==0){
                wanted_user_id_validation = 1;
                break;
            }
        }
    }
    return (wanted_flight_id_validation && wanted_user_id_validation);
}

int validate_flight(char parametros[][FIELD_SIZE]){
    int validation = check_length(parametros[0]) && check_length(parametros[1]) && check_length(parametros[2]) &&
                 check_length (parametros[3]) && check_length (parametros[6]) && check_length (parametros[7]) &&
                 check_length(parametros[10]) && check_length(parametros[11]) &&
                 compare_seats_passengers(parametros[3], count_passengers(contador_array, num_linhas_contador, &parametros[3])) &&
                 verify_airport(parametros[4]) && verify_airport(parametros[5]) && compare_date_time(parametros[6], parametros[7]) &&
                 compare_date_time(parametros[8], parametros[9]) && check_dateWtime(parametros[6]) && check_dateWtime(parametros[7]) && 
                 check_dateWtime(parametros[8]) && check_dateWtime(parametros[9]);
    return validation; 
}


int validate_user(char parametros[][FIELD_SIZE]){
    int validation = check_length(parametros[0]) && check_length(parametros[1]) && verify_email(parametros[2]) && check_length(parametros[3]) &&
                 check_length (parametros[4]) && check_date(parametros[4]) && check_length(parametros[5]) && check_length(parametros[6]) &&
                 verify_country_code(parametros[7]) && check_length(parametros[8]) && check_dateWtime(parametros[9]) && check_length(parametros[10]) && 
                 check_length (parametros[11]) && (verify_account_status(parametros[11])==1 || verify_account_status(parametros[11])==2) && compare_date_time(parametros[4], parametros[9]);
    return validation;
}

int validate_reservation(char parametros[][FIELD_SIZE]){
    int validation = 0, wanted_user_id_validation = 0, ind;
    UNo *unodo;
    ind = found_index_users(parametros[1]);
    unodo = user_array_valid[ind].init;
    for (unodo = user_array_valid[ind].init; unodo != NULL; unodo = unodo->prox) {
        if (strcmp(parametros[1], unodo->user.id)==0) {    //encontrou o id desse utilizador no array de utilizadores válidos
            wanted_user_id_validation = 1;
            break;
        }
    }
    if (wanted_user_id_validation==1) {
        validation = check_length(parametros[0]) && check_length(parametros[1]) && check_length(parametros[2]) && check_length(parametros[3]) &&
        verify_hotel_stars(parametros[4]) && check_length (parametros[5]) && verify_city_tax(parametros[5]) && check_length(parametros[6]) &&
        check_date(parametros[7]) && check_date(parametros[8]) && check_length (parametros[9]) && check_price_per_night(parametros[9]) && 
        check_length (parametros[10]) && verify_breakfast(parametros[10]) && check_length(parametros[11]) && check_length (parametros[12]) &&
        check_reserva_rating(parametros[12]) && compare_date_time(parametros[7], parametros[8]);
    }
    return validation;
}