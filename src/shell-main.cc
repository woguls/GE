#include <common-util.h>
#include <shell/shell.h>

int main(int argc, char** argv){
    v8Shell sh;
    LOG("starting v8 shell");
    return sh._run_args(argc, argv);
}