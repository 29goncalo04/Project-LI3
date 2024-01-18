#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ncurses.h>

#include "../include/Pagination.h"
#include "../include/Menu.h"

void show_output(){
  FILE *output;
  output = fopen("../trabalho-pratico/Resultados/command0_output.txt", "r");
  int total_lines = 0;
  while (fgets((char[100]){0}, 100, output) != NULL) {
        total_lines++;
  }
  int number_of_pages = 0;
  if(total_lines%45 == 0) number_of_pages = total_lines/45;
  else number_of_pages = total_lines/45 + 1;
  clear();
  attron(COLOR_PAIR(COR_TEXTO));
  mvprintw(30, (COLS-56)/2,"To start press '1' + ENTER to see the first page of the output");
  mvprintw(48, (COLS-13)/2, "Pages available: %d", number_of_pages);
  attroff(COLOR_PAIR(COR_TEXTO));
  attron(COLOR_PAIR(COR_TEXTO3));
  mvprintw(45, (COLS-10)/2, "Your selection:");
  attroff(COLOR_PAIR(COR_TEXTO3));
  attron(COLOR_PAIR(COR_TEXTO2));
  mvprintw(50, (COLS-35)/2,"If you want to continue press 'q' + ENTER");
  attroff(COLOR_PAIR(COR_TEXTO2));
  refresh();
  noecho();
  while (1){
    int page[10] = {0}, i = 0, command_index = 0;
    char command[10], caractere;
    memset(command, 0, sizeof(command));
    move(48, (COLS+22)/2);
    refresh();
    while (1) {
        int c = getch();
        if (c == KEY_BACKSPACE || c == 127) {
            if (command_index > 0) {
                command[--command_index] = '\0';
                i--;
            }
        } else if (c == '\n') {
            page[i] = '\0';
            break;
        } else if (command_index < 9) {
            caractere = (char)c;
            command[command_index++] = caractere;
            page[i] = c-'0';
            i++;
        }
        move(45, (COLS+22)/2);
        clrtoeol();
        mvprintw(45, (COLS+22)/2, "%s", command);
        refresh();
    }
    if (page[0]+'0' == 'q' && page[1]=='\0') break;   //sai do ciclo caso o utilizador clique em 'q'
    int ch = 0;
    for (int j = 0, k = i-1; j<i; j++, k--){
      ch+=page[j]*pow((double)10, (double)k);
    }
    if ((ch)>0 && (ch)<=number_of_pages){
      clear();
      // Fecha e reabre o arquivo para reiniciar o cursor de leitura
      fclose(output);
      output = fopen("../trabalho-pratico/Resultados/command0_output.txt", "r");
      int start_line = (ch-1) * 45;
      int end_line = start_line + 45;
      size_t line_length = 0;
      char *line = NULL;
      for (int i = 0; i < end_line; ++i) {
        if (getline(&line, &line_length, output) != -1) {
          if (i >= start_line && i < end_line) printw("%s", line);
        }
        else break;
      }
      free(line);  // Libera a memória alocada por getline
      attron(COLOR_PAIR(COR_TEXTO3));
      mvprintw(45, (COLS-10)/2, "Your selection:");
      attroff(COLOR_PAIR(COR_TEXTO3));
      attron(COLOR_PAIR(COR_TEXTO2));
      mvprintw(46, (COLS-35)/2,"If you want to continue press 'q' + ENTER");
      attroff(COLOR_PAIR(COR_TEXTO2));
      attron(COLOR_PAIR(COR_TEXTO));
      mvprintw(48, (COLS+130)/2, "Current page: '%d'", ch);
      mvprintw(47, (COLS+130)/2, "Number of pages: '%d'", number_of_pages);
      attroff(COLOR_PAIR(COR_TEXTO));
      refresh();
    }
  }
  fclose(output);
}