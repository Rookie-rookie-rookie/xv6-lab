#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char* path,char* target){ // almost rewrite from ls
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){   //can not open the path,error
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){         //can not get the state of the file
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if(st.type != T_DIR){           //the para "path" is not a path
        fprintf(2,"%s is not a directory!\n");
        exit(-1);
    }

    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){ //length of path too long
        printf("path too long\n");
        close(fd);
        exit(-1);
    }

    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)continue;
        if(!strcmp(de.name,".") || !strcmp(de.name,".."))continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf("cannot stat %s\n", buf);
            continue;
        }
        if(st.type == T_DIR){    //recurse find
            find(buf,target);
        }
        else if(st.type == T_FILE && !strcmp(de.name,target)){ // cmp the file and target
            printf("%s\n",buf);                                // this is what we looking for
        }
    }
}

int main(int argc,char* argv[]){
    if(argc < 3){
        fprintf(2,"usage: find dirName targetName");
        exit(-1);
    }
    find(argv[1],argv[2]);
    exit(0);
}