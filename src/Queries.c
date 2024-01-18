#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "../include/Aux_validation.h"
#include "../include/Output_queries.h"
#include "../include/Free.h"
#include "../include/Aux_functions.h"
#include "../include/Aux_structs.h"
#include "../include/Arguments_of_inputs.h"
#include "../include/Queries.h"
#include "../include/Hash.h"
#include "../include/Catalogs.h"


// void query1(char *argument, int i, int n){
//     int wanted_id = -1, index_line = i, wanted_user_id = -1, wanted_id_2 = -1, generated_file = 0;
//     char *breakfast;
//     char *status;
    
//     //char* argument = arguments_query1(line, i, &index_line);

//     if (isdigit(line[index_line])){   //irá listar o resumo de um voo
//         wanted_id = -1;
//         /*
//         for (int k=0; k<num_linhas_invalid_flight; k++){   //procura esse id de voo no array que tem os voos inválidos guardados
//             if (strcmp(argument, flight_array_invalid[k].id)==0){
//                 wanted_id = k;  //encontrou o id desse voo
//                 break;
//             }
//         }*/
//         //if (wanted_id != -1);//encontrou o id desse voo nos inválidos
//         //else {   //esse id de voo é válido
//             for (int k=0; k<num_linhas_valid_flight; k++){   //procura esse id de voo no array que tem os voos válidos guardados
//                 if (strcmp(argument, flight_array_valid[k].id)==0){
//                     wanted_id = k;  //encontrou o id desse voo
//                     break;
//                 }
//             }
//             if (wanted_id != -1){
//                 for (int l = 0; l < num_linhas_contador; l++) {
//                     if (strcmp(argument, contador_array[l].id_flight) == 0) {
//                         wanted_id_2 = l;
//                         break;
//                     }
//                 }
//                 outputs_query1_flights(flight_array_valid, contador_array, wanted_id, wanted_id_2, index_line, n); ////voos
//                 generated_file = 1;
//             }
//         //}
//     }
    
//     else if (line[index_line]=='B' && line[index_line+1]=='o' && line[index_line+2]=='o' && line[index_line+3]=='k'){  //irá listar o resumo de uma reserva
//         wanted_id = -1;
//         /*
//         for (int k=0; k<num_linhas_invalid_reservation; k++){   //procura esse id da reserva no array que tem as reservas inválidas guardadas
//             if (strcmp(argument, reservation_array_invalid[k].id)==0){
//                 wanted_id = k;  //encontrou o id dessa reserva
//                 break;
//             }
//         }*/
//         //if (wanted_id != -1);//encontrou o id dessa reserva nas inválidas 
//         //else {   //esse id de reserva é válido
//             for (int k=0; k<num_linhas_valid_reservation; k++){   //procura esse id da reserva no array que tem as reservas válidas guardadas
//                 if (strcmp(argument, reservation_array_valid[k].id)==0){
//                     wanted_id = k;  //encontrou o id dessa reserva
//                     break;
//                 }
//             }
//             if (wanted_id != -1){
//                 for (int k = 0; k<num_linhas_valid_user; k++){   //procura o id do utilizador que fez essa reserva para ver qual o seu account status
//                     if (strcmp(reservation_array_valid[wanted_id].user_id, user_array_valid[k].id)==0){
//                         wanted_user_id = k;  //encontrou o id desse utilizador
//                         break;
//                     }
//                 }
//                 if (verify_account_status(user_array_valid[wanted_user_id].account_status) == 2); //não imprime nada caso a conta do utilizador esteja inativa
//                 else{
//                     if (verify_breakfast(reservation_array_valid[wanted_id].includes_breakfast) == 1) breakfast = strdup("True");
//                     else  breakfast = strdup("False");
//                     outputs_query1_reservations(reservation_array_valid, breakfast, wanted_id, index_line, n); //reservas
//                     free(breakfast);
//                     generated_file = 1;
//                 }
//             }
//         //}
//     }
//     else{  //irá listar o resumo de um utilizador
//         wanted_id = -1;
//         /*
//         for (int k=0; k<num_linhas_invalid_user; k++){   //procura esse id do utilizador no array que tem os utilizadores inválidos guardados
//             if (strcmp(argument, user_array_invalid[k].id)==0){
//                 wanted_id = k;  //encontrou o id desse utilizador
//                 break;
//             }
//         }*/
//         //if (wanted_id != -1);//encontrou o id desse utilizador nos inválidos  
//         //else{
//             for (int k=0; k<num_linhas_valid_user; k++){   //procura esse id do utilizador no array que tem os utilizadores válidos guardados
//                 if (strcmp(argument, user_array_valid[k].id)==0){
//                     wanted_id = k;  //encontrou o id desse utilizador
//                     break;
//                 }
//             }
//             if (wanted_id != -1){
//                 status = strdup(pointer->user.account_status);
//                 toLowerCase(status);
//                 if (verify_account_status(status) == 2);   //não imprime nada caso a conta do utilizador esteja inativa
//                 else{
//                     int /*flights = 0,*/ reservations = 0;
//                     double total_spent = 0;/*
//                     for (int l = 0; l<num_linhas[0]; l++){   //procura o id do utilizador no array dos passageiros para ver em quantos voos ele andou 
//                         if (strcmp(user_array[wanted_id].id, passenger_array[l].user_id)==0) flights++;
//                     }*/
//                     for (int k = 0; k<num_linhas_valid_reservation; k++){   //procura o id do utilizador no array das reservas para ver quantas reservas ele fez 
//                         if (strcmp(pointer->user.id, reservation_array_valid[k].user_id)==0){
//                             reservations++;
//                             total_spent += total_price(reservation_array_valid[k].price_per_night, nights(reservation_array_valid[k].begin_date,reservation_array_valid[k].end_date), reservation_array_valid[k].city_tax);
//                         }
//                     }
//                     outputs_query1_users(user_array_valid, total_spent, reservations, wanted_id, index_line, n); //utilizadores
//                     generated_file = 1;
//                 }
//                 free(status);
//             }
//         //}  
//     }
//     free(argument);
//     if (generated_file==0) create_output(n, 0);
// }

