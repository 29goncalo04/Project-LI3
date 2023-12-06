#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "../include/Output_queries.h"
#include "../include/Aux_validation.h"
#include "../include/Queries.h"
#include "../include/Aux_functions.h"

FILE *output;

void create_output(int n, int conteudo){    //conteudo = 1 se existir conteudo para escrever nesse ficheiro, e conteudo = 0 se for para criar um ficheiro vazio
    int filename_size = strlen("../trabalho-pratico/Resultados/command1_output.txt");  //calcula o tamanho do nome do ficheiro
    if (n>=10 && n<100) filename_size++;
    else if (n>=100) filename_size++;
    char *filename = (char *)malloc(filename_size + 1); //aloca memória dinamicamente para o nome do ficheiro
    snprintf(filename, filename_size + 1, "../trabalho-pratico/Resultados/command%d_output.txt", n);  //formata o nome do arquivo
    output = fopen(filename, "w");
    free(filename);

    if (output == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        free(filename);
        return;
    }

    if (conteudo==0) fclose(output);
}

void outputs_query1_flights (Flight *flight_array_valid, Contador_id *contador_array, int wanted_id, int wanted_id_2, int index_line, int n) {
    create_output(n, 1);
    if (index_line==2){   //1
      fprintf(output, "%s;%s;%s;%s;%s;%s;%d;%d\n", flight_array_valid[wanted_id].airline, flight_array_valid[wanted_id].plane_model, flight_array_valid[wanted_id].origin, flight_array_valid[wanted_id].destination, flight_array_valid[wanted_id].schedule_departure_date, flight_array_valid[wanted_id].schedule_arrival_date, contador_array[wanted_id_2].contador, delay(flight_array_valid[wanted_id].schedule_departure_date, flight_array_valid[wanted_id].real_departure_date));
    }
    else{   //1F
        fprintf(output, "--- 1 ---\n");
        fprintf(output, "airline: %s\n", flight_array_valid[wanted_id].airline);
        fprintf(output, "plane_model: %s\n", flight_array_valid[wanted_id].plane_model);
        fprintf(output, "origin: %s\n", flight_array_valid[wanted_id].origin);
        fprintf(output, "destination: %s\n", flight_array_valid[wanted_id].destination);
        fprintf(output, "schedule_departure_date: %s\n", flight_array_valid[wanted_id].schedule_departure_date);
        fprintf(output, "schedule_arrival_date: %s\n", flight_array_valid[wanted_id].schedule_arrival_date);
        fprintf(output, "passengers: %d\n", contador_array[wanted_id_2].contador);
        fprintf(output, "delay: %d\n", delay(flight_array_valid[wanted_id].schedule_departure_date, flight_array_valid[wanted_id].real_departure_date));
    }
    fclose(output);
}

void outputs_query1_reservations (Reservation *reservation_array_valid, char *breakfast, int wanted_id, int index_line, int n) {
    create_output(n, 1);
    if (index_line==2){   //1
        fprintf(output, "%s;%s;%s;%s;%s;%s;%d;%.3f\n", reservation_array_valid[wanted_id].hotel_id, reservation_array_valid[wanted_id].hotel_name, reservation_array_valid[wanted_id].hotel_stars, reservation_array_valid[wanted_id].begin_date, reservation_array_valid[wanted_id].end_date, breakfast, nights(reservation_array_valid[wanted_id].begin_date,reservation_array_valid[wanted_id].end_date), total_price(reservation_array_valid[wanted_id].price_per_night, nights(reservation_array_valid[wanted_id].begin_date,reservation_array_valid[wanted_id].end_date), reservation_array_valid[wanted_id].city_tax));
    }
    else{   //1F
        fprintf(output, "--- 1 ---\n");
        fprintf(output, "hotel_id: %s\n", reservation_array_valid[wanted_id].hotel_id);
        fprintf(output, "hotel_name: %s\n", reservation_array_valid[wanted_id].hotel_name);
        fprintf(output, "hotel_stars: %s\n", reservation_array_valid[wanted_id].hotel_stars);
        fprintf(output, "begin_date: %s\n", reservation_array_valid[wanted_id].begin_date);
        fprintf(output, "end_date: %s\n", reservation_array_valid[wanted_id].end_date);
        fprintf(output, "includes_breakfast: %s\n", breakfast);
        fprintf(output, "nights: %d\n", nights(reservation_array_valid[wanted_id].begin_date,reservation_array_valid[wanted_id].end_date));
        fprintf(output, "total_price: %.3f\n", total_price(reservation_array_valid[wanted_id].price_per_night, nights(reservation_array_valid[wanted_id].begin_date,reservation_array_valid[wanted_id].end_date), reservation_array_valid[wanted_id].city_tax));
    }
    fclose(output);
}

