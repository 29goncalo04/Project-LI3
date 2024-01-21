#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/Catalogs.h"
#include "../include/Validation.h"
#include "../include/Statistics.h"
#include "../include/Hash.h"
#include "../include/Aux_functions.h"
#include "../include/Aux_validation.h"
#include "../include/Output_errors.h"

////////////////////////YEAR///////////////////////////
////////////////////////YEAR///////////////////////////
////////////////////////YEAR///////////////////////////
////////////////////////YEAR///////////////////////////
////////////////////////YEAR///////////////////////////
////////////////////////YEAR///////////////////////////
////////////////////////YEAR///////////////////////////
////////////////////////YEAR///////////////////////////
////////////////////////YEAR///////////////////////////
////////////////////////YEAR///////////////////////////
struct YNo {   //2023     2023/02
    int airports;
    int *list_airports;
    int new_users;
    int flights;
    int passengers;
    int unique_passengers;
    //int users;
    //char **list_users;
    int reservations;
};

void set_year_airports(YNo* YNo, int airports){
    YNo->airports = airports;
}
void set_year_list_airports(YNo* YNo){
    YNo->list_airports = NULL;
}
void set_year_new_users(YNo* YNo, int new_user){
    YNo->new_users = new_user;
}
void set_year_flights(YNo* YNo, int flights){
    YNo->flights = flights;
}
void set_year_passengers(YNo* YNo, int passengers){
    YNo->passengers = passengers;
}
void set_year_unique_passengers(YNo* YNo, int unique_passengers){
    YNo->passengers = unique_passengers;
}
//void set_year_users(YNo* YNo, int users){
//    YNo->users = users;
//}
//void set_year_list_users(YNo* YNo){
//    YNo->list_users = NULL;
//}
void set_year_reservations(YNo* YNo, int reservations){
    YNo->reservations = reservations;
}

struct YList {
    YNo *init;
};

YList year_array_valid[NUM_LINHAS_VALID_YEAR];

const YList* get_year_array_valid(int pos) {
    return &year_array_valid[pos];
}
const YNo* getYListInit(const YList* YList){
    return YList->init;
}
const int* get_year_list_airports(const YNo* YNo){
    return YNo->list_airports;
}
int get_year_airports(const YNo* YNo){
    return YNo->airports;
}
int get_year_new_users(const YNo* YNo){
    return YNo->new_users;
}
int get_year_flights(const YNo* YNo){
    return YNo->flights;
}
int get_year_passengers(const YNo* YNo){
    return YNo->passengers;
}
int get_year_unique_passengers(const YNo* YNo){
    return YNo->unique_passengers;
}
int get_year_reservations(const YNo* YNo){
    return YNo->reservations;
}

void create_array_years() {
    for (int i = 0; i < NUM_LINHAS_VALID_YEAR; i++) { 
        YNo* nova = malloc(sizeof(struct YNo));
        set_year_airports(nova, 0);                                           
        set_year_list_airports(nova);
        set_year_new_users(nova, 0); 
        set_year_flights(nova, 0); 
        set_year_unique_passengers(nova, 0);
        set_year_passengers(nova, 0);
        set_year_reservations(nova, 0); 
        year_array_valid[i].init = nova;
    }
    return;
}

void free_list_year(const YNo *nodo) {
    const YNo* atual = nodo;
    free((int*)atual->list_airports);
    //for(int i = 0; i < atual->users; i++) {
    //    free(atual->list_users[i]);
    //}
    //free((char**)atual->list_users);
    free((char*)atual);
}

void perform_operation_on_year_array(void (*operation)(YList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_YEAR; i++) {
        operation(&year_array_valid[i]);
    }
}

void free_year_element(YList *year_element) {
    free_list_year(getYListInit(year_element));
}

void free_year_valid() {
    perform_operation_on_year_array(free_year_element);
}

////////////////////////PREFIX_5///////////////////////////
////////////////////////PREFIX_5///////////////////////////
////////////////////////PREFIX_5///////////////////////////
////////////////////////PREFIX_5///////////////////////////
////////////////////////PREFIX_5///////////////////////////
////////////////////////PREFIX_5///////////////////////////
////////////////////////PREFIX_5///////////////////////////
////////////////////////PREFIX_5///////////////////////////
////////////////////////PREFIX_5///////////////////////////
////////////////////////PREFIX_5///////////////////////////

struct PNo {
    int users;
    int *list_users;
};

void set_Prefix_users(PNo* PNo, int users){
    PNo->users = users;
}
void set_Prefix_list_users(PNo* PNo){
    PNo->list_users = NULL;
}

struct PList{
    PNo *init;
};

PList Prefix_array_valid[NUM_LINHAS_VALID_PREFIX_5];

const PList* get_Prefix_array_valid(int pos) {
    return &Prefix_array_valid[pos];
}
const PNo* getPListInit(const PList* PList){
    return PList->init;
}
const int* get_Prefix_list_users(const PNo* PNo){
    return PNo->list_users;
}
int get_Prefix_users(const PNo* PNo){
    return PNo->users;
}

void create_array_Prefix() {
    for (int i = 0; i < NUM_LINHAS_VALID_PREFIX_5; i++) { 
        PNo* nova = malloc(sizeof(struct PNo));
        set_Prefix_users(nova, 0);                                           
        set_Prefix_list_users(nova);
        Prefix_array_valid[i].init = nova;
    }
    return;
}

void free_list_Prefix(const PNo *nodo) {
    const PNo* atual = nodo;
    free((int*)atual->list_users);
    free((char*)atual);
}

