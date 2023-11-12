#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/Data_Types_&_Data_Structures.h"
#include "../include/Parser.h"
#include "../include/Validation.h"
#include "../include/Queries.h"

FILE *input;  //ficheiro dos comandos das queries
FILE *output;

int delay(char *schedule, char *real){ //2021/07/01 05:56:50  !!!!  2021/07/01 06:56:50
    int atraso = 0, verdadeira = 0, prevista = 0;
    verdadeira = (real[11]-'0')*36000 + (real[12]-'0')*3600 + (real[14]-'0')*600 + (real[15]-'0')*60 + (real[17]-'0')*10 + (real[18]-'0');
    prevista = (schedule[11]-'0')*36000 + (schedule[12]-'0')*3600 + (schedule[14]-'0')*600 + (schedule[15]-'0')*60 + (schedule[17]-'0')*10 + (schedule[18]-'0');
    atraso = verdadeira-prevista;
    return atraso;
}

int nights(char *begin, char *end){  //2021/07/01   !!!!!   2021/07/03
    int noites = 0, inicio = 0, fim = 0;
    inicio = (begin[8]-'0')*10 + (begin[9]-'0');
    fim = (end[8]-'0')*10 + (end[9]-'0');
    noites = fim-inicio;
    return noites;
}

double total_price(char *price_per_night, int nights, char *city_tax){
    double price = 0;
    price = (double)(atof(price_per_night)*nights) + ((double)(atof(price_per_night)*nights*atof(city_tax)) / 100) ;
    return price;
}

int age_user(char *birth_date){  //1979/11/27
    int ano = 0, mes = 0, dia = 0, age = 0;
    ano = (birth_date[0]-'0')*1000 + (birth_date[1]-'0')*100 + (birth_date[2]-'0')*10 + (birth_date[3]-'0');
    mes = (birth_date[5]-'0')*10 + (birth_date[6]-'0');
    dia = (birth_date[8]-'0')*10 + (birth_date[9]-'0');
    age = (2023-ano);
    if (10 < mes || (10 == mes && 1 < dia)) age--;
    return age;
}

int number_of_flights(char *user){
    int flights = 0;
    for (int l = 0; l<num_linhas[0]; l++){   //procura o id do utilizador no array dos passageiros para ver em quantos voos ele andou 
        if (strcmp(user, passenger_array[l].user_id)==0) flights++;
    }
    return flights;
}

void free_flight_id_passenger(Flight_id_passenger *flight_id_passenger_array, int num_flights_passenger_id){
    for (int i = 0; i<num_flights_passenger_id; i++){
        free(flight_id_passenger_array[i].flight_id);
    }
    free(flight_id_passenger_array);
}

void free_flight_aux(Flight_aux *flight_aux_array, int num_flights_passenger_id){
    for (int i = 0; i<num_flights_passenger_id; i++){
        free(flight_aux_array[i].flight_id);
        free(flight_aux_array[i].schedule_departure_date);
        free(flight_aux_array[i].type);
    }
    free(flight_aux_array);
}

void free_reservation_aux(Reservation_aux *reservation_aux_array, int num_reservations){
    for (int i = 0; i<num_reservations; i++){
        free(reservation_aux_array[i].reservation_id);
        free(reservation_aux_array[i].begin_date);
        free(reservation_aux_array[i].type);
    }
    free(reservation_aux_array);
}

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

char *only_date(char *schedule_departure_date){  //2023/02/10 03:24:09
    char *date = (char*)malloc(11 * sizeof(char));
    strncpy(date, schedule_departure_date, 10);
    date[10] = '\0'; 
    return date;
}

void insertionSort_flights(Flight_aux *flight_aux_array, int size){
    for (int i = 1; i < size; i++) {
        Flight_aux key = flight_aux_array[i];
        int j = i - 1;
        while (j >= 0 && compare_date_time(flight_aux_array[j].schedule_departure_date, key.schedule_departure_date)==1) {
            flight_aux_array[j + 1] = flight_aux_array[j];
            j--;
        }  
        flight_aux_array[j + 1] = key;
    }
}

