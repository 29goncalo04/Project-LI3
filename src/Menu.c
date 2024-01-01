#include <ncurses.h>
#include <string.h>

#include "../include/Menu.h"
#include "../include/Menu_options.h"
#include "../include/Interactive_mode_screens.h"

void create_menu(){
  initscr(); // Inicializa a biblioteca ncurses
  curs_set(0);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_BLACK);
  init_color(COLOR_YELLOW, 941, 902, 549);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK); 
  init_color(COLOR_RED, 800, 400,0 );
  init_pair(6, COLOR_RED, COLOR_BLACK);
  init_pair(7, COLOR_GREEN, COLOR_BLACK);
  init_pair(8, COLOR_WHITE, COLOR_WHITE);
  init_pair(9, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(COR_FUNDO, COLOR_BLACK, COLOR_WHITE);
  init_pair(COR_TEXTO, COLOR_BLUE, COLOR_BLACK);
  init_pair(COR_OPCAO, COLOR_BLACK, COLOR_RED);
  init_pair(COR_TEXTO2, COLOR_RED, COLOR_BLACK);
  init_pair(COR_TEXTO3, COLOR_GREEN, COLOR_BLACK);

    // cria as opções do menu
  opcao_menu opcoes[] = {
    {"Start", start_dataset},
    {"Help", ajuda},
    {"Credits", creditos},
    {"Leave", sair},
  };

  int opcao_atual = 0;        // variável que armazena a opção selecionada
  int programa_ativo = 1;         // variável para controlar o estado do programa
  int dataset_started = 0;   //variável para indicar se o dataset já foi processado

  // loop do menu
  while (programa_ativo) {
    clear();
    attron(COLOR_PAIR(COR_TEXTO3));  // Ativar a cor de fundo definida pelo par de cores especificado           
    mvprintw(2, (COLS-135)/2,"########     ###    ########    ###             ##     ##    ###    ##    ##    ###     ######   ######## ##     ## ######## ##    ## ########");
    mvprintw(3, (COLS-135)/2,"##     ##   ## ##      ##      ## ##            ###   ###   ## ##   ###   ##   ## ##   ##    ##  ##       ###   ### ##       ###   ##    ##");
    mvprintw(4, (COLS-135)/2,"##     ##  ##   ##     ##     ##   ##           #### ####  ##   ##  ####  ##  ##   ##  ##        ##       #### #### ##       ####  ##    ##");
    mvprintw(5, (COLS-135)/2,"##     ## ##     ##    ##    ##     ##          ## ### ## ##     ## ## ## ## ##     ## ##   #### ######   ## ### ## ######   ## ## ##    ##");
    mvprintw(6, (COLS-135)/2,"##     ## #########    ##    #########          ##     ## ######### ##  #### ######### ##    ##  ##       ##     ## ##       ##  ####    ##");
    mvprintw(7, (COLS-135)/2,"##     ## ##     ##    ##    ##     ##          ##     ## ##     ## ##   ### ##     ## ##    ##  ##       ##     ## ##       ##   ###    ##");
    mvprintw(8, (COLS-135)/2,"########  ##     ##    ##    ##     ##          ##     ## ##     ## ##    ## ##     ##  ######   ######## ##     ## ######## ##    ##    ##");
    mvprintw(10, (COLS-100)/2,"   ###    ########  ########  ##       ####  ######     ###    ######## ####  #######  ##    ## ");
    mvprintw(11, (COLS-100)/2,"  ## ##   ##     ## ##     ## ##        ##  ##    ##   ## ##      ##     ##  ##     ## ###   ## ");
    mvprintw(12, (COLS-100)/2," ##   ##  ##     ## ##     ## ##        ##  ##        ##   ##     ##     ##  ##     ## ####  ## ");
    mvprintw(13, (COLS-100)/2,"##     ## ########  ########  ##        ##  ##       ##     ##    ##     ##  ##     ## ## ## ## ");
    mvprintw(14, (COLS-100)/2,"######### ##        ##        ##        ##  ##       #########    ##     ##  ##     ## ##  #### ");
    mvprintw(15, (COLS-100)/2,"##     ## ##        ##        ##        ##  ##    ## ##     ##    ##     ##  ##     ## ##   ### ");
    mvprintw(16, (COLS-100)/2,"##     ## ##        ##        ######## ####  ######  ##     ##    ##    ####  #######  ##    ## ");
    attroff(COLOR_PAIR(COR_TEXTO3));
    printw("\n\n\n");

    // imprime as opções do menu
    for (int i=0; i<4; i++) {
      if (i==opcao_atual){
        attron(COLOR_PAIR(COR_TEXTO2));
        printw("* %s *", opcoes[i].titulo);
        attroff(COLOR_PAIR(COR_TEXTO2));
      } else {
        attron(COLOR_PAIR(COR_TEXTO));
        printw("  %s  ", opcoes[i].titulo);
        attroff(COLOR_PAIR(COR_TEXTO));
      }
      printw("\n");
    }

    // seleção do jogador
    int tecla = getch();
    switch (tecla) {
      case 65:    //Código ASCII para seta para cima
        opcao_atual--;
        if (opcao_atual < 0) {
          opcao_atual = 3;
        }
        break;
      case 66:     //Código ASCII para seta para baixo
        opcao_atual++;
        if (opcao_atual > 3) {
          opcao_atual = 0;
        }
        break;
      case '\n':   //seleciona a opção desejada
        if (strcmp(opcoes[opcao_atual].titulo, "Leave") == 0) programa_ativo = 0;  // Define o menu como inativo se a opção "Leave" for selecionada
        else if (strcmp(opcoes[opcao_atual].titulo, "Start") == 0 && dataset_started == 0){    //o dataset ainda não foi iniciado
          start_dataset();
          dataset_started = 1;
        }
        else if (strcmp(opcoes[opcao_atual].titulo, "Start") == 0 && dataset_started == 1){    //o dataset já foi iniciado anteriormente
          start_query();
        }
        else{
          opcoes[opcao_atual].acao();
        }
        break;
    }
  }
  endwin();
}