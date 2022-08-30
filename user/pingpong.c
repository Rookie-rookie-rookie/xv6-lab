#include "kernel/types.h"
#include "stddef.h"
#include "user.h"

int main(int argc,char* argv[]){
    int fd1[2],fd2[2];
    char buf[8];
    pipe(fd1);
    pipe(fd2);
    if(fork() != 0){
        write(fd1[1],"ping",strlen("ping"));
        wait(NULL);
        read(fd2[0],buf,4);
        printf("%d: received %s\n",getpid(),buf);
    }else{
        read(fd1[0],buf,4);
        printf("%d: received %s\n",getpid(),buf);
        write(fd2[1],"pong",strlen("pong"));
    }
    exit(0);
}