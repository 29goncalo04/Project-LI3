#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/Performance.h"
#include "../include/Queries.h"
#include "../include/Interpreter.h"

FILE *input;  //ficheiro dos comandos das queries

void identify_query(char* path){
    char *line = NULL;
    size_t len = 0;
    int n = 0;
    char *aux_queries = strdup(path);
    input = fopen(aux_queries, "r");
    if (input == NULL) {
        perror("Error\n");
        return;
    }
    while (getline(&line, &len, input) != -1) {
        //printf("%s\n",line);
        //printf("identificando query\n");
        int i = 0;
        n++;
        for (; line[i]!=' '; i++);
        if (0 < i && i < 4) {// 1_   1F_  10F_
            switch (line[0]){
                case '1':  //1 ou 1F ou 10
                    if (line[1]=='0') continue;//10
                    else {
                        //printf("query 1 con n  = %d y argument = %s\n", n, line + i + 1);
                        if (line[1]== 'F') query1(line + i + 1, 1, n);//1F
                        if (line[1]== ' ') {
                            //printf("query1\n");
                            //printf("%s\n",line);
                            query1(line + i + 1, 0, n);//1
                        }
                    }
                break;
                case '2':  //2 ou 2F
                    if (line[1]== 'F') query2(line + i + 1, 1, n);//2F
                    else query2(line + i + 1, 0, n);//2
                break;
                case '3':  //3 ou 3F
                    if (line[1]== 'F') query3(line + i + 1, 1, n);//3F
                    else query3(line + i + 1, 0, n);//3
                break;
                // case '4':  //4 ou 4F
                //     query4(line, i, n);

                // break;
                // case '5':  //5 ou 5F
                //     query5(line, i, n);

                // break;
                // case '6':  //6 ou 6F
                //     query6(line, i, n);
                // break;
                // case '7':  //7 ou 7F
                //     query7(line, i, n);
                // break;
                case '8':  //8 ou 8F
                    if (line[1]== 'F') query8(line + i + 1, 1, n);//8F
                    else query8(line + i + 1, 0, n);//8
                break;
                // case '9':  //9 ou 9F
                //     query9(line, i, n);
                // break;
            }
        }
    }
    free(line);
    free(aux_queries);
    fclose(input);
}