void perform_operation_on_Prefix_array(void (*operation)(PList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_PREFIX_5; i++) {
        operation(&Prefix_array_valid[i]);
    }
}

void free_Prefix_element(PList *Prefix_element) {
    free_list_Prefix(getPListInit(Prefix_element));
}

void free_Prefix_valid() {
    perform_operation_on_Prefix_array(free_Prefix_element);
}







////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////
////////////////////////USERS///////////////////////////

struct UNo{
    char *id;
    char *name;
    char *birth_date;
    char *sex;
    char *passport;
    char *country_code;
    char *account_creation;
    char *account_status;
    int reservations;
    int *list_reservations;
    int flights;
    int *list_flights;
    double total_spent;
    int validation;
    struct UNo *prox;
};

void set_user_id(UNo* UNo, const char* id){
    UNo->id = strdup(id);
}
void set_user_name(UNo* UNo, const char* name){
    UNo->name = strdup(name);
}
void set_user_birth_date(UNo* UNo, const char* birth_date){
    UNo->birth_date = strdup(birth_date);
}
void set_user_sex(UNo* UNo, const char* sex){
    UNo->sex = strdup(sex);
}
void set_user_passport(UNo* UNo, const char* passport){
    UNo->passport = strdup(passport);
}
void set_user_country_code(UNo* UNo, const char* country_code){
    UNo->country_code = strdup(country_code);
}
void set_user_account_creation(UNo* UNo, const char* account_creation){
    UNo->account_creation = strdup(account_creation);
}
void set_user_account_status(UNo* UNo, const char* account_status){
    UNo->account_status = strdup(account_status);
}
void set_user_reservations(UNo* UNo, int reservations){
    UNo->reservations = reservations;
}
void set_user_list_reservations(UNo* UNo){
    UNo->list_reservations = NULL;
}
void set_user_flights(UNo* UNo, int flights){
    UNo->flights = flights;
}
void set_user_list_flights(UNo* UNo){
    UNo->list_flights = NULL;
}
void set_user_total_spent(UNo* UNo, double total_spent){
    UNo->total_spent = total_spent;
}
void set_user_validation(UNo* UNo, int validation){
    UNo->validation = validation;
}
void set_user_prox(UNo* UNo){
    UNo->prox = NULL;
}

struct UList{
    UNo *init;
};

UList user_array_valid[NUM_LINHAS_VALID_USER];

const UList* get_user_array_valid(int pos) {
    return &user_array_valid[pos];
}
const UNo* getUListInit(const UList* UList){
    return UList->init;
}

UNo* create_user(char parametros[][FIELD_SIZE]) {    
    UNo* nova = malloc(sizeof(struct UNo));
    set_user_id(nova, parametros[0]);                                           
    set_user_name(nova, parametros[1]);
    set_user_birth_date(nova, parametros[4]);
    set_user_sex(nova, parametros[5]);
    set_user_passport(nova, parametros[6]);
    set_user_country_code(nova, parametros[7]);
    set_user_account_creation(nova, parametros[9]);
    set_user_account_status(nova, parametros[11]);
    set_user_reservations(nova, 0);
    set_user_list_reservations(nova);
    set_user_flights(nova, 0);
    set_user_list_flights(nova);
    set_user_total_spent(nova, 0);
    set_user_validation(nova, 1);
    set_user_prox(nova);
    return nova;
}

const char* get_user_id(const UNo* UNo){
    return UNo->id;
}
const char* get_user_name(const UNo* UNo){
    return UNo->name;
}
const char* get_user_birth_date(const UNo* UNo){
    return UNo->birth_date;
}
const char* get_user_sex(const UNo* UNo){
    return UNo->sex;
}
const char* get_user_passport(const UNo* UNo){
    return UNo->passport;
}
const char* get_user_country_code(const UNo* UNo){
    return UNo->country_code;
}
const char* get_user_account_creation(const UNo* UNo){
    return UNo->account_creation;
}
const char* get_user_account_status(const UNo* UNo){
    return UNo->account_status;
}
int get_user_reservations(const UNo* UNo){
    return UNo->reservations;
}
const int* get_user_list_reservations(const UNo* UNo){
    return UNo->list_reservations;
}
int get_user_flights(const UNo* UNo){
    return UNo->flights;
}
const int* get_user_list_flights(const UNo* UNo){
    return UNo->list_flights;
}
double get_user_total_spent(const UNo* UNo){
    return UNo->total_spent;
}
int get_user_validation(const UNo* UNo){
    return UNo->validation;
}
const UNo* get_user_prox(const UNo* UNo){
    return UNo->prox;
}

void users_hash_sort(UList *user_array_valid, UList list) {
    char* aux = strdup(get_user_id(list.init));
    int ind = found_index_users(aux);
    free(aux);
    if (user_array_valid[ind].init == NULL) { //esta tudo NULL (vacio)
        user_array_valid[ind] = list;
    }
    else {
        list.init->prox = user_array_valid[ind].init;
        user_array_valid[ind] = list;
    }
}

