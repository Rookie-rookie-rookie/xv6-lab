#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

void prime(int fd){
    int base;
    if(read(fd,&base,sizeof(int)) == 0){
        exit(0);
    }
    printf("prime %d\n",base);
    int p[2];
    pipe(p);
    if(fork()){
        close(p[0]);
        int n,end;
        do{
            end = read(fd,&n,sizeof(int));
            if(n % base != 0){
                write(p[1],&n,sizeof(int));
            }
        }while(end);
        close(p[1]);
    }else{
        close(p[1]);
        prime(p[0]);
    }
}

int main(int argc,char* argv[]){
    int fd[2];
    pipe(fd);
    if(fork()){
        close(fd[0]);
        for(int i=2;i<=35;i++){
            write(fd[1],&i,sizeof(int));
        }
        close(fd[1]);
    }else{
        close(fd[1]);
        prime(fd[0]);
    }
    wait(0);
    exit(0);
}