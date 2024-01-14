#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "../include/Output_queries.h"
#include "../include/Aux_validation.h"
#include "../include/Queries.h"
#include "../include/Aux_functions.h"
#include "../include/Catalogs.h"

FILE *output;

void create_output(int check, int n){    //conteudo = 1 se existir conteudo para escrever nesse ficheiro, e conteudo = 0 se for para criar um ficheiro vazio
    int filename_size = strlen("../trabalho-pratico/Resultados/command1_output.txt");  //calcula o tamanho do nome do ficheiro
    if (n>=10 && n<100) filename_size++;
    else if (n>=100) filename_size = filename_size + 2;
    char *filename = (char *)malloc(filename_size + 1); //aloca memória dinamicamente para o nome do ficheiro
    snprintf(filename, filename_size + 1, "../trabalho-pratico/Resultados/command%d_output.txt", n);  //formata o nome do arquivo
    output = fopen(filename, "w");
    free(filename);
    if (output == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }
    if (check == 0) fclose(output);
}

void outputs_query1_flights (const FNo *pointer, int flag, int n) {
    create_output(1, n);
    if (flag==0){   //1
        fprintf(output, "%s;%s;%s;%s;%s;%s;%d;%d\n", get_flight_airline(pointer), get_flight_plane_model(pointer), get_flight_origin(pointer), get_flight_destination(pointer), get_flight_schedule_departure_date(pointer), get_flight_schedule_arrival_date(pointer), get_flight_passengers(pointer), delay(get_flight_schedule_departure_date(pointer), get_flight_real_departure_date(pointer)));
    }
    else{   //1F
        fprintf(output, "--- 1 ---\n");
        fprintf(output, "airline: %s\n", get_flight_airline(pointer));
        fprintf(output, "plane_model: %s\n", get_flight_plane_model(pointer));
        fprintf(output, "origin: %s\n", get_flight_origin(pointer));
        fprintf(output, "destination: %s\n", get_flight_destination(pointer));
        fprintf(output, "schedule_departure_date: %s\n", get_flight_schedule_departure_date(pointer));
        fprintf(output, "schedule_arrival_date: %s\n", get_flight_schedule_arrival_date(pointer));
        fprintf(output, "passengers: %d\n", get_flight_passengers(pointer));
        fprintf(output, "delay: %d\n", delay(get_flight_schedule_departure_date(pointer), get_flight_real_departure_date(pointer)));
    }
    
    fclose(output);
}

void outputs_query1_reservations (const RNo *pointer,  char *breakfast, int flag, int n) {
    create_output(1, n);
    if (flag==0){   //1
        fprintf(output, "%s;%s;%d;%s;%s;%s;%d;%.3f\n", get_reservation_hotel_id(pointer), get_reservation_hotel_name(pointer), get_reservation_hotel_stars(pointer), get_reservation_begin_date(pointer), get_reservation_end_date(pointer), breakfast, nights(get_reservation_begin_date(pointer),get_reservation_end_date(pointer)), total_price(get_reservation_price_per_night(pointer), nights(get_reservation_begin_date(pointer),get_reservation_end_date(pointer)), get_reservation_city_tax(pointer)));
    }
    else{   //1F
        fprintf(output, "--- 1 ---\n");
        fprintf(output, "hotel_id: %s\n", get_reservation_hotel_id(pointer));
        fprintf(output, "hotel_name: %s\n", get_reservation_hotel_name(pointer));
        fprintf(output, "hotel_stars: %d\n", get_reservation_hotel_stars(pointer));
        fprintf(output, "begin_date: %s\n", get_reservation_begin_date(pointer));
        fprintf(output, "end_date: %s\n", get_reservation_end_date(pointer));
        fprintf(output, "includes_breakfast: %s\n", breakfast);
        fprintf(output, "nights: %d\n", nights(get_reservation_begin_date(pointer),get_reservation_end_date(pointer)));
        fprintf(output, "total_price: %.3f\n", total_price(get_reservation_price_per_night(pointer), nights(get_reservation_begin_date(pointer),get_reservation_end_date(pointer)), get_reservation_city_tax(pointer)));
    }
    fclose(output);
}

