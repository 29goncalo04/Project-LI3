#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
                        query2(line, i, n);
                    break;
                    case '3':  //3 ou 3F
                        query3(line, i, n);
                    break;
                    case '4':  //4 ou 4F
                        query4(line, i, n);

                    break;
                    case '5':  //5 ou 5F
                        query5(line, i, n);

                    break;
                    case '6':  //6 ou 6F
                        query6(line, i, n);
                    break;
                    case '7':  //7 ou 7F
                        query7(line, i, n);
                    break;
                    case '8':  //8 ou 8F

                    break;
                    case '9':  //9 ou 9F
                        query9(line, i, n);
                    break;
                }
            }
    }
    free(line);
    free(aux_queries);
    fclose(input);
}

int command_error = 0;  //se o comando é válido command_error = 0

void identify_single_query(char* command){
    int i = 0;
    for (; command[i]!=' '; i++);
    if (i==3);//10F
    else {
        if (i>3){
            command_error = 1;
            return;
        }
        switch (command[0]){
            case '1':  //1 ou 1F ou 10
                if (command[1]=='0');//10
                else query1(command, i, 0);//1 ou 1F 
            break;
            case '2':  //2 ou 2F
                query2(command, i, 0);
            break;
            case '3':  //3 ou 3F
                query3(command, i, 0);
            break;
            case '4':  //4 ou 4F
                query4(command, i, 0);
            break;
            case '5':  //5 ou 5F
                query5(command, i, 0);
            break;
            case '6':  //6 ou 6F
                query6(command, i, 0);
            break;
            case '7':  //7 ou 7F
                query7(command, i, 0);
            break;
            case '8':  //8 ou 8F
            break;
            case '9':  //9 ou 9F
                query9(command, i, 0);
            break;
            default:
                command_error = 1;
            break;
        }
    }
}