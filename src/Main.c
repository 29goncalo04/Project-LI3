#include <locale.h>

#include "../include/Parser.h"
#include "../include/Interpreter.h"
#include "../include/Free.h"
#include "../include/Main.h"

int main(int argc, char* argv[]) {
    if (argc < 3) perror("Error\n");
    setlocale(LC_COLLATE, "en_US.UTF-8");
    open_files(argv[1]);
    create_files(argv[1]);
    identify_query(argv[2]);//função que faz as queries
    free_all();
    return 0;
}