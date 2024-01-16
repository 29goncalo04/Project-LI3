#include <string.h>
#include <stdlib.h>

#include "../include/Aux_validation.h"
#include "../include/Catalogs.h"
#include "../include/Aux_structs.h"
#include "../include/Aux_functions.h"

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

int year(char* date) {
    char date_copy[20];
    strcpy(date_copy, date);
    int aux = atoi(strtok(date_copy, "/"));
    return aux;
}

int delay(const char *schedule, const char *real){ //2021/07/01 05:56:50  !!!!  2021/07/01 06:56:50
    int atraso = 0, verdadeira = 0, prevista = 0;
    verdadeira = (real[11]-'0')*36000 + (real[12]-'0')*3600 + (real[14]-'0')*600 + (real[15]-'0')*60 + (real[17]-'0')*10 + (real[18]-'0');
    prevista = (schedule[11]-'0')*36000 + (schedule[12]-'0')*3600 + (schedule[14]-'0')*600 + (schedule[15]-'0')*60 + (schedule[17]-'0')*10 + (schedule[18]-'0');
    atraso = verdadeira-prevista;
    return atraso;
}

int nights(const char *begin, const char *end){  //2021/07/01   !!!!!   2021/07/03
    int noites = 0, inicio = 0, fim = 0;
    inicio = (begin[8]-'0')*10 + (begin[9]-'0');
    fim = (end[8]-'0')*10 + (end[9]-'0');
    noites = fim-inicio;
    return noites;
}

int nights_between (const char *begin_res, const char* end_res, char* begin_arg, char* end_arg) {
    if (strcmp (begin_arg, end_arg) > 0 || strcmp (begin_arg, end_res) > 0 || strcmp (end_arg, begin_res) < 0) return 0;   // deve retornar 0 ou dizer q o input da query foi inválido (no modo interativo)???
    if (strcmp (begin_arg, begin_res) >= 0) {
        if (strcmp (end_arg, end_res) < 0) return nights (begin_arg, end_arg) + 1;
        return nights (begin_arg, end_res);
    }
    else {
        if (strcmp (end_arg, end_res) < 0) return nights (begin_res, end_arg) + 1;
        return nights (begin_res, end_res);
    }
}

double total_price(int price_per_night, int nights, int city_tax){
    double price = 0;
    price = (double)((price_per_night)*nights) + ((double)((price_per_night)*nights*(city_tax)) / 100) ;
    return price;
}

int age_user(const char *birth_date){  //1979/11/27
    int ano = 0, mes = 0, dia = 0, age = 0;
    ano = (birth_date[0]-'0')*1000 + (birth_date[1]-'0')*100 + (birth_date[2]-'0')*10 + (birth_date[3]-'0');
    mes = (birth_date[5]-'0')*10 + (birth_date[6]-'0');
    dia = (birth_date[8]-'0')*10 + (birth_date[9]-'0');
    age = (2023-ano);
    if (10 < mes || (10 == mes && 1 < dia)) age--;
    return age;
}

int compare_reservations (const void *a, const void *b) {  // ordenar da data mais recente para a mais antiga, ou pelo id se as datas forem iguais
    char *beginA = strdup(get_reservation_begin_date(getRListInit(get_reservation_array_valid(*(const int*)a))));
    char *beginB = strdup(get_reservation_begin_date(getRListInit(get_reservation_array_valid(*(const int*)b))));
    if (strcmp (beginA, beginB) < 0){
        free(beginA);
        free(beginB);
        return 1;
    }
    if (strcmp (beginA, beginB) > 0){
        free(beginA);
        free(beginB);
        return -1;
    }
    char *idA = strdup(get_reservation_id(getRListInit(get_reservation_array_valid(*(const int*)a))));
    char *idB = strdup(get_reservation_id(getRListInit(get_reservation_array_valid(*(const int*)b))));
    if (strcmp (idA, idB) < 0){
        free(beginA);
        free(beginB);
        free(idA);
        free(idB);
        return -1;
    }
    if (strcmp (idA, idB) > 0){
        free(beginA);
        free(beginB);
        free(idA);
        free(idB);
        return 1;
    }
    return 0;
}

int compare_flights (const void *a, const void *b) {  // ordenar da data mais recente para a mais antiga, ou pelo id se as datas forem iguais
    char *beginA = strdup(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(*(const int*)a))));
    char *beginB = strdup(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(*(const int*)b))));
    if (strcmp (beginA, beginB) < 0){
        free(beginA);
        free(beginB);
        return 1;
    }
    if (strcmp (beginA, beginB) > 0){
        free(beginA);
        free(beginB);
        return -1;
    }
    char *idA = strdup(get_flight_id(getFListInit(get_flight_array_valid(*(const int*)a))));
    char *idB = strdup(get_flight_id(getFListInit(get_flight_array_valid(*(const int*)b))));
    if (strcmp (idA, idB) < 0){
        free(beginA);
        free(beginB);
        free(idA);
        free(idB);
        return -1;
    }
    if (strcmp (idA, idB) > 0){
        free(beginA);
        free(beginB);
        free(idA);
        free(idB);
        return 1;
    }
    return 0;
}

