#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "../include/Output_queries.h"
#include "../include/Aux_validation.h"
#include "../include/Queries.h"
#include "../include/Aux_functions.h"
#include "../include/Catalogs.h"
#include "../include/Hash.h"

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
            for (int i = 0, num = 1; i < tam; i++, num++) {
                ind = list[i];
                fprintf(output, "--- %d ---\n", num);
                fprintf(output, "id: %s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind))));
                if (i == tam-1) fprintf(output, "date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))));
                else {
                    fprintf(output, "date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))));
                    fprintf(output, "\n");
                }
            }
        }
        else {
            int ind;
            for (int i = 0; i < tam; i++) {
                ind = list[i];
                if (i == tam-1) fprintf(output, "%s;%s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind))), get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind))));
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
            for (int i = 0, num = 1; i < tam; i++, num++) {
                ind = list[i];
                fprintf(output, "--- %d ---\n", num);
                fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind))));
                char *only_date_aux = only_date2(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind))));
                if (i == tam-1) fprintf(output, "date: %s\n", only_date_aux);
                else {
                    fprintf(output, "date: %s\n", only_date_aux);
                    fprintf(output, "\n");
                }
                free(only_date_aux);
            }
        }
        else {
            int ind;
            for (int i = 0; i < tam; i++) {
                ind = list[i];
                char *only_date_aux = only_date2(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind))));
                if (i == tam-1) fprintf(output, "%s;%s\n", get_flight_id(getFListInit(get_flight_array_valid(ind))), only_date_aux);
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
        int check_date, ind_f, ind_r, i = 0, j = 0, num = 1;
        if (flag == 1) {
            while (i < tam_r || j < tam_f) {
                if (i < tam_r && j==tam_f) {
                    for (; i < tam_r; i++, num++) {
                        ind_r = list_r[i];
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "type: reservation\n");
                        if(i != tam_r-1) fprintf(output, "\n");
                    }
                    fclose(output);
                    return;
                }

                if (j<tam_f && i==tam_r) {
                    for (; j < tam_f; j++, num++) {
                        ind_f = list_f[j];
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind_f))));
                        char *only_date_aux = only_date2(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind_f))));
                        fprintf(output, "date: %s\n", only_date_aux);
                        free(only_date_aux);
                        fprintf(output, "type: flight\n");
                        if(j != tam_f-1) fprintf(output, "\n");
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
                        i++;
                    }
                    else {
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind_f))));
                        fprintf(output, "date: %s\n", only_date_aux);
                        fprintf(output, "type: flight\n");
                        fprintf(output, "\n");
                        j++;
                    }
                } 
                else {
                    if (atoi(get_flight_id(getFListInit(get_flight_array_valid(ind_f)))) - atoi(get_reservation_id(getRListInit(get_reservation_array_valid(ind_r)))) > 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind_f))));
                        fprintf(output, "date: %s\n", only_date_aux);
                        fprintf(output, "type: flight\n");
                        fprintf(output, "\n");
                        j++;
                    }
                    else{
                        fprintf(output, "--- %d ---\n", num);
                        fprintf(output, "id: %s\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "date: %s\n", get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                        fprintf(output, "type: reservation\n");
                        fprintf(output, "\n");
                        i++;
                    }
                }
                free(only_date_aux);
                num++;
            }
            fclose(output);
            return;
        }
        else {
            while (i < tam_r || j < tam_f) {
                if (i < tam_r && j==tam_f) {
                    for (; i < tam_r; i++, num++) {
                        ind_r = list_r[i];
                        fprintf(output, "%s;%s;reservation\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))), get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                    }
                    fclose(output);
                    return;
                }

                if (j < tam_f && i==tam_r) {
                    for (; j < tam_f; j++, num++) {
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
                        i++;
                    }
                    else {
                        fprintf(output, "%s;%s;flight\n",get_flight_id(getFListInit(get_flight_array_valid(ind_f))), only_date_aux);
                        j++;
                    }
                } 
                else {
                    if (atoi(get_flight_id(getFListInit(get_flight_array_valid(ind_f)))) - atoi(get_reservation_id(getRListInit(get_reservation_array_valid(ind_r)))) > 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                        fprintf(output, "%s;%s;flight\n", get_flight_id(getFListInit(get_flight_array_valid(ind_f))), only_date_aux);
                        j++;
                    }
                    else{
                        fprintf(output, "%s;%s;reservation\n", get_reservation_id(getRListInit(get_reservation_array_valid(ind_r))), get_reservation_begin_date(getRListInit(get_reservation_array_valid(ind_r))));
                        i++;
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
void outputs_query5 (char *origin, char *arg_begin_date, char *arg_end_date, const int *list3, const int *list2, const int *list1, int num_flights3, int num_flights2, int num_flights1, int flag, int check, int n) {
    create_output(check, n);
    if (check == 1) {
        int check_date, ind3, ind2, ind1, is_first_line = 1, j = 0;
        if (flag == 1) {
            for (int i = 0; i < num_flights3; i++) {
                ind3 = list3[i];
                char *origin_cpy = strdup(get_flight_origin(getFListInit(get_flight_array_valid(ind3))));
                toUpperCase(origin_cpy);
                if (strcmp(origin, origin_cpy) == 0) {
                    check_date = is_date_between (get_flight_schedule_departure_date (getFListInit (get_flight_array_valid(ind3))), arg_begin_date, arg_end_date);
                    if (check_date == 1) {
                        char *destination_cpy = strdup(get_flight_destination(getFListInit(get_flight_array_valid(ind3))));
                        toUpperCase(destination_cpy);
                        if (!is_first_line) fprintf(output, "\n");
                        fprintf(output, "--- %d ---\n", j+1);
                        fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind3))));
                        fprintf(output, "schedule_departure_date: %s\n", get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind3))));
                        fprintf(output, "destination: %s\n", destination_cpy);
                        fprintf(output, "airline: %s\n", get_flight_airline(getFListInit(get_flight_array_valid(ind3))));
                        fprintf(output, "plane_model: %s\n", get_flight_plane_model(getFListInit(get_flight_array_valid(ind3))));
                        free(destination_cpy);
                        is_first_line = 0;
                        j++;
                    }
                }
                free(origin_cpy);
            }
            for (int i = 0; i < num_flights2; i++) {
                ind2 = list2[i];
                char *origin_cpy = strdup(get_flight_origin(getFListInit(get_flight_array_valid(ind2))));
                toUpperCase(origin_cpy);
                if (strcmp(origin, origin_cpy) == 0) {
                    check_date = is_date_between (get_flight_schedule_departure_date (getFListInit (get_flight_array_valid(ind2))), arg_begin_date, arg_end_date);
                    if (check_date == 1) {
                        char *destination_cpy = strdup(get_flight_destination(getFListInit(get_flight_array_valid(ind2))));
                        toUpperCase(destination_cpy);
                        if (!is_first_line) fprintf(output, "\n");
                        fprintf(output, "--- %d ---\n", j+1);
                        fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind2))));
                        fprintf(output, "schedule_departure_date: %s\n", get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind2))));
                        fprintf(output, "destination: %s\n", destination_cpy);
                        fprintf(output, "airline: %s\n", get_flight_airline(getFListInit(get_flight_array_valid(ind2))));
                        fprintf(output, "plane_model: %s\n", get_flight_plane_model(getFListInit(get_flight_array_valid(ind2))));
                        free(destination_cpy);
                        is_first_line = 0;
                        j++;
                    }
                }
                free(origin_cpy);
            }
            for (int i = 0; i < num_flights1; i++) {
                ind1 = list1[i];
                char *origin_cpy = strdup(get_flight_origin(getFListInit(get_flight_array_valid(ind1))));
                toUpperCase(origin_cpy);
                if (strcmp(origin, origin_cpy) == 0) {
                    check_date = is_date_between (get_flight_schedule_departure_date (getFListInit (get_flight_array_valid(ind1))), arg_begin_date, arg_end_date);
                    if (check_date == 1) {
                        char *destination_cpy = strdup(get_flight_destination(getFListInit(get_flight_array_valid(ind1))));
                        toUpperCase(destination_cpy);
                        if (!is_first_line) fprintf(output, "\n");
                        fprintf(output, "--- %d ---\n", j+1);
                        fprintf(output, "id: %s\n", get_flight_id(getFListInit(get_flight_array_valid(ind1))));
                        fprintf(output, "schedule_departure_date: %s\n", get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind1))));
                        fprintf(output, "destination: %s\n", destination_cpy);
                        fprintf(output, "airline: %s\n", get_flight_airline(getFListInit(get_flight_array_valid(ind1))));
                        fprintf(output, "plane_model: %s\n", get_flight_plane_model(getFListInit(get_flight_array_valid(ind1))));
                        free(destination_cpy);
                        is_first_line = 0;
                        j++;
                    }
                }
                free(origin_cpy);
            }
        }
        else {
            for (int i = 0; i < num_flights3; i++) {
                ind3 = list3[i];
                char *origin_cpy = strdup(get_flight_origin(getFListInit(get_flight_array_valid(ind3))));
                toUpperCase(origin_cpy);
                if (strcmp(origin, origin_cpy) == 0) {
                    check_date = is_date_between (get_flight_schedule_departure_date (getFListInit (get_flight_array_valid(ind3))), arg_begin_date, arg_end_date);
                    if (check_date == 1) {
                        char *destination_cpy = strdup(get_flight_destination(getFListInit(get_flight_array_valid(ind3))));
                        toUpperCase(destination_cpy);
                        fprintf (output, "%s;%s;%s;%s;%s\n", get_flight_id(getFListInit(get_flight_array_valid(ind3))), get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind3))), destination_cpy, get_flight_airline(getFListInit(get_flight_array_valid(ind3))), get_flight_plane_model(getFListInit(get_flight_array_valid(ind3))));
                        free(destination_cpy);
                    }
                }
                free(origin_cpy);
            }
            for (int i = 0; i < num_flights2; i++) {
                ind2 = list2[i];
                char *origin_cpy = strdup(get_flight_origin(getFListInit(get_flight_array_valid(ind2))));
                toUpperCase(origin_cpy);
                if (strcmp(origin, origin_cpy) == 0) {
                    check_date = is_date_between (get_flight_schedule_departure_date (getFListInit (get_flight_array_valid(ind2))), arg_begin_date, arg_end_date);
                    if (check_date == 1) {
                        char *destination_cpy = strdup(get_flight_destination(getFListInit(get_flight_array_valid(ind2))));
                        toUpperCase(destination_cpy);
                        fprintf (output, "%s;%s;%s;%s;%s\n", get_flight_id(getFListInit(get_flight_array_valid(ind2))), get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind2))), destination_cpy, get_flight_airline(getFListInit(get_flight_array_valid(ind2))), get_flight_plane_model(getFListInit(get_flight_array_valid(ind2))));
                        free(destination_cpy);
                    }
                }
                free(origin_cpy);
            }
            for (int i = 0; i < num_flights1; i++) {
                ind1 = list1[i];
                char *origin_cpy = strdup(get_flight_origin(getFListInit(get_flight_array_valid(ind1))));
                toUpperCase(origin_cpy);
                if (strcmp(origin, origin_cpy) == 0) {
                    check_date = is_date_between (get_flight_schedule_departure_date (getFListInit (get_flight_array_valid(ind1))), arg_begin_date, arg_end_date);
                    if (check_date == 1) {
                        char *destination_cpy = strdup(get_flight_destination(getFListInit(get_flight_array_valid(ind1))));
                        toUpperCase(destination_cpy);
                        fprintf (output, "%s;%s;%s;%s;%s\n", get_flight_id(getFListInit(get_flight_array_valid(ind1))), get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(ind1))), destination_cpy, get_flight_airline(getFListInit(get_flight_array_valid(ind1))), get_flight_plane_model(getFListInit(get_flight_array_valid(ind1))));
                        free(destination_cpy);
                    }
                }
                free(origin_cpy);
            }
        }
    }
    fclose (output);
}

