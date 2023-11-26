#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Data_Types_&_Data_Structures.h"
#include "../include/Parser.h"
#include "../include/Validation.h"
#include "../include/Queries.h"


int num_linhas_valid[4] = {0}, num_linhas_invalid[4] = {0};
int num_linhas_contador = 0, num_Atrasos = 0;
Flight *flight_array_valid = NULL;                          //inicialização de cada array
Flight *flight_array_invalid = NULL;
Passenger *passenger_array_valid = NULL;
Passenger *passenger_array_invalid = NULL;
Reservation *reservation_array_valid = NULL;
Reservation *reservation_array_invalid = NULL;
User *user_array_valid = NULL;
User *user_array_invalid = NULL;
FILE *fpassengers;
FILE *freservations;
FILE *fusers;
FILE *fflights;
FILE *arquivo;
Contador_id *contador_array = NULL;
Atrasos *Atrasos_array = NULL;

void insertionSort_atrasos(int *atrasos, int num_atrasos){
    for (int i = 1; i < num_atrasos; i++) {
        int key = atrasos[i];
        int j = i - 1;
        while (j >= 0 && atrasos[j]>key){
            atrasos[j + 1] = atrasos[j];
            j--;
        }  
        atrasos[j + 1] = key;
    }
}

void free_flight_valid(Flight *flight_array_valid, int num_linhas_valid) {      
    for (int i = 0; i < num_linhas_valid; i++) {                             
        free(flight_array_valid[i].id);
        free(flight_array_valid[i].airline);
        free(flight_array_valid[i].plane_model);
        free(flight_array_valid[i].total_seats);
        free(flight_array_valid[i].origin);
        free(flight_array_valid[i].destination);
        free(flight_array_valid[i].schedule_departure_date);
        free(flight_array_valid[i].schedule_arrival_date);
        free(flight_array_valid[i].real_departure_date);
        free(flight_array_valid[i].real_arrival_date);
        free(flight_array_valid[i].pilot);
        free(flight_array_valid[i].copilot);
        free(flight_array_valid[i].notes);
    }
    free(flight_array_valid);
}

void free_flight_invalid(Flight *flight_array_invalid, int num_linhas_invalid) {      
    for (int i = 0; i < num_linhas_invalid; i++) {                             
        free(flight_array_invalid[i].id);
        free(flight_array_invalid[i].airline);
        free(flight_array_invalid[i].plane_model);
        free(flight_array_invalid[i].total_seats);
        free(flight_array_invalid[i].origin);
        free(flight_array_invalid[i].destination);
        free(flight_array_invalid[i].schedule_departure_date);
        free(flight_array_invalid[i].schedule_arrival_date);
        free(flight_array_invalid[i].real_departure_date);
        free(flight_array_invalid[i].real_arrival_date);
        free(flight_array_invalid[i].pilot);
        free(flight_array_invalid[i].copilot);
        free(flight_array_invalid[i].notes);
    }
    free(flight_array_invalid);
}


void free_passenger_valid(Passenger *passenger_array_valid, int num_linhas_valid) {
    for (int i = 0; i < num_linhas_valid; i++) {                               
        free(passenger_array_valid[i].flight_id);
        free(passenger_array_valid[i].user_id);
    }
    free(passenger_array_valid);
}

void free_passenger_invalid(Passenger *passenger_array_invalid, int num_linhas_invalid) {
    for (int i = 0; i < num_linhas_invalid; i++) {                               
        free(passenger_array_invalid[i].flight_id);
        free(passenger_array_invalid[i].user_id);
    }
    free(passenger_array_invalid);
}


void free_reservation_valid(Reservation *reservation_array_valid, int num_linhas_valid) { 
    for (int i = 0; i < num_linhas_valid; i++) {                                  
        free(reservation_array_valid[i].id);
        free(reservation_array_valid[i].user_id);
        free(reservation_array_valid[i].hotel_id);
        free(reservation_array_valid[i].hotel_name);
        free(reservation_array_valid[i].hotel_stars);
        free(reservation_array_valid[i].city_tax);
        free(reservation_array_valid[i].address);
        free(reservation_array_valid[i].begin_date);
        free(reservation_array_valid[i].end_date);
        free(reservation_array_valid[i].price_per_night);
        free(reservation_array_valid[i].includes_breakfast);
        free(reservation_array_valid[i].room_details);
        free(reservation_array_valid[i].rating);
        free(reservation_array_valid[i].comment);
    }
    free(reservation_array_valid);
}

