//módulo para as estatísticas
//módulo que efetua relações entre as várias entidades, proporcionando
//um acesso mais rápido a dados e resultados pedidos nas queries do programa

#ifndef STATISTICS_H
#define STATISTICS_H

#include "../include/Catalogs.h"

typedef struct{  //struct com os aeroportos e os respetivos atrasos dos voos com origem nesse aeroporto
    char *airport;
    int *atraso;
    int num_atrasos;
} Atrasos;

extern int num_Atrasos;
extern Atrasos *Atrasos_array;

Atrasos create_atrasos (char *airport, int atraso);
    //     |->função que cria um elemento individual do array de atrasos
    //        que guarda os atrasos respetivos de cada aeroporto

void adicionar_atrasos(Atrasos *atrasos, int novo_atraso);
    //     |->função que insere o atraso de um voo na respetiva posição do array de atrasos que contém
    //        o nome desse aeroporto e os respetivos atrasos de voos com origem nesse aeroporto

void create_array_atrasos(Flight nova, int num_linhas_valid_flight, char parametros[][FIELD_SIZE]);

typedef struct {       //struct com os dados do array de contadores
    char *id_flight;
    int contador;
} Contador_id;

extern int num_linhas_contador;
extern Contador_id *contador_array;

Contador_id create_contador(char parametros[][FIELD_SIZE]);
    //     |->função que cria um elemento individual do array de contadores
    //        que guarda o número de passageiros num determinado voo

void create_array_contador(Passenger nova, char parametros[][FIELD_SIZE]);

#endif