//new users
void create_array_users(char parametros[][FIELD_SIZE]) {
    int val = validate_user(parametros);
    if (val == 1) {
        UNo* nova = create_user(parametros);
        UList list;
        list.init = nova;

        if(verify_account_status(parametros[11]) == 1){    //account_status é active
            int id_user_table = found_index_users(parametros[0]);
            int ind_Prefix = found_index_Prefix(parametros[1]);
            PNo *pointer_P = Prefix_array_valid[ind_Prefix].init;
            pointer_P->list_users = realloc(pointer_P->list_users, (pointer_P->users+1)*sizeof(int));
            pointer_P->list_users[pointer_P->users] = id_user_table;
            pointer_P->users++;
            int ind_prefix = found_index_prefix(parametros[1]);
            PNo *pointer_p = Prefix_array_valid[ind_prefix].init;
            pointer_p->list_users = realloc(pointer_p->list_users, (pointer_p->users+1)*sizeof(int));
            pointer_p->list_users[pointer_p->users] = id_user_table;
            pointer_p->users++;
        }

        //query 10
        if(compare_date(parametros[9], "2023/10/01")!=1){
            YNo *pointer;
            char *str;
            int ind_year = found_index_year(year(parametros[9]));
            pointer = year_array_valid[ind_year].init;
            pointer->new_users++;
            str = year_month(parametros[9]);
            int ind_year_month = found_index_year_month_day(str);
            free(str);
            pointer = year_array_valid[ind_year_month].init;
            pointer->new_users++;
            
            str = year_month_day(parametros[9]);
            int ind_year_month_day = found_index_year_month_day(str);
            free(str);
            pointer = year_array_valid[ind_year_month_day].init;
            pointer->new_users++;
        }

        users_hash_sort(user_array_valid, list);
    } 
    else {
        complete_files_users(parametros); 
    }
}

void free_list_user(const UNo *nodo) {
    const UNo *atual = nodo;
    const UNo *next;
    while (atual!=NULL){
        next = atual->prox;
        free((char*)atual->id);
        free((char*)atual->name);
        free((char*)atual->birth_date);
        free((char*)atual->sex);
        free((char*)atual->passport);
        free((char*)atual->country_code);
        free((char*)atual->account_creation);
        free((char*)atual->account_status);
        free((int*)atual->list_reservations);
        free((int*)atual->list_flights);
        free((char*)atual);
        atual = next;
    }
}

void perform_operation_on_user_array(void (*operation)(UList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_USER; i++) {
        operation(&user_array_valid[i]);
    }
}

void free_user_element(UList *user_element) {
    free_list_user(getUListInit(user_element));
}

void free_user_valid() {
    perform_operation_on_user_array(free_user_element);
}










////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////
////////////////////////HOTELS///////////////////////////

struct HNo {
    int reservations;
    int *list_reservations;
};

void set_hotel_reservations(HNo* HNo, int reservations){
    HNo->reservations = reservations;
}
void set_hotel_list_reservations(HNo* HNo){
    HNo->list_reservations = NULL;
}

struct HList{
    HNo *init;
};

HList hotel_array_valid[NUM_LINHAS_VALID_HOTEL];

const HList* get_hotel_array_valid(int pos) {
    return &hotel_array_valid[pos];
}
const HNo* getHListInit(const HList* HList){
    return HList->init;
}
const int* get_hotel_list_reservations(const HNo* HNo){
    return HNo->list_reservations;
}
int get_hotel_reservations(const HNo* HNo){
    return HNo->reservations;
}

void create_array_hotels() {
    for (int i = 0; i < NUM_LINHAS_VALID_HOTEL; i++) { 
        HNo* nova = malloc(sizeof(struct HNo));
        set_hotel_reservations(nova, 0);                                           
        set_hotel_list_reservations(nova);
        hotel_array_valid[i].init = nova;
    }
    return;
}

void free_list_hotel(const HNo *nodo) {
    const HNo* atual = nodo;
    free((int*)atual->list_reservations);
    free((char*)atual);
}

void perform_operation_on_hotel_array(void (*operation)(HList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_HOTEL; i++) {
        operation(&hotel_array_valid[i]);
    }
}

void free_hotel_element(HList *hotel_element) {
    free_list_hotel(getHListInit(hotel_element));
}

void free_hotel_valid() {
    perform_operation_on_hotel_array(free_hotel_element);
}










////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////
////////////////////////RESERVATIONS///////////////////////////

struct RNo {
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    int hotel_stars;
    int city_tax;
    char *begin_date;
    char *end_date;
    int price_per_night;
    char *includes_breakfast;
    int rating;
    int validation;
    struct RNo *prox;
};

void set_reservation_id(RNo* RNo, const char* id){
    RNo->id = strdup(id);
}
void set_reservation_user_id(RNo* RNo, const char* user_id){
    RNo->user_id = strdup(user_id);
}
void set_reservation_hotel_id(RNo* RNo, const char* hotel_id){
    RNo->hotel_id = strdup(hotel_id);
}
void set_reservation_hotel_name(RNo* RNo, const char* hotel_name){
    RNo->hotel_name = strdup(hotel_name);
}
void set_reservation_hotel_stars(RNo* RNo, int hotel_stars){
    RNo->hotel_stars = hotel_stars;
}
void set_reservation_city_tax(RNo* RNo, int city_tax){
    RNo->city_tax = city_tax;
}
void set_reservation_begin_date(RNo* RNo, const char* begin_date){
    RNo->begin_date = strdup(begin_date);
}
void set_reservation_end_date(RNo* RNo, const char* end_date){
    RNo->end_date = strdup(end_date);
}
void set_reservation_price_per_night(RNo* RNo, int price_per_night){
    RNo->price_per_night = price_per_night;
}
void set_reservation_includes_breakfast(RNo* RNo, const char* includes_breakfast){
    RNo->includes_breakfast = strdup(includes_breakfast);
}
void set_reservation_rating(RNo* RNo, int rating){
    RNo->rating = rating;
}
void set_reservation_validation(RNo* RNo, int validation){
    RNo->validation = validation;
}
void set_reservation_prox(RNo* RNo){
    RNo->prox = NULL;
}

struct RList {
    RNo *init;
};

