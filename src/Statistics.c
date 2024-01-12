#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Statistics.h"
#include "../include/Catalogs.h"
#include "../include/Aux_validation.h"
#include "../include/Aux_functions.h"

Atrasos *Atrasos_array = NULL;
int num_Atrasos = 0;

Atrasos create_atrasos (char *airport, int atraso){
    Atrasos novo;
    novo.airport = strdup(airport);
    novo.atraso = malloc(sizeof(int));
    novo.atraso[0] = atraso;
    novo.num_atrasos = 1;
    return novo;
}

void adicionar_atrasos(Atrasos *atrasos, int novo_atraso){    //para o módulo de estatísticas
    atrasos->atraso = realloc(atrasos->atraso, (atrasos->num_atrasos + 1) * sizeof(int));
    atrasos->atraso[atrasos->num_atrasos] = novo_atraso;
    atrasos->num_atrasos++; 
}

void create_array_atrasos(FNo* nova, int num_linhas_valid_flight, char parametros[][FIELD_SIZE]){
    const char *Airport_aux = get_flight_origin(nova);
    char *Airport = strdup(Airport_aux);
    toUpperCase(Airport);
    int found = 0;   //variável auxiliar para dizer se o aeroporto foi encontrado ou não
    if (num_linhas_valid_flight == 0){   //se for a primeira linha a ser lida
        Atrasos novo = create_atrasos(Airport, delay(parametros[6], parametros[8]));
        Atrasos_array = realloc(Atrasos_array, (num_Atrasos + 1) * sizeof(Atrasos));
        Atrasos_array[num_Atrasos] = novo;
        num_Atrasos++; 
    }
    else{
        for (int i = 0; i<num_Atrasos; i++){
            if (strcmp(Airport, Atrasos_array[i].airport) == 0){    //caso esse aeoroporto lido já esteja no array de atrasos então é só inserir o respetivo atraso no aeroporto correspondente
                adicionar_atrasos(&Atrasos_array[i], delay(parametros[6], parametros[8]));
                found = 1;
                break;
            }
        }
        if (found==0){   //não encontrou o aeroporto no array de atrasos
            Atrasos novo = create_atrasos(Airport, delay(parametros[6], parametros[8]));
            Atrasos_array = realloc(Atrasos_array, (num_Atrasos + 1) * sizeof(Atrasos));
            Atrasos_array[num_Atrasos] = novo;
            num_Atrasos++;  
        }
    }
    free(Airport);
}