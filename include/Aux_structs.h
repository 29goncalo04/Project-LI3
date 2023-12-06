//módulo dos tipos e estruturas de dados auxiliares
//Tipos e estruturas de dados necessários para a representação e armazenamento de dados, respetivamente

#ifndef AUX_STRUCTS_H
#define AUX_STRUCTS_H

//#define DATE 20231001    /////////

typedef struct {       //struct com os id's dos voos de um passageiro
    char *flight_id;
} Flight_id_passenger;

typedef struct{     //struct com os pârametros do voo de um passageiro
    char *flight_id;
    char *schedule_departure_date;
    char *type;
} Flight_aux;

typedef struct{     //struct com os pârametros da reserva de um passageiro
    char *reservation_id;
    char *begin_date;
    char *type;
} Reservation_aux;

typedef struct {       //struct com os dados para a Query6
    char *origin;
    int passengers;
} PassengersXairport;

typedef struct {       //struct com os dados para a Query9
    char *id;
    char *name;
} idXname;

typedef struct {     //struct com os pârametros da reserva de um hotel para a Query4
    char *id;
    char *begin_date;
    char *end_date;
    char *user_id;
    char *rating;
    double total_price;
} hotel_aux;

typedef struct {     // struct com os parâmetros dos voos entre duas datas para a Query5
    char *id;
    char *schedule_departure_date;
    char *destination;
    char *airline;
    char *plane_model;
} flight_date_aux;

typedef struct{
    char *airport;
    int mediana;
} Mediana;

Flight_id_passenger create_flight_id(char *flight_id);

Flight_aux create_flight_aux(char *flight_id, char *schedule_departure_date, int exists_argument2);

Reservation_aux create_reservation_aux(char *reservation_id, char *begin_date, int exists_argument2);

PassengersXairport create_PassengersXairport(char* origin, int passengers);

idXname create_IdXname(char* id, char* name);

hotel_aux create_hotel_aux (char *id, char *begin_date, char *end_date, char *user_id, char *rating, double total_price);

flight_date_aux create_flight_date_aux (char *id, char *schedule_departure_date, char *destination, char *airline, char *plane_model);

Mediana create_mediana (char *airport, int mediana);

#endif 