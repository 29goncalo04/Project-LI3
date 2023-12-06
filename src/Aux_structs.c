#include <string.h>

#include "../include/Aux_structs.h"

Flight_id_passenger create_flight_id(char *flight_id){     
    Flight_id_passenger novo;                                          
    novo.flight_id = strdup(flight_id);
    return novo;
}

Flight_aux create_flight_aux(char *flight_id, char *schedule_departure_date, int exists_argument2){
    Flight_aux novo;
    novo.flight_id = strdup(flight_id);
    novo.schedule_departure_date = strdup(schedule_departure_date);
    if(exists_argument2==1) novo.type = strdup("");
    else novo.type = strdup (";flight");
    return novo;
}

Reservation_aux create_reservation_aux(char *reservation_id, char *begin_date, int exists_argument2){
    Reservation_aux novo;
    novo.reservation_id = strdup(reservation_id);
    novo.begin_date = strdup(begin_date);
    if(exists_argument2==1) novo.type = strdup("");
    else novo.type = strdup (";reservation");
    return novo;
}

PassengersXairport create_PassengersXairport(char* origin, int passengers){    
    PassengersXairport novo;                                          
    novo.origin = strdup(origin);
    novo.passengers = passengers;
    return novo;
}

idXname create_IdXname(char* id, char* name){     
    idXname novo;                                          
    novo.id = strdup(id);
    novo.name = strdup(name);
    return novo;
}

hotel_aux create_hotel_aux (char *id, char *begin_date, char *end_date, char *user_id, char *rating, double total_price) {
    hotel_aux novo;
    novo.id = strdup (id);
    novo.begin_date = strdup (begin_date);
    novo.end_date = strdup (end_date);
    novo.user_id = strdup (user_id);
    novo.rating = strdup (rating);
    novo.total_price = total_price;
    return novo;
}

flight_date_aux create_flight_date_aux (char *id, char *schedule_departure_date, char *destination, char *airline, char *plane_model) {
    flight_date_aux novo;
    novo.id = strdup (id);
    novo.schedule_departure_date = strdup (schedule_departure_date);
    novo.destination = strdup (destination);
    novo.airline = strdup (airline);
    novo.plane_model = strdup (plane_model);
    return novo;
}

Mediana create_mediana (char *airport, int mediana){
    Mediana novo;
    novo.airport = strdup(airport);
    novo.mediana = mediana;
    return novo;
}