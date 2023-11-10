#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Data_Types_&_Data_Structures.h"
#include "../include/Parser.h"
#include "../include/Validation.h"

int num_linhas[4] = {0};
int num_linhas_contador = 0;
Flight *flight_array = NULL;                          //inicialização de cada array
Passenger *passenger_array = NULL;
Reservation *reservation_array = NULL;
User *user_array = NULL;
FILE *arquivo;
Contador_id *contador_array = NULL;

void free_flight(Flight *flight_array, int num_linhas) {      
    for (int i = 0; i < num_linhas; i++) {                             
        free(flight_array[i].id);
        free(flight_array[i].airline);
        free(flight_array[i].plane_model);
        free(flight_array[i].total_seats);
        free(flight_array[i].origin);
        free(flight_array[i].destination);
        free(flight_array[i].schedule_departure_date);
        free(flight_array[i].schedule_arrival_date);
        free(flight_array[i].real_departure_date);
        free(flight_array[i].real_arrival_date);
        free(flight_array[i].pilot);
        free(flight_array[i].copilot);
        free(flight_array[i].notes);
    }
    free(flight_array);
}


void free_passenger(Passenger *passenger_array, int num_linhas) {
    for (int i = 0; i < num_linhas; i++) {                               
        free(passenger_array[i].flight_id);
        free(passenger_array[i].user_id);
    }
    free(passenger_array);
}


void free_reservation(Reservation *reservation_array, int num_linhas) { 
    for (int i = 0; i < num_linhas; i++) {                                  
        free(reservation_array[i].id);
        free(reservation_array[i].user_id);
        free(reservation_array[i].hotel_id);
        free(reservation_array[i].hotel_name);
        free(reservation_array[i].hotel_stars);
        free(reservation_array[i].city_tax);
        free(reservation_array[i].address);
        free(reservation_array[i].begin_date);
        free(reservation_array[i].end_date);
        free(reservation_array[i].price_per_night);
        free(reservation_array[i].includes_breakfast);
        free(reservation_array[i].room_details);
        free(reservation_array[i].rating);
        free(reservation_array[i].comment);
    }
    free(reservation_array);
}

void free_user(User *user_array, int num_linhas) {  
    for (int i = 0; i < num_linhas; i++) {               
        free(user_array[i].id);
        free(user_array[i].name);
        free(user_array[i].email);
        free(user_array[i].phone_number);
        free(user_array[i].birth_date);
        free(user_array[i].sex);
        free(user_array[i].passport);
        free(user_array[i].country_code);
        free(user_array[i].address);
        free(user_array[i].account_creation);
        free(user_array[i].pay_method);
        free(user_array[i].account_status);
    }
    free(user_array);
}