void outputs_query1_users (const UNo *pointer, int flag, int check, int n) {
    create_output(check, n);
    if (check == 1) {
        if (flag == 1) {
            fprintf(output, "--- 1 ---\n");
            fprintf(output, "name: %s\n", get_user_name(pointer));
            fprintf(output, "sex: %s\n", get_user_sex(pointer));
            fprintf(output, "age: %d\n", age_user(get_user_birth_date(pointer)));
            fprintf(output, "country_code: %s\n", get_user_country_code(pointer));
            fprintf(output, "passport: %s\n", get_user_passport(pointer));
            fprintf(output, "number_of_flights: %d\n", get_user_flights(pointer));
            fprintf(output, "number_of_reservations: %d\n", get_user_reservations(pointer));
            fprintf(output, "total_spent: %.3f\n", get_user_total_spent(pointer));
        } else fprintf(output, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", get_user_name(pointer), get_user_sex(pointer), age_user(get_user_birth_date(pointer)),get_user_country_code(pointer), get_user_passport(pointer), get_user_flights(pointer), get_user_reservations(pointer), get_user_total_spent(pointer));
        fclose(output);    
    }
}

void outputs_query2_reservations(const int *list, int tam, int flag, int check, int n) {
    create_output(check, n);
    if (check == 1) {
        if (flag == 1) {
            int ind;
            for (int i = tam - 1, num = 1; 0 <= i; i--, num++) {
                ind = list[i];
                fprintf(output, "--- %d ---\n", num);
                fprintf(output, "id: %s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind))));
                if (i == 0) fprintf(output, "date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))));
                else {
                    fprintf(output, "date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))));
                    fprintf(output, "\n");
                }
            }
        }
        else {
            int ind;
            for (int i = tam - 1; 0 <= i; i--) {
                ind = list[i];
                if (i == 0) fprintf(output, "%s;%s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind))), get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))));
                else fprintf(output, "%s;%s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind))), get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))));
            }
        }
        fclose(output);
    }
}

void outputs_query2_flights(const int *list, int tam, int flag, int check, int n) {
    create_output(check, n);
    if (check == 1) {
        if (flag == 1) {
            int ind;
            for (int i = tam - 1, num = 1; 0 <= i; i--, num++) {
                ind = list[i];
                fprintf(output, "--- %d ---\n", num);
                fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind))));
                char *only_date_aux = only_date2(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind))));
                if (i == 0) fprintf(output, "date: %s\n", only_date_aux);
                else {
                    fprintf(output, "date: %s\n", only_date_aux);
                    fprintf(output, "\n");
                }
                free(only_date_aux);
            }
        }
        else {
            int ind;
            for (int i = tam - 1; 0 <= i; i--) {
                ind = list[i];
                char *only_date_aux = only_date2(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind))));
                if (i == 0) fprintf(output, "%s;%s\n", get_flight_id(getFListInit(get_flight_array_valid(ind))), only_date_aux);
                else fprintf(output, "%s;%s\n", get_flight_id(getFListInit(get_flight_array_valid(ind))), only_date_aux);
                free(only_date_aux);
            }
        }
        fclose(output);
    }
}

