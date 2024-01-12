#include "../include/Catalogs.h"

void ordena_list_reservations(int ind, char *date_ind, int **list, int n);
void ordena_list_flights(int ind, const char *date_ind, char *id_f, int **list, int n);

void init_user(UList *list);
void init_flight(FList *list);
void init_reservation(RList *list);

int found_index_flights(const char *key);
int found_index_reservations(char *key);
int found_index_users(char *key);
int found_index_hotels(char *key);

void init_user_array(UList *user_array);
void init_flight_array(FList *flight_array_valid);
void init_reservation_array(RList *reservation_array);

void users_hash_sort(UList *user_array_valid, UList list);
void reservations_hash_sort(RList *reservation_array_valid, RList list);
void hotels_hash_sort (HList *hotel_array_valid, HList list);