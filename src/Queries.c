#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/Data_Types_&_Data_Structures.h"
#include "../include/Parser.h"
#include "../include/Validation.h"
#include "../include/Queries.h"
#include "../include/Output_queries.h"

FILE *input;  //ficheiro dos comandos das queries

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
    for (int l = 0; l<num_linhas_valid[0]; l++){   //procura o id do utilizador no array dos passageiros para ver em quantos voos ele andou 
        if (strcmp(user, passenger_array_valid[l].user_id)==0) flights++;
    }
    return flights;
}

int compare_hotels (const void *a, const void *b) {  // ordenar da data mais recente para a mais antiga, ou pelo id se as datas forem iguais
    char *beginA = ((hotel_aux *) a)->begin_date;
    char *beginB = ((hotel_aux *) b)->begin_date;
    if (strcmp (beginA, beginB) < 0) return 1;
    if (strcmp (beginA, beginB) > 0) return -1;
    char *idA = ((hotel_aux *) a)->id;
    char *idB = ((hotel_aux *) b)->id;
    if (strcmp (idA, idB) < 0) return -1;
    if (strcmp (idA, idB) > 0) return 1;
    return 0;
}

int is_date_between (char *date, char *i, char *f) {  // date é a que queremos verificar, i é a data inicial e f a data final
    if (strcmp (date, i) < 0) return 0;  // date é menor que i, logo não está entre as datas
    if (strcmp (date, f) > 0) return 0;  // date é maior que f, não está entre as datas
    return 1;  // date está entre i e f
}

int compare_flights (const void *a, const void *b) {  // ordenar da data mais antiga para a mais recente, ou pelo id se as datas forem iguais
    char *beginA = ((flight_date_aux *) a)->schedule_departure_date;
    char *beginB = ((flight_date_aux *) b)->schedule_departure_date;
    if (strcmp (beginA, beginB) < 0) return 1;
    if (strcmp (beginA, beginB) > 0) return -1;
    char *idA = ((flight_date_aux *) a)->id;
    char *idB = ((flight_date_aux *) b)->id;
    if (strcmp (idA, idB) < 0) return -1;
    if (strcmp (idA, idB) > 0) return 1;
    return 0;
}