// void query2(char *line, int i, int n){
//     int wanted_user_id = -1, index_line = i, exists_argument2 = 0, generated_file = 0;
//     char *status;
//     char *argument2 = NULL;
    
//     char* argument1 = arguments_query2(line, i, &exists_argument2, &argument2, &index_line);
//     /*
//     for (int i = 0; i<num_linhas_invalid_user; i++){     //vai procurar o id do utilizador nos inválidos
//         if (strcmp(argument1, user_array_invalid[i].id)==0){   //se encontrar o id desse utilizador
//             wanted_user_id = i;
//             break;
//         }
//     }*/
//     //if (wanted_user_id==-1){   //caso o utilizador seja válido
//         for (int i = 0; i<num_linhas_valid_user; i++){     //vai procurar o id do utilizador nos válidos
//             if (strcmp(argument1, user_array_valid[i].id)==0){   //se encontrar o id desse utilizador
//                 wanted_user_id = i;
//                 break;
//             }
//         }
//         if (wanted_user_id != -1){
//             status = strdup(user_array_valid[wanted_user_id].account_status);
//             toLowerCase(status);
//             if (verify_account_status(status) == 1){   //apenas imprime caso a conta do utilizador esteja ativa
//                 int num_flights_passenger_id = 0, num_reservations = 0;
//                 Flight_id_passenger *flight_id_passenger_array = NULL;      //será um array para armazenar os id's de todos os voos em que o utilizador já voou
//                 Flight_aux *flight_aux_array = NULL; //será um array para armazenar a data esperada de partida e o id do voo em que o utilizador voou
//                 Reservation_aux *reservation_aux_array = NULL; //será um array para armazenar a data da reserva e o id da reserva que o utilizador fez
//                 if (strcmp(argument2, "reservations")!=0){
//                     for (int i = 0; i<num_linhas_valid_passenger; i++){   //procura o id desse utilizador no array dos passageiros para saber qual o seu voo
//                         if (strcmp(argument1, passenger_array_valid[i].user_id)==0){   //se econtrar o id do utilizador no ficheiro dos passageiros e essa linha for válida
//                             Flight_id_passenger novo = create_flight_id(passenger_array_valid[i].flight_id);    //é criado um novo elemento do array com o parâmetro lido
//                             flight_id_passenger_array = realloc(flight_id_passenger_array, (num_flights_passenger_id+1)*sizeof(Flight_id_passenger)); 
//                             flight_id_passenger_array[num_flights_passenger_id] = novo;        //esse novo elemento é adicionado ao array existente
//                             num_flights_passenger_id++;
//                         }
//                     }
//                     if (num_flights_passenger_id!=0){  //se encontrou voos em que o utilizador voou
//                         for (int i = 0, j = 0; i<num_linhas_valid_flight && j<num_flights_passenger_id; i++){   //procura esses id's de voos no ficheiro dos voos
//                             if (strcmp(flight_array_valid[i].id, flight_id_passenger_array[j].flight_id)==0){   //encontrou o id de voo
//                                 char* departure_date = only_date(flight_array_valid[i].schedule_departure_date);
//                                 Flight_aux novo;
//                                 if (exists_argument2==0) novo = create_flight_aux(flight_array_valid[i].id, departure_date, 0);
//                                 else novo = create_flight_aux(flight_array_valid[i].id, departure_date, 1);
//                                 flight_aux_array = realloc(flight_aux_array, (j+1)*sizeof(Flight_aux));
//                                 flight_aux_array[j] = novo;
//                                 j++;
//                                 free(departure_date);
//                             }
//                         }
//                         insertionSort_flights(flight_aux_array, num_flights_passenger_id);
//                     }
//                 }
//                 if (strcmp(argument2, "flights")!=0){    //só lista as reservas que um utilizador fez caso o segundo argumento não exista ou seja diferente de "flights"
//                     for (int i = 0; i<num_linhas_valid_reservation; i++){   //procura o id desse utilizador no array das reservas para saber qual a sua reserva
//                         if (strcmp(argument1, reservation_array_valid[i].user_id)==0){   //se econtrar o id do utilizador no ficheiro das reservas válidas
//                             Reservation_aux novo;
//                             if (exists_argument2 == 0) novo = create_reservation_aux(reservation_array_valid[i].id, reservation_array_valid[i].begin_date, 0);
//                             else novo = create_reservation_aux(reservation_array_valid[i].id, reservation_array_valid[i].begin_date, 1);
//                             int j = num_reservations - 1;
//                             reservation_aux_array = realloc(reservation_aux_array, (num_reservations + 1) * sizeof(Reservation_aux));
//                             while (j >= 0 && compare_date_time(reservation_aux_array[j].begin_date, novo.begin_date) == 1) {
//                                 reservation_aux_array[j + 1] = reservation_aux_array[j];
//                                 j--;
//                             }
//                             reservation_aux_array[j + 1] = novo;
//                             num_reservations++;
//                         }
//                     }
//                 }  
//                 outputs_query2(flight_aux_array, reservation_aux_array, index_line, argument2, num_flights_passenger_id, num_reservations, n);
//                 generated_file = 1;
//                 free_flight_id_passenger(flight_id_passenger_array, num_flights_passenger_id);
//                 free_flight_aux(flight_aux_array, num_flights_passenger_id);
//                 free_reservation_aux(reservation_aux_array, num_reservations);
//             }
//             free(status);
//         }
//     //}
//     free(argument1);
//     free(argument2);
//     if (generated_file==0) create_output(n, 0);
// }