void outputs_query2_both(const int *list_f, int tam_f, const int *list_r, int tam_r, int flag, int check, int n) {
    create_output(check, n);
    if (check == 1) {
        int check_date, ind_f, ind_r, i = tam_r - 1, j = tam_f - 1, num = 1;
        if (flag == 1) {
            while (0 <= i || 0 <= j) {
                if (0<=i && j==-1) {
                    for (; 0 <= i; i--, num++) {
                        ind_r = list_r[i];
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "type: reservation\n");
                        if(i != 0) fprintf(output, "\n");
                    }
                    fclose(output);
                    return;
                }

                if (0<=j && i==-1) {
                    for (; 0 <= j; j--, num++) {
                        ind_f = list_f[j];
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind_f))));
                        char *only_date_aux = only_date2(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind_f))));
                        fprintf(output, "date: %s\n", only_date_aux);
                        free(only_date_aux);
                        fprintf(output, "type: flight\n");
                        if(j != 0) fprintf(output, "\n");
                    }
                    fclose(output);
                    return;
                }

                ind_f = list_f[j];
                ind_r = list_r[i];
                char *only_date_aux = only_date2(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind_f))));
                if (strcmp(only_date_aux, get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r)))) != 0) {
                    check_date = compare_date_time3(only_date_aux, get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                    if (check_date == 1) {
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "type: reservation\n");
                        fprintf(output, "\n");
                        i--;
                    }
                    else {
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind_f))));
                        fprintf(output, "date: %s\n", only_date_aux);
                        fprintf(output, "type: flight\n");
                        fprintf(output, "\n");
                        j--;
                    }
                } 
                else {
                    if (atoi(get_flight_id(getFListInit(get_flight_array_valid(ind_f)))) - atoi(get_reservation_id(getRListInit(get_reservation_array_valid(ind_r)))) > 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind_f))));
                        fprintf(output, "date: %s\n", only_date_aux);
                        fprintf(output, "type: flight\n");
                        fprintf(output, "\n");
                        j--;
                    }
                    else{
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "type: reservation\n");
                        fprintf(output, "\n");
                        i--;
                    }
                }
                free(only_date_aux);
                num++;
            }
            fclose(output);
            return;
        }
        else {
            while (0 <= i || 0 <= j) {
                if (0<=i && j==-1) {
                    for (; 0 <= i; i--, num++) {
                        ind_r = list_r[i];
                        fprintf(output, "%s;%s;reservation\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))), get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                    }
                    fclose(output);
                    return;
                }

                if (0<=j && i==-1) {
                    for (; 0 <= j; j--, num++) {
                        ind_f = list_f[j];
                        char *only_date_aux = only_date2(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind_f))));
                        fprintf(output, "%s;%s;flight\n", get_flight_id(getFListInit(get_flight_array_valid(ind_f))), only_date_aux);
                        free(only_date_aux);
                    }
                    fclose(output);
                    return;
                }
                
                ind_r = list_r[i];
                ind_f = list_f[j];
                char *only_date_aux = only_date2(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind_f))));
                if (strcmp(only_date_aux, get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r)))) != 0) {
                    check_date = compare_date_time3(only_date_aux, get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                    if (check_date == 1) {
                        fprintf(output, "%s;%s;reservation\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))), get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                        i--;
                    }
                    else {
                        fprintf(output, "%s;%s;flight\n",get_flight_id(getFListInit(get_flight_array_valid(ind_f))), only_date_aux);
                        j--;
                    }
                } 
                else {
                    if (atoi(get_flight_id(getFListInit(get_flight_array_valid(ind_f)))) - atoi(get_reservation_id(getRListInit(get_reservation_array_valid(ind_r)))) > 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                        fprintf(output, "%s;%s;flight\n", get_flight_id(getFListInit(get_flight_array_valid(ind_f))), only_date_aux);
                        j--;
                    }
                    else{
                        fprintf(output, "%s;%s;reservation\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))), get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                        i--;
                    }
                }
                free(only_date_aux);
                num++;
            }
            fclose(output);
            return;
        }
    }
    return;
}

void outputs_query3(double med, int flag, int check, int n) {
    create_output(check, n);
    if (check == 1) {
        if (flag == 0) fprintf(output, "%.3f\n", med);//3
        else {   //3F
            fprintf(output, "--- 1 ---\n");
            fprintf(output, "rating: %.3f\n", med);
        }
        fclose(output);
    }
}