int compare_airports2023 (const void *a, const void *b) {
    int passengersA = get_airport_passengers2023(getAListInit(get_airport_array_valid(*(const int*)a)));
    int passengersB = get_airport_passengers2023(getAListInit(get_airport_array_valid(*(const int*)b)));
    if ((passengersA - passengersB) < 0){
        return 1;
    }
    if ((passengersA - passengersB) > 0){
        return -1;
    }
    char *originA = strdup(get_airport_name(getAListInit(get_airport_array_valid(*(const int*)a))));
    char *originB = strdup(get_airport_name(getAListInit(get_airport_array_valid(*(const int*)b))));
    if (strcmp (originA, originB) < 0){
        free(originA);
        free(originB);
        return -1;
    }
    if (strcmp (originA, originB) > 0){
        free(originA);
        free(originB);
        return 1;
    }
    return 0;
}

int compare_airports2022 (const void *a, const void *b) {
    int passengersA = get_airport_passengers2022(getAListInit(get_airport_array_valid(*(const int*)a)));
    int passengersB = get_airport_passengers2022(getAListInit(get_airport_array_valid(*(const int*)b)));
    if ((passengersA - passengersB) < 0){
        return 1;
    }
    if ((passengersA - passengersB) > 0){
        return -1;
    }
    char *originA = strdup(get_airport_name(getAListInit(get_airport_array_valid(*(const int*)a))));
    char *originB = strdup(get_airport_name(getAListInit(get_airport_array_valid(*(const int*)b))));
    if (strcmp (originA, originB) < 0){
        free(originA);
        free(originB);
        return -1;
    }
    if (strcmp (originA, originB) > 0){
        free(originA);
        free(originB);
        return 1;
    }
    return 0;
}

int compare_airports2021 (const void *a, const void *b) {
    int passengersA = get_airport_passengers2021(getAListInit(get_airport_array_valid(*(const int*)a)));
    int passengersB = get_airport_passengers2021(getAListInit(get_airport_array_valid(*(const int*)b)));
    if ((passengersA - passengersB) < 0){
        return 1;
    }
    if ((passengersA - passengersB) > 0){
        return -1;
    }
    char *originA = strdup(get_airport_name(getAListInit(get_airport_array_valid(*(const int*)a))));
    char *originB = strdup(get_airport_name(getAListInit(get_airport_array_valid(*(const int*)b))));
    if (strcmp (originA, originB) < 0){
        free(originA);
        free(originB);
        return -1;
    }
    if (strcmp (originA, originB) > 0){
        free(originA);
        free(originB);
        return 1;
    }
    return 0;
}

int is_date_between (const char *date, const char *i, const char *f) {  // date é a que queremos verificar, i é a data inicial e f a data final
    if (strcmp (date, i) < 0) return 0;  // date é menor que i, logo não está entre as datas
    if (strcmp (date, f) > 0) return 0;  // date é maior que f, não está entre as datas
    return 1;  // date está entre i e f
}

// int compare_flights (const void *a, const void *b) {  // ordenar da data mais antiga para a mais recente, ou pelo id se as datas forem iguais
//     char *beginA = ((flight_date_aux *) a)->schedule_departure_date;
//     char *beginB = ((flight_date_aux *) b)->schedule_departure_date;
//     if (strcmp (beginA, beginB) < 0) return 1;
//     if (strcmp (beginA, beginB) > 0) return -1;
//     char *idA = ((flight_date_aux *) a)->id;
//     char *idB = ((flight_date_aux *) b)->id;
//     if (strcmp (idA, idB) < 0) return -1;
//     if (strcmp (idA, idB) > 0) return 1;
//     return 0;
// }

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

char *only_date(char *schedule_departure_date){  //2023/02/10 03:24:09
    char *date = (char*)malloc(11 * sizeof(char));
    strncpy(date, schedule_departure_date, 10);
    date[10] = '\0'; 
    return date;
}

char *only_date2(const char *schedule_departure_date){  //2023/02/10 03:24:09
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

int compare_date_time2(char *i, char *f) {
    return strcmp(i, f);
}

int is_prime(int num) {
    if (num < 2) {
        return 0;
    }

    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

int find_near_prime(int num) {
    if (num < 2) {
        return 2;  // O numero primo mais perto é o 2
    }

    int previous_prime = num - 1;
    int posterior_prime = num + 1;

    while (1) {
        if (is_prime(previous_prime)) {
            return previous_prime;
        } else if (is_prime(posterior_prime)) {
            return posterior_prime;
        } else {
            previous_prime--;
            posterior_prime++;
        }
    }
}