// void query3(char *line, int i, int n) {
//     double rating = 0, rating_t = 0, total = 0, media = 0;
//     int flag, generated_file = 0, index_line = i;

//     if (i == 2) flag = 1;
//     else flag = 0;
 
//     char* argument = arguments_query3(line, i, &index_line);

//     int check = check_length(argument);
//     if (check == 1) {
//         for (i = 0; i < num_linhas_valid_reservation; i++) {
//             if (strcmp(reservation_array_valid[i].hotel_id, argument) == 0){
//                 rating = (double) atof(reservation_array_valid[i].rating);
//                 rating_t += (double) rating;
//                 total = (double) total + 1;
//             }
//         }

//         if (total != 0) {
//             media = (double) (rating_t / total);
//             outputs_query3(media, flag, n);
//             generated_file = 1;
//         }
//     }
//     free(argument);
//     if (generated_file==0) create_output(n, 0);
// }

// void query4 (char *line, int i, int n) {
//     int index_line = i, generated_file = 0;  // i=1

//     char* argument = arguments_query4(line, i, &index_line);

//     hotel_aux *hotel_aux_array = NULL;  // será um array para armazenar os campos do hotel pretendidos
//     int num_hotels = 0;
//     for (i = 0; i < num_linhas_valid_reservation; i++) {  // vai percorrer o array das reservas para procurar o id pretendido
//         if ((strcmp(argument, reservation_array_valid[i].hotel_id) == 0)) {  // se econtrar o id do hotel no ficheiro das reservas válidas
//             hotel_aux novo = create_hotel_aux (reservation_array_valid[i].id, reservation_array_valid[i].begin_date, reservation_array_valid[i].end_date, reservation_array_valid[i].user_id, reservation_array_valid[i].rating, total_price (reservation_array_valid[i].price_per_night, nights(reservation_array_valid[i].begin_date,reservation_array_valid[i].end_date), reservation_array_valid[i].city_tax));
//             hotel_aux_array = realloc (hotel_aux_array, (num_hotels+1)*sizeof(hotel_aux));
//             hotel_aux_array [num_hotels] = novo;
//             num_hotels++;
//         }
//     }
//     qsort (hotel_aux_array, num_hotels, sizeof(hotel_aux), compare_hotels);
//     outputs_query4(hotel_aux_array, index_line, num_hotels, n);
//     generated_file = 1;
//     free(argument);
//     free_hotel_aux (hotel_aux_array, num_hotels);
//     if (generated_file==0) create_output(n, 0);
// }

// void query5 (char *line, int i, int n) {
//     int index1_line = i;  // i=1
//     char* arg_begin_date = NULL;
//     char* arg_end_date = NULL;

//     char* arg_origin = arguments_query5(line, i, &index1_line, &arg_begin_date, &arg_end_date);

//     flight_date_aux *flight_date_aux_array = NULL;  // será um array para armazenar os campos do voo pretendidos
//     int num_flights = 0;
//     char *arg_origin_cpy = strdup (arg_origin);
//     toLowerCase(arg_origin_cpy);
//     for (i = 0; i < num_linhas_valid_flight; i++) {  // vai percorrer o array dos voos para procurar os que têm a origin pretendida
//         char *flight_origin_cpy = strdup(flight_array_valid[i].origin);
//         toLowerCase(flight_origin_cpy);
//         if ((strcmp(arg_origin_cpy, flight_origin_cpy) == 0) && is_date_between (flight_array_valid[i].schedule_departure_date, arg_begin_date, arg_end_date)) {  // se encontrar a origin no ficheiro dos voos válidos e se a schedule_departure_date desse voo estiver entre as datas pretendidas
//             flight_date_aux novo = create_flight_date_aux (flight_array_valid[i].id, flight_array_valid[i].schedule_departure_date, flight_array_valid[i].destination, flight_array_valid[i].airline, flight_array_valid[i].plane_model);
//             flight_date_aux_array = realloc (flight_date_aux_array, (num_flights+1)*sizeof(flight_date_aux));
//             flight_date_aux_array [num_flights] = novo;
//             num_flights++;
//         }
//         free (flight_origin_cpy);
//     }
//     free (arg_origin_cpy);
//     qsort (flight_date_aux_array, num_flights, sizeof(flight_date_aux), compare_flights);
//     free(arg_origin);
//     free(arg_begin_date);
//     free(arg_end_date);
//     outputs_query5(flight_date_aux_array, index1_line, num_flights, n);
//     free_flight_date_aux (flight_date_aux_array, num_flights);
// }

