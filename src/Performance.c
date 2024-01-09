#include <stdio.h>
#include <time.h>
#include <sys/resource.h>

#include "../include/Performance.h"

void start_output_time (){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "w");
    fclose(Performance);
}

void start_time(struct timespec *start){
    clock_gettime(CLOCK_REALTIME, start);
}

void end_time(struct timespec *end){
    clock_gettime(CLOCK_REALTIME, end);
}

float calculate_time(struct timespec start, struct timespec end){
    return (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);
}

void application_time(struct timespec start, struct timespec end){
    float time = calculate_time(start, end);
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "\nApplication time: %.6f seconds\n", time);
    fclose(Performance);
}

void memory_used(){
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Memory usage: %ld KB\n", r_usage.ru_maxrss);
    fclose(Performance);
}

void query1_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 1 time: %.6f seconds\n", time);
    fclose(Performance);
}

void query2_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 2 time: %.6f seconds\n", time);
    fclose(Performance);
}

void query3_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 3 time: %.6f seconds\n", time);
    fclose(Performance);
}

void query4_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 4 time: %.6f seconds\n", time);
    fclose(Performance);
}

void query5_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 5 time: %.6f seconds\n", time);
    fclose(Performance);
}

void query6_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 6 time: %.6f seconds\n", time);
    fclose(Performance);
}

void query7_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 7 time: %.6f seconds\n", time);
    fclose(Performance);
}

void query8_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 8 time: %.6f seconds\n", time);
    fclose(Performance);
}

void query9_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 9 time: %.6f seconds\n", time);
    fclose(Performance);
}

void query10_time (float time){
    FILE *Performance = fopen("../trabalho-pratico/Resultados/Performance.csv", "a");
    fprintf(Performance, "Query 10 time: %.6f seconds\n", time);
    fclose(Performance);
}