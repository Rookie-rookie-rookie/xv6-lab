#include "kernel/types.h"
#include "user.h"

int main(int argc,char* argv[]){
    if(argc != 2){
        write(2,"Usage:sleep time",strlen("Usage:sleep time"));
        exit(-1);
    }
    int n = atoi(argv[1]);
    sleep(n);
    write(1,"nothing happens for a little while\n",strlen("nothing happens for a little while"));
    exit(0);
}