// void query6 (char *line, int i, int n) {
//     int flag, index_pXa, index, index_line = i;
//     char *date_t = (char*)malloc(5 * sizeof(char));
//     char* origin = (char*)malloc(4 * sizeof(char));
    
//     if (i == 2) flag = 1;
//     else flag = 0;

//     int top = atoi(&line[7]);
//     char* date = arguments_query6(line, i, &index_line);

//     int num_linhas_PassengersXairport = 0;
//     PassengersXairport *passengersXairport_array = NULL;
//     for (int k = 0; k < num_linhas_valid_flight; k++) {
//         if (flight_array_valid[k].validation == 1) {
//             for (index = 0; index < 4; index++) {
//                 date_t[index] = flight_array_valid[k].schedule_departure_date[index];
//             }
//             date_t[index] = '\0';
//             if (strcmp(date_t, date) == 0) {
//                 strcpy(origin, flight_array_valid[k].origin);
//                 toUpperCase(origin);
//                 for (int pos = 0; pos < num_linhas_contador; pos++) {
//                     if (strcmp(contador_array[pos].id_flight, flight_array_valid[k].id) == 0) {
//                         int ind;
//                         for (ind = 0; ind < num_linhas_PassengersXairport; ind++) {
//                             if (strcmp(origin,passengersXairport_array[ind].origin) == 0) {
//                                 passengersXairport_array[ind].passengers += contador_array[pos].contador;
//                                 break;
//                             }
//                         }
//                         if (ind == num_linhas_PassengersXairport) {
//                             PassengersXairport novo = create_PassengersXairport (origin, contador_array[pos].contador);
//                             passengersXairport_array = realloc(passengersXairport_array, (num_linhas_PassengersXairport + 1) * sizeof(PassengersXairport));
//                             passengersXairport_array[num_linhas_PassengersXairport] = novo;
//                             num_linhas_PassengersXairport++; 
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     for (index_pXa = 0; index_pXa < num_linhas_PassengersXairport; index_pXa++) {
//         for (int index_pXa_prox = index_pXa + 1; index_pXa_prox < num_linhas_PassengersXairport; index_pXa_prox++) {
//             if (passengersXairport_array[index_pXa].passengers < passengersXairport_array[index_pXa_prox].passengers) {
//                 // Uso da função para trocar ints
//                 swap_contador(&passengersXairport_array[index_pXa].passengers, &passengersXairport_array[index_pXa_prox].passengers);
//                 // Uso da função para trocar strings
//                 swapStrings(&passengersXairport_array[index_pXa].origin, &passengersXairport_array[index_pXa_prox].origin);
//             }
//             else
//                 if (passengersXairport_array[index_pXa].passengers == passengersXairport_array[index_pXa_prox].passengers) {
//                     if (strcmp(passengersXairport_array[index_pXa].origin, passengersXairport_array[index_pXa_prox].origin) < 0) {
//                          // Uso da função para trocar ints
//                         swap_contador(&passengersXairport_array[index_pXa].passengers, &passengersXairport_array[index_pXa_prox].passengers);
//                         // Uso da função para trocar strings
//                         swapStrings(&passengersXairport_array[index_pXa].origin, &passengersXairport_array[index_pXa_prox].origin);
//                     }
//                 }
            
//         }
//     }

//     outputs_query6(passengersXairport_array, index_pXa, top, flag, n);
//     free_PassengersXairport(passengersXairport_array, num_linhas_PassengersXairport);
//     free(date);
//     free(origin);
//     free(date_t);
// }

// void query7(char *line, int i, int n){
//     int N = 0, index_line = i, generated_file = 0;

//     char* argument = arguments_query7(line, i, &index_line);

//     if (strlen(argument)>0){
//         N = atoi(argument);
//         int num_medianas = 0;
//         Mediana *mediana_array = NULL;    //array que irá guardar as medianas e o respetivo aeroporto
//         for (int i = 0; i<num_Atrasos; i++){
//             Mediana novo = create_mediana(Atrasos_array[i].airport, calculate_mediana(Atrasos_array[i].atraso, Atrasos_array[i].num_atrasos));
//             mediana_array = realloc(mediana_array, (num_medianas+1)*sizeof(Mediana));
//             mediana_array[num_medianas] = novo;
//             num_medianas++;
//         }

//         insertionSort_medianas(mediana_array, num_medianas);
        
//         if(N>num_medianas) N = num_medianas;
//         outputs_query7(mediana_array, index_line, N, n);
//         generated_file = 1;
//         free_Mediana(mediana_array, num_medianas);
//     }
//     free(argument);
//     if (generated_file==0) create_output(n, 0);
// }

// void query9 (char *line, int i, int n) {
//     int flag, ind, index_line = i, generated_file = 0;
    
//     if (i == 2) flag = 1;
//     else flag = 0;

//     char* name = arguments_query9(line, i, &index_line);

//     if (strlen(name)>0){
//         char *status_cpy = NULL;
//         int num_linhas_idXname = 0;
//         idXname *idXname_array = NULL;
//         for (int k = 0; k < num_linhas_valid_user; k++) {
//             status_cpy = strdup(user_array_valid[k].account_status);
//             toLowerCase (status_cpy);
//             if (strcmp(status_cpy,"active") == 0) {
//                 for (ind = 0; name[ind] == user_array_valid[k].name[ind]; ind++);
//                 if (name[ind] == '\0') {
//                     idXname novo = create_IdXname (user_array_valid[k].id, user_array_valid[k].name);
//                     idXname_array = realloc(idXname_array, (num_linhas_idXname + 1) * sizeof(idXname));
//                     idXname_array[num_linhas_idXname] = novo;
//                     num_linhas_idXname++;
//                 }
//             }
//             free(status_cpy);
//         }

//         for(int index_idXn = 0; index_idXn < num_linhas_idXname; index_idXn++) {
//             for (int index_idXn_prox = index_idXn + 1; index_idXn_prox < num_linhas_idXname; index_idXn_prox++) {
//                 if (strcoll(idXname_array[index_idXn].name,idXname_array[index_idXn_prox].name) > 0) { //comparar ignorando maiusculas e minusculas
//                     // Uso da função para trocar strings
//                     swapStrings(&idXname_array[index_idXn].name, &idXname_array[index_idXn_prox].name);
//                     swapStrings(&idXname_array[index_idXn].id, &idXname_array[index_idXn_prox].id);
//                 }
//                 else
//                     if (strcoll(idXname_array[index_idXn].name,idXname_array[index_idXn_prox].name) == 0) { //comparar ignorando maiusculas e minusculas
//                         if (strcoll(idXname_array[index_idXn].id,idXname_array[index_idXn_prox].id) > 0) { //comparar ignorando maiusculas e minusculas
//                             // Uso da função para trocar strings
//                             swapStrings(&idXname_array[index_idXn].name, &idXname_array[index_idXn_prox].name);
//                             swapStrings(&idXname_array[index_idXn].id, &idXname_array[index_idXn_prox].id);
//                         }
//                     }  
//             }
//         }  

//         outputs_query9(idXname_array, num_linhas_idXname, flag, n);
//         generated_file = 1;
//         free_idXname(idXname_array, num_linhas_idXname);
//     }
//     free(name);
//     if (generated_file==0) create_output(n, 0);
// }

void query1 (char *argument, int flag, int n) {
	int generated_file = 0;
    if (argument[strlen(argument)-1] == '\n') argument[strlen(argument)-1] = '\0';
    if (isdigit(argument[0])) {
        int ind = found_index_flights(argument);
        const FNo *pointer = getFListInit(get_flight_array_valid(ind));
        while (pointer != NULL) {
            if (strcmp(argument, get_flight_id(pointer)) == 0) break;
            else pointer = get_flight_prox(pointer);
        }
        if (pointer != NULL) {
            outputs_query1_flights (pointer, flag, n);
            generated_file = 1;
        }
    }
	else {
        if (argument[0] == 'B' && argument[1] == 'o' && argument[2] == 'o' && argument[3] == 'k') {
            int ind_r = found_index_reservations(argument);
            const RNo *rpointer = getRListInit(get_reservation_array_valid(ind_r));
            while (rpointer != NULL) {
                if (strcmp(argument, get_reservation_id(rpointer)) == 0) break;
                else rpointer = get_reservation_prox(rpointer);
            }

            if (rpointer != NULL) {
                char* aux = strdup(get_reservation_user_id(rpointer));
                int ind_u = found_index_users(aux);
                free(aux);
                const UNo *upointer = getUListInit(get_user_array_valid(ind_u));
                while (upointer != NULL) {
                    if (strcmp(get_reservation_user_id(rpointer), get_user_id(upointer)) == 0) break;
                    else upointer = get_user_prox(upointer);
                }

                if (upointer != NULL) {
                    //if (verify_account_status(upointer->user.account_status) != 2) { //não imprime nada caso a conta do utilizador esteja inativa
                        char *breakfast;
                        char* aux_breakfast = strdup(get_reservation_includes_breakfast(rpointer));
                        if (verify_breakfast(aux_breakfast) == 1) breakfast = strdup("True");
                        else  breakfast = strdup("False");
                        free(aux_breakfast);
                        outputs_query1_reservations(rpointer, breakfast, flag, n); //reservas UNo *pointer, int flag, int check, int n
                        free(breakfast);
                        generated_file = 1;
                    //}
                }
            }
        }
        else {
            int ind = found_index_users(argument);
            const UNo *pointer = getUListInit(get_user_array_valid(ind));
            while (pointer != NULL) {
                if (strcmp(argument, get_user_id(pointer)) == 0) break;
                else pointer = get_user_prox(pointer);
            }
            if (pointer != NULL) {
                if (verify_account_status(get_user_account_status(pointer)) != 2) outputs_query1_users(pointer, flag, 1, n);
                else outputs_query1_users(pointer, flag, 0, n);
                generated_file = 1;
            }
        }
    }
    
    if (generated_file == 0) create_output(0, n);
}

void query2 (char *str, int flag, int n) {
    int ind_u, l;
    char *id = strtok(str, " ");
    char *argument = strtok(NULL, " ");
    if (argument != NULL) {
        l = strlen(argument);
        argument[l-1] = '\0';
        if (strcmp("reservations", argument) == 0) {
            ind_u = found_index_users(id);
            const UNo *upointer = getUListInit(get_user_array_valid(ind_u));
            while (upointer != NULL) {
                if (strcmp(id, get_user_id(upointer)) == 0) {
                    if (verify_account_status(get_user_account_status(upointer)) != 2) {
                        int tam = get_user_reservations(upointer);
                        int* list_reservations = (int* )malloc(tam * sizeof(int));
                        for (int j = 0; j<tam; j++) {
                            list_reservations[j] = get_user_list_reservations(upointer)[j];
                        }
                        qsort(list_reservations, tam, sizeof(int), compare_reservations);
                        outputs_query2_reservations(list_reservations, get_user_reservations(upointer), flag, 1, n);
                        free(list_reservations);
                    }
                    else {
                        outputs_query2_reservations(get_user_list_reservations(upointer), get_user_reservations(upointer), flag, 0, n);   
                    }
                    return;
                }
                else upointer = get_user_prox(upointer);
            }
            create_output(0, n);
        }
        if (strcmp("flights", argument) == 0) {
            ind_u = found_index_users(id);
            const UNo *upointer = getUListInit(get_user_array_valid(ind_u));
            while (upointer != NULL) {
                if (strcmp(id, get_user_id(upointer)) == 0) {
                    if (verify_account_status(get_user_account_status(upointer)) != 2) {
                        int tam = get_user_flights(upointer);
                        int* list_flights = (int* )malloc(tam * sizeof(int));
                        for (int j = 0; j<tam; j++) {
                            list_flights[j] = get_user_list_flights(upointer)[j];
                        }
                        qsort(list_flights, tam, sizeof(int), compare_flights);
                        outputs_query2_flights(list_flights, tam, flag, 1, n);
                        free(list_flights);
                    }
                    else {
                        outputs_query2_flights(get_user_list_flights(upointer), get_user_flights(upointer), flag, 0, n);   
                    }
                    return;
                }
                else upointer = get_user_prox(upointer);
            }
            create_output(0, n);
        }
    }
    else {
        l = strlen(id);
        id[l-1] = '\0';
        ind_u = found_index_users(id);
        const UNo *upointer = getUListInit(get_user_array_valid(ind_u));
        while (upointer != NULL) {
            if (strcmp(id, get_user_id(upointer)) == 0) {
                if (verify_account_status(get_user_account_status(upointer)) != 2) {
                    int tam = get_user_reservations(upointer);
                    int* list_reservations = (int* )malloc(tam * sizeof(int));
                    for (int j = 0; j<tam; j++) {
                        list_reservations[j] = get_user_list_reservations(upointer)[j];
                    }
                    qsort(list_reservations, tam, sizeof(int), compare_reservations);

                    int tam2 = get_user_flights(upointer);
                    int* list_flights = (int* )malloc(tam2 * sizeof(int));
                    for (int j = 0; j<tam2; j++) {
                        list_flights[j] = get_user_list_flights(upointer)[j];
                    }
                    qsort(list_flights, tam2, sizeof(int), compare_flights);

                    outputs_query2_both(list_flights, tam2, list_reservations, tam, flag, 1, n);
                    free(list_reservations);
                    free(list_flights);
                }
                else outputs_query2_both(get_user_list_flights(upointer), get_user_flights(upointer), get_user_list_reservations(upointer), get_user_reservations(upointer), flag, 0, n);
                return;
            }
            else upointer = get_user_prox(upointer);
        }
        create_output(0, n);
    }
}

void query3 (char *id, int flag, int n) {
    int l = strlen(id), ind;
    double rt = 0, total = 0, med;
    id[l-1] = '\0';
    ind = found_index_hotels(id);
    const int *list = get_hotel_list_reservations(getHListInit(get_hotel_array_valid(ind)));
    for (int i = 0; i<get_hotel_reservations((getHListInit(get_hotel_array_valid(ind)))); i++) {
        rt += get_reservation_rating(getRListInit(get_reservation_array_valid(list[i])));
        total++;
    }
    med = (double) (rt / total);
    outputs_query3(med, flag, 1, n);
}

void query4 (char *id, int flag, int n) {
    int ind = found_index_hotels(id); 
    const HNo *pointer = getHListInit(get_hotel_array_valid(ind));
    int tam = get_hotel_reservations(pointer);
    int* list_reservations = (int* )malloc(tam * sizeof(int));
    for (int j = 0; j<tam; j++) {
        list_reservations[j] = get_hotel_list_reservations(pointer)[j];
    }
    qsort(list_reservations, tam, sizeof(int), compare_reservations);
    if (pointer == NULL) outputs_query4(list_reservations, get_hotel_reservations(pointer), flag, 0, n);
    else outputs_query4(list_reservations, get_hotel_reservations(pointer), flag, 1, n);
    free(list_reservations);
}

void query5 (char *str, int flag, int n) {
    int l_arg_end_date, ind_airport;
    char *origin = strtok(str, " ");
    char *arg_begin_date = strtok(NULL, "\"");
    strtok(NULL, "\"");
    char *arg_end_date = strtok(NULL, "\n");
    l_arg_end_date = strlen (arg_end_date);
    arg_end_date[l_arg_end_date-1] = '\0';
    
    ind_airport = found_index_airport(origin);
    const ANo *pointer = getAListInit(get_airport_array_valid(ind_airport));
    int tam3 = get_airport_flights2023(pointer);
    int tam2 = get_airport_flights2022(pointer);
    int tam1 = get_airport_flights2021(pointer);
    int* list_airport2023 = (int* )malloc(tam3 * sizeof(int));
    int* list_airport2022 = (int* )malloc(tam2 * sizeof(int));
    int* list_airport2021 = (int* )malloc(tam1 * sizeof(int));
    for (int j = 0; j<tam3; j++) {
        list_airport2023[j] = get_airport_list_flights2023(pointer)[j];
    }
    for (int j = 0; j<tam2; j++) {
        list_airport2022[j] = get_airport_list_flights2022(pointer)[j];
    }
    for (int j = 0; j<tam1; j++) {
        list_airport2021[j] = get_airport_list_flights2021(pointer)[j];
    }
    qsort(list_airport2023, tam3, sizeof(int), compare_flights);
    qsort(list_airport2022, tam2, sizeof(int), compare_flights);
    qsort(list_airport2021, tam1, sizeof(int), compare_flights);
    outputs_query5(origin, arg_begin_date, arg_end_date, list_airport2023, list_airport2022, list_airport2021, tam3, tam2, tam1, flag, 1, n);
    free(list_airport2023);
    free(list_airport2022);
    free(list_airport2021);
    return;
}

void query6(char *str, int flag, int n){
    int year = atoi(strtok(str, " "));
    int N = atoi(strtok(NULL, "\0"));
    int ind_y = found_index_year(2022);
    const int *list = get_year_list_airports(getYListInit(get_year_array_valid(ind_y)));
    int tam = get_year_airports(getYListInit(get_year_array_valid(ind_y)));
    int* list_aux = (int* )malloc(tam * sizeof(int));
    for (int j = 0; j<tam; j++) {
        list_aux[j] = list[j];
    }
    if (year==2023) qsort(list_aux, tam, sizeof(int), compare_airports2023);
    if (year==2022) qsort(list_aux, tam, sizeof(int), compare_airports2022);
    if (year==2021) qsort(list_aux, tam, sizeof(int), compare_airports2021);
    outputs_query6(list_aux, year, N, flag, n, tam);
    free(list_aux);
    return;
}

void query7(char *str, int flag, int n) {
    int number = atoi(strtok(str, "\n")), tam = 0;
    list_mediana *list;
    list = NULL;
    for (int i = 0; i < NUM_LINHAS_VALID_AIRPORT; i++) {
        if(get_airport_atrasos(getAListInit(get_airport_array_valid(i))) != 0) {
            list = realloc(list, (tam+1) * sizeof(struct list_mediana));
            list[tam].airport = strdup(get_airport_name(getAListInit(get_airport_array_valid(i))));
            list[tam].mediana = get_airport_mediana(getAListInit(get_airport_array_valid(i)));
            tam++;
        }
    }

    qsort(list, tam, sizeof(struct list_mediana), compare_medianas);
    outputs_query7(list, tam, number, flag, n);
    for (int i = 0; i < tam; i++) {
        free(list[i].airport);
    }
    free(list);
}

void query8 (char *str, int flag, int n) {
    int l_arg_end_date, ind_h, revenue = 0;
    char *id = strtok (str, " ");
    char *arg_begin_date = strtok (NULL, " ");
    char *arg_end_date = strtok (NULL, " ");
    l_arg_end_date = strlen (arg_end_date);
    arg_end_date[l_arg_end_date-1] = '\0';
    ind_h = found_index_hotels(id);
    const int *list = get_hotel_list_reservations(getHListInit(get_hotel_array_valid(ind_h)));
    for (int i = 0; i<get_hotel_reservations(getHListInit(get_hotel_array_valid(ind_h))); i++) {
        if (strcmp (id, get_reservation_hotel_id(getRListInit(get_reservation_array_valid(list[i])))) == 0) {
            revenue += nights_between (get_reservation_begin_date(getRListInit(get_reservation_array_valid(list[i]))), get_reservation_end_date(getRListInit(get_reservation_array_valid(list[i]))), arg_begin_date, arg_end_date) * get_reservation_price_per_night(getRListInit(get_reservation_array_valid(list[i])));
        }
    }
    outputs_query8 (revenue, flag, n);
    return;
}

const char *global_prefix;

int compare_Prefix (const void *a, const void *b) {
    const UNo* auxA = getUListInit(get_user_array_valid(*(const int*)a));
    while(auxA!=NULL && strncmp(get_user_name(auxA), global_prefix, strlen(global_prefix))!=0){
        auxA = get_user_prox(auxA);
    }
    char *nameA = NULL; 
    if (auxA!=NULL) nameA = strdup(get_user_name(auxA));
    const UNo* auxB = getUListInit(get_user_array_valid(*(const int*)b));
    while(auxB!=NULL && strncmp(get_user_name(auxB), global_prefix, strlen(global_prefix))!=0){
        auxB = get_user_prox(auxB);
    }
    char *nameB = NULL;
    int result;
    if(auxB!=NULL) nameB = strdup(get_user_name(auxB));
    if (nameA == NULL && nameB == NULL) {
        return 0;
    } else if (nameA == NULL) {
        free(nameB);
        return -1;
    } else if (nameB == NULL) {
        free(nameA);
        return 1;
    } else if (strcoll(nameA, nameB) != 0) {
        result = strcoll(nameA, nameB);
        free(nameA);
        free(nameB);
        return result;
    }
    char *idA = strdup(get_user_id(auxA));
    char *idB = strdup(get_user_id(auxB));
    result = strcoll(idA, idB);
    free(nameA);
    free(nameB);
    free(idA);
    free(idB);
    return result;
}

void query9 (char *str, int flag, int n) {
    char *prefix;
    if (str[0]=='\"') prefix = strtok (str+1, "\"");
    else prefix = strtok (str, "\n");
    int ind_P;
    if (strlen(prefix)<5) ind_P = found_index_prefix(prefix);
    else ind_P = found_index_Prefix(prefix);
    const int *list = get_Prefix_list_users(getPListInit(get_Prefix_array_valid(ind_P)));
    int tam = get_Prefix_users(getPListInit(get_Prefix_array_valid(ind_P)));
    int* list_temp = (int* )malloc(tam * sizeof(int));
    for (int j = 0; j<tam; j++) {
        list_temp[j] = list[j];
    }
    global_prefix = prefix;
    qsort(list_temp, tam, sizeof(int), compare_Prefix);
    //if(strcmp(prefix, "Julia")==0){    
    //    for(int i=0; i<tam-1; i++){
    //        if(strncmp(get_user_name(getUListInit(get_user_array_valid(list_aux[i]))), prefix, strlen(prefix))==0 && list_aux[i]==list_aux[i+1]){
    //            printf("%d == %d\n", list_aux[i], list_aux[i+1]);
    //            const UNo* aux = (getUListInit(get_user_array_valid(list_aux[i])));
    //            while(aux!=NULL){
    //                printf("%s %s\n", get_user_id(aux), get_user_name(aux));
    //                aux = get_user_prox(aux);
    //            }
    //        }
    //    }
    //}
    list_users *list_aux;
    list_aux = NULL;
    int tam_aux = 0/*, found = 0*/;
    for (int /*i = 0,*/ j = 0; j < tam; j++/*, i = tam_aux*/) {
        if(j==0){
            const UNo* aux = getUListInit(get_user_array_valid(list_temp[j]));
            while(aux!=NULL){
                if(strncmp(get_user_name(aux), prefix, strlen(prefix))==0 && verify_account_status(get_user_account_status(aux))==1){
                    list_aux = realloc(list_aux, (tam_aux+1) * sizeof(struct list_users));
                    list_aux[tam_aux].name = strdup(get_user_name(aux));
                    list_aux[tam_aux].id = strdup(get_user_id(aux));
                    tam_aux++;
                    //found = 1;
                }
                aux = get_user_prox(aux);
            }
            //if (found==1 && i==tam_aux) break;
        }
        else{
            if (list_temp[j]!=list_temp[j-1]){
                const UNo* aux = getUListInit(get_user_array_valid(list_temp[j]));
                while(aux!=NULL){
                    if(strncmp(get_user_name(aux), prefix, strlen(prefix))==0 && verify_account_status(get_user_account_status(aux))==1){
                        list_aux = realloc(list_aux, (tam_aux+1) * sizeof(struct list_users));
                        list_aux[tam_aux].name = strdup(get_user_name(aux));
                        list_aux[tam_aux].id = strdup(get_user_id(aux));
                        tam_aux++;
                        //found = 1;
                    }
                    aux = get_user_prox(aux);
                }
                //if (found==1 && i==tam_aux) break;
            }
        }
    }
    free(list_temp);
    qsort(list_aux, tam_aux, sizeof(struct list_users), compare_users);
    outputs_query9 (list_aux, tam_aux, flag, n);
    for (int i = 0; i < tam_aux; i++) {
        free(list_aux[i].name);
        free(list_aux[i].id);
    }
    free(list_aux);
    return;
}