RList reservation_array_valid[NUM_LINHAS_VALID_RESERVATION];

const RList* get_reservation_array_valid(int pos) {
    return &reservation_array_valid[pos];
}
const RNo* getRListInit(const RList* RList){
    return RList->init;
}

RNo* create_reservation(char parametros[][FIELD_SIZE]) {  
    RNo* nova = malloc(sizeof(struct RNo));  
    set_reservation_id(nova, parametros[0]);
    set_reservation_user_id(nova, parametros[1]);                                           
    set_reservation_hotel_id(nova, parametros[2]);                                           
    set_reservation_hotel_name(nova, parametros[3]);                                           
    set_reservation_hotel_stars(nova, atoi(parametros[4]));                                           
    set_reservation_city_tax(nova, atoi(parametros[5]));                                           
    set_reservation_begin_date(nova, parametros[7]);                                           
    set_reservation_end_date(nova, parametros[8]);                                           
    set_reservation_price_per_night(nova, atoi(parametros[9]));                                           
    set_reservation_includes_breakfast(nova, parametros[10]);                                           
    set_reservation_rating(nova, atoi(parametros[12]));                                           
    set_reservation_validation(nova, 1);                                           
    set_reservation_prox(nova);                                           
    return nova;
}

const char* get_reservation_id(const RNo* RNo){
    return RNo->id;
}
const char* get_reservation_user_id(const RNo* RNo){
    return RNo->user_id;
}
const char* get_reservation_hotel_id(const RNo* RNo){
    return RNo->hotel_id;
}
const char* get_reservation_hotel_name(const RNo* RNo){
    return RNo->hotel_name;
}
int get_reservation_hotel_stars(const RNo* RNo){
    return RNo->hotel_stars;
}
int get_reservation_city_tax(const RNo* RNo){
    return RNo->city_tax;
}
const char* get_reservation_begin_date(const RNo* RNo){
    return RNo->begin_date;
}
const char* get_reservation_end_date(const RNo* RNo){
    return RNo->end_date;
}
int get_reservation_price_per_night(const RNo* RNo){
    return RNo->price_per_night;
}
const char* get_reservation_includes_breakfast(const RNo* RNo){
    return RNo->includes_breakfast;
}
int get_reservation_rating(const RNo* RNo){
    return RNo->rating;
}
int get_reservation_validation(const RNo* RNo){
    return RNo->validation;
}
const RNo* get_reservation_prox(const RNo* RNo){
    return RNo->prox;
}

void reservations_hash_sort(RList *reservation_array_valid, RList list) {
    int ind = found_index_reservations(get_reservation_id(list.init));
    if (reservation_array_valid[ind].init == NULL) { //esta tudo NULL (vacio)
        reservation_array_valid[ind] = list;
    }
    else {
        list.init->prox = reservation_array_valid[ind].init;
        reservation_array_valid[ind] = list;
    }
}

void create_array_reservations(char parametros[][FIELD_SIZE]){
    int val = validate_reservation(parametros);
    if (val == 1){  //se essa linha for válida os seus parâmetros são armazenados no array de reservas válidas
        int id_reservation_table = found_index_reservations(parametros[0]);
        RNo* nova = create_reservation(parametros);
        RList list;
        list.init = nova;
        int ind = found_index_users(parametros[1]);
        UNo *pointer = user_array_valid[ind].init;
        while (pointer != NULL) {
            if (strcmp(get_reservation_user_id(list.init), get_user_id(pointer)) == 0) {
                pointer->list_reservations = realloc(pointer->list_reservations, (pointer->reservations+1)*sizeof(int));
                pointer->list_reservations[pointer->reservations] = id_reservation_table;
                pointer->reservations++;
                pointer->total_spent += total_price(get_reservation_price_per_night(list.init), nights(get_reservation_begin_date(list.init), get_reservation_end_date(list.init)), get_reservation_city_tax(list.init));
                break;
            }
            else pointer = pointer->prox;
        }
        int ind_hotel = found_index_hotels(parametros[2]);
        HNo *pointer_h = hotel_array_valid[ind_hotel].init;
        pointer_h->list_reservations = realloc(pointer_h->list_reservations, (pointer_h->reservations+1)*sizeof(int));
        pointer_h->list_reservations[pointer_h->reservations] = id_reservation_table;
        pointer_h->reservations++;
        reservations_hash_sort(reservation_array_valid, list);

        //query 10
        if(compare_date(parametros[7], "2023/10/01")!=1){
            YNo *ypointer;
            char *str;
            int ind_year = found_index_year(year(parametros[7]));
            ypointer = year_array_valid[ind_year].init;
            ypointer->reservations++;

            str = year_month(parametros[7]);
            int ind_year_month = found_index_year_month_day(str);
            free(str);
            ypointer = year_array_valid[ind_year_month].init;
            ypointer->reservations++;

            str = year_month_day(parametros[7]);
            int ind_year_month_day = found_index_year_month_day(str);
            free(str);
            ypointer = year_array_valid[ind_year_month_day].init;
            ypointer->reservations++;
        }
        
    }   
    else{
        complete_files_reservations(parametros);
    }
}

void free_list_reservation(const RNo *nodo) {
    const RNo* atual = nodo;
    const RNo* next;
    while(atual!=NULL){
        next = atual->prox;
        free((char*)atual->id);
        free((char*)atual->user_id);
        free((char*)atual->hotel_id);
        free((char*)atual->hotel_name);
        free((char*)atual->begin_date);
        free((char*)atual->end_date);
        free((char*)atual->includes_breakfast);
        free((char*)atual);
        atual = next;
    }
}

