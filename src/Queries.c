#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/Data_Types_&_Data_Structures.h"
#include "../include/Parser.h"
#include "../include/Validation.h"
#include "../include/Queries.h"

FILE *input;  //ficheiro dos comandos das queries
FILE *output;

int delay(char *schedule, char *real){ //2021/07/01 05:56:50  !!!!  2021/07/01 06:56:50
    int atraso = 0, verdadeira = 0, prevista = 0;
    verdadeira = (real[11]-'0')*36000 + (real[12]-'0')*3600 + (real[14]-'0')*600 + (real[15]-'0')*60 + (real[17]-'0')*10 + (real[18]-'0');
    prevista = (schedule[11]-'0')*36000 + (schedule[12]-'0')*3600 + (schedule[14]-'0')*600 + (schedule[15]-'0')*60 + (schedule[17]-'0')*10 + (schedule[18]-'0');
    atraso = verdadeira-prevista;
    return atraso;
}

int nights(char *begin, char *end){  //2021/07/01   !!!!!   2021/07/03
    int noites = 0, inicio = 0, fim = 0;
    inicio = (begin[8]-'0')*10 + (begin[9]-'0');
    fim = (end[8]-'0')*10 + (end[9]-'0');
    noites = fim-inicio;
    return noites;
}

double total_price(char *price_per_night, int nights, char *city_tax){
    double price = 0;
    price = (double)(atof(price_per_night)*nights) + ((double)(atof(price_per_night)*nights*atof(city_tax)) / 100) ;
    return price;
}

int age_user(char *birth_date){  //1979/11/27
    int ano = 0, mes = 0, dia = 0, age = 0;
    ano = (birth_date[0]-'0')*1000 + (birth_date[1]-'0')*100 + (birth_date[2]-'0')*10 + (birth_date[3]-'0');
    mes = (birth_date[5]-'0')*10 + (birth_date[6]-'0');
    dia = (birth_date[8]-'0')*10 + (birth_date[9]-'0');
    age = (2023-ano);
    if (10 < mes || (10 == mes && 1 < dia)) age--;
    return age;
}
/*
int number_of_flights(){
    int flights = 0,
    for (int l = 0; l<num_linhas[0]; l++){   //procura o id do utilizador no array dos passageiros para ver em quantos voos ele andou 
        if (strcmp(user_array[wanted_id].id, passenger_array[l].user_id)==0) flights++;
    }
}*/

