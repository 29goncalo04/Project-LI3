#include "../include/Catalogs.h"
#include "../include/Aux_functions.h"
#include "../include/Aux_validation.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

void ordena_list_reservations(int ind, char *date_ind, char *id_r, int **list, int n) {
    int j, check;
    for (int i = 0; i < n; i++) {
        if ((*list)[i] == -1) {
            (*list)[i] = ind;
            return;
        }
        else {
            j = (*list)[i];
            RNo *pointer = reservation_array_valid[j].init;
            if (strcmp(date_ind, pointer->reservation.begin_date) != 0) {
                check = compare_date_time(date_ind, pointer->reservation.begin_date);
                if (check == 1) {
                    for (int k = n-1; i < k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    return;
                }
            } 
            else { //Book00903905
                if (atoi(pointer->reservation.id + 4) - atoi(id_r + 4) < 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                    for (int k = n-1; i < k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    return;
                }
            }
        }
    }
    return;
}

void ordena_list_flights(int ind, const char *date_ind, char *id_f, int **list, int n) {
    int j, check;
    for (int i = 0; i < n; i++) {
        if ((*list)[i] == -1) {
            (*list)[i] = ind;
            return;
        }
        else {
            j = (*list)[i];
            FNo *pointer = getFListInit(get_flight_array_valid(j));
            if (strcmp(date_ind, get_flight_schedule_departure_date(pointer)) != 0) {
                check = compare_date_time3(date_ind, get_flight_schedule_departure_date(pointer));
                if (check == 1) {
                    for (int k = n-1; i < k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    return;
                }
            } 
            else { //00903905
                if (atoi(get_flight_id(pointer)) - atoi(id_f) < 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                    for (int k = n-1; i <= k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    return;
                }
            }
        }
    }
    return;
}





unsigned long hash_djb2(char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % NUM_LINHAS_VALID_USER;
}

int found_index_users(char *key) {
    return hash_djb2(key);
}

int found_index_flights(const char *key) {
    int id = atoi(key), ind = id % NUM_LINHAS_VALID_FLIGHT;
    return ind;
}

int found_index_reservations(char *key) {
    int id = atoi(key+4), ind = id % NUM_LINHAS_VALID_RESERVATION;
    return ind;
}

int found_index_hotels(char *key) {
    int id = atoi(key+3), ind = id % NUM_LINHAS_VALID_RESERVATION;
    return ind;
}

void init_user_array(UList *user_array) {
    for (int i = 0; i < NUM_LINHAS_VALID_USER; i++) {
        user_array[i].init = NULL;
    }
}

//void init_flight_array(FList *flight_array) {
//    for (int i = 0; i < NUM_LINHAS_VALID_FLIGHT; i++) {
//        flight_array[i].init = NULL;
//    }
//}

void init_reservation_array(RList *reservation_array) {
    for (int i = 0; i < NUM_LINHAS_VALID_RESERVATION; i++) {
        reservation_array[i].init = NULL;
    }
}

void users_hash_sort(UList *user_array_valid, UList list) {
    int ind = found_index_users(list.init->user.id);
    //printf("calculo bien el id\n");
    if (user_array_valid[ind].init == NULL) { //esta tudo NULL (vacio)
        user_array_valid[ind] = list;
    }
    else {
        list.init->prox = user_array_valid[ind].init;
        user_array_valid[ind] = list;
    }
}

void reservations_hash_sort(RList *reservation_array_valid, RList list) {
    int ind = found_index_reservations(list.init->reservation.id);
    //printf("calculo bien el id\n");
    if (reservation_array_valid[ind].init == NULL) { //esta tudo NULL (vacio)
        reservation_array_valid[ind] = list;
    }
    else {
        list.init->prox = reservation_array_valid[ind].init;
        reservation_array_valid[ind] = list;
    }

    int ind_u = found_index_users(list.init->reservation.user_id);
    UNo *upointer = user_array_valid[ind_u].init;
    while (upointer != NULL) {
        if (strcmp(list.init->reservation.user_id, upointer->user.id) == 0) {
            ordena_list_reservations(ind, list.init->reservation.begin_date, list.init->reservation.id, &(upointer->user.list_reservations), upointer->user.reservations);                  
            break;
        }
        else upointer = upointer->prox;
    }
}

void hotels_hash_sort (HList *hotel_array_valid, HList list) {
    int ind = found_index_hotels(list.init->hotel.id);
    if (hotel_array_valid[ind].init == NULL) { //esta tudo NULL (vacio)
        hotel_array_valid[ind] = list;
    }
    else {
        list.init->prox = hotel_array_valid[ind].init;
        hotel_array_valid[ind] = list;
    }
}