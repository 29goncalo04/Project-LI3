//módulo da execução das interrogações
// módulo responsável por implementar a lógica das 
//interrogações, delegando responsabilidades aos respetivos catálogos conforme necessário

#ifndef QUERIES_H
#define QUERIES_H


typedef struct list_mediana {
    char *airport;
    int mediana;
}list_mediana;

typedef struct list_users {
    char *name;
    char *id;
}list_users;


void query1(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 1

void query2(char *line, int i, int n, int mode);   //mode==0 é interativo
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 2

void query3(char *line, int i, int n, int mode);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 3

void query4 (char *id, int flag, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 4

void query5 (char *str, int flag, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 5

void query6(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 6

void query7(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 7

void query8(char *line, int i, int n, int mode);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 8

void query9(char *line, int i, int n);
    //     |->função responsável por criar o output pedido sempre
    //        que o id da query for 9
void query10 (char *str, int flag, int n);

#endif