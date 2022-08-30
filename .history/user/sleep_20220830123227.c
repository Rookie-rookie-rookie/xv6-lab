#include "kernel/types.h"
#include "user.h"

int main(int argc,char* argv[]){
    int n = atoi(argv);
    sleep(n);
}