void free_contador(Contador_id *contador_array, int num_linhas_contador) {
    for (int i = 0; i < num_linhas_contador; i++) {                         
        free(contador_array[i].id_flight);
    }
    free(contador_array);
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

void validate_passenger(Passenger *nova, char parametros[][FIELD_SIZE], int flight_validation){
    int wanted_flight_id_validation = 0, wanted_user_id_validation = 0;
    if (flight_validation==0){
        if (check_length(parametros[0])==1){
            for (int k=0; k<num_linhas[1]; k++){   //procura esse id de voo no array que tem os voos guardados
                if (strcmp(parametros[0], flight_array[k].id)==0){
                    if (flight_array[k].validation == 1) wanted_flight_id_validation = 1; //o id desse voo é válido
                    break;
                }
            }
        }
    }
    if (flight_validation==1) wanted_flight_id_validation = 1;
    if (wanted_flight_id_validation==1 && check_length(parametros[1])==1){
        for (int l=0; l<num_linhas[3]; l++){   //procura esse id de utilizador no array que tem os utilizadores guardados
            if (strcmp(parametros[1], user_array[l].id)==0){
                if (user_array[l].validation == 1) wanted_user_id_validation = 1; //o id desse utilizador é válido
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
    nova->account_status = strdup(parametros[11]);
}


void validate_reservation(Reservation *nova, char parametros[][FIELD_SIZE]){
    int validation = check_length(parametros[0]) && check_length(parametros[1]) && check_length(parametros[2]) && check_length(parametros[3]) &&
                 verify_hotel_stars(parametros[4]) && check_length (parametros[5]) && verify_city_tax(parametros[5]) && check_length(parametros[6]) &&
                 check_date(parametros[7]) && check_date(parametros[8]) && check_length (parametros[9]) && check_price_per_night(parametros[9]) && 
                 check_length (parametros[10]) && verify_breakfast(parametros[10]) && check_length(parametros[11]) && check_length (parametros[12]) &&
                 check_reserva_rating(parametros[12]) && compare_date_time(parametros[7], parametros[8]);
    nova->validation = validation;
    nova->includes_breakfast = strdup(parametros[10]);
}

void free_all(){
    free_passenger(passenger_array, num_linhas[0]); 
    free_flight(flight_array, num_linhas[1]);            
    free_reservation(reservation_array, num_linhas[2]); 
    free_user(user_array, num_linhas[3]); 
    free_contador(contador_array, num_linhas_contador);
}


void open_files(){
    char *line = NULL;
    size_t len = 0;
    int j = 0;
    for (int num_ficheiro = 0; num_ficheiro<4; num_ficheiro++){         //existe um caso específico para cada ficheiro     
        int l = 0;
        switch (num_ficheiro){
            case 3:                                                      //ficheiro dos passageiros
                    arquivo = fopen("../trabalho-pratico/dataset/data/passengers.csv", "r");
                    if (arquivo == NULL) {
                        perror("Error\n");
                        return;
                    }
                    while (getline(&line, &len, arquivo) != -1) {
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
                            if (num_linhas[0] == 0) validate_passenger(&nova, parametros, 0);
                            else{
                                if (strcmp(nova.flight_id, passenger_array[num_linhas[0]-1].flight_id)==0){
                                    if (passenger_array[num_linhas[0]-1].validation_flight==1) validate_passenger(&nova, parametros, 1);
                                    else {
                                        nova.validation = 0;
                                        nova.validation_flight = 0;
                                    }
                                }
                                else validate_passenger(&nova, parametros, 0);
                            }

                            if (nova.validation==1){
                                if (num_linhas[0]==0){ // Se for a primeira iteração, apenas adicione o novo elemento ao contador_array
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
                            }
                            passenger_array = realloc(passenger_array, (num_linhas[0]+1)*sizeof(Passenger));
                            passenger_array[num_linhas[0]] = nova;
                            num_linhas[0]++;

                        } else {
                            l++;
                        }
                    }
                    fclose(arquivo);
                    break;
            case 1:                                                         //ficheiro dos voos
                arquivo = fopen("../trabalho-pratico/dataset/data/flights.csv", "r");
                if (arquivo == NULL) {
                    perror("Error\n");
                    return;
                }
                while (getline(&line, &len, arquivo) != -1) {               //o programa vai ler linha a linha do ficheiro aberto
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
                        flight_array = realloc(flight_array, (num_linhas[1]+1)*sizeof(Flight));   
                        flight_array[num_linhas[1]] = nova;        //esse novo elemento é adicionado ao array existente
                        num_linhas[1]++;

                    } else {
                        l++;
                    }
                }
    
                fclose(arquivo);
                break;

            case 2:                                                       //ficheiro das reservas
                arquivo = fopen("../trabalho-pratico/dataset/data/reservations.csv", "r");
                if (arquivo == NULL) {
                    perror("Error\n");
                    return;
                }
                while (getline(&line, &len, arquivo) != -1) {
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
                        reservation_array = realloc(reservation_array, (num_linhas[2]+1)*sizeof(Reservation));
                        reservation_array[num_linhas[2]] = nova;
                        num_linhas[2]++;
                    } else {
                        l++;
                    }
                }
                fclose(arquivo);
                break;

            case 0:                                                 //ficheiro dos utilizadores
                arquivo = fopen("../trabalho-pratico/dataset/data/users.csv", "r");
                if (arquivo == NULL) {
                    perror("Error\n");
                    return;
                }
                while (getline(&line, &len, arquivo) != -1) {
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
                        user_array = realloc(user_array, (num_linhas[3]+1)*sizeof(User));
                        user_array[num_linhas[3]] = nova;
                        num_linhas[3]++;
                    } else {
                        l++;
                    }
                }
                fclose(arquivo); 
                break;           
        }
    }
    free(line);
    
 
}


void create_files() {
    arquivo = fopen("../trabalho-pratico/Resultados/passengers_errors.csv", "w");
    char *passengers_first_line = "flight_id;user_id";
    fprintf(arquivo, "%s\n", passengers_first_line);
    for (int i = 0; i < num_linhas[0]; i++) {
        if (passenger_array[i].validation == 0) fprintf(arquivo, "%s;%s\n",passenger_array[i].flight_id, passenger_array[i].user_id);
    }
    fclose(arquivo);

    arquivo = fopen("../trabalho-pratico/Resultados/flights_errors.csv", "w");
    char *flights_first_line = "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes";
    fprintf(arquivo, "%s\n", flights_first_line);
    for (int i = 0; i < num_linhas[1]; i++) {
        if (flight_array[i].validation == 0) fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",flight_array[i].id,flight_array[i].airline,flight_array[i].plane_model,flight_array[i].total_seats,flight_array[i].origin,flight_array[i].destination,flight_array[i].schedule_departure_date,flight_array[i].schedule_arrival_date,flight_array[i].real_departure_date,flight_array[i].real_arrival_date,flight_array[i].pilot,flight_array[i].copilot, flight_array[i].notes);
    }
    fclose(arquivo);
    
    arquivo = fopen("../trabalho-pratico/Resultados/reservations_errors.csv", "w");
    char *reservation_first_line = "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment";
    fprintf(arquivo, "%s\n", reservation_first_line);
    for (int i = 0; i < num_linhas[2]; i++) {
        if (strcmp(reservation_array[i].includes_breakfast, " ") == 0) {
            if (reservation_array[i].validation == 0) fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",reservation_array[i].id,reservation_array[i].user_id,reservation_array[i].hotel_id,reservation_array[i].hotel_name,reservation_array[i].hotel_stars,reservation_array[i].city_tax,reservation_array[i].address,reservation_array[i].begin_date,reservation_array[i].end_date,reservation_array[i].price_per_night,reservation_array[i].room_details,reservation_array[i].rating,reservation_array[i].comment);
        }
        else {
            if (reservation_array[i].validation == 0) fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",reservation_array[i].id,reservation_array[i].user_id,reservation_array[i].hotel_id,reservation_array[i].hotel_name,reservation_array[i].hotel_stars,reservation_array[i].city_tax,reservation_array[i].address,reservation_array[i].begin_date,reservation_array[i].end_date,reservation_array[i].price_per_night,reservation_array[i].includes_breakfast,reservation_array[i].room_details,reservation_array[i].rating,reservation_array[i].comment);
        }
    }
    fclose(arquivo);

    arquivo = fopen("../trabalho-pratico/Resultados/users_errors.csv", "w");
    char *users_first_line = "id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status";
    fprintf(arquivo, "%s\n", users_first_line);
    for (int i = 0; i < num_linhas[3]; i++) {
        if (user_array[i].validation == 0) fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",user_array[i].id,user_array[i].name,user_array[i].email,user_array[i].phone_number,user_array[i].birth_date,user_array[i].sex,user_array[i].passport,user_array[i].country_code,user_array[i].address,user_array[i].account_creation,user_array[i].pay_method,user_array[i].account_status);
    }
    fclose(arquivo);
}