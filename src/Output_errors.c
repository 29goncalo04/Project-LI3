#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Data_Types_&_Data_Structures.h"
#include "../include/Parser.h"


void create_files() {
    arquivo = fopen("../trabalho-pratico/Resultados/passengers_errors.csv", "w");
    char *passengers_first_line = "flight_id;user_id";
    fprintf(arquivo, "%s\n", passengers_first_line);
    for (int i = 0; i < num_linhas_invalid[0]; i++) {
        fprintf(arquivo, "%s;%s\n",passenger_array_invalid[i].flight_id, passenger_array_invalid[i].user_id);
    }
    fclose(arquivo);

    arquivo = fopen("../trabalho-pratico/Resultados/flights_errors.csv", "w");
    char *flights_first_line = "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes";
    fprintf(arquivo, "%s\n", flights_first_line);
    for (int i = 0; i < num_linhas_invalid[1]; i++) {
        fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",flight_array_invalid[i].id,flight_array_invalid[i].airline,flight_array_invalid[i].plane_model,flight_array_invalid[i].total_seats,flight_array_invalid[i].origin,flight_array_invalid[i].destination,flight_array_invalid[i].schedule_departure_date,flight_array_invalid[i].schedule_arrival_date,flight_array_invalid[i].real_departure_date,flight_array_invalid[i].real_arrival_date,flight_array_invalid[i].pilot,flight_array_invalid[i].copilot, flight_array_invalid[i].notes);
    }
    fclose(arquivo);
    
    arquivo = fopen("../trabalho-pratico/Resultados/reservations_errors.csv", "w");
    char *reservation_first_line = "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment";
    fprintf(arquivo, "%s\n", reservation_first_line);
    for (int i = 0; i < num_linhas_invalid[2]; i++) {
        if (strcmp(reservation_array_invalid[i].includes_breakfast, " ")==0){
            fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;;%s;%s;%s\n",reservation_array_invalid[i].id,reservation_array_invalid[i].user_id,reservation_array_invalid[i].hotel_id,reservation_array_invalid[i].hotel_name,reservation_array_invalid[i].hotel_stars,reservation_array_invalid[i].city_tax,reservation_array_invalid[i].address,reservation_array_invalid[i].begin_date,reservation_array_invalid[i].end_date,reservation_array_invalid[i].price_per_night,reservation_array_invalid[i].room_details,reservation_array_invalid[i].rating,reservation_array_invalid[i].comment);
        }
        else fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",reservation_array_invalid[i].id,reservation_array_invalid[i].user_id,reservation_array_invalid[i].hotel_id,reservation_array_invalid[i].hotel_name,reservation_array_invalid[i].hotel_stars,reservation_array_invalid[i].city_tax,reservation_array_invalid[i].address,reservation_array_invalid[i].begin_date,reservation_array_invalid[i].end_date,reservation_array_invalid[i].price_per_night,reservation_array_invalid[i].includes_breakfast,reservation_array_invalid[i].room_details,reservation_array_invalid[i].rating,reservation_array_invalid[i].comment);
    }
    fclose(arquivo);

    arquivo = fopen("../trabalho-pratico/Resultados/users_errors.csv", "w");
    char *users_first_line = "id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status";
    fprintf(arquivo, "%s\n", users_first_line);
    for (int i = 0; i < num_linhas_invalid[3]; i++) {
        fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",user_array_invalid[i].id,user_array_invalid[i].name,user_array_invalid[i].email,user_array_invalid[i].phone_number,user_array_invalid[i].birth_date,user_array_invalid[i].sex,user_array_invalid[i].passport,user_array_invalid[i].country_code,user_array_invalid[i].address,user_array_invalid[i].account_creation,user_array_invalid[i].pay_method,user_array_invalid[i].account_status);
    }
    fclose(arquivo);
}