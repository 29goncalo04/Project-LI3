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

void create_array_atrasos(Flight nova, int num_linhas_valid_flight, char parametros[][FIELD_SIZE]){
    char *Airport = nova.origin;
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
}


Contador_id *contador_array = NULL;
int num_linhas_contador = 0;

Contador_id create_contador(char parametros[][FIELD_SIZE]){     
    Contador_id novo;                                          
    novo.id_flight = strdup(parametros[0]);
    novo.contador = 0;
    return novo;
}

void create_array_contador(Passenger nova, char parametros[][FIELD_SIZE]){
    if (num_linhas_contador==0){ // Se for a primeira iteração, apenas adicione o novo elemento ao contador_array
        Contador_id novo = create_contador(parametros);
        contador_array = realloc(contador_array, (num_linhas_contador + 1) * sizeof(Contador_id));
        contador_array[num_linhas_contador] = novo;
        num_linhas_contador++;
    }
    else{
        if (atoi(nova.flight_id)-atoi(contador_array[num_linhas_contador-1].id_flight)>1){ //se o ID anterior não é o estritamente anterior ao ID da linha atual  (por exemplo: atual->003, anterior->001)
            int array_vazio = atoi(nova.flight_id)-atoi(contador_array[num_linhas_contador-1].id_flight);
            for (int k = 0; k<array_vazio; k++){
                contador_array = realloc(contador_array, (num_linhas_contador + 1) * sizeof(Contador_id));
                contador_array[num_linhas_contador].id_flight = strdup("");
                contador_array[num_linhas_contador].contador = 0;
                num_linhas_contador++;
            }
        }
        if (strcmp(nova.flight_id, contador_array[num_linhas_contador-1].id_flight)==0){  //se o ID anterior é igual ao da linha atual 
            // Se o ID do voo é o mesmo, apenas atualiza o contador do elemento existente
            if (contador_array[num_linhas_contador - 1].contador == 0) contador_array[num_linhas_contador - 1].contador++;
            contador_array[num_linhas_contador - 1].contador++;
        } else{  // Se o ID do voo é diferente, cria um novo elemento Contador_id e adiciona ao contador_array
        Contador_id novo = create_contador(parametros);
        contador_array = realloc(contador_array, (num_linhas_contador + 1) * sizeof(Contador_id));
        contador_array[num_linhas_contador] = novo;
        num_linhas_contador++;
        }
    }
}