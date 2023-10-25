#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../include/Parser.h"


int main() {
    open_files();
    create_files();
    //função que faz as queries
    free_all();
    return 0;
}