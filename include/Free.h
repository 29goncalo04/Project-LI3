//módulo da libertação da memória
// módulo responsável por libertar toda a memória alocada dinamicamente ao longo do programa

#ifndef FREE_H
#define FREE_H

#include "../include/Catalogs.h"
#include "../include/Statistics.h"
#include "../include/Aux_structs.h"

void free_list_flight(FNo *nodo);

void free_flight_valid(FList *flight_array_valid, int num_linhas_valid);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de voos, e libera elemento a elemento

void free_flight_invalid(Flight *flight_array_invalid, int num_linhas_invalid);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de voos, e libera elemento a elemento

void free_passenger_valid(Passenger *passenger_array_valid, int num_linhas_valid);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de passageiros, e libera elemento a elemento

void free_passenger_invalid(Passenger *passenger_array_invalid, int num_linhas_invalid);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de passageiros, e libera elemento a elemento

void free_list_reservation(RNo *nodo);

void free_reservation_valid(RList *reservation_array_valid, int num_linhas_valid);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de reservas, e libera elemento a elemento

void free_reservation_invalid(Reservation *reservation_array_invalid, int num_linhas_invalid);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de reservas, e libera elemento a elemento

void free_user_valid();
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de utilizadores, e libera elemento a elemento

void free_user_invalid(User *user_array_invalid, int num_linhas_invalid);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de utilizadores, e libera elemento a elemento

void free_contador(Contador_id *contador_array, int num_linhas_contador);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de contador de passageiros num voo, e libera elemento a elemento

void free_Atrasos(Atrasos *Atrasos_array, int num_Atrasos);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de atrasos, e libera elemento a elemento

void free_flight_id_passenger(Flight_id_passenger *flight_id_passenger_array, int num_flights_passenger_id);
    //     |->função responsável por fazer free do array com os id's dos 
    //        voos em que um passageiro voou

void free_flight_aux(Flight_aux *flight_aux_array, int num_flights_passenger_id);
    //     |->função responsável por fazer free do array com os parâmetros dos 
    //        voos em que um passageiro voou

void free_reservation_aux(Reservation_aux *reservation_aux_array, int num_reservations);
    //     |->função responsável por fazer free do array com os parâmetros das 
    //        reservas que um utilizador fez

void free_PassengersXairport(PassengersXairport *passengersXairport_array, int num_linhas_PassengersXairport);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de passengersXairport, e libera elemento a elemento
    
void free_idXname(idXname *idXname_array, int num_linhas_idXname);
    //     |->função que libera a memória que foi alocada para criar cada
    //        elemento do array de ideXname, e libera elemento a elemento

void free_hotel_aux(hotel_aux *hotel_aux_array, int num_hotels);
    //     |->função responsável por fazer free do array com os parâmetros das 
    //        reservas de um dado hotel

void free_flight_date_aux (flight_date_aux *flight_date_aux_array, int num_flights);
    //     |->função responsável por fazer free do array com os parâmetros dos 
    //        voos com origem num dado aeroporto

void free_Mediana(Mediana *mediana_array, int num_medianas);
    //     |->função responsável por fazer free do array com as medianas de todos os aeroportos

void free_all();
    //    |->função responsável por libertar toda a memória alocada durante o programa

#endif