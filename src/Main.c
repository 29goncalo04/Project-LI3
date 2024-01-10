#include <locale.h>
#include <stdlib.h>
#include <curses.h>
#include <stdio.h>

#include "../include/Parser.h"
#include "../include/Interpreter.h"
#include "../include/Free.h"
#include "../include/Main.h"
#include "../include/Menu.h"
#include "../include/Tests.h"
#include "../include/Performance.h"

// int main(int argc, char* argv[]) {
//     if (argc < 3) perror("Error\n");
//     setlocale(LC_COLLATE, "en_US.UTF-8");
//     open_files(argv[1]);
//     //create_files(argv[1]);
//                 //create_files_flights();
//                 //create_files_users();

//     identify_query(argv[2]);//função que faz as queries
//     free_all();
//     printf("perfecto\n");
//     return 0;
// }

int main(int argc, char* argv[]) {
    system("clear");
    setlocale(LC_COLLATE, "en_US.UTF-8");
    if (argc == 1) create_menu();    //modo interativo
    else {
        if(argc == 3){   //modo batch
            open_files(argv[1]);
            identify_query(argv[2]);//função que faz as queries
            free_all();
        }
        else {    //programa de testes         ./programa-testes dataset/data/ dataset/input.txt dataset/outputs/
            struct timespec start, end;
            start_output_time();

            start_time(&start);
            open_files(argv[1]);
            identify_query_tests_mode(argv[2]);
            find_equal_files(argv[3]);
            free_all();

            end_time(&end);
            application_time(start, end);
            memory_used();
        }
    }
    printf("perfecto\n");
    exit(0);
    return 0;
}