void outputs_query4(const int *list, int num_reservations, int flag, int check, int n) {
    create_output(check, n);
    if (check == 1) {
        if (flag == 0) {
            for (int i = 0; i<num_reservations; i++){
                int ind = list[i];
                fprintf (output, "%s;%s;%s;%s;%d;%.3f\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind))), get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))), get_reservation_end_date(getRListInit(get_reservation_array_valid(ind))), get_reservation_user_id(getRListInit(get_reservation_array_valid(ind))), get_reservation_rating(getRListInit(get_reservation_array_valid(ind))), total_price(get_reservation_price_per_night(getRListInit(get_reservation_array_valid(ind))), nights(get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))), get_reservation_end_date(getRListInit(get_reservation_array_valid(ind)))), get_reservation_city_tax(getRListInit(get_reservation_array_valid(ind)))));
            }
        }
        else {   //4F
            for (int i = 0; i<num_reservations; i++) {
                int ind = list[i];
                fprintf(output, "--- %d ---\n", i+1);
                fprintf(output, "id: %s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind))));
                fprintf(output, "begin_date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))));
                fprintf(output, "end_date: %s\n", get_reservation_end_date(getRListInit(get_reservation_array_valid(ind))));
                fprintf(output, "user_id: %s\n",  get_reservation_user_id(getRListInit(get_reservation_array_valid(ind))));
                fprintf(output, "rating: %d\n", get_reservation_rating(getRListInit(get_reservation_array_valid(ind))));
                fprintf(output, "total_price: %.3f\n", total_price(get_reservation_price_per_night(getRListInit(get_reservation_array_valid(ind))), nights(get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))), get_reservation_end_date(getRListInit(get_reservation_array_valid(ind)))), get_reservation_city_tax(getRListInit(get_reservation_array_valid(ind)))));
                if (i!=num_reservations-1) fprintf(output, "\n");
            }
        }
        fclose(output);
    }
}


//Um voo está entre <begin_date> e <end_date> caso a
//sua respetiva data estimada de partida esteja entre <begin_date> e <end_date> (ambos inclusivos).

//is_date_between (char *date, char *i, char *f) retorna 1 si esta entre las dos
void outputs_query5 (char *arg_begin_date, char *arg_end_date, const int *list, int num_flights, int flag, int check, int n) {
    create_output(check, n);
    if (check == 1) {
        int check_date, ind, is_first_line = 1;
        if (flag == 1) {
            for (int i = num_flights-1, j=0; 0 <= i; i--, j++) {
                ind = list[i];
                check_date = is_date_between (get_flight_schedule_arrival_date (getFListInit (get_flight_array_valid(ind))), arg_begin_date, arg_end_date);
                if (check_date == 1) {
                    char *destination_cpy = strdup(get_flight_destination(getFListInit(get_flight_array_valid(ind))));
                    toUpperCase(destination_cpy);
                    if (!is_first_line) fprintf(output, "\n");
                    fprintf(output, "--- %d ---\n", j+1);
                    fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind))));
                    fprintf(output, "schedule_departure_date: %s\n", get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind))));
                    fprintf(output, "destination: %s\n", destination_cpy);
                    fprintf(output, "airline: %s\n", get_flight_airline(getFListInit(get_flight_array_valid(ind))));
                    fprintf(output, "plane_model: %s\n", get_flight_plane_model(getFListInit(get_flight_array_valid(ind))));
                    free(destination_cpy);
                    is_first_line = 0;
                }
                else j--;
            }
        }
        else {
            for (int i = num_flights-1; 0 <= i; i--) {
                ind = list[i];
                check_date = is_date_between (get_flight_schedule_arrival_date (getFListInit (get_flight_array_valid(ind))), arg_begin_date, arg_end_date);
                if (check_date == 1) {
                    char *destination_cpy = strdup(get_flight_destination(getFListInit(get_flight_array_valid(ind))));
                    toUpperCase(destination_cpy);
                    fprintf (output, "%s;%s;%s;%s;%s\n", get_flight_id(getFListInit(get_flight_array_valid(ind))), get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind))), destination_cpy, get_flight_airline(getFListInit(get_flight_array_valid(ind))), get_flight_plane_model(getFListInit(get_flight_array_valid(ind))));
                    free(destination_cpy);
                }
            }
        }
    }
    fclose (output);
}


