#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../include/Parser.h"
#include "../include/Queries.h"


int main(int argc, char* argv[]) {
    setlocale(LC_COLLATE, "en_US.UTF-8");
    open_files(argv[1]);
    create_files(argv[1]);
    identify_query(argv[2]);//função que faz as queries
    free_all();
    return 0;
}