void outputs_query6 (const int *list, int year, int top, int flag, int n, int tam) {
    create_output(1, n);
    if (flag == 0){   //6
        for (int i = 0; i < top && i < tam; i++) {
            int ind = list[i];
            fprintf(output, "%s;", get_airport_name(getAListInit(get_airport_array_valid(ind))));
            if (year==2023) fprintf(output, "%d\n", get_airport_passengers2023(getAListInit(get_airport_array_valid(ind))));
            if (year==2022) fprintf(output, "%d\n", get_airport_passengers2022(getAListInit(get_airport_array_valid(ind))));
            if (year==2021) fprintf(output, "%d\n", get_airport_passengers2021(getAListInit(get_airport_array_valid(ind))));
        }
    }
    else {          //6F
        for (int i = 0; i < top && i < tam; i++) {
            int ind = list[i];
            fprintf(output, "--- %d ---\n",i+1);
            fprintf(output, "name: %s\n", get_airport_name(getAListInit(get_airport_array_valid(ind))));
            if(year==2023) fprintf(output, "passengers: %d\n", get_airport_passengers2023(getAListInit(get_airport_array_valid(ind))));
            if(year==2022) fprintf(output, "passengers: %d\n", get_airport_passengers2022(getAListInit(get_airport_array_valid(ind))));
            if(year==2021) fprintf(output, "passengers: %d\n", get_airport_passengers2021(getAListInit(get_airport_array_valid(ind))));
            if (i+1 != top && i+1 != tam) fprintf(output, "\n");
        }
    }
    fclose(output);
}