void free_reservation_invalid(Reservation *reservation_array_invalid, int num_linhas_invalid) { 
    for (int i = 0; i < num_linhas_invalid; i++) {                                  
        free(reservation_array_invalid[i].id);
        free(reservation_array_invalid[i].user_id);
        free(reservation_array_invalid[i].hotel_id);
        free(reservation_array_invalid[i].hotel_name);
        free(reservation_array_invalid[i].hotel_stars);
        free(reservation_array_invalid[i].city_tax);
        free(reservation_array_invalid[i].address);
        free(reservation_array_invalid[i].begin_date);
        free(reservation_array_invalid[i].end_date);
        free(reservation_array_invalid[i].price_per_night);
        free(reservation_array_invalid[i].includes_breakfast);
        free(reservation_array_invalid[i].room_details);
        free(reservation_array_invalid[i].rating);
        free(reservation_array_invalid[i].comment);
    }
    free(reservation_array_invalid);
}

void free_user_valid(User *user_array_valid, int num_linhas_valid) {  
    for (int i = 0; i < num_linhas_valid; i++) {               
        free(user_array_valid[i].id);
        free(user_array_valid[i].name);
        free(user_array_valid[i].email);
        free(user_array_valid[i].phone_number);
        free(user_array_valid[i].birth_date);
        free(user_array_valid[i].sex);
        free(user_array_valid[i].passport);
        free(user_array_valid[i].country_code);
        free(user_array_valid[i].address);
        free(user_array_valid[i].account_creation);
        free(user_array_valid[i].pay_method);
        free(user_array_valid[i].account_status);
    }
    free(user_array_valid);
}

void free_user_invalid(User *user_array_invalid, int num_linhas_invalid) {  
    for (int i = 0; i < num_linhas_invalid; i++) {               
        free(user_array_invalid[i].id);
        free(user_array_invalid[i].name);
        free(user_array_invalid[i].email);
        free(user_array_invalid[i].phone_number);
        free(user_array_invalid[i].birth_date);
        free(user_array_invalid[i].sex);
        free(user_array_invalid[i].passport);
        free(user_array_invalid[i].country_code);
        free(user_array_invalid[i].address);
        free(user_array_invalid[i].account_creation);
        free(user_array_invalid[i].pay_method);
        free(user_array_invalid[i].account_status);
    }
    free(user_array_invalid);
}


void free_contador(Contador_id *contador_array, int num_linhas_contador) {
    for (int i = 0; i < num_linhas_contador; i++) {                         
        free(contador_array[i].id_flight);
    }
    free(contador_array);
}

void free_Atrasos(Atrasos *Atrasos_array, int num_Atrasos){
    for (int i = 0; i<num_Atrasos; i++){
        free(Atrasos_array[i].airport);
        free(Atrasos_array[i].atraso);
    }
    free(Atrasos_array);
}


Flight create_flight(char parametros[][FIELD_SIZE]) {           
    Flight nova;                                              
    nova.id = strdup(parametros[0]);                                   
    nova.airline = strdup(parametros[1]);                                                                        
    nova.plane_model = strdup(parametros[2]);
    nova.total_seats = strdup(parametros[3]);
    nova.origin = strdup(parametros[4]);
    nova.destination = strdup(parametros[5]);
    nova.schedule_departure_date = strdup(parametros[6]);
    nova.schedule_arrival_date = strdup(parametros[7]);
    nova.real_departure_date = strdup(parametros[8]);
    nova.real_arrival_date = strdup(parametros[9]);
    nova.pilot = strdup(parametros[10]);
    nova.copilot = strdup(parametros[11]);
    nova.notes = strdup(parametros[12]);
    nova.validation = 1;
    return nova;
}


Passenger create_passenger(char parametros[][FIELD_SIZE]) {  
    Passenger nova;                                           
    nova.flight_id = strdup(parametros[0]);                         
    nova.user_id = strdup(parametros[1]);                                                                     
    nova.validation_flight = 1;
    nova.validation = 1;
    return nova;
}