void outputs_query8 (int revenue, int flag, int n) {
    create_output (1, n);
    if (flag == 0) {   // 8
        fprintf (output, "%d\n", revenue);
    }
    else {   // 8F
        fprintf (output, "--- 1 ---\n");
        fprintf (output, "revenue: %d\n", revenue);
    }
    fclose (output);
}


// void outputs_query2 (Flight_aux *flight_aux_array, Reservation_aux *reservation_aux_array, int index_line, char *argument2, int num_flights_passenger_id, int num_reservations, int n) {
//     create_output(n, 1);
//     if (index_line==2){ //2
//     if (strcmp(argument2, "flights")==0){  //só lista os voos
//         for (int i = 0; i<num_flights_passenger_id; i++){
//             fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
//         }
//     }
//     else if(strcmp(argument2, "reservations")==0){  //só lista as reservas
//             for (int i = 0; i<num_reservations; i++){
//                 fprintf(output, "%s;%s%s\n", reservation_aux_array[i].reservation_id, reservation_aux_array[i].begin_date, reservation_aux_array[i].type);
//             }
//         }
//         else{
//             for (int i = 0, j = 0; i<num_flights_passenger_id || j<num_reservations;){
//                 if(i==num_flights_passenger_id){   //já só há informações de reservas para serem impressas
//                     fprintf(output, "%s;%s%s\n", reservation_aux_array[j].reservation_id, reservation_aux_array[j].begin_date, reservation_aux_array[j].type);
//                     j++;
//                 }
//                 else if (j==num_reservations){   //já só há informações de voos para serem impressas
//                     fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
//                     i++;
//                 }
//                     else{
//                         if (strcmp(flight_aux_array[i].schedule_departure_date, reservation_aux_array[j].begin_date)==0){
//                             fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
//                             i++;
//                             fprintf(output, "%s;%s%s\n", reservation_aux_array[j].reservation_id, reservation_aux_array[j].begin_date, reservation_aux_array[j].type);
//                             j++;
//                         }
//                         else if (compare_date_time2(flight_aux_array[i].schedule_departure_date, reservation_aux_array[j].begin_date)>0){
//                             fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
//                             i++;
//                         }
//                             else if (compare_date_time2(flight_aux_array[i].schedule_departure_date, reservation_aux_array[j].begin_date)<0){
//                                 fprintf(output, "%s;%s%s\n", reservation_aux_array[j].reservation_id, reservation_aux_array[j].begin_date, reservation_aux_array[j].type);
//                                 j++;
//                             }
//                     }
//             }
//         }
//     }
//     else{  //2F
//         if (strcmp(argument2, "flights")==0){  //só lista os voos
//             for (int i = 1; i<=num_flights_passenger_id; i++){
//                 fprintf(output, "--- %d ---\n", i);
//                 fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
//                 fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
//                 if (i!=num_flights_passenger_id) fprintf(output, "\n");
//             }
//         }
//         else if (strcmp(argument2, "reservations")==0){  //só lista as reservas
//             for (int i = 1; i<=num_reservations; i++){
//                 fprintf(output, "--- %d ---\n", i);
//                 fprintf(output, "id: %s\n", reservation_aux_array[i-1].reservation_id);
//                 fprintf(output, "date: %s\n", reservation_aux_array[i-1].begin_date);
//                 if (i!=num_reservations) fprintf(output, "\n");
//             }
//         }
//         else{  //lista voos e reservas
//             for (int i = 1, j = 1; i<=num_flights_passenger_id || j<=num_reservations;){
//                 fprintf(output, "--- %d ---\n", (i+j-1));
//                 if(i==num_flights_passenger_id+1){   //já só há informações de reservas para serem impressas
//                         fprintf(output, "id: %s\n", reservation_aux_array[j-1].reservation_id);
//                         fprintf(output, "date: %s\n", reservation_aux_array[j-1].begin_date);
//                         fprintf(output, "type: reservation\n");
//                         if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
//                         j++;
//                 }
//                 else if (j==num_reservations+1){   //já só há informações de voos para serem impressas
//                         fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
//                         fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
//                         fprintf(output, "type: flight\n");
//                         if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
//                         i++;
//                 }
//                 else if (strcmp(flight_aux_array[i-1].schedule_departure_date, reservation_aux_array[j-1].begin_date)==0){
//                     fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
//                     fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
//                     fprintf(output, "type: flight\n");
//                     i++;
//                     fprintf(output, "\n");
//                     fprintf(output, "--- %d ---\n", (i+j-1));
//                     fprintf(output, "id: %s\n", reservation_aux_array[j-1].reservation_id);
//                     fprintf(output, "date: %s\n", reservation_aux_array[j-1].begin_date);
//                     fprintf(output, "type: reservation\n");
//                     if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
//                     j++;
//                 }
//                 else if (compare_date_time(flight_aux_array[i-1].schedule_departure_date, reservation_aux_array[j-1].begin_date)==0){
//                     //fprintf(output, "--- %d -ok--\n", (i+j-1));
//                     fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
//                     fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
//                     fprintf(output, "type: flight\n");
//                     if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
//                     i++;
//                 }
//                 else if (compare_date_time(flight_aux_array[i-1].schedule_departure_date, reservation_aux_array[j-1].begin_date)==1){
//                     fprintf(output, "--- %d ---\n", (i+j-1));        //////////////////////////////////////////////////////////////////////////////////////////
//                     fprintf(output, "id: %s\n", reservation_aux_array[j-1].reservation_id);
//                     fprintf(output, "date: %s\n", reservation_aux_array[j-1].begin_date);
//                     fprintf(output, "type: reservation\n");
//                     if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
//                     j++;
//                 }
//             }
//         }
//     }
//     fclose(output);
// }

