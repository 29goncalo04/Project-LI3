#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/Data_Types_&_Data_Structures.h"
#include "../include/Parser.h"


int compare_date_time (char *i, char *f){     //i de evento inicial, f de evento final
    int tamanho = strlen(i);                    //1979/11/27      2016/09/10 17:34:41
    for (int k = 0; k<tamanho; k++){
        if (i[k]-f[k]>0) return 0;  //não é válido
        else if (i[k]-f[k]<0) return 1;   //é válido
    }
    if (tamanho>0) return 1;
    return 0;
}

int verify_email (char *e){    //<username>@<domain>.<TLD>
    int tamanho = strlen(e);   //alícsá-mendes@li3.pt
    if (tamanho<6) return 0;
    int i = 0, j = 0;
    while (e[i]!='@' && i<tamanho){
            i++;
            j++;                    
    }
    if (i==0 || i==tamanho) return 0; //é inválido
    j = 0;
    i++;
    while (e[i]!='.' && i<tamanho){
        i++;
        j++;
    }
    if (j==0 || i==tamanho) return 0; //é inválido
    j = 0;
    i++;
    while (i<tamanho){
        i++;
        j++;
    }
    if (j<2) return 0;
    return 1;
}


int verify_account_status(char *status){
    int tamanho = strlen(status), i = 0, result = 2;
    char *status2 = malloc(tamanho + 1); //o +1 é para guardar o '\0'
    while (i<tamanho){
        status2[i] = tolower(status[i]);
        i++;
    }
    status2[i] = '\0';
    if (strcmp (status2, "active")==0) result = 1;
    else if (strcmp (status2, "inactive")==0) result = 2;
    else result = 0;
    free(status2);
    return result;
}

int verify_airport (char *airport){     //função para verificar se um aeroporto é válido
    int tamanho = strlen(airport);
    if (tamanho!=3) return 0;   //é inválido
    return 1;
}

void toLowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

void toUpperCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int verify_breakfast(char *breakfast){
    int result;
    if (breakfast[0] != ' ') toLowerCase(breakfast);
    if (strcmp (breakfast, "t")==0 || strcmp (breakfast, "true")==0 || strcmp (breakfast, "1")==0) result = 1;    //parâmetro válido
    else {
        if (strcmp (breakfast, "f")==0 || strcmp (breakfast, "false")==0 || strcmp (breakfast, "0")==0 || strcmp (breakfast, " ")==0) result = 2;
        else result = 0;  //caso em que é inválido
    }
    return result; 
}

int verify_country_code (char *c) { 
    if (strlen (c)!=2) return 0; // se o comprimento do country_code for diferente de 2, é inválido
    int i;
    for (i=0; i<2; i++) {
        if ((c[i]>=97 && c[i]<=122) || (c[i]>=65 && c[i]<=90)) continue; // se for uma letra (maiúscula ou minúscula), continua a analisar
        else return 0; // se não for uma letra é inválido
    }
    return 1;
}


int count_passengers (Contador_id *contador_array, int num_linhas_contador, char parametros[][FIELD_SIZE]){
    for (int i = 0; i<num_linhas_contador; i++){
        if (strcmp(parametros[0],contador_array[i].id_flight)==0) return contador_array[i].contador;
    }
    return 0;
}



int compare_seats_passengers (char *seats, int num_passengers) {
    int comp_s = strlen(seats);
    for (int i = 0; i<comp_s; i++){
        if (seats[i]<48 || seats[i]>57) return 0;
    }
    int num_seats = atoi(seats);                   //passou uma string de números para o respetivo número inteiro
    if (num_seats>=num_passengers) return 1;
    else return 0;
}


int verify_hotel_stars (char *s) {
    if (strlen (s)!=1) return 0; // se s tiver mais do que um caracter/algarismo, não é válido
    if (s[0]<49 || s[0]>53) return 0; // se s não estiver entre 1 (código ASCII 49) e 5 (código ASCII 53) não é válido
    return 1;
}