void perform_operation_on_reservation_array(void (*operation)(RList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_RESERVATION; i++) {
        operation(&reservation_array_valid[i]);
    }
}

void free_reservation_element(RList *reservation_element) {
    free_list_reservation(getRListInit(reservation_element));
}

void free_reservation_valid() {
    perform_operation_on_reservation_array(free_reservation_element);
}










////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////
////////////////////////AIRPORT///////////////////////////


struct ANo {
    char *name;
    int flights2023;
    int passengers2023;
    int *list_flights2023;
    int flights2022;
    int passengers2022;
    int *list_flights2022;
    int flights2021;
    int passengers2021;
    int *list_flights2021;
    int *list_atrasos;
    int atrasos;
    int mediana;
};

void set_airport_name(ANo* ANo){
    ANo->name = NULL;
}
void set_airport_passengers2023(ANo* ANo, int passengers){
    ANo->passengers2023 = passengers;
}
void set_airport_flights2023(ANo* ANo, int flights){
    ANo->flights2023 = flights;
}
void set_airport_list_flights2023(ANo* ANo){
    ANo->list_flights2023 = NULL;
}
void set_airport_passengers2022(ANo* ANo, int passengers){
    ANo->passengers2022 = passengers;
}
void set_airport_flights2022(ANo* ANo, int flights){
    ANo->flights2022 = flights;
}
void set_airport_list_flights2022(ANo* ANo){
    ANo->list_flights2022 = NULL;
}
void set_airport_passengers2021(ANo* ANo, int passengers){
    ANo->passengers2021 = passengers;
}
void set_airport_flights2021(ANo* ANo, int flights){
    ANo->flights2021 = flights;
}
void set_airport_list_flights2021(ANo* ANo){
    ANo->list_flights2021 = NULL;
}
void set_airport_list_atrasos(ANo* ANo){
    ANo->list_atrasos = NULL;
}
void set_airport_atrasos(ANo* ANo, int atrasos){
    ANo->atrasos = atrasos;
}
void set_airport_mediana(ANo* ANo, int mediana){
    ANo->mediana = mediana;
}


struct AList {
    ANo *init;
};

AList airport_array_valid[NUM_LINHAS_VALID_AIRPORT];

const AList* get_airport_array_valid(int pos) {
    return &airport_array_valid[pos];
}
const ANo* getAListInit(const AList* AList){
    return AList->init;
}
const char* get_airport_name(const ANo* ANo){
    return ANo->name;
}
const int* get_airport_list_flights2023(const ANo* ANo){
    return ANo->list_flights2023;
}
int get_airport_flights2023(const ANo* ANo){
    return ANo->flights2023;
}
int get_airport_passengers2023(const ANo* ANo){
    return ANo->passengers2023;
}
const int* get_airport_list_flights2022(const ANo* ANo){
    return ANo->list_flights2022;
}
int get_airport_flights2022(const ANo* ANo){
    return ANo->flights2022;
}
int get_airport_passengers2022(const ANo* ANo){
    return ANo->passengers2022;
}
const int* get_airport_list_flights2021(const ANo* ANo){
    return ANo->list_flights2021;
}
int get_airport_flights2021(const ANo* ANo){
    return ANo->flights2021;
}
int get_airport_passengers2021(const ANo* ANo){
    return ANo->passengers2021;
}
int get_airport_atrasos(const ANo* ANo){
    return ANo->atrasos;
}
const int* get_airport_list_atrasos(const ANo* ANo){
    return ANo->list_atrasos;
}
int get_airport_mediana(const ANo* ANo){
    return ANo->mediana;
}

void create_array_airport() {
    for (int i = 0; i < NUM_LINHAS_VALID_AIRPORT; i++) { 
        ANo* nova = malloc(sizeof(struct ANo));
        set_airport_name(nova);
        set_airport_passengers2023(nova, 0);
        set_airport_flights2023(nova, 0);                                           
        set_airport_list_flights2023(nova);
        set_airport_passengers2022(nova, 0);
        set_airport_flights2022(nova, 0);                                           
        set_airport_list_flights2022(nova);
        set_airport_passengers2021(nova, 0);
        set_airport_flights2021(nova, 0);                                           
        set_airport_list_flights2021(nova);
        set_airport_atrasos(nova, 0);
        set_airport_list_atrasos(nova);
        set_airport_mediana(nova, 0);
        airport_array_valid[i].init = nova;
    }
    return;
}

void free_list_airport(const ANo *nodo) {
    const ANo* atual = nodo;
    free((char*)atual->name);
    free((int*)atual->list_flights2023);
    free((int*)atual->list_flights2022);
    free((int*)atual->list_flights2021);
    free((int*)atual->list_atrasos);
    free((char*)atual);
}

void perform_operation_on_airport_array(void (*operation)(AList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_AIRPORT; i++) {
        operation(&airport_array_valid[i]);
    }
}

void free_airport_element(AList *airport_element) {
    free_list_airport(getAListInit(airport_element));
}

void free_airport_valid() {
    perform_operation_on_airport_array(free_airport_element);
}


void ordena_atrasos(int num) {
    int tam;
    for (int i = 0; i < num; i++) {
        if(get_airport_atrasos(getAListInit(get_airport_array_valid(i))) != 0) {
            tam = get_airport_atrasos(getAListInit(get_airport_array_valid(i)));
            qsort(airport_array_valid[i].init->list_atrasos, tam, sizeof(int), comparar_numbers);
        }
    }
}