Reservation create_reservation(char parametros[][FIELD_SIZE]) {  
    Reservation nova;                                              
    nova.id = strdup(parametros[0]);                                   
    nova.user_id = strdup(parametros[1]);
    nova.hotel_id = strdup(parametros[2]);
    nova.hotel_name = strdup(parametros[3]);
    nova.hotel_stars = strdup(parametros[4]);
    nova.city_tax = strdup(parametros[5]);
    nova.address = strdup(parametros[6]);
    nova.begin_date = strdup(parametros[7]);
    nova.end_date = strdup(parametros[8]);
    nova.price_per_night = strdup(parametros[9]);
    nova.includes_breakfast = strdup(parametros[10]);
    nova.room_details = strdup(parametros[11]);
    nova.rating = strdup(parametros[12]);
    nova.comment = strdup(parametros[13]);
    nova.validation = 1;
    return nova;
}


User create_user(char parametros[][FIELD_SIZE]) {    
    User nova;                                           
    nova.id = strdup(parametros[0]);                          
    nova.name = strdup(parametros[1]);
    nova.email = strdup(parametros[2]);
    nova.phone_number = strdup(parametros[3]);
    nova.birth_date = strdup(parametros[4]);
    nova.sex = strdup(parametros[5]);
    nova.passport = strdup(parametros[6]);
    nova.country_code = strdup(parametros[7]);
    nova.address = strdup(parametros[8]);
    nova.account_creation = strdup(parametros[9]);
    nova.pay_method = strdup(parametros[10]);
    nova.account_status = strdup(parametros[11]);
    nova.validation = 1;
    return nova;
}


Contador_id create_contador(char parametros[][FIELD_SIZE]){     
    Contador_id novo;                                          
    novo.id_flight = strdup(parametros[0]);
    novo.contador = 0;
    return novo;
}

Atrasos create_atrasos (char *airport, int atraso){
    Atrasos novo;
    novo.airport = strdup(airport);
    novo.atraso = malloc(sizeof(int));
    novo.atraso[0] = atraso;
    novo.num_atrasos = 1;
    return novo;
}

void adicionar_atrasos(Atrasos *atrasos, int novo_atraso){
    atrasos->atraso = realloc(atrasos->atraso, (atrasos->num_atrasos + 1) * sizeof(int));
    atrasos->atraso[atrasos->num_atrasos] = novo_atraso;
    atrasos->num_atrasos++; 
}

void validate_passenger(Passenger *nova, char parametros[][FIELD_SIZE], int flight_validation){
    int wanted_flight_id_validation = 1, wanted_user_id_validation = 1;
    if (flight_validation==0){
        for (int k=0; k<num_linhas_invalid[1]; k++){   //procura esse id de voo no array que tem os voos inválidos guardados
            if (strcmp(parametros[0], flight_array_invalid[k].id)==0){
                wanted_flight_id_validation = 0;
                break;
            }
        }
    }
    if (wanted_flight_id_validation==1){
        for (int l=0; l<num_linhas_invalid[3]; l++){   //procura esse id de utilizador no array que tem os utilizadores inválidos guardados
            if (strcmp(parametros[1], user_array_invalid[l].id)==0){
                wanted_user_id_validation = 0;
                break;
            }
        }
    }
    nova->validation_flight = wanted_flight_id_validation;
    nova->validation = wanted_flight_id_validation && wanted_user_id_validation;
}


void validate_flight(Flight *nova, char parametros[][FIELD_SIZE], Contador_id *contador_array, int num_linhas_contador){
    int validation = check_length(parametros[0]) && check_length(parametros[1]) && check_length(parametros[2]) &&
                 check_length (parametros[3]) && check_length (parametros[6]) && check_length (parametros[7]) &&
                 check_length(parametros[10]) && check_length(parametros[11]) &&
                 compare_seats_passengers(parametros[3], count_passengers(contador_array, num_linhas_contador, &parametros[3])) &&
                 verify_airport(parametros[4]) && verify_airport(parametros[5]) && compare_date_time(parametros[6], parametros[7]) &&
                 compare_date_time(parametros[8], parametros[9]) && check_dateWtime(parametros[6]) && check_dateWtime(parametros[7]) && 
                 check_dateWtime(parametros[8]) && check_dateWtime(parametros[9]);
    nova->validation = validation;
}


