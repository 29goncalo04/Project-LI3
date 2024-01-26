#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "../include/Aux_validation.h"
#include "../include/Output_queries.h"
#include "../include/Free.h"
#include "../include/Aux_functions.h"
#include "../include/Queries.h"
#include "../include/Hash.h"
#include "../include/Catalogs.h"



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
                        char *breakfast;
                        char* aux_breakfast = strdup(get_reservation_includes_breakfast(rpointer));
                        if (verify_breakfast(aux_breakfast) == 1) breakfast = strdup("True");
                        else  breakfast = strdup("False");
                        free(aux_breakfast);
                        outputs_query1_reservations(rpointer, breakfast, flag, n);
                        free(breakfast);
                        generated_file = 1;
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

void query2 (char *str, int flag, int n, int mode) {
    int ind_u, l;
    char *id = strtok(str, " ");
    char *argument = strtok(NULL, " ");
    if (argument != NULL) {
        l = strlen(argument);
        argument[l-1] = '\0';
        if (strcmp("reservations", argument) == 0 || strcmp("reservation", argument) == 0) {
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
        if (strcmp("flights", argument) == 0 || strcmp("flight", argument) == 0) {
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
        if(mode == 1) id[l-1] = '\0';
        else id[l] = '\0';
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

void query3 (char *id, int flag, int n, int mode) {
    int l = strlen(id), ind;
    double rt = 0, total = 0, med;
    if(mode==1) id[l-1] = '\0';
    else id[l] = '\0';
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

void query8 (char *str, int flag, int n, int mode) {
    int l_arg_end_date, ind_h, revenue = 0;
    char *id = strtok (str, " ");
    char *arg_begin_date = strtok (NULL, " ");
    char *arg_end_date = strtok (NULL, " ");
    l_arg_end_date = strlen (arg_end_date);
    if(mode==1) arg_end_date[l_arg_end_date-1] = '\0';
    else arg_end_date[l_arg_end_date] = '\0';
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
    list_users *list_aux;
    list_aux = NULL;
    int tam_aux = 0;
    for (int j = 0; j < tam; j++) {
        if(j==0){
            const UNo* aux = getUListInit(get_user_array_valid(list_temp[j]));
            while(aux!=NULL){
                if(strncmp(get_user_name(aux), prefix, strlen(prefix))==0 && verify_account_status(get_user_account_status(aux))==1){
                    list_aux = realloc(list_aux, (tam_aux+1) * sizeof(struct list_users));
                    list_aux[tam_aux].name = strdup(get_user_name(aux));
                    list_aux[tam_aux].id = strdup(get_user_id(aux));
                    tam_aux++;
                }
                aux = get_user_prox(aux);
            }
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
                    }
                    aux = get_user_prox(aux);
                }
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

void query10 (char *str, int flag, int n) {
    if (strcmp(str, "v")==0) {
        outputs_query10_years(2010, flag, n);
    }
    else {
        char* argument = strtok (str, "\n");
        if (strlen(argument)>5) {
            char *year = strtok(argument, " ");
            char *month = strtok(NULL, "\n");
            outputs_query10_year_month(year, month, flag, n);
        }
        else {
            outputs_query10_year(argument, flag, n);
        }
    }
    return;
}