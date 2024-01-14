#include <dirent.h>
#include <unistd.h>

#include "../include/Parser.h"
#include "../include/Aux_functions.h"
#include "../include/Catalogs.h"
#include "../include/Statistics.h"
#include "../include/Output_errors.h"
#include "../include/Hash.h"

FILE *fpassengers;
FILE *freservations;
FILE *fusers;
FILE *fflights;
FILE *arquivo;
int path_error = 0;  //se o caminho é válido path_error = 0

void open_files(char* path){
    char *line = NULL;
    size_t len = 0;
    int j = 0;
    char *aux_passengers = NULL;
    aux_passengers = (char *)malloc(strlen(path) + strlen("/passengers.csv") + 1);
    strcpy(aux_passengers, path);
    strcat(aux_passengers, "/passengers.csv");
    char *aux_flights = NULL;
    aux_flights = (char *)malloc(strlen(path) + strlen("/flights.csv") + 1);
    strcpy(aux_flights, path);
    strcat(aux_flights, "/flights.csv");
    char *aux_reservations = NULL;
    aux_reservations = (char *)malloc(strlen(path) + strlen("/reservations.csv") + 1);
    strcpy(aux_reservations, path);
    strcat(aux_reservations, "/reservations.csv");
    char *aux_users = NULL;
    aux_users = (char *)malloc(strlen(path) + strlen("/users.csv") + 1);
    strcpy(aux_users, path);
    strcat(aux_users, "/users.csv");


    for (int num_ficheiro = 0; num_ficheiro<4; num_ficheiro++) {         //existe um caso específico para cada ficheiro     
        int l = 0;
        switch (num_ficheiro){
            case 3: 
                fpassengers = fopen(aux_passengers, "r");
                start_files_passengers();
                if (fpassengers==NULL){
                    path_error = 1;
                    return;
                }                                                //ficheiro dos passageiros
                while (getline(&line, &len, fpassengers) != -1) {
                    if (l != 0) {
                        char parametros[2][FIELD_SIZE];
                        int j_linha = 0;
                        for (int i = 0; i<2; i++){
                            if (i==0){
                                for (j = 0; line[j_linha] != ';'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                parametros[i][j] = '\0';
                                j_linha++;
                            }
                            else{           //parte do código responsável por guardar o último parâmetro (user_id)
                                for (j = 0; line[j_linha] != '\0' && line[j_linha] != '\n'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                parametros[i][j] = '\0';
                            }
                        }
                        create_array_passengers(parametros);
                    } else {
                        l++;
                    }
                }
                fclose(fpassengers);
                printf("pasajeros listo\n");
                break;
            
            case 1:   
                //init_flight_array(flight_array_valid);
                create_array_airport();
                fflights = fopen(aux_flights, "r");
                start_files_flights();
                if (fflights==NULL){
                    path_error = 1;
                    return;
                }                                                 //ficheiro dos voos
                while (getline(&line, &len, fflights) != -1) {               //o programa vai ler linha a linha do ficheiro aberto
                    if (l != 0) {
                        char parametros[13][FIELD_SIZE];                       //o número de parâmetros varia de ficheiro para ficheiro
                        int j_linha = 0;

                        for (int i = 0; i<13; i++){
                            if (i<12){
                                for (j = 0; line[j_linha] != ';'; j_linha++, j++) {     //o programa copia caracter a caracter 
                                    parametros[i][j] = line[j_linha];                   //para o respetivo parâmetro até encontrar um ";"
                                }
                                parametros[i][j] = '\0';
                                j_linha++;
                            }
                            else{
                                if (line[j_linha] != '\0') {          //o programa apenas copia os caracteres para o parâmetro "notes"         
                                    j = 0;                           //caso existam notes para ser lidas nessa linha, senão o parâmetro fica ""
                                    while (line[j_linha] != '\0' && line[j_linha] != '\n') {
                                        parametros[12][j] = line[j_linha];
                                        j_linha++;
                                        j++;
                                    }
                                    parametros[12][j] = '\0';
                                }
                                else parametros[12][j] = '\0';
                            }
                        }
                        create_array_flights(parametros);
                    } else {
                        l++;
                    }
                }
                for (int i = 0; i<num_Atrasos; i++){
                    insertionSort_atrasos(Atrasos_array[i].atraso, Atrasos_array[i].num_atrasos);
                }
                fclose(fflights);
                printf("vuelos listo\n");
                break;

            case 2:  
                //init_reservation_array(reservation_array_valid);
                create_array_hotels();
                freservations = fopen(aux_reservations, "r"); 
                start_files_reservations();                                         //ficheiro das reservas
                if (freservations==NULL){
                    path_error = 1;
                    return;
                }
                while (getline(&line, &len, freservations) != -1) {
                    if (l != 0) {
                        char parametros[14][FIELD_SIZE];
                        int j_linha = 0;
                        for (int i = 0; i<14; i++){
                            if (i<13){
                                for (j = 0; line[j_linha] != ';'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                if (j == 0 && i == 10 && line[j_linha] == ';') {
                                    parametros[i][j] = ' ';
                                    parametros[i][j+1] = '\0';
                                }
                                else {
                                    parametros[i][j] = '\0';
                                }
                                j_linha++;
                            }
                            else{
                                if (line[j_linha] != '\0') {     //o programa apenas copia os caracteres para o parâmetro "comment"         
                                    j = 0;                       //caso existam comentários para ser lidos nessa linha, senão o parâmetro fica ""
                                    while (line[j_linha] != '\0' && line[j_linha] != '\n') {
                                        parametros[13][j] = line[j_linha];
                                        j_linha++;
                                        j++;
                                    }
                                    parametros[13][j] = '\0';
                                }
                            }
                        }
                        create_array_reservations(parametros);
                    } else {
                        l++;
                    }
                }
                fclose(freservations);
                printf("reservas listo\n");
                break;
            
            case 0:
                //init_user_array(user_array_valid);
                fusers = fopen(aux_users, "r");                                                 //ficheiro dos utilizadores
                start_files_users();
                if (fusers==NULL){
                    path_error = 1;
                    return;
                }
                while (getline(&line, &len, fusers) != -1) {
                    if (l != 0) {
                        char parametros[12][FIELD_SIZE];
                        int j_linha = 0;
                        for (int i = 0; i<12; i++){
                            if (i<11){
                                for (j = 0; line[j_linha] != ';'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                parametros[i][j] = '\0';
                                j_linha++;
                            }
                            else{              //parte do código responsável por guardar o último parâmetro (account_status)
                                for (j = 0; line[j_linha] != '\0' && line[j_linha] != '\n'; j_linha++, j++) {
                                    parametros[i][j] = line[j_linha];
                                }
                                parametros[i][j] = '\0';
                            }
                        }
                        create_array_users(parametros);
                    } else {
                        l++;
                    }
                }
                fclose(fusers);
                printf("users listo\n");
                break;          
        }
    }
    free(aux_passengers);
    free(aux_flights);
    free(aux_users);
    free(aux_reservations);
    free(line);
}