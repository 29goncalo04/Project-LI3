#include <locale.h>
#include <stdlib.h>
#include <curses.h>
#include "../include/Parser.h"
#include "../include/Interpreter.h"
#include "../include/Free.h"

#include "../include/Main.h"
#include "../include/Menu.h"

int main(int argc, char* argv[]) {
    setlocale(LC_COLLATE, "en_US.UTF-8");
    if (argc < 2) create_menu();
    else {
        open_files(argv[1]);
        identify_query(argv[2]);//função que faz as queries
        free_all();
    }
    exit(0);
    return 0;
}