void identify_query_tests_mode(char* path){
    struct timespec start, end;
    double elapsed_query1 = 0, elapsed_query2 = 0, elapsed_query3 = 0, elapsed_query4 = 0, elapsed_query5 = 0, elapsed_query6 = 0, elapsed_query7 = 0, elapsed_query8 = 0, elapsed_query9 = 0, elapsed_query10 = 0;
    char *line = NULL;
    size_t len = 0;
    int n = 0;
    char *aux_queries = strdup(path);
    input = fopen(aux_queries, "r");
    if (input == NULL) {
        perror("Error\n");
        return;
    }
    while (getline(&line, &len, input) != -1) {
        int i = 0;
        n++;
        for (; line[i]!=' '; i++);
        if (0 < i && i < 4) {// 1_   1F_  10F_
            switch (line[0]){
                case '1':  //1 ou 1F ou 10
                    if (line[1]=='0'){ //10 e 10F
                        start_time(&start);
                        //meter aqui a query 10
                        end_time(&end);
                        elapsed_query10 += calculate_time(start, end);
                        continue;
                    }
                    else {
                        if (line[1]== 'F'){ 
                            start_time(&start);
                            query1(line + i + 1, 1, n);//1F
                            end_time(&end);
                            elapsed_query1 += calculate_time(start, end);
                        }
                        if (line[1]== ' ') {
                            start_time(&start);
                            query1(line + i + 1, 0, n);//1
                            end_time(&end);
                            elapsed_query1 += calculate_time(start, end);
                        }
                    }
                break;
                case '2':  //2 ou 2F
                    if (line[1]== 'F'){
                        start_time(&start);
                        query2(line + i + 1, 1, n);//2F
                        end_time(&end);
                        elapsed_query2 += calculate_time(start, end);
                    }
                    else {
                        start_time(&start);
                        query2(line + i + 1, 0, n);//2
                        end_time(&end);
                        elapsed_query2 += calculate_time(start, end);
                    }
                break;
                case '3':  //3 ou 3F
                    if (line[1]== 'F'){
                        start_time(&start);
                        query3(line + i + 1, 1, n);//3F
                        end_time(&end);
                        elapsed_query3 += calculate_time(start, end);
                    }
                    else {
                        start_time(&start);
                        query3(line + i + 1, 0, n);//3F
                        end_time(&end);
                        elapsed_query3 += calculate_time(start, end);
                    }
                break;
                // case '4':  //4 ou 4F
                //     start_time(&start);
                //     query4(line, i, n);
                //     end_time(&end);
                //     elapsed_query4 += calculate_time(start, end);
                // break;
                // case '5':  //5 ou 5F
                //     start_time(&start);
                //     query5(line, i, n);
                //     end_time(&end);
                //     elapsed_query5 += calculate_time(start, end);
                // break;
                // case '6':  //6 ou 6F
                //     start_time(&start);
                //     query6(line, i, n);
                //     end_time(&end);
                //     elapsed_query6 += calculate_time(start, end);
                // break;
                // case '7':  //7 ou 7F
                //     start_time(&start);
                //     query7(line, i, n);
                //     end_time(&end);
                //     elapsed_query7 += calculate_time(start, end);
                // break;
                case '8':  //8 ou 8F
                    if (line[1]== 'F'){
                        start_time(&start);
                        query8(line + i + 1, 1, n);//8F
                        end_time(&end);
                        elapsed_query8 += calculate_time(start, end);
                    }
                    else {
                        start_time(&start);
                        query8(line + i + 1, 0, n);//8
                        end_time(&end);
                        elapsed_query8 += calculate_time(start, end);
                    }
                break;
                // case '9':  //9 ou 9F
                //     start_time(&start);
                //     query9(line, i, n);
                //     end_time(&end);
                //     elapsed_query9 += calculate_time(start, end);
                // break;
            }
        }
    }
    
    query1_time(elapsed_query1);
    query2_time(elapsed_query2);
    query3_time(elapsed_query3);
    // query4_time(elapsed_query4);
    // query5_time(elapsed_query5);
    // query6_time(elapsed_query6);
    // query7_time(elapsed_query7);
    query8_time(elapsed_query8);
    // query9_time(elapsed_query9);
    // query10_time(elapsed_query10);
    free(line);
    free(aux_queries);
    fclose(input);
}

int command_error = 0;  //se o comando é válido command_error = 0

void identify_single_query(char* line){
    int i = 0;
    for (; line[i]!=' '; i++);
    if (0 < i && i < 4) {// 1_   1F_  10F_
        switch (line[0]){
            case '1':  //1 ou 1F ou 10
                if (line[1]=='0');//10
                else {
                    //printf("query 1 con n  = %d y argument = %s\n", n, line + i + 1);
                    if (line[1]== 'F') query1(line + i + 1, 1, 0);//1F
                    if (line[1]== ' ') {
                        //printf("query1\n");
                        //printf("%s\n",line);
                        query1(line + i + 1, 0, 0);//1
                    }
                }
            break;
            case '2':  //2 ou 2F
                if (line[1]== 'F') query2(line + i + 1, 1, 0);//2F
                else query2(line + i + 1, 0, 0);//2
            break;
            case '3':  //3 ou 3F
                if (line[1]== 'F') query3(line + i + 1, 1, 0);//3F
                else query3(line + i + 1, 0, 0);//3
            break;
            // case '4':  //4 ou 4F
            //     query4(line, i, n);

            // break;
            // case '5':  //5 ou 5F
            //     query5(line, i, n);

            // break;
            // case '6':  //6 ou 6F
            //     query6(line, i, n);
            // break;
            // case '7':  //7 ou 7F
            //     query7(line, i, n);
            // break;
            case '8':  //8 ou 8F
                if (line[1]== 'F') query8(line + i + 1, 1, 0);//8F
                else query8(line + i + 1, 0, 0);//8
            break;
            // case '9':  //9 ou 9F
            //     query9(line, i, n);
            // break;
        }
    }
}