void outputs_query1_users (User *user_array_valid, double total_spent, int reservations, int wanted_id, int index_line, int n) {
    create_output(n, 1);
    if (index_line==2){   //1
        fprintf(output, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", user_array_valid[wanted_id].name, user_array_valid[wanted_id].sex, age_user(user_array_valid[wanted_id].birth_date),user_array_valid[wanted_id].country_code, user_array_valid[wanted_id].passport, number_of_flights(user_array_valid[wanted_id].id), reservations, total_spent);
    }
    else{   //1F
        fprintf(output, "--- 1 ---\n");
        fprintf(output, "name: %s\n", user_array_valid[wanted_id].name);
        fprintf(output, "sex: %s\n", user_array_valid[wanted_id].sex);
        fprintf(output, "age: %d\n", age_user(user_array_valid[wanted_id].birth_date));
        fprintf(output, "country_code: %s\n", user_array_valid[wanted_id].country_code);
        fprintf(output, "passport: %s\n", user_array_valid[wanted_id].passport);
        fprintf(output, "number_of_flights: %d\n", number_of_flights(user_array_valid[wanted_id].id));
        fprintf(output, "number_of_reservations: %d\n", reservations);
        fprintf(output, "total_spent: %.3f\n", total_spent);
    }
    fclose(output);
}

void outputs_query2 (Flight_aux *flight_aux_array, Reservation_aux *reservation_aux_array, int index_line, char *argument2, int num_flights_passenger_id, int num_reservations, int n) {
    create_output(n, 1);
    if (index_line==2){ //2
    if (strcmp(argument2, "flights")==0){  //só lista os voos
        for (int i = 0; i<num_flights_passenger_id; i++){
            fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
        }
    }
    else if(strcmp(argument2, "reservations")==0){  //só lista as reservas
            for (int i = 0; i<num_reservations; i++){
                fprintf(output, "%s;%s%s\n", reservation_aux_array[i].reservation_id, reservation_aux_array[i].begin_date, reservation_aux_array[i].type);
            }
        }
        else{
            for (int i = 0, j = 0; i<num_flights_passenger_id || j<num_reservations;){
                if(i==num_flights_passenger_id){   //já só há informações de reservas para serem impressas
                    fprintf(output, "%s;%s%s\n", reservation_aux_array[j].reservation_id, reservation_aux_array[j].begin_date, reservation_aux_array[j].type);
                    j++;
                }
                else if (j==num_reservations){   //já só há informações de voos para serem impressas
                    fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
                    i++;
                }
                    else{
                        if (strcmp(flight_aux_array[i].schedule_departure_date, reservation_aux_array[j].begin_date)==0){
                            fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
                            i++;
                            fprintf(output, "%s;%s%s\n", reservation_aux_array[j].reservation_id, reservation_aux_array[j].begin_date, reservation_aux_array[j].type);
                            j++;
                        }
                        else if (compare_date_time2(flight_aux_array[i].schedule_departure_date, reservation_aux_array[j].begin_date)>0){
                            fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
                            i++;
                        }
                            else if (compare_date_time2(flight_aux_array[i].schedule_departure_date, reservation_aux_array[j].begin_date)<0){
                                fprintf(output, "%s;%s%s\n", reservation_aux_array[j].reservation_id, reservation_aux_array[j].begin_date, reservation_aux_array[j].type);
                                j++;
                            }
                    }
            }
        }
    }
    else{  //2F
        if (strcmp(argument2, "flights")==0){  //só lista os voos
            for (int i = 1; i<=num_flights_passenger_id; i++){
                fprintf(output, "--- %d ---\n", i);
                fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
                fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
                if (i!=num_flights_passenger_id) fprintf(output, "\n");
            }
        }
        else if (strcmp(argument2, "reservations")==0){  //só lista as reservas
            for (int i = 1; i<=num_reservations; i++){
                fprintf(output, "--- %d ---\n", i);
                fprintf(output, "id: %s\n", reservation_aux_array[i-1].reservation_id);
                fprintf(output, "date: %s\n", reservation_aux_array[i-1].begin_date);
                if (i!=num_reservations) fprintf(output, "\n");
            }
        }
        else{  //lista voos e reservas
            for (int i = 1, j = 1; i<=num_flights_passenger_id || j<=num_reservations;){
                fprintf(output, "--- %d ---\n", (i+j-1));
                if(i==num_flights_passenger_id+1){   //já só há informações de reservas para serem impressas
                        fprintf(output, "id: %s\n", reservation_aux_array[j-1].reservation_id);
                        fprintf(output, "date: %s\n", reservation_aux_array[j-1].begin_date);
                        fprintf(output, "type: reservation\n");
                        if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                        j++;
                }
                else if (j==num_reservations+1){   //já só há informações de voos para serem impressas
                        fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
                        fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
                        fprintf(output, "type: flight\n");
                        if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                        i++;
                }
                else if (strcmp(flight_aux_array[i-1].schedule_departure_date, reservation_aux_array[j-1].begin_date)==0){
                    fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
                    fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
                    fprintf(output, "type: flight\n");
                    i++;
                    fprintf(output, "\n");
                    fprintf(output, "--- %d ---\n", (i+j-1));
                    fprintf(output, "id: %s\n", reservation_aux_array[j-1].reservation_id);
                    fprintf(output, "date: %s\n", reservation_aux_array[j-1].begin_date);
                    fprintf(output, "type: reservation\n");
                    if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                    j++;
                }
                else if (compare_date_time(flight_aux_array[i-1].schedule_departure_date, reservation_aux_array[j-1].begin_date)==0){
                    //fprintf(output, "--- %d -ok--\n", (i+j-1));
                    fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
                    fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
                    fprintf(output, "type: flight\n");
                    if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                    i++;
                }
                else if (compare_date_time(flight_aux_array[i-1].schedule_departure_date, reservation_aux_array[j-1].begin_date)==1){
                    fprintf(output, "--- %d ---\n", (i+j-1));        //////////////////////////////////////////////////////////////////////////////////////////
                    fprintf(output, "id: %s\n", reservation_aux_array[j-1].reservation_id);
                    fprintf(output, "date: %s\n", reservation_aux_array[j-1].begin_date);
                    fprintf(output, "type: reservation\n");
                    if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                    j++;
                }
            }
        }
    }
    fclose(output);
}

void outputs_query3 (double media, int flag, int n) {
    create_output(n, 1);
    if (flag == 0)   //3
        fprintf(output, "%.3f\n", media);
    else {   //3F
        fprintf(output, "--- 1 ---\n");
        fprintf(output, "rating: %.3f\n", media);
    }
    fclose(output);
}

void outputs_query4 (hotel_aux *hotel_aux_array, int index_line, int num_hotels, int n) {
    create_output(n, 1);
    if (index_line==2) {  // 4
        for (int j=0; j<num_hotels; j++) fprintf (output, "%s;%s;%s;%s;%s;%.3f\n", hotel_aux_array[j].id, hotel_aux_array[j].begin_date, hotel_aux_array[j].end_date, hotel_aux_array[j].user_id, hotel_aux_array[j].rating, hotel_aux_array[j].total_price);
    }
    else {  // 4F
        for (int j=0; j<num_hotels; j++) {
            fprintf(output, "--- %d ---\n", j+1);
            fprintf(output, "id: %s\n", hotel_aux_array[j].id);
            fprintf(output, "begin_date: %s\n", hotel_aux_array[j].begin_date);
            fprintf(output, "end_date: %s\n", hotel_aux_array[j].end_date);
            fprintf(output, "user_id: %s\n", hotel_aux_array[j].user_id);
            fprintf(output, "rating: %s\n", hotel_aux_array[j].rating);
            fprintf(output, "total_price: %.3f\n", hotel_aux_array[j].total_price);
            if (j!=num_hotels-1) fprintf(output, "\n");
        }
    }
    fclose (output);
}

void outputs_query5 (flight_date_aux *flight_date_aux_array, int index1_line, int num_flights, int n) {
    create_output(n, 1);
    if (index1_line==2) {  // 5
        for (int j=0; j<num_flights; j++) {
            char *destination_cpy = flight_date_aux_array[j].destination;
            toUpperCase(destination_cpy);
            fprintf (output, "%s;%s;%s;%s;%s\n", flight_date_aux_array[j].id, flight_date_aux_array[j].schedule_departure_date, destination_cpy, flight_date_aux_array[j].airline, flight_date_aux_array[j].plane_model);
        }
    }
    else {  // 5F
        for (int j=0; j<num_flights; j++) {
            char *destination_cpy = flight_date_aux_array[j].destination;
            toUpperCase(destination_cpy);
            fprintf(output, "--- %d ---\n", j+1);
            fprintf(output, "id: %s\n", flight_date_aux_array[j].id);
            fprintf(output, "schedule_departure_date: %s\n", flight_date_aux_array[j].schedule_departure_date);
            fprintf(output, "destination: %s\n", destination_cpy);
            fprintf(output, "airline: %s\n", flight_date_aux_array[j].airline);
            fprintf(output, "plane_model: %s\n", flight_date_aux_array[j].plane_model);
            if (j!=num_flights-1) fprintf(output, "\n");
        }
    }
    fclose (output);
}

void outputs_query6 (PassengersXairport *passengersXairport_array, int index_pXa, int top, int flag, int n) {
    create_output(n, 1);
    if (flag == 0){   //6
        for (index_pXa = 0; index_pXa < top; index_pXa++) {
            fprintf(output, "%s;%d\n", passengersXairport_array[index_pXa].origin, passengersXairport_array[index_pXa].passengers);
        }
    }
    else {          //6F
        for (index_pXa = 0; index_pXa < top; index_pXa++) {
            fprintf(output, "--- %d ---\n",index_pXa+1);
            fprintf(output, "name: %s\n", passengersXairport_array[index_pXa].origin);
            fprintf(output, "passengers: %d\n", passengersXairport_array[index_pXa].passengers);
            if (index_pXa+1 != top) fprintf(output, "\n");
        }
    }
    fclose(output);
}

void outputs_query7 (Mediana *mediana_array, int index_line, int N, int n) {
    create_output(n, 1);
    for (int i = 0; i<N; i++){
        if (index_line==2){   //7
            fprintf(output, "%s;%d\n", mediana_array[i].airport, mediana_array[i].mediana);
        }
        else{   //7F
            fprintf(output, "--- %d ---\n", i+1);
            fprintf(output, "name: %s\n", mediana_array[i].airport);
            fprintf(output, "median: %d\n", mediana_array[i].mediana);
            if (i!=N-1) fprintf(output, "\n");
        }
    }
    fclose(output);
}

void outputs_query9 (idXname *idXname_array, int num_linhas_idXname, int flag, int n) {
    create_output(n, 1);
    if (flag == 0){   //9
        for (int index_idXn = 0; index_idXn < num_linhas_idXname; index_idXn++) {
            fprintf(output, "%s;%s\n", idXname_array[index_idXn].id, idXname_array[index_idXn].name);
        }
    }
    else {          //9F
        for (int index_idXn = 0; index_idXn < num_linhas_idXname; index_idXn++) {
            fprintf(output, "--- %d ---\n",index_idXn+1);
            fprintf(output, "id: %s\n", idXname_array[index_idXn].id);
            fprintf(output, "name: %s\n", idXname_array[index_idXn].name);
            if (index_idXn+1 != num_linhas_idXname) fprintf(output, "\n");
        }
    }
    fclose(output);
}