void mediana_airport(int num) {
    int tam, mediana;
    for (int i = 0; i < num; i++) {
        if(get_airport_atrasos(getAListInit(get_airport_array_valid(i))) != 0) {
            tam = get_airport_atrasos(getAListInit(get_airport_array_valid(i)));
            if (tam % 2 == 0) {
                mediana = (get_airport_list_atrasos(getAListInit(get_airport_array_valid(i)))[tam/2 - 1] + get_airport_list_atrasos(getAListInit(get_airport_array_valid(i)))[tam/2]) / 2;
                set_airport_mediana(airport_array_valid[i].init, mediana);
            }
            else {
                mediana = get_airport_list_atrasos(getAListInit(get_airport_array_valid(i)))[tam/2];
                set_airport_mediana(airport_array_valid[i].init, mediana);
            }
        }
    }
}





////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////
////////////////////////FLIGHTS///////////////////////////

struct FNo {
    char *id;
    char *airline;
    char *plane_model;
    char *total_seats;
    char *origin; 
    char *destination; 
    char *schedule_departure_date;
    char *schedule_arrival_date;
    char *real_departure_date;
    char *real_arrival_date;
    int passengers;
    int delay_time;
    int validation;
    struct FNo *prox;
};

void set_flight_id(FNo* FNo, const char* id){
    FNo->id = strdup(id);
}
void set_flight_airline(FNo* FNo, const char* airline){
    FNo->airline = strdup(airline);
}
void set_flight_plane_model(FNo* FNo, const char* plane_model){
    FNo->plane_model = strdup(plane_model);
}
void set_flight_total_seats(FNo* FNo, const char* total_seats){
    FNo->total_seats = strdup(total_seats);
}
void set_flight_origin(FNo* FNo, const char* origin){
    FNo->origin = strdup(origin);
}
void set_flight_destination(FNo* FNo, const char* destination){
    FNo->destination = strdup(destination);
}
void set_flight_schedule_departure_date(FNo* FNo, const char* schedule_departure_date){
    FNo->schedule_departure_date = strdup(schedule_departure_date);
}
void set_flight_schedule_arrival_date(FNo* FNo, const char* schedule_arrival_date){
    FNo->schedule_arrival_date = strdup(schedule_arrival_date);
}
void set_flight_real_departure_date(FNo* FNo, const char* real_departure_date){
    FNo->real_departure_date = strdup(real_departure_date);
}
void set_flight_real_arrival_date(FNo* FNo, const char* real_arrival_date){
    FNo->real_arrival_date = strdup(real_arrival_date);
}
void set_flight_passengers(FNo* FNo, int passengers){
    FNo->passengers = passengers;
}
void set_flight_delay_time(FNo* FNo, int delay_time){
    FNo->delay_time = delay_time;
}
void set_flight_validation(FNo* FNo, int validation){
    FNo->validation = validation;
}
void set_flight_prox(FNo* FNo){
    FNo->prox = NULL;
}

struct FList {
    FNo *init;
};

FList flight_array_valid[NUM_LINHAS_VALID_FLIGHT];

const FList* get_flight_array_valid(int pos) {
    return &flight_array_valid[pos];
}

const FNo* getFListInit(const FList* FList){
    return FList->init;
}

FNo* create_flight(char parametros[][FIELD_SIZE]) {           
    FNo* nova = malloc(sizeof(struct FNo));   
    set_flight_id(nova, parametros[0]);                                           
    set_flight_airline(nova, parametros[1]);
    set_flight_plane_model(nova, parametros[2]);
    set_flight_total_seats(nova, parametros[3]);
    set_flight_origin(nova, parametros[4]);
    set_flight_destination(nova, parametros[5]);
    set_flight_schedule_departure_date(nova, parametros[6]);
    set_flight_schedule_arrival_date(nova, parametros[7]);
    set_flight_real_departure_date(nova, parametros[8]);
    set_flight_real_arrival_date(nova, parametros[9]);
    set_flight_passengers(nova, 0);
    set_flight_delay_time(nova, 0);
    set_flight_validation(nova, 1);
    set_flight_prox(nova);
    return nova;
}

const char* get_flight_id(const FNo* FNo){
    return FNo->id;
}
const char* get_flight_airline(const FNo* FNo){
    return FNo->airline;
}
const char* get_flight_plane_model(const FNo* FNo){
    return FNo->plane_model;
}
const char* get_flight_total_seats(const FNo* FNo){
    return FNo->total_seats;
}
const char* get_flight_origin(const FNo* FNo){
    return FNo->origin;
}
const char* get_flight_destination(const FNo* FNo){
    return FNo->destination;
}
const char* get_flight_schedule_departure_date(const FNo* FNo){
    return FNo->schedule_departure_date;
}
const char* get_flight_schedule_arrival_date(const FNo* FNo){
    return FNo->schedule_arrival_date;
}
const char* get_flight_real_departure_date(const FNo* FNo){
    return FNo->real_departure_date;
}
const char* get_flight_real_arrival_date(const FNo* FNo){
    return FNo->real_arrival_date;
}
int get_flight_passengers(const FNo* FNo){
    return FNo->passengers;
}
int get_flight_delay_time(const FNo* FNo){
    return FNo->delay_time;
}
const FNo* get_flight_prox(const FNo* FNo){
    return FNo->prox;
}


void flights_hash_sort(FList *flight_array_valid, FList list) {
    int ind = found_index_flights(get_flight_id(list.init));
    if (flight_array_valid[ind].init == NULL) { //esta tudo NULL (vacio)
        flight_array_valid[ind] = list;
    }
    else {
        list.init->prox = flight_array_valid[ind].init;
        flight_array_valid[ind] = list;
    }
}

