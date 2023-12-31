//módulo de funções auxiliares
//módulo no qual são criadas as funções que irão auxiliar nas queries e no armazenamento dos dados

#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include "../include/Aux_structs.h"

void insertionSort_atrasos(int *atrasos, int num_atrasos);
    //     |->função que ordena o array de atrasos de um aeroporto

int delay(char *schedule, char *real);
    //     |->função responsável por calcular a diferença de segundos entre
    //        a hora estimada de partida e a hora real de partida do voo

int nights(char *begin, char *end);
    //     |->função responsável por calcular o número de noites
    //        disponíveis na reserva de um utilizador

double total_price(char *price_per_night, int nights, char *city_tax);
    //     |->função responsável por calcular os gastos numa reserva

int age_user(char *birth_date);
    //     |->função responsável por calcular a idade de um utilizador

int number_of_flights(char *user);
    //     |->função responsável por calcular o número de voos
    //        em que um utilizador andou

int compare_hotels (const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array das reservas
    //        para o ordenar por data de início (ou id, caso a data seja igual)

int is_date_between (char *date, char *i, char *f);
    //     |->função que verifica se uma data (date) está entre duas outras datas (i e f)

int compare_flights (const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array dos voos
    //        para o ordenar por data de partida (ou id, caso a data seja igual) 

void swap_contador(int *a, int *b);

void swapStrings(char **str1, char **str2);

char *only_date(char *schedule_departure_date);
    //     |->função responsável por retornar apenas a data após ler a data 
    //        prevista de partida que inicialmente também contém as horas

void insertionSort_flights(Flight_aux *flight_aux_array, int size);
    //     |->função responsável por ordenar o array que tem as informações 
    //        de voo em que um passageiro voou

void insertionSort_medianas(Mediana *mediana_array, int num_medianas);
    //     |->função responsável por ordenar o array que tem as medianas 
    //        dos vários aeroportos

int calculate_mediana(int *atrasos, int num_atrasos);
    //     |->função responsável por calcular a mediana de um aeroporto 

int compare_date_time2(char *i, char *f);
    //     |->função que compara duas datas para saber qual a mais antiga

#endif 