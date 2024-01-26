#include <stdlib.h>

#include "../include/Free.h"
#include "../include/Catalogs.h"


void free_all() {
    free_flight_valid();
    free_reservation_valid();
    free_user_valid();
    free_hotel_valid();
    free_airport_valid();
    free_year_valid();
    free_Prefix_valid();
}