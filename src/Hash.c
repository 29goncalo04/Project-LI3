#include "../include/Catalogs.h"
#include "../include/Aux_functions.h"
#include "../include/Aux_validation.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

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

int found_index_reservations(const char *key) {
    int id = atoi(key+4), ind = id % NUM_LINHAS_VALID_RESERVATION;
    return ind;
}

int found_index_hotels(char *key) {
    int id = atoi(key+3), ind = id % NUM_LINHAS_VALID_RESERVATION;
    return ind;
}

//void init_user_array(UList *user_array) {
//    for (int i = 0; i < NUM_LINHAS_VALID_USER; i++) {
//        user_array[i].init = NULL;
//    }
//}

//void init_flight_array(FList *flight_array) {
//    for (int i = 0; i < NUM_LINHAS_VALID_FLIGHT; i++) {
//        flight_array[i].init = NULL;
//    }
//}

//void init_reservation_array(RList *reservation_array) {
//    for (int i = 0; i < NUM_LINHAS_VALID_RESERVATION; i++) {
//        reservation_array[i].init = NULL;
//    }
//}