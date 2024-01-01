#include <string.h>
#include <stdlib.h>

#include "../include/Catalogs.h"
#include "../include/Aux_validation.h"
#include "../include/Statistics.h"
#include "../include/Validation.h"

void validate_passenger(Passenger *nova, char parametros[][FIELD_SIZE], int flight_validation){
    int wanted_flight_id_validation = 0, wanted_user_id_validation = 0;
    if (flight_validation==1) wanted_flight_id_validation = 1;
    if (flight_validation==0){
        for (int k=0; k<num_linhas_valid_flight; k++){   //procura esse id de voo no array que tem os voos válidos guardados
            if (strcmp(parametros[0], flight_array_valid[k].id)==0){
                wanted_flight_id_validation = 1;
                break;
            }
        }
    }
    if (wanted_flight_id_validation==1){
        for (int l=0; l<num_linhas_valid_user; l++){   //procura esse id de utilizador no array que tem os utilizadores válidos guardados
            if (strcmp(parametros[1], user_array_valid[l].id)==0){
                wanted_user_id_validation = 1;
                break;
            }
        }
    }
    nova->validation_flight = wanted_flight_id_validation;
    nova->validation = wanted_flight_id_validation && wanted_user_id_validation;
}


void validate_flight(Flight *nova, char parametros[][FIELD_SIZE], Contador_id *contador_array, int num_linhas_contador){
    int validation = check_length(parametros[0]) && check_length(parametros[1]) && check_length(parametros[2]) &&
                 check_length (parametros[3]) && check_length (parametros[6]) && check_length (parametros[7]) &&
                 check_length(parametros[10]) && check_length(parametros[11]) &&
                 compare_seats_passengers(parametros[3], count_passengers(contador_array, num_linhas_contador, &parametros[3])) &&
                 verify_airport(parametros[4]) && verify_airport(parametros[5]) && compare_date_time(parametros[6], parametros[7]) &&
                 compare_date_time(parametros[8], parametros[9]) && check_dateWtime(parametros[6]) && check_dateWtime(parametros[7]) && 
                 check_dateWtime(parametros[8]) && check_dateWtime(parametros[9]);
    nova->validation = validation;
}


void validate_user(User *nova, char parametros[][FIELD_SIZE]){
    int validation = check_length(parametros[0]) && check_length(parametros[1]) && verify_email(parametros[2]) && check_length(parametros[3]) &&
                 check_length (parametros[4]) && check_date(parametros[4]) && check_length(parametros[5]) && check_length(parametros[6]) &&
                 verify_country_code(parametros[7]) && check_length(parametros[8]) && check_dateWtime(parametros[9]) && check_length(parametros[10]) && 
                 check_length (parametros[11]) && (verify_account_status(parametros[11])==1 || verify_account_status(parametros[11])==2) && compare_date_time(parametros[4], parametros[9]);
    nova->validation = validation;
    free(nova->account_status);
    nova->account_status = strdup(parametros[11]);
}


void validate_reservation(Reservation *nova, char parametros[][FIELD_SIZE]){
    int validation = 0, wanted_user_id_validation = 0;
    for (int i = 0; i<num_linhas_valid_user; i++){
        if (strcmp(parametros[1], user_array_valid[i].id)==0) {    //encontrou o id desse utilizador no array de utilizadores válidos
            wanted_user_id_validation = 1;
            break;
        }
    }
    if (wanted_user_id_validation==1){
        validation = check_length(parametros[0]) && check_length(parametros[1]) && check_length(parametros[2]) && check_length(parametros[3]) &&
        verify_hotel_stars(parametros[4]) && check_length (parametros[5]) && verify_city_tax(parametros[5]) && check_length(parametros[6]) &&
        check_date(parametros[7]) && check_date(parametros[8]) && check_length (parametros[9]) && check_price_per_night(parametros[9]) && 
        check_length (parametros[10]) && verify_breakfast(parametros[10]) && check_length(parametros[11]) && check_length (parametros[12]) &&
        check_reserva_rating(parametros[12]) && compare_date_time(parametros[7], parametros[8]);
    }
    nova->validation = validation;
    free(nova->includes_breakfast);
    nova->includes_breakfast = strdup(parametros[10]);
}