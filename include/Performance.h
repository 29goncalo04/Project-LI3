//módulo do desempenho 
//módulo responsável por indicar o tempo que demora a aplicação e cada query, e indicar a memória utilizada pela aplicação

#ifndef PERFORMANCE_H
#define PERFORMANCE_H

void start_output_time ();
    //     |->função auxiliar como objetivo é criar o ficheiro vazio onde serão escritos os tempos de execução

void start_time(struct timespec *start);

void end_time(struct timespec *end);

float calculate_time(struct timespec start, struct timespec end);

void application_time(struct timespec start, struct timespec end);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a aplicação a ser executada

void memory_used();
    //     |->função que escreve no respetivo ficheiro a memória utilizada pelo programa

void query1_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 1 a ser executada

void query2_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 2 a ser executada

void query3_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 3 a ser executada

void query4_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 4 a ser executada

void query5_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 5 a ser executada

void query6_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 6 a ser executada

void query7_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 7 a ser executada

void query8_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 8 a ser executada

void query9_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 9 a ser executada

void query10_time (float time);
    //     |->função que escreve no respetivo ficheiro o tempo que demora a query 10 a ser executada

#endif