// void outputs_query3 (double media, int flag, int n) {
//     create_output(n, 1);
//     if (flag == 0)   //3
//         fprintf(output, "%.3f\n", media);
//     else {   //3F
//         fprintf(output, "--- 1 ---\n");
//         fprintf(output, "rating: %.3f\n", media);
//     }
//     fclose(output);
// }

// void outputs_query4 (hotel_aux *hotel_aux_array, int index_line, int num_hotels, int n) {
//     create_output(n, 1);
//     if (index_line==2) {  // 4
//         for (int j=0; j<num_hotels; j++) fprintf (output, "%s;%s;%s;%s;%s;%.3f\n", hotel_aux_array[j].id, hotel_aux_array[j].begin_date, hotel_aux_array[j].end_date, hotel_aux_array[j].user_id, hotel_aux_array[j].rating, hotel_aux_array[j].total_price);
//     }
//     else {  // 4F
//         for (int j=0; j<num_hotels; j++) {
//             fprintf(output, "--- %d ---\n", j+1);
//             fprintf(output, "id: %s\n", hotel_aux_array[j].id);
//             fprintf(output, "begin_date: %s\n", hotel_aux_array[j].begin_date);
//             fprintf(output, "end_date: %s\n", hotel_aux_array[j].end_date);
//             fprintf(output, "user_id: %s\n", hotel_aux_array[j].user_id);
//             fprintf(output, "rating: %s\n", hotel_aux_array[j].rating);
//             fprintf(output, "total_price: %.3f\n", hotel_aux_array[j].total_price);
//             if (j!=num_hotels-1) fprintf(output, "\n");
//         }
//     }
//     fclose (output);
// }