void create_array_flights(char parametros[][FIELD_SIZE]){
    int val = validate_flight(parametros);
    if (val == 1){    //se essa linha for válida os seus parâmetros são armazenados no array de voos válidos
        FNo* nova = create_flight(parametros);
        FList list;
        list.init = nova;
        char *origin_cpy = strdup (parametros[4]);//origin
        toUpperCase (origin_cpy);
        int ind_org = found_index_airport(origin_cpy), ind_f = found_index_flights(parametros[0]);
        free (origin_cpy);
        char *destination_cpy = strdup (parametros[5]);//destination
        toUpperCase (destination_cpy);
        int ind_dest = found_index_airport(destination_cpy);
        free (destination_cpy);
        
        int ind_year = found_index_year(year(parametros[6]));
        YNo *pointer_y = year_array_valid[ind_year].init;
        if(pointer_y->airports == 0){
            pointer_y->list_airports = realloc(pointer_y->list_airports, (pointer_y->airports+1)*sizeof(int));
            pointer_y->list_airports[pointer_y->airports] = ind_org;
            pointer_y->airports++;
            pointer_y->list_airports = realloc(pointer_y->list_airports, (pointer_y->airports+1)*sizeof(int));
            pointer_y->list_airports[pointer_y->airports] = ind_dest;
            pointer_y->airports++;
        }
        else{
            for(int i = 0; i<pointer_y->airports; i++){
                if (pointer_y->list_airports[i] == ind_org) break;
                if (i == pointer_y->airports-1){
                    pointer_y->list_airports = realloc(pointer_y->list_airports, (pointer_y->airports+1)*sizeof(int));
                    pointer_y->list_airports[pointer_y->airports] = ind_org;
                    pointer_y->airports++;
                }
            }
            for(int i = 0; i<pointer_y->airports; i++){
                if (pointer_y->list_airports[i] == ind_dest) break;
                if (i == pointer_y->airports-1){
                    pointer_y->list_airports = realloc(pointer_y->list_airports, (pointer_y->airports+1)*sizeof(int));
                    pointer_y->list_airports[pointer_y->airports] = ind_dest;
                    pointer_y->airports++;
                }
            }
        }

        ANo *pointer = airport_array_valid[ind_org].init;
        char *nameUP = strdup(parametros[4]);
        toUpperCase(nameUP);
        if (pointer->flights2023 + pointer->flights2022 + pointer->flights2021 == 0) pointer->name = strdup(nameUP);
        free(nameUP);
        if (year(parametros[6]) == 2023){
            pointer->list_flights2023 = realloc(pointer->list_flights2023, (pointer->flights2023+1)*sizeof(int));
            pointer->list_flights2023[pointer->flights2023] = ind_f;
            pointer->flights2023++;
        }
        if (year(parametros[6]) == 2022){
            pointer->list_flights2022 = realloc(pointer->list_flights2022, (pointer->flights2022+1)*sizeof(int));
            pointer->list_flights2022[pointer->flights2022] = ind_f;
            pointer->flights2022++;
        }
        if (year(parametros[6]) == 2021){
            pointer->list_flights2021 = realloc(pointer->list_flights2021, (pointer->flights2021+1)*sizeof(int));
            pointer->list_flights2021[pointer->flights2021] = ind_f;
            pointer->flights2021++;
        }
        ANo *pointerDest = airport_array_valid[ind_dest].init;
        char *nameUP2 = strdup(parametros[5]);
        toUpperCase(nameUP2);
        if (pointerDest->flights2023 + pointerDest->flights2022 + pointerDest->flights2021 == 0) pointerDest->name = strdup(nameUP2);
        free(nameUP2);
        toUpperCase(pointer->name);
        if (year(parametros[6]) == 2023){
            pointerDest->list_flights2023 = realloc(pointerDest->list_flights2023, (pointerDest->flights2023+1)*sizeof(int));
            pointerDest->list_flights2023[pointerDest->flights2023] = ind_f;
            pointerDest->flights2023++;
        }
        if (year(parametros[6]) == 2022){
            pointerDest->list_flights2022 = realloc(pointerDest->list_flights2022, (pointerDest->flights2022+1)*sizeof(int));
            pointerDest->list_flights2022[pointerDest->flights2022] = ind_f;
            pointerDest->flights2022++;
        }
        if (year(parametros[6]) == 2021){
            pointerDest->list_flights2021 = realloc(pointerDest->list_flights2021, (pointerDest->flights2021+1)*sizeof(int));
            pointerDest->list_flights2021[pointerDest->flights2021] = ind_f;
            pointerDest->flights2021++;
        }

        pointer->list_atrasos = realloc(pointer->list_atrasos, (pointer->atrasos+1) * sizeof(int));
        pointer->list_atrasos[pointer->atrasos] = delay(parametros[6], parametros[8]);
        pointer->atrasos++;

        //query 10
        if(compare_date(parametros[6], "2023/10/01")!=1){
            YNo *ypointer;
            char *str;
            ind_year = found_index_year(year(parametros[6]));
            ypointer = year_array_valid[ind_year].init;
            ypointer->flights++;

            str = year_month(parametros[6]);
            int ind_year_month = found_index_year_month_day(str);
            free(str);
            ypointer = year_array_valid[ind_year_month].init;
            ypointer->flights++;

            str = year_month_day(parametros[6]);
            int ind_year_month_day = found_index_year_month_day(str);
            free(str);
            ypointer = year_array_valid[ind_year_month_day].init;
            ypointer->flights++;
        }

        create_array_atrasos(list.init, NUM_LINHAS_VALID_FLIGHT, parametros);
        flights_hash_sort(flight_array_valid, list);
    }
    else{
        complete_files_flights(parametros);
    }
}

