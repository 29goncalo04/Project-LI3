#include "../include/Catalogs.h"

void init_user(UList *list);
void init_flight(FList *list);
void init_reservation(RList *list);

int found_index_flights(const char *key);
int found_index_reservations(const char *key);
int found_index_users(char *key);
int found_index_hotels(char *key);
int found_index_airport(char *key);
int found_index_year(int key);
int found_index_Prefix(char *key);
int found_index_prefix(char *key);