void insertionSort_reservations(Reservation_aux *reservation_aux_array, int size){
    for (int i = 1; i < size; i++) {
        Reservation_aux key = reservation_aux_array[i];
        int j = i - 1;
        while (j >= 0 && compare_date_time(reservation_aux_array[j].begin_date, key.begin_date)==1) {
            reservation_aux_array[j + 1] = reservation_aux_array[j];
            j--;
        }  
        reservation_aux_array[j + 1] = key;
    }
}

void query1(char *line, int i, int n){
    int wanted_id = -1, index_line = i, wanted_user_id = -1, wanted_id_2 = -1;
    char *breakfast;
    char *status;
    
    for (; line[index_line]==' ' || line[index_line]=='"'; index_line++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j=index_line; line[j]!='\0' && line[j]!='\n' && line[j]!='"'; j++, argument_length++);  //conta o tamanho do argumento
    char argument[argument_length];
    for (int k=0, j=index_line; k<argument_length; k++, j++) argument[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    argument[argument_length] = '\0';

    int filename_size = strlen("../trabalho-pratico/Resultados/command1_output.txt");  //calcula o tamanho do nome do ficheiro
    if (n>=10 && n<100) filename_size++;
    else if (n>=100) filename_size+= 2;
    char *filename = (char *)malloc(filename_size + 1); //aloca memória dinamicamente para o nome do ficheiro
    snprintf(filename, filename_size + 1, "../trabalho-pratico/Resultados/command%d_output.txt", n);  //formata o nome do arquivo
    output = fopen(filename, "w");

    if (isdigit(line[index_line])){   //irá listar o resumo de um voo
        wanted_id = -1;
        for (int k=0; k<num_linhas[1]; k++){   //procura esse id de voo no array que tem os voos guardados
            if (strcmp(argument, flight_array[k].id)==0){
                wanted_id = k;  //encontrou o id desse voo
                break;
            }
        }
        if (wanted_id == -1);//não encontrou o id desse voo por isso tem de criar um ficheiro vazio 
        else {   //esse id de voo existe
            if (flight_array[wanted_id].validation==0); //esse voo é inválido por isso tem de criar um ficheiro vazio 
            else{
                for (int l = 0; l < num_linhas_contador; l++) {
                    if (strcmp(argument, contador_array[l].id_flight) == 0) {
                        wanted_id_2 = l;
                        break;
                    }
                }
                if (index_line==2){   //1
                  fprintf(output, "%s;%s;%s;%s;%s;%s;%d;%d\n", flight_array[wanted_id].airline, flight_array[wanted_id].plane_model, flight_array[wanted_id].origin, flight_array[wanted_id].destination, flight_array[wanted_id].schedule_departure_date, flight_array[wanted_id].schedule_arrival_date, contador_array[wanted_id_2].contador, delay(flight_array[wanted_id].schedule_departure_date, flight_array[wanted_id].real_departure_date));
                }
                else{   //1F
                    fprintf(output, "--- 1 ---\n");
                    fprintf(output, "airline: %s\n", flight_array[wanted_id].airline);
                    fprintf(output, "plane_model: %s\n", flight_array[wanted_id].plane_model);
                    fprintf(output, "origin: %s\n", flight_array[wanted_id].origin);
                    fprintf(output, "destination: %s\n", flight_array[wanted_id].destination);
                    fprintf(output, "schedule_departure_date: %s\n", flight_array[wanted_id].schedule_departure_date);
                    fprintf(output, "schedule_arrival_date: %s\n", flight_array[wanted_id].schedule_arrival_date);
                    fprintf(output, "passengers: %d\n", contador_array[wanted_id_2].contador);
                    fprintf(output, "delay: %d\n", delay(flight_array[wanted_id].schedule_departure_date, flight_array[wanted_id].real_departure_date));
                }
            }
        }
    }
    
    else if (line[index_line]=='B' && line[index_line+1]=='o' && line[index_line+2]=='o' && line[index_line+3]=='k'){  //irá listar o resumo de uma reserva
        wanted_id = -1;
        for (int k=0; k<num_linhas[2]; k++){   //procura esse id da reserva no array que tem as reservas guardados
            if (strcmp(argument, reservation_array[k].id)==0){
                wanted_id = k;  //encontrou o id dessa reserva
                break;
            }
        }
        if (wanted_id == -1);//não encontrou o id dessa reserva por isso tem de criar um ficheiro vazio 
        else {   //esse id de voo existe
            if (reservation_array[wanted_id].validation==0); //essa reserva é inválida por isso tem de criar um ficheiro vazio 
            else{
                for (int k = 0; k<num_linhas[3]; k++){   //procura o id do utilizador que fez essa reserva para ver qual o seu account status
                    if (strcmp(reservation_array[wanted_id].user_id, user_array[k].id)==0){
                        wanted_user_id = k;  //encontrou o id desse utilizador
                        break;
                    }
                }
                if (verify_account_status(user_array[wanted_user_id].account_status) == 2); //não imprime nada caso a conta do utilizador esteja inativa
                else{
                    if (verify_breakfast(reservation_array[wanted_id].includes_breakfast) == 1) breakfast = strdup("True");
                    else  breakfast = strdup("False");
                    if (index_line==2){   //1
                        fprintf(output, "%s;%s;%s;%s;%s;%s;%d;%.3f\n", reservation_array[wanted_id].hotel_id, reservation_array[wanted_id].hotel_name, reservation_array[wanted_id].hotel_stars, reservation_array[wanted_id].begin_date, reservation_array[wanted_id].end_date, breakfast, nights(reservation_array[wanted_id].begin_date,reservation_array[wanted_id].end_date), total_price(reservation_array[wanted_id].price_per_night, nights(reservation_array[wanted_id].begin_date,reservation_array[wanted_id].end_date), reservation_array[wanted_id].city_tax));
                    }
                    else{   //1F
                        fprintf(output, "--- 1 ---\n");
                        fprintf(output, "hotel_id: %s\n", reservation_array[wanted_id].hotel_id);
                        fprintf(output, "hotel_name: %s\n", reservation_array[wanted_id].hotel_name);
                        fprintf(output, "hotel_stars: %s\n", reservation_array[wanted_id].hotel_stars);
                        fprintf(output, "begin_date: %s\n", reservation_array[wanted_id].begin_date);
                        fprintf(output, "end_date: %s\n", reservation_array[wanted_id].end_date);
                        fprintf(output, "includes_breakfast: %s\n", breakfast);
                        fprintf(output, "nights: %d\n", nights(reservation_array[wanted_id].begin_date,reservation_array[wanted_id].end_date));
                        fprintf(output, "total_price: %.3f\n", total_price(reservation_array[wanted_id].price_per_night, nights(reservation_array[wanted_id].begin_date,reservation_array[wanted_id].end_date), reservation_array[wanted_id].city_tax));
                    }
                    free(breakfast);
                }
            }
        }
    }
    else{  //irá listar o resumo de um utilizador
        wanted_id = -1;
        for (int k=0; k<num_linhas[3]; k++){   //procura esse id do utilizador no array que tem os utilizadores guardados
            if (strcmp(argument, user_array[k].id)==0){
                wanted_id = k;  //encontrou o id desse utilizador
                break;
            }
        }
        if (wanted_id == -1);//não encontrou o id desse utilizador por isso tem de criar um ficheiro vazio  
        else{
            if (user_array[wanted_id].validation==0); //esse utilizador é inválido por isso tem de criar um ficheiro vazio 
            else{
                status = strdup(user_array[wanted_id].account_status);
                toLowerCase(status);
                if (verify_account_status(status) == 2);   //não imprime nada caso a conta do utilizador esteja inativa
                else{
                    int /*flights = 0,*/ reservations = 0;
                    double total_spent = 0;/*
                    for (int l = 0; l<num_linhas[0]; l++){   //procura o id do utilizador no array dos passageiros para ver em quantos voos ele andou 
                        if (strcmp(user_array[wanted_id].id, passenger_array[l].user_id)==0) flights++;
                    }*/
                    for (int k = 0; k<num_linhas[2]; k++){   //procura o id do utilizador no array das reservas para ver quantas reservas ele fez 
                        if (strcmp(user_array[wanted_id].id, reservation_array[k].user_id)==0){
                            reservations++;
                            total_spent += total_price(reservation_array[k].price_per_night, nights(reservation_array[k].begin_date,reservation_array[k].end_date), reservation_array[k].city_tax);
                        }
                    }
                    if (index_line==2){   //1
                        fprintf(output, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", user_array[wanted_id].name, user_array[wanted_id].sex, age_user(user_array[wanted_id].birth_date),user_array[wanted_id].country_code, user_array[wanted_id].passport, number_of_flights(user_array[wanted_id].id), reservations, total_spent);
                    }
                    else{   //1F
                        fprintf(output, "--- 1 ---\n");
                        fprintf(output, "name: %s\n", user_array[wanted_id].name);
                        fprintf(output, "sex: %s\n", user_array[wanted_id].sex);
                        fprintf(output, "age: %d\n", age_user(user_array[wanted_id].birth_date));
                        fprintf(output, "country_code: %s\n", user_array[wanted_id].country_code);
                        fprintf(output, "passport: %s\n", user_array[wanted_id].passport);
                        fprintf(output, "number_of_flights: %d\n", number_of_flights(user_array[wanted_id].id));
                        fprintf(output, "number_of_reservations: %d\n", reservations);
                        fprintf(output, "total_spent: %.3f\n", total_spent);
                    }
                }
                free(status);
            }
        }  
    }
    fclose(output);
    free(filename);
}

void query2(char *line, int i, int n){
    int wanted_user_id = -1, index_line = i, exists_argument2 = 0;
    char *status;
  //  const char* type_f = "flight";
  //  const char* type_r = "reservation";
    
    for (; line[index_line]==' ' || line[index_line]=='"'; index_line++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument1_length = 0;
    int argument2_length = 0;
    for (int j=index_line; line[j]!='\0' && line[j]!='\n' && line[j]!=' '; j++, argument1_length++);  //conta o tamanho do argumento
    char argument1[argument1_length];
    for (int k=0, j=index_line; k<argument1_length; k++, j++) argument1[k] = line[j];   //copia o argumento da query para um array que guarda esse argumento
    argument1[argument1_length] = '\0';
    int index2_line = index_line;
    for (; line[index2_line + argument1_length] == ' '; index2_line++);  //vai econtrar o id do segundo argumento caso exista
    char *argument2 = strdup("");
    if (line[index2_line + argument1_length] != '\0' && line[index2_line + argument1_length] != '\n') {   //existe segundo argumento para ler
        for (int j = index2_line + argument1_length; line[j] != '\0' && line[j] != '\n' && line[j] != ' '; j++, argument2_length++);  //calcula o tamanho do segundo argumento
        char argument2_aux[argument2_length];
        for (int k = 0, j = index2_line + argument1_length; k < argument2_length; k++, j++) argument2_aux[k] = line[j];  //copia o segundo argumento
        argument2_aux[argument2_length] = '\0';
        free(argument2);
        argument2 = strdup(argument2_aux);
        exists_argument2 = 1;
    }
  //  printf("%s;%s\n", argument1, argument2);

    int filename_size = strlen("../trabalho-pratico/Resultados/command1_output.txt");  //calcula o tamanho do nome do ficheiro
    if (n>=10 && n<100) filename_size++;
    else if (n>=100) filename_size+=2;
    char *filename = (char *)malloc(filename_size + 1); //aloca memória dinamicamente para o nome do ficheiro
    snprintf(filename, filename_size + 1, "../trabalho-pratico/Resultados/command%d_output.txt", n);  //formata o nome do arquivo
    output = fopen(filename, "w");

    for (int i = 0; i<num_linhas[3]; i++){     //vai procurar o id do utilizador
        if (strcmp(argument1, user_array[i].id)==0){   //se encontrar o id desse utilizador
            wanted_user_id = i;
            break;
        }
    }
    if (wanted_user_id!=-1){   //caso o utilizador exista
        if (user_array[wanted_user_id].validation==1){  //só vai buscar parâmetros caso essa linha do utilizador seja válida
            status = strdup(user_array[wanted_user_id].account_status);
            toLowerCase(status);
            if (verify_account_status(status) == 1){   //apenas imprime caso a conta do utilizador esteja ativa
                int num_flights_passenger_id = 0, num_reservations = 0;
                Flight_id_passenger *flight_id_passenger_array = NULL;      //será um array para armazenar os id's de todos os voos em que o utilizador já voou
                Flight_aux *flight_aux_array = NULL; //será um array para armazenar a data esperada de partida e o id do voo em que o utilizador voou
                Reservation_aux *reservation_aux_array = NULL; //será um array para armazenar a data da reserva e o id da reserva que o utilizador fez
                if (strcmp(argument2, "reservations")!=0){
                    for (int i = 0; i<num_linhas[0]; i++){   //procura o id desse utilizador no array dos passageiros para saber qual o seu voo
                        if (strcmp(argument1, passenger_array[i].user_id)==0 && passenger_array[i].validation==1){   //se econtrar o id do utilizador no ficheiro dos passageiros e essa linha for válida
                            Flight_id_passenger novo = create_flight_id(passenger_array[i].flight_id);    //é criado um novo elemento do array com o parâmetro lido
                            flight_id_passenger_array = realloc(flight_id_passenger_array, (num_flights_passenger_id+1)*sizeof(Flight_id_passenger)); 
                            flight_id_passenger_array[num_flights_passenger_id] = novo;        //esse novo elemento é adicionado ao array existente
                            num_flights_passenger_id++;
                        }
                    }
                    if (num_flights_passenger_id!=0){  //se encontrou voos em que o utilizador voou
                        for (int i = 0, j = 0; i<num_linhas[1] && j<num_flights_passenger_id; i++){   //procura esses id's de voos no ficheiro dos voos
                            if (strcmp(flight_array[i].id, flight_id_passenger_array[j].flight_id)==0){   //encontrou o id de voo
                                char* departure_date = only_date(flight_array[i].schedule_departure_date);
                                Flight_aux novo;
                                if (exists_argument2==0) novo = create_flight_aux(flight_array[i].id, departure_date, 0);
                                else novo = create_flight_aux(flight_array[i].id, departure_date, 1);
                                flight_aux_array = realloc(flight_aux_array, (j+1)*sizeof(Flight_aux));
                                flight_aux_array[j] = novo;
                                j++;
                                free(departure_date);
                            }
                        }
                        insertionSort_flights(flight_aux_array, num_flights_passenger_id);
                    }
                }
                if (strcmp(argument2, "flights")!=0){    //só lista as reservas que um utilizador fez caso o segundo argumento não exista ou seja diferente de "flights"
               //     printf("reservation\n");
                    for (int i = 0; i<num_linhas[2]; i++){   //procura o id desse utilizador no array das reservas para saber qual a sua reserva
                        if (strcmp(argument1, reservation_array[i].user_id)==0 && reservation_array[i].validation==1){   //se econtrar o id do utilizador no ficheiro das reservas e essa linha for válida
                            Reservation_aux novo;
                            if (exists_argument2==0) novo = create_reservation_aux(reservation_array[i].id, reservation_array[i].begin_date, 0);
                            else novo = create_reservation_aux(reservation_array[i].id, reservation_array[i].begin_date, 1);
                            reservation_aux_array = realloc(reservation_aux_array, (num_reservations+1)*sizeof(Reservation_aux));
                            reservation_aux_array[num_reservations] = novo;
                            num_reservations++; 
                        }
                    }
                    insertionSort_reservations(reservation_aux_array, num_reservations);
                }  
                if (index_line==2){ //2
                    if (strcmp(argument2, "flights")==0){  //só lista os voos
                        for (int i = 0; i<num_flights_passenger_id; i++){
                            fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
                        }
                    }
                    else if(strcmp(argument2, "reservations")==0){  //só lista as reservas
                        //    printf("%d\n", num_reservations);
                            for (int i = 0; i<num_reservations; i++){
                                fprintf(output, "%s;%s%s\n", reservation_aux_array[i].reservation_id, reservation_aux_array[i].begin_date, reservation_aux_array[i].type);
                            }
                        }
                        else{
                            for (int i = 0, j = 0; i<num_flights_passenger_id || j<num_reservations;){
                                if(i==num_flights_passenger_id){   //já só há informações de reservas para serem impressas
                                    fprintf(output, "%s;%s%s\n", reservation_aux_array[j].reservation_id, reservation_aux_array[j].begin_date, reservation_aux_array[j].type);
                                    j++;
                                }
                                else if (j==num_reservations){   //já só há informações de voos para serem impressas
                                    fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
                                    i++;
                                }
                                    else{
                                        if (strcmp(flight_aux_array[i].schedule_departure_date, reservation_aux_array[j].begin_date)==0){
                                            fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
                                            i++;
                                            fprintf(output, "%s;%s%s\n", reservation_aux_array[j].reservation_id, reservation_aux_array[j].begin_date, reservation_aux_array[j].type);
                                            j++;
                                        }
                                        else if (compare_date_time(flight_aux_array[i].schedule_departure_date, reservation_aux_array[j].begin_date)==0){
                                            fprintf(output, "%s;%s%s\n", flight_aux_array[i].flight_id, flight_aux_array[i].schedule_departure_date, flight_aux_array[i].type);
                                            i++;
                                        }
                                            else if (compare_date_time(flight_aux_array[i].schedule_departure_date, reservation_aux_array[j].begin_date)==1){
                                                fprintf(output, "%s;%s%s\n", reservation_aux_array[j].reservation_id, reservation_aux_array[j].begin_date, reservation_aux_array[j].type);
                                                j++;
                                            }
                                    }
                            }
                        }
                }
                else{  //2F
                    if (strcmp(argument2, "flights")==0){  //só lista os voos
                        for (int i = 1; i<=num_flights_passenger_id; i++){
                            fprintf(output, "--- %d ---\n", i);
                            fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
                            fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
                            if (i!=num_flights_passenger_id) fprintf(output, "\n");
                        }
                    }
                    else if (strcmp(argument2, "reservations")==0){  //só lista as reservas
                        for (int i = 1; i<=num_reservations; i++){
                            fprintf(output, "--- %d ---\n", i);
                            fprintf(output, "id: %s\n", reservation_aux_array[i-1].reservation_id);
                            fprintf(output, "date: %s\n", reservation_aux_array[i-1].begin_date);
                            if (i!=num_reservations) fprintf(output, "\n");
                        }
                    }
                    else{  //lista voos e reservas
                        for (int i = 1, j = 1; i<=num_flights_passenger_id || j<=num_reservations;){
                            fprintf(output, "--- %d ---\n", (i+j-1));
                            if(i==num_flights_passenger_id+1){   //já só há informações de reservas para serem impressas
                                    fprintf(output, "id: %s\n", reservation_aux_array[j-1].reservation_id);
                                    fprintf(output, "date: %s\n", reservation_aux_array[j-1].begin_date);
                                    fprintf(output, "type: reservation\n");
                                    if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                                    j++;
                            }
                            else if (j==num_reservations+1){   //já só há informações de voos para serem impressas
                                    fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
                                    fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
                                    fprintf(output, "type: flight\n");
                                    if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                                    i++;
                            }
                            else if (strcmp(flight_aux_array[i-1].schedule_departure_date, reservation_aux_array[j-1].begin_date)==0){
                                fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
                                fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
                                fprintf(output, "type: flight\n");
                                i++;
                                fprintf(output, "\n");
                                fprintf(output, "--- %d ---\n", (i+j-1));
                                fprintf(output, "id: %s\n", reservation_aux_array[j-1].reservation_id);
                                fprintf(output, "date: %s\n", reservation_aux_array[j-1].begin_date);
                                fprintf(output, "type: reservation\n");
                                if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                                j++;
                            }
                            else if (compare_date_time(flight_aux_array[i-1].schedule_departure_date, reservation_aux_array[j-1].begin_date)==0){
                                //fprintf(output, "--- %d -ok--\n", (i+j-1));
                                fprintf(output, "id: %s\n", flight_aux_array[i-1].flight_id);
                                fprintf(output, "date: %s\n", flight_aux_array[i-1].schedule_departure_date);
                                fprintf(output, "type: flight\n");
                                if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                                i++;
                            }
                            else if (compare_date_time(flight_aux_array[i-1].schedule_departure_date, reservation_aux_array[j-1].begin_date)==1){
                                fprintf(output, "--- %d ---\n", (i+j-1));        //////////////////////////////////////////////////////////////////////////////////////////
                                fprintf(output, "id: %s\n", reservation_aux_array[j-1].reservation_id);
                                fprintf(output, "date: %s\n", reservation_aux_array[j-1].begin_date);
                                fprintf(output, "type: reservation\n");
                                if((i+j-1)!=(num_flights_passenger_id+num_reservations)) fprintf(output, "\n");
                                j++;
                            }
                        }
                    }
                }
                free_flight_id_passenger(flight_id_passenger_array, num_flights_passenger_id);
                free_flight_aux(flight_aux_array, num_flights_passenger_id);
                free_reservation_aux(reservation_aux_array, num_reservations);
            }
            free(status);
        }
    }
    fclose(output);
    free(filename);
    free(argument2);
}

void query3(char *line, int i, int n) {
    double rating = 0, rating_t = 0, total = 0, media = 0;

    int flag;
    if (i == 2) flag = 1;
    else flag = 0;

    int filename_size = strlen("../trabalho-pratico/Resultados/command1_output.txt");  //calcula o tamanho do nome do ficheiro
    if (n>=10 && n<100) filename_size++;
    else if (n>=100) filename_size+=2;
    char *filename = (char *)malloc(filename_size + 1); //aloca memória dinamicamente para o nome do ficheiro
    snprintf(filename, filename_size + 1, "../trabalho-pratico/Resultados/command%d_output.txt", n);  //formata o nome do arquivo
    output = fopen(filename, "w");

    if (output == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        free(filename);
        return;
    }

    int index_line = i;
    for (; line[index_line]== ' ' || line[index_line] == '"'; index_line++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j = index_line; line[j] != '\0' && line[j] != '\n'; j++, argument_length++);  //conta o tamanho do argumento
    char argument[argument_length];
    for (int k = 0, j = index_line; k < argument_length; k++, j++) argument[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    argument[argument_length] = '\0';

    int check = check_length(argument);
    if (check == 1) {
        for (i = 0; i < num_linhas[2]; i++) {
            if ((strcmp(reservation_array[i].hotel_id, argument) == 0) && reservation_array[i].validation == 1) {
                rating = (double) atof(reservation_array[i].rating);
                rating_t += (double) rating;
                total = (double) total + 1;
            }
        }

        if (total != 0) {
            media = (double) (rating_t / total);

            if (flag == 0)   //3
                fprintf(output, "%.3f\n", media);
            else {   //3F
                fprintf(output, "--- 1 ---\n");
                fprintf(output, "rating: %.3f\n", media);
            }
        }
    }

    fclose(output);
    free(filename);
}

void identify_query(){
    char *line = NULL;
    size_t len = 0;
    int n = 0;
    input = fopen("../trabalho-pratico/dataset/input.txt", "r");
    if (input == NULL) {
        perror("Error\n");
        return;
    }
    while (getline(&line, &len, input) != -1) {
        int i = 0;
        n++;
        for (; line[i]!=' '; i++);
        if (i==3) continue;//10F
            else {
                switch (line[0]){
                    case '1':  //1 ou 1F ou 10
                        if (line[1]=='0') continue;//10
                        else query1(line, i, n);//1 ou 1F 
                    break;
                    case '2':  //2 ou 2F
                        query2(line, i, n);
                    break;
                    case '3':  //3 ou 3F
                        query3(line, i, n);
                    break;
                    case '4':  //4 ou 4F

                    break;
                    case '5':  //5 ou 5F

                    break;
                    case '6':  //6 ou 6F

                    break;
                    case '7':  //7 ou 7F

                    break;
                    case '8':  //8 ou 8F

                    break;
                    case '9':  //9 ou 9F

                    break;
                }
            }
    }
    free(line);
}