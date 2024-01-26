#include <string.h>
#include <ncurses.h>
#include <unistd.h>

#include "../include/Menu_options.h"
#include "../include/Menu.h"
#include "../include/Parser.h"
#include "../include/Interactive_mode_screens.h"

void start_dataset(){
    clear();
    attron(COLOR_PAIR(COR_TEXTO));
    mvprintw(30, (COLS-75)/2,"Write the dataset path, for example, ");
    attroff(COLOR_PAIR(COR_TEXTO));
    attron(COLOR_PAIR(COR_TEXTO2));
    mvprintw(30, (COLS-1)/2,"dataset/data/ ");
    attroff(COLOR_PAIR(COR_TEXTO2));
    attron(COLOR_PAIR(COR_TEXTO));
    mvprintw(30, (COLS+27)/2,"(press 'ENTER' when you finish):\n");
    attroff(COLOR_PAIR(COR_TEXTO));
    refresh();

    char dataset_path[100];
    memset(dataset_path, 0, sizeof(dataset_path)); // Inicializa a string
    int ch, path_index = 0;
    move(31, (COLS-17)/2);
    refresh();
    while ((ch = getch()) != '\n') {
      char caractere;
      if (ch == KEY_BACKSPACE || ch == 127) {
        // Trata o caso do backspace
        if (path_index > 0) {
          dataset_path[--path_index] = '\0';
        }
      }
      else if (path_index < 99) {  // Adiciona o caractere digitado à string
      caractere = (char)ch;
          dataset_path[path_index++] = caractere;
      }   // Limpa a linha e imprime o caminho atualizado
      move(31, (COLS-17)/2);
      clrtoeol();
      mvprintw(31, (COLS-17)/2, "%s", dataset_path);
      refresh();
    }
    open_files(dataset_path);  //se já fez a open_files no passado já não a vai deixar fazer outra vez
    if(path_error==0){
      clear();
      attron(COLOR_PAIR(COR_TEXTO));
      mvprintw(30, (COLS-17)/2,"Files processed");
      attroff(COLOR_PAIR(COR_TEXTO));
      refresh();
      sleep(3);
      start_query();
      return;
    }
    else{
      clear();
      attron(COLOR_PAIR(COR_TEXTO2));
      mvprintw(30, (COLS-20)/2,"Invalid path to dataset");
      attroff(COLOR_PAIR(COR_TEXTO2));
      refresh();
      sleep(3);
      path_error = 0;
      flushinp();
      start_dataset();
    }
}

// função que abre a tela de ajuda
void ajuda(){
  clear();
  attron(COLOR_PAIR(COR_TEXTO));
  printw("Help:\n\n\n");
  attroff(COLOR_PAIR(COR_TEXTO));
  printw(" ----------------------\n");
  printw("|1 -> ");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("Goal of the app  ");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  printw("|2 -> ");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("Back to main menu");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  printw(" ----------------------\n");
  refresh();
  int opcao_selecionada = getch();
  switch (opcao_selecionada) {
    case '1':
      while(1){
        clear();
        init_pair(COR_TEXTO3, COLOR_GREEN, COLOR_BLACK);
        init_pair(COR_TEXTO4, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(COR_TEXTO3));
        printw("Application instructions:\n\n\n\n");
        attroff(COLOR_PAIR(COR_TEXTO3));
        printw("    - When you click on ");
        attron(COLOR_PAIR(COR_TEXTO4));
        printw("start");
        attroff(COLOR_PAIR(COR_TEXTO4));
        printw(" the application will start;\n\n\n");
        printw("    - Then you will have to indicate the path to the dataset (there will be an example on the screen);\n\n\n");
        printw("    - Invalid data files will be created in the 'Resultados' folder and the files will be parsed so that the data contained in them can be accessed by queries;\n\n\n");
        printw("    - Then you will have to indicate a command to execute a query '<query number><(may or may not write 'F' and then the way the output is printed will be different)><arguments that the query asks for>';\n\n\n");
        printw("    - If the written command is invalid an empty file will be created;\n\n\n");
        printw("    - If the written command is valid, a screen will appear where you will have to choose whether you just want to create a file\n");
        printw("      with the output for that command or whether you also want to see the output in the terminal;\n\n\n");
        printw("    - If you want to see the output in the terminal, a screen will appear where you can see the number of pages available to view;\n\n\n");
        printw("    - If you indicate an invalid page, nothing will happen;\n\n\n");
        printw("    - If you click on the 'q' key you will go to the next screen;\n\n\n");
        printw("    - Don't forget that after writing the page you want, you will have to click the ENTER key at the end;\n\n\n");
        printw("    - At the end you will have to indicate whether you want to return to the initial menu or whether you want to write another command;\n");
        attron(COLOR_PAIR(COR_TEXTO2));
        printw("       | -> Don't forget that if you want to indicate another command, the old output will be replaced by the new generated output\n\n\n");
        attroff(COLOR_PAIR(COR_TEXTO2));
        printw("    - If you want to indicate another path to the dataset you will have to restart the program.\n\n\n");
        refresh();
        if (getch() != ERR) break;   //volta para o menu de ajuda mal alguma tecla seja pressionada
      }
      break;
    case '2':
      break;   //volta para o menu de ajuda quando a tecla 2 for pressionada
    default:   //caso uma tecla que não '1' ou '2' seja pressionada, nada acontece
      ajuda();
  }
}

// função que abre a tela de créditos
void creditos(){
  clear();
  attron(COLOR_PAIR(COR_TEXTO));
  printw("Credits:\n\n\n");
  attroff(COLOR_PAIR(COR_TEXTO));
  printw("This application was made by:\n");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("                            ->");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("Gonçalo Cruz (a104346)\n");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("                            ->");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("Gonçalo Cunha (a104003)\n");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("                            ->");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("Luis Freitas (a104000)\n\n\n\n\n\n");
  for (int k=0; k<(COLS-24)/2; k++) printw(" ");
  printw(" ------------------------\n");
  for (int k=(COLS-25)/2+25; k<COLS; k++) printw(" ");
  printw("|");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("1 -> Return to main menu");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  for (int k=0; k<(COLS-24)/2; k++) printw(" ");
  printw(" ------------------------\n");
  for (int k=(COLS-24)/2+24; k<COLS; k++) printw(" ");
  refresh();
  int opcao_selecionada = getch();
  switch (opcao_selecionada) {
    case '1':
      break;
    default:   //caso uma tecla que não '1' seja pressionada, nada acontece
      creditos();
  }
}

// função que indiretamente fecha o programa
void sair(){}