#include "../include/Catalogs.h"

void ordena_list_reservations(int ind, char *date_ind, int **list, int n);
void ordena_list_flights(int ind, char *date_ind, char *id_f, int **list, int n);

void init_user(UList *list);
void init_flight(FList *list);
void init_reservation(RList *list);

int found_index_flights(char *key);
int found_index_reservations(char *key);
int found_index_users(char *key);

void init_user_array(UList *user_array_valid, int num_linhas_valid_user, int m_users);
void init_flight_array(FList *flight_array_valid, int num_linhas_valid_flight, int m_flights);
void init_reservation_array(RList *reservation_array_valid, int num_linhas_valid_reservation, int m_reservations);

void users_hash_sort();
void flights_hash_sort();
void reservations_hash_sort();