void validate_user(User *nova, char parametros[][FIELD_SIZE]){
    int validation = check_length(parametros[0]) && check_length(parametros[1]) && verify_email(parametros[2]) && check_length(parametros[3]) &&
                 check_length (parametros[4]) && check_date(parametros[4]) && check_length(parametros[5]) && check_length(parametros[6]) &&
                 verify_country_code(parametros[7]) && check_length(parametros[8]) && check_dateWtime(parametros[9]) && check_length(parametros[10]) && 
                 check_length (parametros[11]) && (verify_account_status(parametros[11])==1 || verify_account_status(parametros[11])==2) && compare_date_time(parametros[4], parametros[9]);
    nova->validation = validation;
    free(nova->account_status);
    nova->account_status = strdup(parametros[11]);
}


void validate_reservation(Reservation *nova, char parametros[][FIELD_SIZE]){
    int validation = 0, wanted_user_id_validation = 1;
    for (int i = 0; i<num_linhas_invalid[3]; i++){
        if (strcmp(parametros[1], user_array_invalid[i].id)==0) {    //encontrou o id desse utilizador no array de utilizadores inválidos
            wanted_user_id_validation = 0;
            break;
        }
    }
    if (wanted_user_id_validation==1){
        validation = check_length(parametros[0]) && check_length(parametros[1]) && check_length(parametros[2]) && check_length(parametros[3]) &&
        verify_hotel_stars(parametros[4]) && check_length (parametros[5]) && verify_city_tax(parametros[5]) && check_length(parametros[6]) &&
        check_date(parametros[7]) && check_date(parametros[8]) && check_length (parametros[9]) && check_price_per_night(parametros[9]) && 
        check_length (parametros[10]) && verify_breakfast(parametros[10]) && check_length(parametros[11]) && check_length (parametros[12]) &&
        check_reserva_rating(parametros[12]) && compare_date_time(parametros[7], parametros[8]);
    }
    nova->validation = validation;
    free(nova->includes_breakfast);
    nova->includes_breakfast = strdup(parametros[10]);
}

void free_all(){
    free_passenger_valid(passenger_array_valid, num_linhas_valid[0]);
    free_flight_valid(flight_array_valid, num_linhas_valid[1]);
    free_reservation_valid(reservation_array_valid, num_linhas_valid[2]);
    free_user_valid(user_array_valid, num_linhas_valid[3]);
    free_passenger_invalid(passenger_array_invalid, num_linhas_invalid[0]); 
    free_flight_invalid(flight_array_invalid, num_linhas_invalid[1]);            
    free_reservation_invalid(reservation_array_invalid, num_linhas_invalid[2]); 
    free_user_invalid(user_array_invalid, num_linhas_invalid[3]); 
    free_contador(contador_array, num_linhas_contador);
    free_Atrasos(Atrasos_array, num_Atrasos);
}