void outputs_query7 (list_mediana *list, int tam, int N, int flag, int n) {
    create_output(1, n);
    if (flag == 0){   //7
        for (int i = 0; i < N && i < tam; i++) {
            fprintf(output, "%s;%d\n", list[i].airport, list[i].mediana);
            //printf("%s;%d\n", list->airport, list->mediana);
        }
    }
    else {          //7F
        for (int i = 0; i < N && i < tam; i++) {
            fprintf(output, "--- %d ---\n",i+1);
            fprintf(output, "name: %s\n", list[i].airport);
            fprintf(output, "median: %d\n", list[i].mediana);
            //printf("%s;%d\n", list->airport, list->mediana);
            if (i+1 != N && i+1 != tam) fprintf(output, "\n");
        }
    }
    fclose(output);
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

void outputs_query9 (list_users *list, int tam, int flag, int n){
    create_output (1, n);
    if (flag == 0){   //9
        for (int i = 0; i<tam; i++) {
            fprintf(output, "%s;%s\n", list[i].id, list[i].name);
        }
    }
    else {          //9F
        for (int i = 0, j = 0; i<tam; i++) {
            j++;
            fprintf(output, "--- %d ---\n", j);
            fprintf(output, "id: %s\n", list[i].id);
            fprintf(output, "name: %s\n", list[i].name);
            if(i!=tam-1) fprintf(output, "\n");
        }
    }
    fclose(output);
}

void outputs_query10_years(int year, int flag, int n){
    create_output (1, n);
    for(int i = 0; i<14; i++){
        if (flag == 0){  //10
            fprintf(output, "%d;%d;%d;%d;%d;%d\n", year+i, get_year_new_users(getYListInit(get_year_array_valid(found_index_year(year+i)))), get_year_flights(getYListInit(get_year_array_valid(found_index_year(year+i)))), get_year_passengers(getYListInit(get_year_array_valid(found_index_year(year+i)))), get_year_unique_passengers(getYListInit(get_year_array_valid(found_index_year(year+i)))), get_year_reservations(getYListInit(get_year_array_valid(found_index_year(year+i)))));
        }
        else {   //10F
            fprintf(output, "--- %d ---\n", i+1);
            fprintf(output, "year: %d\n", year+i);
            fprintf(output, "users: %d\n", get_year_new_users(getYListInit(get_year_array_valid(found_index_year(year+i)))));
            fprintf(output, "flights: %d\n", get_year_flights(getYListInit(get_year_array_valid(found_index_year(year+i)))));
            fprintf(output, "passengers: %d\n", get_year_passengers(getYListInit(get_year_array_valid(found_index_year(year+i)))));
            fprintf(output, "unique_passengers: %d\n", get_year_unique_passengers(getYListInit(get_year_array_valid(found_index_year(year+i)))));
            fprintf(output, "reservations: %d\n", get_year_reservations(getYListInit(get_year_array_valid(found_index_year(year+i)))));
            if(i!=13) fprintf(output, "\n");
        }
    }
    fclose(output);
}

void outputs_query10_year(char* year, int flag, int n){
    create_output (1, n);
    int i;
    if(atoi(year)==2023) i = 9;
    else i = 12;
    for(int j = 0; j<i; j++){
        char date[8];
        strcpy(date, year);
        date[4] = '/';
        if (j+1 <= i){
            date[5] = '0' + (j+1)/10;
            date[6] = '0' + (j+1)%10;
        }
        date[7] = '\0';
        if (flag == 0){  //10
            fprintf(output, "%d;%d;%d;%d;%d;%d\n", j+1, get_year_new_users(getYListInit(get_year_array_valid(found_index_year_month_day(date)))), get_year_flights(getYListInit(get_year_array_valid(found_index_year_month_day(date)))), get_year_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date)))), get_year_unique_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date)))), get_year_reservations(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
        }
        else {   //10F
            fprintf(output, "--- %d ---\n", j+1);
            fprintf(output, "month: %d\n", j+1);
            fprintf(output, "users: %d\n", get_year_new_users(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
            fprintf(output, "flights: %d\n", get_year_flights(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
            fprintf(output, "passengers: %d\n", get_year_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
            fprintf(output, "unique_passengers: %d\n", get_year_unique_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
            fprintf(output, "reservations: %d\n", get_year_reservations(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
            if(j!=i-1) fprintf(output, "\n");
        }
    }
    fclose(output);
}

void outputs_query10_year_month(char* year, char* month, int flag, int n){
    create_output (1, n);
    int i, line = 1;
    if(atoi(year)==2023) i = 9;
    else i = 12;
    int j = atoi(month) - 1;
    int dias;
    if(j==0 || j==2 || j==4 || j==6 || j==7 || j==9 || j==11) dias = 31;
    if(j==1) dias = 28;
    if(j==3 || j==5 || j==8 || j==10) dias = 30;
    for(int k = 0, m = 0; k<dias; k++){
        char date[11];
        strcpy(date, year);
        date[4] = '/';
        if (j+1 <= i){
            date[5] = '0' + (j+1)/10;
            date[6] = '0' + (j+1)%10;
            if(k+1 <= dias){
                date[7] = '/';
                date[8] = '0' + (k+1)/10;
                date[9] = '0' + (k+1)%10;
            }
        }
        date[10] = '\0';
        if (flag == 0){  //10
            if(get_year_new_users(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0 || get_year_flights(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0 || get_year_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0 || get_year_unique_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0 || get_year_reservations(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0){
                fprintf(output, "%d;%d;%d;%d;%d;%d\n", k+1, get_year_new_users(getYListInit(get_year_array_valid(found_index_year_month_day(date)))), get_year_flights(getYListInit(get_year_array_valid(found_index_year_month_day(date)))), get_year_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date)))), get_year_unique_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date)))), get_year_reservations(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
            }
        }
        else {   //10F
            if(get_year_new_users(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0 || get_year_flights(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0 || get_year_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0 || get_year_unique_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0 || get_year_reservations(getYListInit(get_year_array_valid(found_index_year_month_day(date))))!=0){
                if(!line) fprintf(output, "\n");
                line = 0;
                fprintf(output, "--- %d ---\n", m+1);
                m++;
                fprintf(output, "day: %d\n", k+1);
                fprintf(output, "users: %d\n", get_year_new_users(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
                fprintf(output, "flights: %d\n", get_year_flights(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
                fprintf(output, "passengers: %d\n", get_year_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
                fprintf(output, "unique_passengers: %d\n", get_year_unique_passengers(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
                fprintf(output, "reservations: %d\n", get_year_reservations(getYListInit(get_year_array_valid(found_index_year_month_day(date)))));
            }
        }
    }
    fclose(output);
}