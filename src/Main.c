#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../include/Parser.h"
#include "../include/Queries.h"


int main() {
    open_files();
    create_files();
    identify_query();//função que faz as queries
    free_all();
    return 0;
}