void open_files(char* path){
    char *line = NULL;
    size_t len = 0;
    int j = 0, previous_flight_id_validation = 0;
    //char *previous_flight_id = NULL;
    char previous_flight_id[11] = "0000000000";
    char *aux_passengers = NULL;
    aux_passengers = (char *)malloc(strlen(path) + strlen("/passengers.csv") + 1);
    strcpy(aux_passengers, path);
    strcat(aux_passengers, "/passengers.csv");
    char *aux_flights = NULL;
    aux_flights = (char *)malloc(strlen(path) + strlen("/flights.csv") + 1);
    strcpy(aux_flights, path);
    strcat(aux_flights, "/flights.csv");
    char *aux_reservations = NULL;
    aux_reservations = (char *)malloc(strlen(path) + strlen("/reservations.csv") + 1);
    strcpy(aux_reservations, path);
    strcat(aux_reservations, "/reservations.csv");
    char *aux_users = NULL;
    aux_users = (char *)malloc(strlen(path) + strlen("/users.csv") + 1);
    strcpy(aux_users, path);
    strcat(aux_users, "/users.csv");






    for (int num_ficheiro = 0; num_ficheiro<4; num_ficheiro++){         //existe um caso específico para cada ficheiro     
        int l = 0;
        switch (num_ficheiro){
            case 3: 
                fpassengers = fopen(aux_passengers, "r");                                                    //ficheiro dos passageiros
                while (getline(&line, &len, fpassengers) != -1) {
                    if (l != 0) {
                        char parametros[2][FIELD_SIZE];
                        int j_linha = 0;
                        for (int i = 0; i<2; i++){
                            if (i==0){
                                for (j = 0; line[j_linha] != ';'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                parametros[i][j] = '\0';
                                j_linha++;
                            }
                            else{           //parte do código responsável por guardar o último parâmetro (user_id)
                                for (j = 0; line[j_linha] != '\0' && line[j_linha] != '\n'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                parametros[i][j] = '\0';
                            }
                        }
                        Passenger nova = create_passenger(parametros);
                        //if (num_linhas_valid[0] == 0) validate_passenger(&nova, parametros, 0);
                        if (num_linhas_contador==0) {
                            validate_passenger(&nova, parametros, 0);  //se for a primeira vez que está a ler uma linha
                            if (nova.validation_flight==0) previous_flight_id_validation = 0;
                            else previous_flight_id_validation = 1;
                         //   printf("%s\n", nova.flight_id);
                        }
                        else{
                            if (strcmp(nova.flight_id, previous_flight_id)==0){
                                if (previous_flight_id_validation == 1){
                                    //printf("1\n");
                                    validate_passenger(&nova, parametros, 1);    //se o id de voo que está a ler é igual ao anterior e esse era válido
                                }
                                else {
                                    //printf("%s\n", nova.flight_id);
                                    nova.validation = 0;
                                    previous_flight_id_validation = 0;
                                    nova.validation_flight = 0;
                                }
                            }
                            else{
                                validate_passenger(&nova, parametros, 0);
                                if (nova.validation_flight==0) previous_flight_id_validation = 0;
                                else previous_flight_id_validation = 1;
                            }
                        }
                        if (nova.validation==1){
                            if (num_linhas_contador==0){ // Se for a primeira iteração, apenas adicione o novo elemento ao contador_array
                                Contador_id novo = create_contador(parametros);
                                contador_array = realloc(contador_array, (num_linhas_contador + 1) * sizeof(Contador_id));
                                contador_array[num_linhas_contador] = novo;
                                num_linhas_contador++;
                            }
                            else{
                                if (atoi(nova.flight_id)-atoi(contador_array[num_linhas_contador-1].id_flight)>1){ //se o ID anterior não é o estritamente anterior ao ID da linha atual  (por exemplo: atual->003, anterior->001)
                                    int array_vazio = atoi(nova.flight_id)-atoi(contador_array[num_linhas_contador-1].id_flight);
                                    for (int k = 0; k<array_vazio; k++){
                                        contador_array = realloc(contador_array, (num_linhas_contador + 1) * sizeof(Contador_id));
                                        contador_array[num_linhas_contador].id_flight = strdup("");
                                        contador_array[num_linhas_contador].contador = 0;
                                        num_linhas_contador++;
                                    }
                                }
                                if (strcmp(nova.flight_id, contador_array[num_linhas_contador-1].id_flight)==0){  //se o ID anterior é igual ao da linha atual 
                                    // Se o ID do voo é o mesmo, apenas atualiza o contador do elemento existente
                                    if (contador_array[num_linhas_contador - 1].contador == 0) contador_array[num_linhas_contador - 1].contador++;
                                    contador_array[num_linhas_contador - 1].contador++;
                                } else{  // Se o ID do voo é diferente, cria um novo elemento Contador_id e adiciona ao contador_array
                                Contador_id novo = create_contador(parametros);
                                contador_array = realloc(contador_array, (num_linhas_contador + 1) * sizeof(Contador_id));
                                contador_array[num_linhas_contador] = novo;
                                num_linhas_contador++;
                                }
                            }
                            previous_flight_id_validation = 1;
                            //free(previous_flight_id);
                            //previous_flight_id = strdup(nova.flight_id);
                            strcpy(previous_flight_id, nova.flight_id);
                            passenger_array_valid = realloc(passenger_array_valid, (num_linhas_valid[0]+1)*sizeof(Passenger));
                            passenger_array_valid[num_linhas_valid[0]] = nova;
                            num_linhas_valid[0]++;
                        }
                        else{
                            //previous_flight_id_validation = 0;
                            //free(previous_flight_id);
                            //previous_flight_id = strdup(nova.flight_id);
                            strcpy(previous_flight_id, nova.flight_id);
                            passenger_array_invalid = realloc(passenger_array_invalid, (num_linhas_invalid[0]+1)*sizeof(Passenger));
                            passenger_array_invalid[num_linhas_invalid[0]] = nova;
                            num_linhas_invalid[0]++;
                        }

                    } else {
                        l++;
                    }
                }
                //free(previous_flight_id);
                fclose(fpassengers);
                break;
            case 1:   
                fflights = fopen(aux_flights, "r");                                                      //ficheiro dos voos
                while (getline(&line, &len, fflights) != -1) {               //o programa vai ler linha a linha do ficheiro aberto
                    if (l != 0) {
                        char parametros[13][FIELD_SIZE];                       //o número de parâmetros varia de ficheiro para ficheiro
                        int j_linha = 0;

                        for (int i = 0; i<13; i++){
                            if (i<12){
                                for (j = 0; line[j_linha] != ';'; j_linha++, j++) {     //o programa copia caracter a caracter 
                                    parametros[i][j] = line[j_linha];                   //para o respetivo parâmetro até encontrar um ";"
                                }
                                parametros[i][j] = '\0';
                                j_linha++;
                            }
                            else{
                                if (line[j_linha] != '\0') {          //o programa apenas copia os caracteres para o parâmetro "notes"         
                                    j = 0;                           //caso existam notes para ser lidas nessa linha, senão o parâmetro fica ""
                                    while (line[j_linha] != '\0' && line[j_linha] != '\n') {
                                        parametros[12][j] = line[j_linha];
                                        j_linha++;
                                        j++;
                                    }
                                    parametros[12][j] = '\0';
                                }
                            }
                        }

                        Flight nova = create_flight(parametros);    //é criado um novo elemento do array com os parâmetros lidos
                        validate_flight(&nova, parametros, contador_array, num_linhas_contador);
                        if (nova.validation == 1){    //se essa linha for válida os seus parâmetros são armazenados no array de voos válidos
                            char *Airport = nova.origin;
                            toUpperCase(Airport);
                            int found = 0;   //variável auxiliar para dizer se o aeroporto foi encontrado ou não
                            if (num_linhas_valid[1] == 0){   //se for a primeira linha a ser lida
                                Atrasos novo = create_atrasos(Airport, delay(parametros[6], parametros[8]));
                                Atrasos_array = realloc(Atrasos_array, (num_Atrasos + 1) * sizeof(Atrasos));
                                Atrasos_array[num_Atrasos] = novo;
                                num_Atrasos++; 
                            }
                            else{
                                for (int i = 0; i<num_Atrasos; i++){
                                    if (strcmp(Airport, Atrasos_array[i].airport) == 0){    //caso esse aeoroporto lido já esteja no array de atrasos então é só inserir o respetivo atraso no aeroporto correspondente
                                        adicionar_atrasos(&Atrasos_array[i], delay(parametros[6], parametros[8]));
                                        found = 1;
                                        break;
                                    }
                                }
                                if (found==0){   //não encontrou o aeroporto no array de atrasos
                                    Atrasos novo = create_atrasos(Airport, delay(parametros[6], parametros[8]));
                                    Atrasos_array = realloc(Atrasos_array, (num_Atrasos + 1) * sizeof(Atrasos));
                                    Atrasos_array[num_Atrasos] = novo;
                                    num_Atrasos++;  
                                }
                            }
                            flight_array_valid = realloc(flight_array_valid, (num_linhas_valid[1]+1)*sizeof(Flight));   
                            flight_array_valid[num_linhas_valid[1]] = nova;        //esse novo elemento é adicionado ao array de válidos
                            num_linhas_valid[1]++;
                        }
                        else{
                            flight_array_invalid = realloc(flight_array_invalid, (num_linhas_invalid[1]+1)*sizeof(Flight));   
                            flight_array_invalid[num_linhas_invalid[1]] = nova;        //esse novo elemento é adicionado ao array de inválidos
                            num_linhas_invalid[1]++;
                        }

                    } else {
                        l++;
                    }
                }
                for (int i = 0; i<num_Atrasos; i++){
                    insertionSort_atrasos(Atrasos_array[i].atraso, Atrasos_array[i].num_atrasos);
                }
                fclose(fflights);
                break;

            case 2:  
                freservations = fopen(aux_reservations, "r");                                                     //ficheiro das reservas
                while (getline(&line, &len, freservations) != -1) {
                    if (l != 0) {
                        char parametros[14][FIELD_SIZE];
                        int j_linha = 0;
                        for (int i = 0; i<14; i++){
                            if (i<13){
                                for (j = 0; line[j_linha] != ';'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                if (j == 0 && i == 10 && line[j_linha] == ';') {
                                    parametros[i][j] = ' ';
                                    parametros[i][j+1] = '\0';
                                }
                                else {
                                    parametros[i][j] = '\0';
                                }
                                j_linha++;
                            }
                            else{
                                if (line[j_linha] != '\0') {     //o programa apenas copia os caracteres para o parâmetro "comment"         
                                    j = 0;                       //caso existam comentários para ser lidos nessa linha, senão o parâmetro fica ""
                                    while (line[j_linha] != '\0' && line[j_linha] != '\n') {
                                        parametros[13][j] = line[j_linha];
                                        j_linha++;
                                        j++;
                                    }
                                    parametros[13][j] = '\0';
                                }
                            }
                        }
                        Reservation nova = create_reservation(parametros);
                        validate_reservation(&nova, parametros);
                        if (nova.validation == 1){  //se essa linha for válida os seus parâmetros são armazenados no array de reservas válidas
                            reservation_array_valid = realloc(reservation_array_valid, (num_linhas_valid[2]+1)*sizeof(Reservation));
                            reservation_array_valid[num_linhas_valid[2]] = nova;
                            num_linhas_valid[2]++;
                        }
                        else{
                            reservation_array_invalid = realloc(reservation_array_invalid, (num_linhas_invalid[2]+1)*sizeof(Reservation));
                            reservation_array_invalid[num_linhas_invalid[2]] = nova;
                            num_linhas_invalid[2]++;
                        }
                    } else {
                        l++;
                    }
                }
                fclose(freservations);
                break;

            case 0:
                fusers = fopen(aux_users, "r");                                                 //ficheiro dos utilizadores
                while (getline(&line, &len, fusers) != -1) {
                    if (l != 0) {
                        char parametros[12][FIELD_SIZE];
                        int j_linha = 0;
                        for (int i = 0; i<12; i++){
                            if (i<11){
                                for (j = 0; line[j_linha] != ';'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                parametros[i][j] = '\0';
                                j_linha++;
                            }
                            else{              //parte do código responsável por guardar o último parâmetro (account_status)
                                for (j = 0; line[j_linha] != '\0' && line[j_linha] != '\n'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                parametros[i][j] = '\0';
                            }
                        }
                        User nova = create_user(parametros);
                        validate_user(&nova, parametros);
                        if (nova.validation == 1){  //se essa linha for válida os seus parâmetros são armazenados no array de utilizadores válidos
                            user_array_valid = realloc(user_array_valid, (num_linhas_valid[3]+1)*sizeof(User));
                            user_array_valid[num_linhas_valid[3]] = nova;
                            num_linhas_valid[3]++;
                        }
                        else{
                            user_array_invalid = realloc(user_array_invalid, (num_linhas_invalid[3]+1)*sizeof(User));
                            user_array_invalid[num_linhas_invalid[3]] = nova;
                            num_linhas_invalid[3]++;
                        }
                    } else {
                        l++;
                    }
                }
                fclose(fusers); 
                break;           
        }
    }
    free(aux_passengers);
    free(aux_flights);
    free(aux_users);
    free(aux_reservations);
    free(line);
    
 
}