//módulo de output dos dados
//módulo no qual é realizada a escrita dos dados para a respetiva saída (consola ou ficheiro)

#ifndef OUTPUT_ERRORS_H
#define OUTPUT_ERRORS_H

void create_files_passengers();
    //     |->função que cria os ficheiros com as linhas inválidas
    //        dos ficheiros de passageiros inicialmente recebidos

void create_files_flights();
    //     |->função que cria os ficheiros com as linhas inválidas
    //        dos ficheiros de voos inicialmente recebidos

void create_files_reservations();
    //     |->função que cria os ficheiros com as linhas inválidas
    //        dos ficheiros de reservas inicialmente recebidos

void create_files_users();
    //     |->função que cria os ficheiros com as linhas inválidas
    //        dos ficheiros de utilizadores inicialmente recebidos

#endif