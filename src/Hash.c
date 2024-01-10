#include "../include/Catalogs.h"
#include "../include/Aux_functions.h"
#include "../include/Aux_validation.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int m_users, m_flights, m_reservations;

#define Null 0

// void init_user(UList *list) {
//     (*list).tam = Null;
//     (*list).init = NULL;
// }

// void init_flight(FList *list) {
//     (*list).tam = Null;
//     (*list).init = NULL;
// }

// void init_reservation(RList *list) {
//     (*list).tam = Null;
//     (*list).init = NULL;
// }


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
            // compare_date_time(i, f) == 0 i ocurre despues de f ||||| compare_date_time(i, f) == 1 i ocurre antes de f
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
                if (atoi(pointer->reservation.id + 4) - atoi(id_r + 4) > 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
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

void ordena_list_flights(int ind, char *date_ind, char *id_f, int **list, int n) {
    int j, check;
    for (int i = 0; i < n; i++) {
        if ((*list)[i] == -1) {
            (*list)[i] = ind;
            // printf("%s\n", id_f);
            // for(int j = 0; j < n; j++) {
            //     printf("%d ", (*list)[j]);
            // }
            // printf("\n");
            // sleep(1);
            return;
        }
        else {
            j = (*list)[i];
            FNo *pointer = flight_array_valid[j].init;
            char *date = only_date(pointer->flight.schedule_departure_date);
            // compare_date_time(i, f) == 0 i ocurre despues de f ||||| compare_date_time(i, f) == 1 i ocurre antes de f
            if (strcmp(date_ind, date) != 0) {
                check = compare_date_time(date_ind, only_date(pointer->flight.schedule_departure_date));
                if (check == 1) {
                    for (int k = n-1; i < k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    // printf("%s\n", id_f);
                    // for(int j = 0; j < n; j++) {
                    //     printf("%d ", (*list)[j]);
                    // }
                    // printf("\n");
                    return;
                }
            } 
            else { //00903905
                if (atoi(pointer->flight.id) - atoi(id_f) > 0) { //de dar errado a query 2 ou outra query por culpa do array(que tenho de guardar de recente-antiga e guardei antiga-recente) mudar o > pelo <
                    for (int k = n-1; i < k; k--) {
                        (*list)[k] = (*list)[k-1];
                    }
                    (*list)[i] = ind;
                    // printf("%s\n", id_f);
                    // for(int j = 0; j < n; j++) {
                    //     printf("%d ", (*list)[j]);
                    // }
                    // printf("\n");
                    return;
                }
            }
        }
    }
    return;
}






int found_index_users(char *key) { // por alguna razon con el id: JúSá retorna un numero negativo: -130. Por que? tube que poner el abs para que coloque el modulo y no de segmentipn fault
    int ind = 0;
    for (int i = 0; key[i] != '\0'; i++)
        ind += key[i];
    ind = abs(ind % m_users);
    return ind;
}

int found_index_flights(char *key) {
    int id = atoi(key), ind = id % m_flights;
    return ind;
}

int found_index_reservations(char *key) {
    int id = atoi(key+4), ind = id % m_reservations;
    return ind;
}






void init_user_array(UList *user_array, int m_users) {
    for (int i = 0; i < m_users; i++) {
        user_array[i].tam = Null;
        user_array[i].init = NULL;
    }
}

void init_flight_array(FList *flight_array, int m_flight) {
    for (int i = 0; i < m_flight; i++) {
        flight_array[i].tam = Null;
        flight_array[i].init = NULL;
    }
}

void init_reservation_array(RList *reservation_array, int m_reservation) {
    for (int i = 0; i < m_reservation; i++) {
        reservation_array[i].tam = Null;
        reservation_array[i].init = NULL;
    }
}








void users_hash_sort() {
    m_users = find_near_prime(2*num_linhas_valid_user);
    UList *user_array = malloc(m_users * sizeof(UList));
    init_user_array(user_array, m_users);
    int init_ID, current_ID;
    for (init_ID = 0; init_ID < num_linhas_valid_user; init_ID++) {
        current_ID = found_index_users(user_array_valid[init_ID].init->user.id);
        if (user_array[current_ID].tam == Null) { //esta tudo NULL (vacio)
            user_array[current_ID].tam = 1;
            user_array[current_ID].init = user_array_valid[init_ID].init;
        }
        else {
            UNo *pointer = user_array[current_ID].init;
            while (pointer->prox != NULL) {
                pointer = pointer->prox;
            }
            pointer->prox = user_array_valid[init_ID].init;
            user_array[current_ID].tam++;
        }
    }

    free(user_array_valid);

    num_linhas_valid_user = m_users;
    user_array_valid = user_array;
}

void flights_hash_sort() {
    m_flights = find_near_prime(2*num_linhas_valid_flight);
    FList *flight_array = malloc(m_flights * sizeof(FList));
    init_flight_array(flight_array, m_flights);
    int init_ID, current_ID;
    for (init_ID = 0; init_ID < num_linhas_valid_flight; init_ID++) {
        current_ID = found_index_flights(flight_array_valid[init_ID].init->flight.id);
        if (flight_array[current_ID].tam == Null) { //esta tudo NULL (vacio)
            flight_array[current_ID].tam = 1;
            flight_array[current_ID].init = flight_array_valid[init_ID].init;
        }
        else {
            FNo *pointer = flight_array[current_ID].init;
            while (pointer->prox != NULL) {
                pointer = pointer->prox;
            }
            pointer->prox = flight_array_valid[init_ID].init;
            flight_array[current_ID].tam++;
        }
    }
    
    free(flight_array_valid);

    num_linhas_valid_flight = m_flights;
    flight_array_valid = flight_array;

}

void reservations_hash_sort() {
    int ind_u;
    m_reservations = find_near_prime(2*num_linhas_valid_reservation);
    RList *reservation_array = malloc(m_reservations * sizeof(RList));
    init_reservation_array(reservation_array, m_reservations);
    int init_ID, current_ID;
    for (init_ID = 0; init_ID < num_linhas_valid_reservation; init_ID++) {
        current_ID = found_index_reservations(reservation_array_valid[init_ID].init->reservation.id);
        if (reservation_array[current_ID].tam == Null) { //esta tudo NULL (vacio)
            reservation_array[current_ID].tam = 1;
            reservation_array[current_ID].init = reservation_array_valid[init_ID].init;
        }
        else {
            RNo *pointer = reservation_array[current_ID].init;
            while (pointer->prox != NULL) {
                pointer = pointer->prox;
            }
            pointer->prox = reservation_array_valid[init_ID].init;
            reservation_array[current_ID].tam++;
        }
    }
    
    free(reservation_array_valid);

    num_linhas_valid_reservation = m_reservations;
    reservation_array_valid = reservation_array;

    //tentar fazer noutra função/ficheiro para a modulação (preenche o array list_reservations por cada usuario)
    for (int i = 1; i < num_linhas_valid_reservation; i++) {
        RNo *rpointer = reservation_array_valid[i].init;
        if (rpointer != NULL) {
            ind_u = found_index_users(rpointer->reservation.user_id);
            UNo *upointer = user_array_valid[ind_u].init;
            while (upointer != NULL) {
                if (strcmp(rpointer->reservation.user_id, upointer->user.id) == 0) {
                    ordena_list_reservations(i, rpointer->reservation.begin_date, rpointer->reservation.id, &(upointer->user.list_reservations), upointer->user.reservations);                  
                    break;
                }
                else upointer = upointer->prox;
            }
        }
        
    }
}