int verify_city_tax (char *t) { // considerando que todos os caracteres de t são números ou '.'
    for (int i=0; t[i]; i++) {
        if (t[i]==46 || t[i]==45) return 0; // se o 'algarismo' na posição i for um '.' ou '-', t é inválido
    }
    return 1;
}

char* strnCpy(char *d, char *s, int n, int p) {
  for (int i = 0; i < n; i++, p++) {
    d[i] = s[p];
    if (s[p] == '\0') {
      break;
    }
  }
  d[n] = '\0';
  return d;
}

int check_date(char *d) { // 2023/12/31 ADICIONAR CASO DE NEGAR DIA: 00 MES: 00 ANO: 0000 nnnn/nn/nn
  int check = 0, i, l = strlen(d);
  if (10 == l) {

    for (i = 0; i < 4; i++) { // xxxx ano Verificamos o ano  
      if (d[i] < '0' || '9' < d[i]) return check; // 48 = 0 e 57 = 9
    }

    if (d[i] != '/') return check;
    else i++; //xx mês Verificamos o mês

    if (d[i] < '0' || '1' < d[i]) return check; // os meses vão de 01-12
    else {
      if (d[i] == '1') { // só é válido: 10, 11 0 12
        if (d[i+1] < '0' || '2' < d[i+1]) return check;  // só é válido: 10, 11 0 12
      }
      else {
        if (d[i+1] < '1' || '9' < d[i+1]) return check;
      }
    }

    i += 2;
    if (d[i] != '/') return check;
    else i++; //xx dias Verificamos o dia

    if (d[i] < '0' || '3' < d[i]) return check; // os dias vão de 01-31 
    else {
      if (d[i] == '3') {
        if (d[i+1] < '0' || '1' < d[i+1]) return check;
      }    
      else {
        if (d[i] == '0') {
          if (d[i+1] < '1' || '9' < d[i+1]) return check;
        }
        else if (d[i+1] < '0' || '9' < d[i+1]) return check;
      }  
    }

    check = 1;
  }
  return check;
}

int check_time(char *t) {
  int i = 0, check = 0;
  for (i = 0; i < 2; i++) {
    if (i == 0) {
      if (t[i] < '0' || '2' < t[i]) return check;
      else {
        if (t[i] == '2') {
          if (t[i+1] < '0' || '3' < t[i+1]) return check;
        }
      }
    }
    else {
      if (t[i] < '0' || '9' < t[i]) return check;
    }
  }

  if (t[2] != ':') return check;

  for (i = 3; i < 5; i++) {
    if (i == 3) {
      if (t[i] < '0' || '5' < t[i]) return check;
    }
    else {
      if (t[i] < '0' || '9' < t[i]) return check;
    }
  }

  if (t[5] != ':') return check;

  for (i = 6; i < 8; i++) {
    if (i == 3) {
      if (t[i] < '0' || '5' < t[i]) return check;
    }
    else {
      if (t[i] < '0' || '9' < t[i]) return check;
    }
  }

  check = 1;
  return check;
}

int check_dateWtime(char *dateT) {
  int check = 0;
  char date[11], time[9];
  if (strlen(dateT) != 19) return check; 
  strnCpy(date, dateT, 10, 0);
  if (check_date(date) == 0) return check;
  if (dateT[10] != ' ') return check;
  strnCpy(time, dateT, 8, 11);
  if (check_time(time) == 0) return check;
  check = 1;
  return check;
}

int check_price_per_night(char *p) {
  int i = 0, check = 0;
  for (; p[i] != '\0'; i++) {
    if (p[i] < '0' || '9' < p[i]) return check;
  }
  check = 1;
  return check;
}

int check_reserva_rating(char *r) {
  int i = 0, check = 0;
  if (strlen(r) == 1) {
      if (r[i] < '1' || '5' < r[i]) return check;
      check = 1;
      return check;
  }
  return check;
}

int check_length(char *s) {
  if (0 < strlen(s)) return 1;
  else return 0;
}