// void outputs_query5 (flight_date_aux *flight_date_aux_array, int index1_line, int num_flights, int n) {
//     create_output(n, 1);
//     if (index1_line==2) {  // 5
//         for (int j=0; j<num_flights; j++) {
//             char *destination_cpy = flight_date_aux_array[j].destination;
//             toUpperCase(destination_cpy);
//             fprintf (output, "%s;%s;%s;%s;%s\n", flight_date_aux_array[j].id, flight_date_aux_array[j].schedule_departure_date, destination_cpy, flight_date_aux_array[j].airline, flight_date_aux_array[j].plane_model);
//         }
//     }
//     else {  // 5F
//         for (int j=0; j<num_flights; j++) {
//             char *destination_cpy = flight_date_aux_array[j].destination;
//             toUpperCase(destination_cpy);
//             fprintf(output, "--- %d ---\n", j+1);
//             fprintf(output, "id: %s\n", flight_date_aux_array[j].id);
//             fprintf(output, "schedule_departure_date: %s\n", flight_date_aux_array[j].schedule_departure_date);
//             fprintf(output, "destination: %s\n", destination_cpy);
//             fprintf(output, "airline: %s\n", flight_date_aux_array[j].airline);
//             fprintf(output, "plane_model: %s\n", flight_date_aux_array[j].plane_model);
//             if (j!=num_flights-1) fprintf(output, "\n");
//         }
//     }
//     fclose (output);
// }

// void outputs_query6 (PassengersXairport *passengersXairport_array, int index_pXa, int top, int flag, int n) {
//     create_output(n, 1);
//     if (flag == 0){   //6
//         for (index_pXa = 0; index_pXa < top; index_pXa++) {
//             fprintf(output, "%s;%d\n", passengersXairport_array[index_pXa].origin, passengersXairport_array[index_pXa].passengers);
//         }
//     }
//     else {          //6F
//         for (index_pXa = 0; index_pXa < top; index_pXa++) {
//             fprintf(output, "--- %d ---\n",index_pXa+1);
//             fprintf(output, "name: %s\n", passengersXairport_array[index_pXa].origin);
//             fprintf(output, "passengers: %d\n", passengersXairport_array[index_pXa].passengers);
//             if (index_pXa+1 != top) fprintf(output, "\n");
//         }
//     }
//     fclose(output);
// }

// void outputs_query7 (Mediana *mediana_array, int index_line, int N, int n) {
//     create_output(n, 1);
//     for (int i = 0; i<N; i++){
//         if (index_line==2){   //7
//             fprintf(output, "%s;%d\n", mediana_array[i].airport, mediana_array[i].mediana);
//         }
//         else{   //7F
//             fprintf(output, "--- %d ---\n", i+1);
//             fprintf(output, "name: %s\n", mediana_array[i].airport);
//             fprintf(output, "median: %d\n", mediana_array[i].mediana);
//             if (i!=N-1) fprintf(output, "\n");
//         }
//     }
//     fclose(output);
// }

// void outputs_query9 (idXname *idXname_array, int num_linhas_idXname, int flag, int n) {
//     create_output(n, 1);
//     if (flag == 0){   //9
//         for (int index_idXn = 0; index_idXn < num_linhas_idXname; index_idXn++) {
//             fprintf(output, "%s;%s\n", idXname_array[index_idXn].id, idXname_array[index_idXn].name);
//         }
//     }
//     else {          //9F
//         for (int index_idXn = 0; index_idXn < num_linhas_idXname; index_idXn++) {
//             fprintf(output, "--- %d ---\n",index_idXn+1);
//             fprintf(output, "id: %s\n", idXname_array[index_idXn].id);
//             fprintf(output, "name: %s\n", idXname_array[index_idXn].name);
//             if (index_idXn+1 != num_linhas_idXname) fprintf(output, "\n");
//         }
//     }
//     fclose(output);
// }