void free_list_flight(const FNo *nodo) {
    const FNo* atual = nodo;
    const FNo* next;
    while(atual!=NULL) {
        next = atual->prox;
        free((char*)atual->id);
        free((char*)atual->airline);
        free((char*)atual->plane_model);
        free((char*)atual->total_seats);
        free((char*)atual->origin);
        free((char*)atual->destination);
        free((char*)atual->schedule_departure_date);
        free((char*)atual->schedule_arrival_date);
        free((char*)atual->real_departure_date);
        free((char*)atual->real_arrival_date);
        free((char*)atual);
        atual = next;
    } 
}

void perform_operation_on_flight_array(void (*operation)(FList *)) {
    for (int i = 0; i < NUM_LINHAS_VALID_FLIGHT; i++) {
        operation(&flight_array_valid[i]);
    }
}

void free_flight_element(FList *flight_element) {
    free_list_flight(getFListInit(flight_element));
}

void free_flight_valid() {
    perform_operation_on_flight_array(free_flight_element);
}









////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////
////////////////////////PASSENGERS///////////////////////////

void create_array_passengers(char parametros[][FIELD_SIZE]){
    int ind_u, ind_f, ind_a, val;
    val = validate_passenger(parametros);
    if (val==1){
        ind_u = found_index_users(parametros[1]); //id_u
        UNo *upointer = user_array_valid[ind_u].init;
        while (upointer != NULL) {
            if (strcmp(parametros[1], get_user_id(upointer)) == 0) {
                ind_f = found_index_flights(parametros[0]);
                upointer->list_flights = realloc(upointer->list_flights, (upointer->flights+1)*sizeof(int));
                upointer->list_flights[upointer->flights] = ind_f;
                upointer->flights++;
                break;
            }
            else upointer = upointer->prox;
        }

        ind_f = found_index_flights(parametros[0]); //id_f
        FNo *fpointer = flight_array_valid[ind_f].init;
        while (fpointer != NULL) {
            if (strcmp(parametros[0], get_flight_id(fpointer)) == 0) {
                fpointer->passengers++;

                //query 10
                if(compare_date(fpointer->schedule_departure_date, "2023/10/01")!=1){
                    YNo *ypointer;
                    char *str;
                    int ind_year = found_index_year(year(fpointer->schedule_departure_date));
                    ypointer = year_array_valid[ind_year].init;
                    ypointer->passengers++;

                    str = year_month(fpointer->schedule_departure_date);
                    int ind_year_month = found_index_year_month_day(str);
                    free(str);
                    ypointer = year_array_valid[ind_year_month].init;
                    ypointer->passengers++;

                    str = year_month_day(fpointer->schedule_departure_date);
                    int ind_year_month_day = found_index_year_month_day(str);
                    free(str);
                    ypointer = year_array_valid[ind_year_month_day].init;
                    ypointer->passengers++;
                }

                break;
            }
            else fpointer = fpointer->prox;
        }
        ind_a = found_index_airport(fpointer->origin); //id_a
        ANo *apointer = airport_array_valid[ind_a].init;
        int year_aux = year(fpointer->schedule_departure_date);
        if (year_aux == 2023) apointer->passengers2023++;
        if (year_aux == 2022) apointer->passengers2022++;
        if (year_aux == 2021) apointer->passengers2021++;
        int ind_b = found_index_airport(fpointer->destination); //id_b
        ANo *apointer2 = airport_array_valid[ind_b].init;
        int year_aux2 = year(fpointer->schedule_departure_date);
        if (year_aux2 == 2023) apointer2->passengers2023++;
        if (year_aux2 == 2022) apointer2->passengers2022++;
        if (year_aux2 == 2021) apointer2->passengers2021++;


    }
    else{
        complete_files_passengers(parametros);
    }
}


void aux_query10(char parametros[][FIELD_SIZE]){
    int ind_u = found_index_users(parametros[0]);
    UNo *upointer = user_array_valid[ind_u].init;
    while (upointer != NULL) {
        if (strcmp(parametros[0], get_user_id(upointer)) == 0) {
            int aux[90054] = {0};
            int* list_flights = upointer->list_flights;
            for(int i = 0; i<get_user_flights(upointer); i++){
                if(compare_date(get_flight_schedule_departure_date(getFListInit(get_flight_array_valid(list_flights[i]))), "2023/10/01")!=1){
                    YNo *ypointer;
                    int ind_year =  found_index_year(year(flight_array_valid[list_flights[i]].init->schedule_departure_date));
                    char *str = year_month(flight_array_valid[list_flights[i]].init->schedule_departure_date);
                    int ind_year_month = found_index_year_month_day(str);
                    free(str);
                    str = year_month_day(flight_array_valid[list_flights[i]].init->schedule_departure_date);
                    int ind_year_month_day = found_index_year_month_day(str);
                    free(str);
                    ypointer = year_array_valid[ind_year].init;
                    if(aux[ind_year]==0){
                        ypointer->unique_passengers++;
                        aux[ind_year] = 1;
                    }

                    ypointer = year_array_valid[ind_year_month].init;
                    if(aux[ind_year_month]==0){
                        ypointer->unique_passengers++;
                        aux[ind_year_month] = 1;
                    }

                    ypointer = year_array_valid[ind_year_month_day].init;
                    if(aux[ind_year_month_day]==0){
                        ypointer->unique_passengers++;
                        aux[ind_year_month_day] = 1;
                    }
                }
            }
        }
    upointer = upointer->prox;
    }
}