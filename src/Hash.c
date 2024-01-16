#include "../include/Catalogs.h"
#include "../include/Aux_functions.h"
#include "../include/Aux_validation.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>

unsigned long hash_djb2(char *key, int num) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % num;
}
unsigned long hash_djb3(char *key, int num) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        c = tolower(c);
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash % num;
}

int found_index_users(char *key) {
    return hash_djb2(key, NUM_LINHAS_VALID_USER);
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

int found_index_airport(char *key) {
    return hash_djb3(key, NUM_LINHAS_VALID_AIRPORT);
}

int found_index_year(int key) {
    int id = (key+2), ind = id % NUM_LINHAS_VALID_YEAR;
    return ind;
}