// Troca o conteudo de dois ints
void swap_contador(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Troca o conteúdo de duas strings
void swapStrings(char **str1, char **str2) {
    char *temp = strdup(*str1);
    free(*str1);
    *str1 = strdup(*str2);
    free(*str2);
    *str2 = strdup(temp);
    free(temp);
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

void free_PassengersXairport(PassengersXairport *passengersXairport_array, int num_linhas_PassengersXairport) {
    for (int i = 0; i < num_linhas_PassengersXairport; i++) {                         
        free(passengersXairport_array[i].origin);
    }
    free(passengersXairport_array);
}

void free_idXname(idXname *idXname_array, int num_linhas_idXname) {
    for (int i = 0; i < num_linhas_idXname; i++){
        free(idXname_array[i].id);
        free(idXname_array[i].name);

    }
    free(idXname_array);
}

void free_hotel_aux (hotel_aux *hotel_aux_array, int num_hotels){
    for (int i = 0; i<num_hotels; i++){
        free (hotel_aux_array[i].id);
        free (hotel_aux_array[i].begin_date);
        free (hotel_aux_array[i].end_date);
        free (hotel_aux_array[i].user_id);
        free (hotel_aux_array[i].rating);
    }
    free (hotel_aux_array);
}

void free_flight_date_aux (flight_date_aux *flight_date_aux_array, int num_flights){
    for (int i = 0; i<num_flights; i++){
        free (flight_date_aux_array[i].id);
        free (flight_date_aux_array[i].schedule_departure_date);
        free (flight_date_aux_array[i].destination);
        free (flight_date_aux_array[i].airline);
        free (flight_date_aux_array[i].plane_model);
    }
    free (flight_date_aux_array);
}

void free_Mediana(Mediana *mediana_array, int num_medianas){
    for (int i = 0; i<num_medianas; i++){
        free(mediana_array[i].airport);
    }
    free(mediana_array);
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

void insertionSort_medianas(Mediana *mediana_array, int num_medianas){
    for (int i = 1; i < num_medianas; i++) {
        Mediana key = mediana_array[i];
        int j = i - 1;
        while (j >= 0 && ((mediana_array[j].mediana<key.mediana) || (mediana_array[j].mediana==key.mediana && strcmp(mediana_array[j].airport, key.airport)>0))) {
            mediana_array[j + 1] = mediana_array[j];
            j--;
        }  
        mediana_array[j + 1] = key;
    }
}


int calculate_mediana(int *atrasos, int num_atrasos){
    if ((num_atrasos%2)==1) return atrasos[num_atrasos/2];
    else return ((atrasos[num_atrasos/2] + atrasos[(num_atrasos/2) - 1]) / 2);
}

void query1(char *line, int i, int n){
    int wanted_id = -1, index_line = i, wanted_user_id = -1, wanted_id_2 = -1, generated_file = 0;
    char *breakfast;
    char *status;
    
    for (; line[index_line]==' ' || line[index_line]=='"'; index_line++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j=index_line; line[j]!='\0' && line[j]!='\n' ; j++, argument_length++);  //conta o tamanho do argumento
    char argument[argument_length];
    for (int k=0, j=index_line; k<argument_length; k++, j++) argument[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    argument[argument_length] = '\0';

    if (isdigit(line[index_line])){   //irá listar o resumo de um voo
        wanted_id = -1;
        for (int k=0; k<num_linhas_invalid[1]; k++){   //procura esse id de voo no array que tem os voos inválidos guardados
            if (strcmp(argument, flight_array_invalid[k].id)==0){
                wanted_id = k;  //encontrou o id desse voo
                break;
            }
        }
        if (wanted_id != -1);//encontrou o id desse voo nos inválidos
        else {   //esse id de voo é válido
            for (int k=0; k<num_linhas_valid[1]; k++){   //procura esse id de voo no array que tem os voos válidos guardados
                if (strcmp(argument, flight_array_valid[k].id)==0){
                    wanted_id = k;  //encontrou o id desse voo
                    break;
                }
            }
            if (wanted_id != -1){
                for (int l = 0; l < num_linhas_contador; l++) {
                    if (strcmp(argument, contador_array[l].id_flight) == 0) {
                        wanted_id_2 = l;
                        break;
                    }
                }
                outputs_query1_flights(flight_array_valid, contador_array, wanted_id, wanted_id_2, index_line, n); ////voos
                generated_file = 1;
            }
        }
    }
    
    else if (line[index_line]=='B' && line[index_line+1]=='o' && line[index_line+2]=='o' && line[index_line+3]=='k'){  //irá listar o resumo de uma reserva
        wanted_id = -1;
        for (int k=0; k<num_linhas_invalid[2]; k++){   //procura esse id da reserva no array que tem as reservas inválidas guardadas
            if (strcmp(argument, reservation_array_invalid[k].id)==0){
                wanted_id = k;  //encontrou o id dessa reserva
                break;
            }
        }
        if (wanted_id != -1);//encontrou o id dessa reserva nas inválidas 
        else {   //esse id de reserva é válido
            for (int k=0; k<num_linhas_valid[2]; k++){   //procura esse id da reserva no array que tem as reservas válidas guardadas
                if (strcmp(argument, reservation_array_valid[k].id)==0){
                    wanted_id = k;  //encontrou o id dessa reserva
                    break;
                }
            }
            if (wanted_id != -1){
                for (int k = 0; k<num_linhas_valid[3]; k++){   //procura o id do utilizador que fez essa reserva para ver qual o seu account status
                    if (strcmp(reservation_array_valid[wanted_id].user_id, user_array_valid[k].id)==0){
                        wanted_user_id = k;  //encontrou o id desse utilizador
                        break;
                    }
                }
                if (verify_account_status(user_array_valid[wanted_user_id].account_status) == 2); //não imprime nada caso a conta do utilizador esteja inativa
                else{
                    if (verify_breakfast(reservation_array_valid[wanted_id].includes_breakfast) == 1) breakfast = strdup("True");
                    else  breakfast = strdup("False");
                    outputs_query1_reservations(reservation_array_valid, breakfast, wanted_id, index_line, n); //reservas
                    free(breakfast);
                    generated_file = 1;
                }
            }
        }
    }
    else{  //irá listar o resumo de um utilizador
        wanted_id = -1;
        for (int k=0; k<num_linhas_invalid[3]; k++){   //procura esse id do utilizador no array que tem os utilizadores inválidos guardados
            if (strcmp(argument, user_array_invalid[k].id)==0){
                wanted_id = k;  //encontrou o id desse utilizador
                break;
            }
        }
        if (wanted_id != -1);//encontrou o id desse utilizador nos inválidos  
        else{
            for (int k=0; k<num_linhas_valid[3]; k++){   //procura esse id do utilizador no array que tem os utilizadores válidos guardados
                if (strcmp(argument, user_array_valid[k].id)==0){
                    wanted_id = k;  //encontrou o id desse utilizador
                    break;
                }
            }
            if (wanted_id != -1){
                status = strdup(user_array_valid[wanted_id].account_status);
                toLowerCase(status);
                if (verify_account_status(status) == 2);   //não imprime nada caso a conta do utilizador esteja inativa
                else{
                    int /*flights = 0,*/ reservations = 0;
                    double total_spent = 0;/*
                    for (int l = 0; l<num_linhas[0]; l++){   //procura o id do utilizador no array dos passageiros para ver em quantos voos ele andou 
                        if (strcmp(user_array[wanted_id].id, passenger_array[l].user_id)==0) flights++;
                    }*/
                    for (int k = 0; k<num_linhas_valid[2]; k++){   //procura o id do utilizador no array das reservas para ver quantas reservas ele fez 
                        if (strcmp(user_array_valid[wanted_id].id, reservation_array_valid[k].user_id)==0){
                            reservations++;
                            total_spent += total_price(reservation_array_valid[k].price_per_night, nights(reservation_array_valid[k].begin_date,reservation_array_valid[k].end_date), reservation_array_valid[k].city_tax);
                        }
                    }
                    outputs_query1_users(user_array_valid, total_spent, reservations, wanted_id, index_line, n); //utilizadores
                    generated_file = 1;
                }
                free(status);
            }
        }  
    }
    if (generated_file==0) create_output(n, 0);
}

int compare_date_time2(char *i, char *f) {
    return strcmp(i, f);
}

void query2(char *line, int i, int n){
    int wanted_user_id = -1, index_line = i, exists_argument2 = 0, generated_file = 0;
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

    for (int i = 0; i<num_linhas_invalid[3]; i++){     //vai procurar o id do utilizador nos inválidos
        if (strcmp(argument1, user_array_invalid[i].id)==0){   //se encontrar o id desse utilizador
            wanted_user_id = i;
            break;
        }
    }
    if (wanted_user_id==-1){   //caso o utilizador seja válido
        for (int i = 0; i<num_linhas_valid[3]; i++){     //vai procurar o id do utilizador nos válidos
            if (strcmp(argument1, user_array_valid[i].id)==0){   //se encontrar o id desse utilizador
                wanted_user_id = i;
                break;
            }
        }
        if (wanted_user_id != -1){
            status = strdup(user_array_valid[wanted_user_id].account_status);
            toLowerCase(status);
            if (verify_account_status(status) == 1){   //apenas imprime caso a conta do utilizador esteja ativa
                int num_flights_passenger_id = 0, num_reservations = 0;
                Flight_id_passenger *flight_id_passenger_array = NULL;      //será um array para armazenar os id's de todos os voos em que o utilizador já voou
                Flight_aux *flight_aux_array = NULL; //será um array para armazenar a data esperada de partida e o id do voo em que o utilizador voou
                Reservation_aux *reservation_aux_array = NULL; //será um array para armazenar a data da reserva e o id da reserva que o utilizador fez
                if (strcmp(argument2, "reservations")!=0){
                    for (int i = 0; i<num_linhas_valid[0]; i++){   //procura o id desse utilizador no array dos passageiros para saber qual o seu voo
                        if (strcmp(argument1, passenger_array_valid[i].user_id)==0){   //se econtrar o id do utilizador no ficheiro dos passageiros e essa linha for válida
                            Flight_id_passenger novo = create_flight_id(passenger_array_valid[i].flight_id);    //é criado um novo elemento do array com o parâmetro lido
                            flight_id_passenger_array = realloc(flight_id_passenger_array, (num_flights_passenger_id+1)*sizeof(Flight_id_passenger)); 
                            flight_id_passenger_array[num_flights_passenger_id] = novo;        //esse novo elemento é adicionado ao array existente
                            num_flights_passenger_id++;
                        }
                    }
                    if (num_flights_passenger_id!=0){  //se encontrou voos em que o utilizador voou
                        for (int i = 0, j = 0; i<num_linhas_valid[1] && j<num_flights_passenger_id; i++){   //procura esses id's de voos no ficheiro dos voos
                            if (strcmp(flight_array_valid[i].id, flight_id_passenger_array[j].flight_id)==0){   //encontrou o id de voo
                                char* departure_date = only_date(flight_array_valid[i].schedule_departure_date);
                                Flight_aux novo;
                                if (exists_argument2==0) novo = create_flight_aux(flight_array_valid[i].id, departure_date, 0);
                                else novo = create_flight_aux(flight_array_valid[i].id, departure_date, 1);
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
                    for (int i = 0; i<num_linhas_valid[2]; i++){   //procura o id desse utilizador no array das reservas para saber qual a sua reserva
                        if (strcmp(argument1, reservation_array_valid[i].user_id)==0){   //se econtrar o id do utilizador no ficheiro das reservas válidas
                            Reservation_aux novo;
                            if (exists_argument2 == 0) novo = create_reservation_aux(reservation_array_valid[i].id, reservation_array_valid[i].begin_date, 0);
                            else novo = create_reservation_aux(reservation_array_valid[i].id, reservation_array_valid[i].begin_date, 1);
                            int j = num_reservations - 1;
                            reservation_aux_array = realloc(reservation_aux_array, (num_reservations + 1) * sizeof(Reservation_aux));
                            while (j >= 0 && compare_date_time(reservation_aux_array[j].begin_date, novo.begin_date) == 1) {
                                reservation_aux_array[j + 1] = reservation_aux_array[j];
                                j--;
                            }
                            reservation_aux_array[j + 1] = novo;
                            num_reservations++;
                        }
                    }
                }  
                outputs_query2(flight_aux_array, reservation_aux_array, index_line, argument2, num_flights_passenger_id, num_reservations, n);
                generated_file = 1;
                free_flight_id_passenger(flight_id_passenger_array, num_flights_passenger_id);
                free_flight_aux(flight_aux_array, num_flights_passenger_id);
                free_reservation_aux(reservation_aux_array, num_reservations);
            }
            free(status);
        }
    }
    free(argument2);
    if (generated_file==0) create_output(n, 0);
}

void query3(char *line, int i, int n) {
    double rating = 0, rating_t = 0, total = 0, media = 0;
    int flag, generated_file = 0;

    if (i == 2) flag = 1;
    else flag = 0;
 
    int index_line = i;
    for (; line[index_line]== ' ' || line[index_line] == '"'; index_line++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j = index_line; line[j] != '\0' && line[j] != '\n'; j++, argument_length++);  //conta o tamanho do argumento
    char argument[argument_length];
    for (int k = 0, j = index_line; k < argument_length; k++, j++) argument[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    argument[argument_length] = '\0';

    int check = check_length(argument);
    if (check == 1) {
        for (i = 0; i < num_linhas_valid[2]; i++) {
            if (strcmp(reservation_array_valid[i].hotel_id, argument) == 0){
                rating = (double) atof(reservation_array_valid[i].rating);
                rating_t += (double) rating;
                total = (double) total + 1;
            }
        }

        if (total != 0) {
            media = (double) (rating_t / total);
            outputs_query3(media, flag, n);
            generated_file = 1;
        }
    }
    if (generated_file==0) create_output(n, 0);
}

void query4 (char *line, int i, int n) {
    int index_line = i, generated_file = 0;  // i=1
    for (; line[index_line] == ' ' || line[index_line] == '"'; index_line++);   // encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j=index_line; line[j]!='\0' && line[j] != '\n'; j++, argument_length++);  // conta o tamanho do argumento
    char argument[argument_length + 1];  // array que vai guardar o argumento da query
    for (int k=0, j=index_line; k<argument_length; k++, j++) argument[k] = line[j];   // opia o argumento da query (id) para o array que guarda esse argumento
    argument[argument_length] = '\0';

    hotel_aux *hotel_aux_array = NULL;  // será um array para armazenar os campos do hotel pretendidos
    int num_hotels = 0;
    if (argument_length > 0) {
        for (i = 0; i < num_linhas_valid[2]; i++) {  // vai percorrer o array das reservas para procurar o id pretendido
            if ((strcmp(argument, reservation_array_valid[i].hotel_id) == 0)) {  // se econtrar o id do hotel no ficheiro das reservas válidas
                hotel_aux novo = create_hotel_aux (reservation_array_valid[i].id, reservation_array_valid[i].begin_date, reservation_array_valid[i].end_date, reservation_array_valid[i].user_id, reservation_array_valid[i].rating, total_price (reservation_array_valid[i].price_per_night, nights(reservation_array_valid[i].begin_date,reservation_array_valid[i].end_date), reservation_array_valid[i].city_tax));
                hotel_aux_array = realloc (hotel_aux_array, (num_hotels+1)*sizeof(hotel_aux));
                hotel_aux_array [num_hotels] = novo;
                num_hotels++;
            }
        }
        qsort (hotel_aux_array, num_hotels, sizeof(hotel_aux), compare_hotels);
        outputs_query4(hotel_aux_array, index_line, num_hotels, n);
        generated_file = 1;
    }
    free_hotel_aux (hotel_aux_array, num_hotels);
    if (generated_file==0) create_output(n, 0);
}

void query5 (char *line, int i, int n) {
    int index1_line = i;  // i=1
    for (; line[index1_line] == ' ' || line[index1_line] == '"'; index1_line++);   // encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int arg_origin_length = 0;
    for (int j=index1_line; line[j]!='\0' && line[j] != '\n' && line[j] != ' '; j++, arg_origin_length++);  // conta o tamanho do primeiro argumento (origin)
    char arg_origin[arg_origin_length + 1];  // array que vai guardar o primeiro argumento da query
    for (int k=0, j=index1_line; k<arg_origin_length; k++, j++) arg_origin[k] = line[j];   // copia o primeiro argumento da query para o array que guarda esse argumento
    arg_origin[arg_origin_length] = '\0';
    
    int index2_line = index1_line + arg_origin_length; // index2_line = 2+3 = 5
    for (; line[index2_line] == ' '; index2_line++);  // encontra o indice do segundo argumento
    int arg_begin_date_length = 0;
    if (line[index2_line] == '"') {  // caso seja data com hora
        index2_line++;
        for (int j=index2_line; line[j] != '"'; j++, arg_begin_date_length++);  //conta o tamanho do segundo argumento (begin_date)
    }
    else {  // caso seja apenas data
        for (int j=index2_line; line[j] != ' '; j++, arg_begin_date_length++);  // conta o tamanho do segundo argumento (begin_date)
    }
    char arg_begin_date[arg_begin_date_length + 1];
    for (int k=0, j=index2_line; k<arg_begin_date_length; k++, j++) arg_begin_date[k] = line[j];   // copia o segundo argumento da query para o array que guarda esse argumento
    arg_begin_date[arg_begin_date_length] = '\0';

    int index3_line = index2_line + arg_begin_date_length;
    for (; line[index3_line] == ' ' || line[index3_line] == '"'; index3_line++);  // encontra o indice do terceiro argumento
    int arg_end_date_length = 0;
    if (line[index3_line - 1] == '"') {  // caso seja data com hora
        for (int j=index3_line; line[j] != '"'; j++, arg_end_date_length++);  //conta o tamanho do terceiro argumento (end_date)
    }
    else {  // caso seja apenas data
        for (int j=index3_line; line[j] != '\0' && line[j] != '\n'; j++, arg_end_date_length++);  // conta o tamanho do terceiro argumento (end_date)
    }
    char arg_end_date[arg_end_date_length + 1];
    for (int k=0, j=index3_line; k<arg_end_date_length; k++, j++) arg_end_date[k] = line[j];   // copia o terceiro argumento da query para o array que guarda esse argumento
    arg_end_date[arg_end_date_length] = '\0';

    flight_date_aux *flight_date_aux_array = NULL;  // será um array para armazenar os campos do voo pretendidos
    int num_flights = 0;
    if (arg_origin_length > 0) {
        char *arg_origin_cpy = strdup (arg_origin);
        toLowerCase(arg_origin_cpy);
        for (i = 0; i < num_linhas_valid[1]; i++) {  // vai percorrer o array dos voos para procurar os que têm a origin pretendida
            char *flight_origin_cpy = strdup(flight_array_valid[i].origin);
            toLowerCase(flight_origin_cpy);
            if ((strcmp(arg_origin_cpy, flight_origin_cpy) == 0) && is_date_between (flight_array_valid[i].schedule_departure_date, arg_begin_date, arg_end_date)) {  // se encontrar a origin no ficheiro dos voos válidos e se a schedule_departure_date desse voo estiver entre as datas pretendidas
                flight_date_aux novo = create_flight_date_aux (flight_array_valid[i].id, flight_array_valid[i].schedule_departure_date, flight_array_valid[i].destination, flight_array_valid[i].airline, flight_array_valid[i].plane_model);
                flight_date_aux_array = realloc (flight_date_aux_array, (num_flights+1)*sizeof(flight_date_aux));
                flight_date_aux_array [num_flights] = novo;
                num_flights++;
            }
            free (flight_origin_cpy);
        }
        free (arg_origin_cpy);
        qsort (flight_date_aux_array, num_flights, sizeof(flight_date_aux), compare_flights);
    }
    
    outputs_query5(flight_date_aux_array, index1_line, num_flights, n);
    free_flight_date_aux (flight_date_aux_array, num_flights);
}

void query6 (char *line, int i, int n) {
    int flag, index_pXa, index;
    char *date_t = (char*)malloc(5 * sizeof(char));
    char* origin = (char*)malloc(4 * sizeof(char));
    
    if (i == 2) flag = 1;
    else flag = 0;
    
    int top = atoi(&line[7]);
    int index_line = i; // _2023 5
    for (; line[index_line] == ' '; index_line++);
    int l_date = 0, j;
    for (j = index_line; line[j] != ' '; j++, l_date++);  //conta o tamanho do argumento
    char date[l_date];
    for (int k = 0, j = index_line; k < l_date; k++, j++) date[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    date[l_date] = '\0';

    int num_linhas_PassengersXairport = 0;
    PassengersXairport *passengersXairport_array = NULL;
    for (int k = 0; k < num_linhas_valid[1]; k++) {
        if (flight_array_valid[k].validation == 1) {
            for (index = 0; index < 4; index++) {
                date_t[index] = flight_array_valid[k].schedule_departure_date[index];
            }
            date_t[index] = '\0';
            //int date_t = atoi(&flight_array[k].schedule_departure_date[0]);
            if (strcmp(date_t, date) == 0) {
                //printf("%s ", flight_array[k].origin);
                strcpy(origin, flight_array_valid[k].origin);
                toUpperCase(origin);
                for (int pos = 0; pos < num_linhas_contador; pos++) {
                    if (strcmp(contador_array[pos].id_flight, flight_array_valid[k].id) == 0) {
                        int ind;
                        //printf("%s %d\n", contador_array[pos].id_flight, contador_array[pos].contador);
                        for (ind = 0; ind < num_linhas_PassengersXairport; ind++) {
                            if (strcmp(origin,passengersXairport_array[ind].origin) == 0) {
                                passengersXairport_array[ind].passengers += contador_array[pos].contador;
                                //printf("%d\n",2);
                                break;
                            }
                        }
                        if (ind == num_linhas_PassengersXairport) {
                            //printf("%d\n",3);
                            PassengersXairport novo = create_PassengersXairport (origin, contador_array[pos].contador);
                            passengersXairport_array = realloc(passengersXairport_array, (num_linhas_PassengersXairport + 1) * sizeof(PassengersXairport));
                            passengersXairport_array[num_linhas_PassengersXairport] = novo;
                            num_linhas_PassengersXairport++; 
                        }
                    }
                }
            }
        }
    }

    for (index_pXa = 0; index_pXa < num_linhas_PassengersXairport; index_pXa++) {
        for (int index_pXa_prox = index_pXa + 1; index_pXa_prox < num_linhas_PassengersXairport; index_pXa_prox++) {
            if (passengersXairport_array[index_pXa].passengers < passengersXairport_array[index_pXa_prox].passengers) {
                // Uso da função para trocar ints
                swap_contador(&passengersXairport_array[index_pXa].passengers, &passengersXairport_array[index_pXa_prox].passengers);
                // Uso da função para trocar strings
                swapStrings(&passengersXairport_array[index_pXa].origin, &passengersXairport_array[index_pXa_prox].origin);
            }
            else
                if (passengersXairport_array[index_pXa].passengers == passengersXairport_array[index_pXa_prox].passengers) {
                    if (strcmp(passengersXairport_array[index_pXa].origin, passengersXairport_array[index_pXa_prox].origin) < 0) {
                         // Uso da função para trocar ints
                        swap_contador(&passengersXairport_array[index_pXa].passengers, &passengersXairport_array[index_pXa_prox].passengers);
                        // Uso da função para trocar strings
                        swapStrings(&passengersXairport_array[index_pXa].origin, &passengersXairport_array[index_pXa_prox].origin);
                    }
                }
            
        }
    }

    outputs_query6(passengersXairport_array, index_pXa, top, flag, n);
    free_PassengersXairport(passengersXairport_array, num_linhas_PassengersXairport);
    free(origin);
    free(date_t);
}

void query7(char *line, int i, int n){
    int N = 0, index_line = i, generated_file = 0;

    for (; line[index_line]==' ' || line[index_line]=='"'; index_line++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j=index_line; line[j]!='\0' && line[j]!='\n' && line[j]!='"'; j++, argument_length++);  //conta o tamanho do argumento
    char argument[argument_length];
    for (int k=0, j=index_line; k<argument_length; k++, j++) argument[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    argument[argument_length] = '\0';

    if (strlen(argument)>0){
        N = atoi(argument);
        int num_medianas = 0;
        Mediana *mediana_array = NULL;    //array que irá guardar as medianas e o respetivo aeroporto
        for (int i = 0; i<num_Atrasos; i++){
            Mediana novo = create_mediana(Atrasos_array[i].airport, calculate_mediana(Atrasos_array[i].atraso, Atrasos_array[i].num_atrasos));
            mediana_array = realloc(mediana_array, (num_medianas+1)*sizeof(Mediana));
            mediana_array[num_medianas] = novo;
            num_medianas++;
        }

        insertionSort_medianas(mediana_array, num_medianas);
        
        if(N>num_medianas) N = num_medianas;
        outputs_query7(mediana_array, index_line, N, n);
        generated_file = 1;
        free_Mediana(mediana_array, num_medianas);
    }
    if (generated_file==0) create_output(n, 0);
}

void query9 (char *line, int i, int n) {
    int flag, ind, index_line = i, generated_file = 0;
    
    if (i == 2) flag = 1;
    else flag = 0;

    for (; line[index_line]==' ' || line[index_line]=='"'; index_line++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j=index_line; line[j]!='\0' && line[j]!='\n' && line[j]!='"'; j++, argument_length++);  //conta o tamanho do argumento
    char name[argument_length];
    for (int k=0, j=index_line; k<argument_length; k++, j++) name[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    name[argument_length] = '\0';

    if (strlen(name)>0){
        char *status_cpy = NULL;
        int num_linhas_idXname = 0;
        idXname *idXname_array = NULL;
        for (int k = 0; k < num_linhas_valid[3]; k++) {
            status_cpy = strdup(user_array_valid[k].account_status);
            toLowerCase (status_cpy);
            if (strcmp(status_cpy,"active") == 0) {
                for (ind = 0; name[ind] == user_array_valid[k].name[ind]; ind++);
                if (name[ind] == '\0') {
                    idXname novo = create_IdXname (user_array_valid[k].id, user_array_valid[k].name);
                    idXname_array = realloc(idXname_array, (num_linhas_idXname + 1) * sizeof(idXname));
                    idXname_array[num_linhas_idXname] = novo;
                    num_linhas_idXname++;
                }
            }
            free(status_cpy);
        }

        for(int index_idXn = 0; index_idXn < num_linhas_idXname; index_idXn++) {
            for (int index_idXn_prox = index_idXn + 1; index_idXn_prox < num_linhas_idXname; index_idXn_prox++) {
                if (strcoll(idXname_array[index_idXn].name,idXname_array[index_idXn_prox].name) > 0) { //comparar ignorando maiusculas e minusculas
                    // Uso da função para trocar strings
                    swapStrings(&idXname_array[index_idXn].name, &idXname_array[index_idXn_prox].name);
                    swapStrings(&idXname_array[index_idXn].id, &idXname_array[index_idXn_prox].id);
                }
                else
                    if (strcoll(idXname_array[index_idXn].name,idXname_array[index_idXn_prox].name) == 0) { //comparar ignorando maiusculas e minusculas
                        if (strcoll(idXname_array[index_idXn].id,idXname_array[index_idXn_prox].id) > 0) { //comparar ignorando maiusculas e minusculas
                            // Uso da função para trocar strings
                            swapStrings(&idXname_array[index_idXn].name, &idXname_array[index_idXn_prox].name);
                            swapStrings(&idXname_array[index_idXn].id, &idXname_array[index_idXn_prox].id);
                        }
                    }  
            }
        }  

        outputs_query9(idXname_array, num_linhas_idXname, flag, n);
        generated_file = 1;
        free_idXname(idXname_array, num_linhas_idXname);
    }
    if (generated_file==0) create_output(n, 0);
}

void identify_query(char* path){
    char *line = NULL;
    size_t len = 0;
    int n = 0;
    char *aux_queries = strdup(path);
    input = fopen(aux_queries, "r");
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
                        query4(line, i, n);

                    break;
                    case '5':  //5 ou 5F
                        query5(line, i, n);

                    break;
                    case '6':  //6 ou 6F
                        query6(line, i, n);
                    break;
                    case '7':  //7 ou 7F
                        query7(line, i, n);
                    break;
                    case '8':  //8 ou 8F

                    break;
                    case '9':  //9 ou 9F
                        query9(line, i, n);
                    break;
                }
            }
    }
    free(line);
    free(aux_queries);
}