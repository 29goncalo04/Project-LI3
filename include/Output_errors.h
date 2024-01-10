//módulo de output dos dados
//módulo no qual é realizada a escrita dos dados para a respetiva saída (consola ou ficheiro)

#ifndef OUTPUT_ERRORS_H
#define OUTPUT_ERRORS_H

void start_files_passengers();

void complete_files_passengers(char parametros[][FIELD_SIZE]);
    //     |->função que cria os ficheiros com as linhas inválidas
    //        dos ficheiros de passageiros inicialmente recebidos

void start_files_flights();

void complete_files_flights(char parametros[][FIELD_SIZE]);
    //     |->função que cria os ficheiros com as linhas inválidas
    //        dos ficheiros de voos inicialmente recebidos

void start_files_reservations();

void complete_files_reservations(char parametros[][FIELD_SIZE]);
    //     |->função que cria os ficheiros com as linhas inválidas
    //        dos ficheiros de reservas inicialmente recebidos

void start_files_users();

void complete_files_users(char parametros[][FIELD_SIZE]);
    //     |->função que cria os ficheiros com as linhas inválidas
    //        dos ficheiros de utilizadores inicialmente recebidos

#endif