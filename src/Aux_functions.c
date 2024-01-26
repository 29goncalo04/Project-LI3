#include <string.h>
#include <stdlib.h>

#include "../include/Aux_validation.h"
#include "../include/Catalogs.h"
#include "../include/Aux_functions.h"
#include "../include/Queries.h"


int year(char* date) {
    char date_copy[20];
    strcpy(date_copy, date);
    int aux = atoi(strtok(date_copy, "/"));
    return aux;
}

char* year_month(char* date) {
    char *year_month_str = strdup(date);
    year_month_str[7] = '\0';
    return year_month_str;
}

char* year_month_day(char* date) {
    char *year_month_day_str = strdup(date);
    year_month_day_str = strtok(year_month_day_str, " ");
    return year_month_day_str;
}

int delay(const char *schedule, const char *real){
    int atraso = 0, verdadeira = 0, prevista = 0;
    verdadeira = (real[11]-'0')*36000 + (real[12]-'0')*3600 + (real[14]-'0')*600 + (real[15]-'0')*60 + (real[17]-'0')*10 + (real[18]-'0');
    prevista = (schedule[11]-'0')*36000 + (schedule[12]-'0')*3600 + (schedule[14]-'0')*600 + (schedule[15]-'0')*60 + (schedule[17]-'0')*10 + (schedule[18]-'0');
    atraso = verdadeira-prevista;
    return atraso;
}

int nights(const char *begin, const char *end){
    int noites = 0, inicio = 0, fim = 0;
    inicio = (begin[8]-'0')*10 + (begin[9]-'0');
    fim = (end[8]-'0')*10 + (end[9]-'0');
    noites = fim-inicio;
    return noites;
}

int nights_between (const char *begin_res, const char* end_res, char* begin_arg, char* end_arg) {
    if (strcmp (begin_arg, end_arg) > 0 || strcmp (begin_arg, end_res) > 0 || strcmp (end_arg, begin_res) < 0) return 0;
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

int age_user(const char *birth_date){
    int ano = 0, mes = 0, dia = 0, age = 0;
    ano = (birth_date[0]-'0')*1000 + (birth_date[1]-'0')*100 + (birth_date[2]-'0')*10 + (birth_date[3]-'0');
    mes = (birth_date[5]-'0')*10 + (birth_date[6]-'0');
    dia = (birth_date[8]-'0')*10 + (birth_date[9]-'0');
    age = (2023-ano);
    if (10 < mes || (10 == mes && 1 < dia)) age--;
    return age;
}

int compare_numbers(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int compare_medianas(const void *a, const void *b) {
    int diff = ((list_mediana *)a)->mediana - ((list_mediana *)b)->mediana;
    if (diff == 0) {
        char *originA = ((list_mediana *)a)->airport;
        char *originB = ((list_mediana *)b)->airport;
        return strcmp(originA, originB);
    }
    if (diff > 0) return -1;
    else return 1;
}

int compare_reservations (const void *a, const void *b) {
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

int compare_flights (const void *a, const void *b) {
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

int compare_users(const void *a, const void *b) {
    char *nameA = strdup(((list_users *)a)->name);
    char *nameB = strdup(((list_users *)b)->name);
    if (strcoll(nameA, nameB)!=0){
        int result = strcoll(nameA, nameB);
        free(nameA);
        free(nameB);
        return result;
    }
    char *idA = strdup(((list_users *)a)->id);
    char *idB = strdup(((list_users *)b)->id);
    if (strcoll(idA, idB)<0){
        free(nameA);
        free(nameB);
        free(idA);
        free(idB);
        return -1;
    }
    if (strcoll(idA, idB)>0){
        free(nameA);
        free(nameB);
        free(idA);
        free(idB);
        return 1;
    }
    return 0;
}

int is_date_between (const char *date, const char *i, const char *f) {  // date é a que queremos verificar, i é a data inicial e f a data final
    if (strcmp (date, i) < 0) return 0;  // date é menor que i, logo não está entre as datas
    if (strcmp (date, f) > 0) return 0;  // date é maior que f, não está entre as datas
    return 1;  // date está entre i e f
}

// Troca o conteúdo de dois ints
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

char *only_date(char *schedule_departure_date){
    char *date = (char*)malloc(11 * sizeof(char));
    strncpy(date, schedule_departure_date, 10);
    date[10] = '\0'; 
    return date;
}

char *only_date2(const char *schedule_departure_date){
    char *date = (char*)malloc(11 * sizeof(char));
    strncpy(date, schedule_departure_date, 10);
    date[10] = '\0'; 
    return date;
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