void query1(char *line, int i, int n){
    int wanted_id = -1, index_line = i, wanted_user_id = -1;//, wanted_id_2 = -1;
    for (; line[index_line]==' ' || line[index_line]=='"'; index_line++);   //encontra o indice do primeiro argumento ignorando os espaços e as aspas
    int argument_length = 0;
    for (int j=index_line; line[j]!='\0' && line[j]!='\n'; j++, argument_length++);  //conta o tamanho do argumento
    char argument[argument_length];
    for (int k=0, j=index_line; k<argument_length; k++, j++) argument[k] = line[j];   //copia o argmento da query para um array que guarda esse argumento
    argument[argument_length] = '\0';

    int filename_size = strlen("../trabalho-pratico/Resultados/command1_output.txt");  //calcula o tamanho do nome do ficheiro
    if (n>=10) filename_size++;
    char *filename = (char *)malloc(filename_size + 1); //aloca memória dinamicamente para o nome do ficheiro
    snprintf(filename, filename_size + 1, "../trabalho-pratico/Resultados/command%d_output.txt", n);  //formata o nome do arquivo
    output = fopen(filename, "w");

    if (isdigit(line[index_line])){   //irá listar o resumo de um voo
        wanted_id = -1;
        for (int k=0; k<num_linhas[1]; k++){   //procura esse id de voo no array que tem os voos guardados
            if (strcmp(argument, flight_array[k].id)==0){
                wanted_id = k;  //encontrou o id desse voo
                break;
            }
        }
        if (wanted_id == -1);//não encontrou o id desse voo por isso tem de criar um ficheiro vazio 
            else {   //esse id de voo existe
                if (flight_array[wanted_id].validation==0); //esse voo é inválido por isso tem de criar um ficheiro vazio 
                else{
                    for (int k=0; strcmp(argument, contador_array[k].id_flight)==0; k++){
              //          wanted_id_2 = k+1;
                    }
                    if (index_line==2){   //1
              //        printf("existe\n");
                        //printf("%s\n", contador_array[3].id_flight);
                      fprintf(output, "%s;%s;%s;%s;%s;%s;%d\n", flight_array[wanted_id].airline, flight_array[wanted_id].plane_model, flight_array[wanted_id].origin, flight_array[wanted_id].destination, flight_array[wanted_id].schedule_departure_date, flight_array[wanted_id].schedule_arrival_date/*, contador_array[wanted_id_2].contador*/, delay(flight_array[wanted_id].schedule_departure_date, flight_array[wanted_id].real_departure_date));
                    }
                    else{   //1F
                //      printf("existe\n");
                        fprintf(output, "--- 1 ---\n");
                        fprintf(output, "airline: %s\n", flight_array[wanted_id].airline);
                        fprintf(output, "plane_model: %s\n", flight_array[wanted_id].plane_model);
                        fprintf(output, "origin: %s\n", flight_array[wanted_id].origin);
                        fprintf(output, "destination: %s\n", flight_array[wanted_id].destination);
                        fprintf(output, "schedule_departure_date: %s\n", flight_array[wanted_id].schedule_departure_date);
                        fprintf(output, "schedule_arrival_date: %s\n", flight_array[wanted_id].schedule_arrival_date);
                        //fprintf(output, "passengers: %d\n", flight_array[wanted_id_2].contador);
                        fprintf(output, "delay: %d\n", delay(flight_array[wanted_id].schedule_departure_date, flight_array[wanted_id].real_departure_date));
                    }
                }
            }
    }
    
    else if (line[index_line]=='B' && line[index_line+1]=='o' && line[index_line+2]=='o' && line[index_line+3]=='k'){  //irá listar o resumo de uma reserva
        wanted_id = -1;
        for (int k=0; k<num_linhas[2]; k++){   //procura esse id da reserva no array que tem as reservas guardados
            if (strcmp(argument, reservation_array[k].id)==0){
                wanted_id = k;  //encontrou o id dessa reserva
                break;
            }
        }
        if (wanted_id == -1);//não encontrou o id dessa reserva por isso tem de criar um ficheiro vazio 
            else {   //esse id de voo existe
                if (reservation_array[wanted_id].validation==0); //essa reserva é inválida por isso tem de criar um ficheiro vazio 
                else{
                    for (int k = 0; k<num_linhas[3]; k++){   //procura o id do utilizador que fez essa reserva para ver qual o seu account status
                        if (strcmp(reservation_array[wanted_id].user_id, user_array[k].id)==0){
                            wanted_user_id = k;  //encontrou o id desse utilizador
                            break;
                        }
                    }
                    if (verify_account_status(user_array[wanted_user_id].account_status) == 2); //não imprime nada caso a conta do utilizador esteja inativa
                        else{
                            if (index_line==2){   //1
                                fprintf(output, "%s;%s;%s;%s;%s;%s;%d;%.3f\n", reservation_array[wanted_id].hotel_id, reservation_array[wanted_id].hotel_name, reservation_array[wanted_id].hotel_stars, reservation_array[wanted_id].begin_date, reservation_array[wanted_id].end_date, reservation_array[wanted_id].includes_breakfast, nights(reservation_array[wanted_id].begin_date,reservation_array[wanted_id].end_date), total_price(reservation_array[wanted_id].price_per_night, nights(reservation_array[wanted_id].begin_date,reservation_array[wanted_id].end_date), reservation_array[wanted_id].city_tax));
                            }
                                else{   //1F
                                    fprintf(output, "--- 1 ---\n");
                                    fprintf(output, "hotel_id: %s\n", reservation_array[wanted_id].hotel_id);
                                    fprintf(output, "hotel_name: %s\n", reservation_array[wanted_id].hotel_name);
                                    fprintf(output, "hotel_stars: %s\n", reservation_array[wanted_id].hotel_stars);
                                    fprintf(output, "begin_date: %s\n", reservation_array[wanted_id].begin_date);
                                    fprintf(output, "end_date: %s\n", reservation_array[wanted_id].end_date);
                                    fprintf(output, "includes_breakfast: %s\n", reservation_array[wanted_id].includes_breakfast);
                                    fprintf(output, "nights: %d\n", nights(reservation_array[wanted_id].begin_date,reservation_array[wanted_id].end_date));
                                    fprintf(output, "total_price: %.3f\n", total_price(reservation_array[wanted_id].price_per_night, nights(reservation_array[wanted_id].begin_date,reservation_array[wanted_id].end_date), reservation_array[wanted_id].city_tax));
                                }
                        }
                }
            }
    }
    else{  //irá listar o resumo de um utilizador
        wanted_id = -1;
        for (int k=0; k<num_linhas[3]; k++){   //procura esse id do utilizador no array que tem os utilizadores guardados
            if (strcmp(argument, user_array[k].id)==0){
                wanted_id = k;  //encontrou o id desse utilizador
                break;
            }
        }
        if (wanted_id == -1);//não encontrou o id desse utilizador por isso tem de criar um ficheiro vazio  
            else{
                if (user_array[wanted_id].validation==0); //esse utilizador é inválido por isso tem de criar um ficheiro vazio 
                else{
                    if (verify_account_status(user_array[wanted_id].account_status) == 2);   //não imprime nada caso a conta do utilizador esteja inativa
                        else{
                            int flights = 0, reservations = 0;
                            double total_spent = 0;
                            for (int l = 0; l<num_linhas[0]; l++){   //procura o id do utilizador no array dos passageiros para ver em quantos voos ele andou 
                                if (strcmp(user_array[wanted_id].id, passenger_array[l].user_id)==0) flights++;
                            }
                            for (int k = 0; k<num_linhas[2]; k++){   //procura o id do utilizador no array das reservas para ver quantas reservas ele fez 
                                if (strcmp(user_array[wanted_id].id, reservation_array[k].user_id)==0){
                                    reservations++;
                                    total_spent += total_price(reservation_array[k].price_per_night, nights(reservation_array[k].begin_date,reservation_array[k].end_date), reservation_array[k].city_tax);
                                }
                            }
                            if (index_line==2){   //1
                                fprintf(output, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", user_array[wanted_id].name, user_array[wanted_id].sex, age_user(user_array[wanted_id].birth_date),user_array[wanted_id].country_code, user_array[wanted_id].passport, flights, reservations, total_spent);
                            }
                                else{   //1F
                                    fprintf(output, "--- 1 ---\n");
                                    fprintf(output, "name: %s\n", user_array[wanted_id].name);
                                    fprintf(output, "sex: %s\n", user_array[wanted_id].sex);
                                    fprintf(output, "age: %d\n", age_user(user_array[wanted_id].birth_date));
                                    fprintf(output, "country_code: %s\n", user_array[wanted_id].country_code);
                                    fprintf(output, "passport: %s\n", user_array[wanted_id].passport);
                                    fprintf(output, "number_of_flights: %d\n", flights);
                                    fprintf(output, "number_of_reservations: %d\n", reservations);
                                    fprintf(output, "total_spent: %.3f\n", total_spent);
                                }
                        }
                }
            }  
    }
    fclose(output);
    free(filename);
}

void identify_query(){
    char *line = NULL;
    size_t len = 0;
    int n = 0;
    input = fopen("../trabalho-pratico/dataset/input.txt", "r");
    if (input == NULL) {
        perror("Error\n");
        return;
    }
    while (getline(&line, &len, input) != -1) {
        int i = 0;
        n++;
        for (; line[i]!=' '; i++);
        if (i==3) continue;//10F
            else {
                switch (line[0]){
                    case '1':  //1 ou 1F ou 10
                        if (line[1]=='0') continue;//10
                        else query1(line, i, n);//1 ou 1F 
                    break;
                    case '2':  //2 ou 2F

                    break;
                    case '3':  //3 ou 3F

                    break;
                    case '4':  //4 ou 4F

                    break;
                    case '5':  //5 ou 5F

                    break;
                    case '6':  //6 ou 6F

                    break;
                    case '7':  //7 ou 7F

                    break;
                    case '8':  //8 ou 8F

                    break;
                    case '9':  //9 ou 9F

                    break;
                }
            }
    }
    free(line);
}