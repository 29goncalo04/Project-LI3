#include <curses.h>
#include <string.h>
#include <unistd.h>

#include "../include/Menu.h"
#include "../include/Interpreter.h"
#include "../include/Pagination.h"
#include "../include/Interactive_mode_screens.h"

void after_output(){
  clear();
  attron(COLOR_PAIR(COR_TEXTO));
  mvprintw(30, (COLS-30)/2,"Do you want to write another command?");
  attroff(COLOR_PAIR(COR_TEXTO));
  mvprintw(34, (COLS-7)/2," --------\n");
  mvprintw(35, (COLS-7)/2,"|");
  attron(COLOR_PAIR(COR_TEXTO2));
  mvprintw(35, (COLS-5)/2,"1 -> Yes");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  mvprintw(36, (COLS-7)/2,"|");
  attron(COLOR_PAIR(COR_TEXTO2));
  mvprintw(36, (COLS-5)/2,"2 -> No ");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  mvprintw(37, (COLS-7)/2," --------\n");
  attron(COLOR_PAIR(COR_TEXTO2));
  mvprintw(50, (COLS-75)/2,"If you want to write another command, the old output will be replaced by the new one");
  attroff(COLOR_PAIR(COR_TEXTO2));
  refresh();
  int opcao_selecionada = getch();
  switch (opcao_selecionada) {
    case '1':
      start_query();
      return;
    case '2':   //volta para o menu inicial caso não queira fazer mais nada
      clear();
      attron(COLOR_PAIR(COR_TEXTO));
      mvprintw(30, (COLS-25)/2,"Returning to main menu...");
      attroff(COLOR_PAIR(COR_TEXTO));
      refresh();
      sleep(3);
      return;
    default:
      after_output();
  }
}

void output_type(){
  clear();
  attron(COLOR_PAIR(COR_TEXTO));
  mvprintw(30, (COLS-30)/2,"How do you want to see the output?");
  attroff(COLOR_PAIR(COR_TEXTO));
  mvprintw(34, (COLS-35)/2," ------------------------------------\n");
  mvprintw(35, (COLS-35)/2,"|");
  attron(COLOR_PAIR(COR_TEXTO2));
  mvprintw(35, (COLS-33)/2,"1 -> Generate only the output file  ");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  mvprintw(36, (COLS-35)/2,"|");
  attron(COLOR_PAIR(COR_TEXTO2));
  mvprintw(36, (COLS-33)/2,"2 -> Show the output in the terminal");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  mvprintw(37, (COLS-35)/2," ------------------------------------\n");
  refresh();
  int opcao_selecionada = getch();
  switch (opcao_selecionada) {
    case '1':
      clear();
      attron(COLOR_PAIR(COR_TEXTO));
      mvprintw(30, (COLS-70)/2,"Your output file is in the 'Results' folder with the name 'command0_output.txt'");
      attroff(COLOR_PAIR(COR_TEXTO));
      refresh();
      sleep(5);
      after_output();
      return;
    case '2':
      clear();
      show_output();
      after_output();
      return;
    default:
      output_type();
  }
}

void start_query(){
  clear();
  attron(COLOR_PAIR(COR_TEXTO));
  mvprintw(30, (COLS-98)/2,"Write a command to process a query, for example, ");
  attroff(COLOR_PAIR(COR_TEXTO));
  attron(COLOR_PAIR(COR_TEXTO2));
  mvprintw(30, (COLS-1)/2," 1F Book0000033110 ");
  attroff(COLOR_PAIR(COR_TEXTO2));
  attron(COLOR_PAIR(COR_TEXTO));
  mvprintw(30, (COLS+36)/2,"(press 'ENTER' when you finish):\n");
  attroff(COLOR_PAIR(COR_TEXTO));
  refresh();
  char query_command[100];
  memset(query_command, 0, sizeof(query_command)); // Inicializa a string
  int ch, command_index = 0;
  move(31, (COLS-17)/2);
  refresh();
  while ((ch = getch()) != '\n') {
    char caractere;
    if (ch == KEY_BACKSPACE || ch == 127) {
      // Trata o caso do backspace
      if (command_index > 0) {
        query_command[--command_index] = '\0';
      }
    }
    else if (command_index < 99) {  // Adiciona o caractere digitado à string
        caractere = (char)ch;
        query_command[command_index++] = caractere;
    }   // Limpa a linha e imprime o caminho atualizado
    move(31, (COLS-17)/2);
    clrtoeol();
    mvprintw(31, (COLS-17)/2, "%s", query_command);
    refresh();
  }
  identify_single_query(query_command);
  if(command_error==0){     //caso o comando seja válido (em princípio)
    FILE *output;
    output = fopen("../trabalho-pratico/Resultados/command0_output.txt", "r");
    fseek(output, 0, SEEK_END);
    if (ftell(output)==0){  //o ficheiro está vazio logo o comando é afinal inválido
      clear();
      attron(COLOR_PAIR(COR_TEXTO2));
      mvprintw(30, (COLS-20)/2,"Invalid command for query");
      attroff(COLOR_PAIR(COR_TEXTO2));
      refresh();
      sleep(3);
      command_error = 0;
      flushinp();
      start_query();
      return;
    }
    fclose(output);
    clear();
    attron(COLOR_PAIR(COR_TEXTO));
    mvprintw(30, (COLS-17)/2,"Command processed");
    attroff(COLOR_PAIR(COR_TEXTO));
    refresh();
    sleep(3);
    output_type();
    return;
  }
  else{
    clear();
    attron(COLOR_PAIR(COR_TEXTO2));
    mvprintw(30, (COLS-20)/2,"Invalid command for query");
    attroff(COLOR_PAIR(COR_TEXTO2));
    refresh();
    sleep(3);
    command_error = 0;
    flushinp();
    start_query();
  }
}