//módulo de funções auxiliares
//módulo no qual são criadas as funções que irão auxiliar nas queries e no armazenamento dos dados

#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H


int year(char* date);
char* year_month(char* date);
char* year_month_day(char* date);

int delay(const char *schedule, const char *real);
    //     |->função responsável por calcular a diferença em segundos entre
    //        a hora estimada de partida e a hora real de partida do voo

int nights(const char *begin, const char *end);
    //     |->função responsável por calcular o número de noites
    //        disponíveis na reserva de um utilizador

int nights_between (const char *begin_res, const char* end_res, char* begin_arg, char* end_arg);
    //     |->função responsável por calcular o número de noites
    //        de uma reserva entre duas datas

double total_price(int price_per_night, int nights, int city_tax);
    //     |->função responsável por calcular os gastos numa reserva

int age_user(const char *birth_date);
    //     |->função responsável por calcular a idade de um utilizador

int compare_numbers(const void *a, const void *b);
    //     |->função que compara dois números

int compare_medianas(const void *a, const void *b);
    //     |->função que compara duas medianas

int compare_reservations (const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array das reservas
    //        para o ordenar por data de início (ou id, caso a data seja igual)

int compare_flights (const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array dos voos
    //        para o ordenar por data de início (ou id, caso a data seja igual)

int compare_airports2023 (const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array dos aeroportos
    //        para o ordenar por data de partida estimada (ou id, caso a data seja igual)
int compare_airports2022 (const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array dos aeroportos
    //        para o ordenar por data de partida estimada (ou id, caso a data seja igual)
int compare_airports2021 (const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array dos aeroportos
    //        para o ordenar por data de partida estimada (ou id, caso a data seja igual)

int compare_users(const void *a, const void *b);
    //     |->função responsável por comparar dois elementos do array dos utilizadores
    //        para o ordenar nome

int is_date_between (const char *date, const char *i, const char *f);
    //     |->função que verifica se uma data (date) está entre duas outras datas (i e f)

void swap_contador(int *a, int *b);
    //     |->função que troca o conteúdo de dois inteiros

void swapStrings(char **str1, char **str2);
    //     |->função que troca o conteúdo de duas strings

char *only_date(char *schedule_departure_date);
    //     |->função responsável por retornar apenas a data após ler a data 
    //        prevista de partida que inicialmente também contém as horas

char *only_date2(const char *schedule_departure_date);
    //     |->função que retorna apenas a data de uma data com horas

int compare_date_time2(char *i, char *f);
    //     |->função que compara duas datas para saber qual a mais antiga

int is_prime(int num);
    //     |->função que verifica se num é primo

int find_near_prime(int num);
    //     |->função que procura o número primo mais perto de num


#endif 