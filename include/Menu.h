//módulo do menu da aplicação
//módulo no qual é criado um menu exibido no terminal utilizando o ncurses;

#ifndef MENU_H
#define MENU_H

#define COR_FUNDO 8
#define COR_TEXTO 9        //letras azuis
#define COR_OPCAO 10
#define COR_TEXTO2 11     //letras vermelhas
#define COR_TEXTO3 12    //letras verdes
#define COR_TEXTO4 13    //letras amarelas
#define COR_TEXTO5 14
#define COR_TEXTO6 15

typedef struct {
  char* titulo;
  void (*acao)();
} opcao_menu;

void create_menu();

#endif