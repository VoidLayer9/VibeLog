#include "wrapper/imports/imports.dep_define.h"
#include <time.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    global_argv = newCArgvParse(argc, argv);
    global_appdeps.argv = &global_argv;
    return appmain(&global_appdeps);
}
