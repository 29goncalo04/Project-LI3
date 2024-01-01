//módulo de interpretação dos comandos
//módulo responsável por ler o ficheiro de comandos, interpretar cada um, 
//e executar a respetiva query com os argumentos indicados (se existirem)

#ifndef INTERPRETER_H
#define INTERPRETER_H

extern int command_error;

void identify_query(char* path);
    //     |->função responsável por identificar
    //        o id da query que o comando do ficheiro de comandos chama

void identify_single_query(char* command);
    //     |->função responsável por identificar
    //        o id da query que o comando chama

#endif