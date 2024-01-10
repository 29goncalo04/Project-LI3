#include "../include/Parser.h"
#include "../include/Catalogs.h"
#include "../include/Output_errors.h"
#include "../include/Free.h"

void start_files_passengers() {
    arquivo = fopen("../trabalho-pratico/Resultados/passengers_errors.csv", "w");
    char *passengers_first_line = "flight_id;user_id";
    fprintf(arquivo, "%s\n", passengers_first_line);
    fclose(arquivo);
}

void complete_files_passengers(char parametros[][FIELD_SIZE]) {
    arquivo = fopen("../trabalho-pratico/Resultados/passengers_errors.csv", "a");
    fprintf(arquivo, "%s;%s\n", parametros[0], parametros[1]);
    fclose(arquivo);
}

void start_files_flights() {
    arquivo = fopen("../trabalho-pratico/Resultados/flights_errors.csv", "w");
    char *flights_first_line = "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes";
    fprintf(arquivo, "%s\n", flights_first_line);
    fclose(arquivo);
}

void complete_files_flights(char parametros[][FIELD_SIZE]) {
    arquivo = fopen("../trabalho-pratico/Resultados/flights_errors.csv", "a");
    fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", parametros[0], parametros[1], parametros[2], parametros[3], parametros[4], parametros[5], parametros[6], parametros[7], parametros[8], parametros[9], parametros[10], parametros[11], parametros[12]);
    fclose(arquivo);
}

void start_files_reservations() {
    arquivo = fopen("../trabalho-pratico/Resultados/reservations_errors.csv", "w");
    char *reservation_first_line = "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment";
    fprintf(arquivo, "%s\n", reservation_first_line);
    fclose(arquivo);
}

void complete_files_reservations(char parametros[][FIELD_SIZE]) {
    arquivo = fopen("../trabalho-pratico/Resultados/reservations_errors.csv", "a");
    if (strcmp(parametros[10], " ")==0){
        fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;;%s;%s;%s\n", parametros[0], parametros[1], parametros[2], parametros[3], parametros[4], parametros[5], parametros[6], parametros[7], parametros[8], parametros[9], parametros[11], parametros[12], parametros[13]);
    }
    else fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", parametros[0], parametros[1], parametros[2], parametros[3], parametros[4], parametros[5], parametros[6], parametros[7], parametros[8], parametros[9], parametros[10], parametros[11], parametros[12], parametros[13]);
    fclose(arquivo);
}

void start_files_users() {
    arquivo = fopen("../trabalho-pratico/Resultados/users_errors.csv", "w");
    char *users_first_line = "id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status";
    fprintf(arquivo, "%s\n", users_first_line);
    fclose(arquivo);
}

void complete_files_users(char parametros[][FIELD_SIZE]) {
    arquivo = fopen("../trabalho-pratico/Resultados/users_errors.csv", "a");
    fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", parametros[0], parametros[1], parametros[2], parametros[3], parametros[4], parametros[5], parametros[6], parametros[7], parametros[8], parametros[9], parametros[10], parametros[11]);
    fclose(arquivo);
}